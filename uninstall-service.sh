#!/bin/bash
#
# uninstall-service.sh — stop, disable, and remove the WOPR web console service.
#
# Usage:  sudo ./uninstall-service.sh
#   Override the name if you installed under a different one:
#   SERVICE_NAME=wopr-web ./uninstall-service.sh
set -euo pipefail

SERVICE_NAME="${SERVICE_NAME:-wopr-web}"
CONTAINER_NAME="${CONTAINER_NAME:-$SERVICE_NAME}"
UNIT_PATH="/etc/systemd/system/${SERVICE_NAME}.service"

systemctl disable --now "$SERVICE_NAME" 2>/dev/null || true
docker rm -f "$CONTAINER_NAME" 2>/dev/null || true
rm -f "$UNIT_PATH"
systemctl daemon-reload
systemctl reset-failed "$SERVICE_NAME" 2>/dev/null || true

echo "Removed $SERVICE_NAME (unit, container, boot entry)."
