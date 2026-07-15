#!/bin/bash
#
# install-service.sh — install the WOPR web console (gotty + docker) as a
# systemd service that restarts on crash and starts on boot.
#
# Usage:   sudo ./install-service.sh
#   or, as root:  ./install-service.sh
#
# Override defaults with env vars, e.g.:
#   PORT=8080 IMAGE=wargames:shellgpt ./install-service.sh
#
# This is the reproducible version of the one-off commands we ran by hand:
# it detects the gotty/docker paths and the invoking user, writes the unit,
# then enables + starts it. Safe to re-run to update the unit.
#
# The spawned game container is locked down: no network, dropped Linux caps,
# no-new-privileges, runs as "nobody", read-only rootfs + code mount, and
# pid/memory/cpu caps. This is safe because wopr does no file I/O — if you
# point this at a game that writes files (dialer/school), you'll need a
# writable data volume and probably a real user, so revisit these flags.
set -euo pipefail

# --- tunables (override via environment) ---
SERVICE_NAME="${SERVICE_NAME:-wopr-web}"
PORT="${PORT:-1337}"
# Interface gotty binds to. Default 0.0.0.0 (reachable directly). If you put a
# TLS reverse proxy (see Caddyfile) in front, set ADDRESS=127.0.0.1 so the
# plaintext port is only reachable over the loopback.
ADDRESS="${ADDRESS:-0.0.0.0}"
IMAGE="${IMAGE:-wargames:nogpt}"
TITLE="${TITLE:-joshua@WOPR}"
# gotty --ws-origin is a REGEX matched against the WebSocket Origin header,
# not a hostname. This default accepts both wopr.* and joshua.* on falken.org.
# (Dots left unescaped on purpose: systemd mangles backslashes in ExecStart,
# and an unescaped '.' still matches the literal dot here.)
WS_ORIGIN="${WS_ORIGIN:-(wopr|joshua).falken.org}"

# --- figure out who the service should run as ---
# When invoked via sudo, run the service as the user who called sudo (so it
# uses that user's Docker access and ~/go/bin), not root — unless root is the
# real owner (e.g. this box).
RUN_USER="${SUDO_USER:-$(whoami)}"
RUN_HOME="$(eval echo "~$RUN_USER")"

# --- locate binaries ---
DOCKER_BIN="$(command -v docker || true)"
GOTTY_BIN="$(command -v gotty || true)"
if [ -z "$GOTTY_BIN" ]; then
  for p in "$RUN_HOME/go/bin/gotty" /root/go/bin/gotty /usr/local/bin/gotty; do
    [ -x "$p" ] && GOTTY_BIN="$p" && break
  done
fi
[ -z "$GOTTY_BIN" ] && GOTTY_BIN="$(find "$RUN_HOME" /root -maxdepth 4 -name gotty -type f 2>/dev/null | head -n1)"

# --- sanity checks: refuse to write a broken unit ---
if [ ! -x "$GOTTY_BIN" ]; then
  echo "ERROR: gotty not found. Install it (go install github.com/sorenisanerd/gotty@latest)" >&2
  echo "       or set GOTTY_BIN and re-run." >&2
  exit 1
fi
if [ ! -x "$DOCKER_BIN" ]; then
  echo "ERROR: docker not found in PATH." >&2
  exit 1
fi
if [ "$RUN_USER" != "root" ] && ! id -nG "$RUN_USER" | tr ' ' '\n' | grep -qx docker; then
  echo "WARNING: user '$RUN_USER' is not in the 'docker' group; the service may fail." >&2
  echo "         Fix with: sudo usermod -aG docker $RUN_USER   (then log out/in)" >&2
fi

UNIT_PATH="/etc/systemd/system/${SERVICE_NAME}.service"
echo "Installing $UNIT_PATH"
echo "  user=$RUN_USER home=$RUN_HOME gotty=$GOTTY_BIN docker=$DOCKER_BIN address=$ADDRESS port=$PORT image=$IMAGE"

# --- write the unit ---
tee "$UNIT_PATH" >/dev/null <<EOF
[Unit]
Description=WOPR web console (gotty + docker)
Documentation=https://github.com/beauwoods/wargames
After=network-online.target docker.service
Requires=docker.service
Wants=network-online.target

[Service]
Type=simple
User=$RUN_USER
Environment=HOME=$RUN_HOME

ExecStart=$GOTTY_BIN \\
    -p $PORT \\
    -a $ADDRESS \\
    --title-format $TITLE \\
    --ws-origin $WS_ORIGIN \\
    --close-timeout 1 \\
    -w \\
    $DOCKER_BIN run -it \\
        --network none \\
        --pids-limit=128 --memory=96m --memory-swap=96m --cpus=0.5 \\
        --read-only --tmpfs /tmp:size=8m \\
        --cap-drop=ALL --security-opt no-new-privileges \\
        --user 65534:65534 \\
        -v $RUN_HOME/wargames:/wargames:ro -w /wargames \\
        --rm $IMAGE \\
        /wargames/wopr

# Crash handling: always restart, with a short backoff.
Restart=always
RestartSec=2

[Install]
WantedBy=multi-user.target
EOF

systemctl daemon-reload
systemctl enable --now "$SERVICE_NAME"
sleep 2
systemctl status "$SERVICE_NAME" --no-pager || true

echo
echo "Done. Logs:      journalctl -u $SERVICE_NAME -f"
echo "     Restart:   sudo systemctl restart $SERVICE_NAME"
echo "     Remove:    sudo ./uninstall-service.sh"
