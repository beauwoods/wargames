# joshua

This repo is a lightly modified version of the quite excellent [Wargames Simulator by zompiexx](https://github.com/zompiexx/wargames/tree/9574b6a63c4f9f3df18da44355deb2aec1326efe) (which is still being actively built and updated, so will differ significantly), done in a hurry for **[DEF CON 31](https://defcon.org/html/defcon-31/dc-31-index.html)**. The following adaptations were made to original code (going from memory here):

* Added support to run this in Docker, to isolate each environment/install for security.
* Create custom Docker containers with minimal installed packages to reduce size, memory, processor, and attack surface.
* Installed the webconsole [gotty](https://github.com/yudai/gotty) and added scripts (`web-wopr.sh` and `web-dialer.sh`) to publish via the web.
* Added a script (`term-dialer.sh`) to publish the dialer via telnet.
* Stripped out the audio, since it kept throwing console errors when published to telnet and web (though it would be fantastic if that worked).
* Added an extra "game" that directed people who found it to a private event.
* Updated WOPR.json to attempt to get people to the private event (though ended up scrapping the Script-GPT component).

## Running the web console as a service (Linux / systemd)

`web-wopr.sh` is fine for running by hand, but for an unattended box you want it
to restart on crash and start on boot. `install-service.sh` wraps the same
gotty + Docker command in a systemd unit:

```bash
sudo ./install-service.sh
```

It auto-detects the `gotty` and `docker` paths and the invoking user, writes
`/etc/systemd/system/wopr-web.service`, then enables and starts it. Override
defaults with environment variables if needed:

```bash
PORT=8080 IMAGE=wargames:shellgpt sudo ./install-service.sh
```

Manage it with the usual systemd commands:

```bash
systemctl status wopr-web        # is it running?
journalctl -u wopr-web -f        # live logs
sudo systemctl restart wopr-web  # bounce it
sudo ./uninstall-service.sh      # stop, disable, and remove
```

Note: don't run `web-wopr.sh` by hand while the service is up — both bind port
1337, and the second one to start dies with `address already in use`.

### Serving multiple hostnames

gotty binds to `0.0.0.0`, so it already answers to any hostname that resolves
to the box — point the DNS A records where you want. The only per-hostname gate
is `--ws-origin`, a regex matched against the WebSocket Origin header. The
default (`(wopr|joshua).falken.org`) accepts both `wopr.` and `joshua.`; widen
it with `WS_ORIGIN='...'` when installing to accept other names.

### HTTPS on port 1337 (nothing else exposed)

The deployed setup serves HTTPS on **1337 only**, with 80 and 443 closed, using
[Caddy](https://caddyserver.com) as a reverse proxy in front of gotty. Caddy
fetches and auto-renews Let's Encrypt certs and proxies gotty's WebSocket
transparently. See the included `Caddyfile`.

Because 80/443 are closed, the usual HTTP/TLS-ALPN ACME challenges can't run, so
certs are issued via the **DNS-01 challenge**. This example uses Cloudflare DNS.

1. Install the service with gotty on an internal loopback port (Caddy takes the
   public 1337):

   ```bash
   ADDRESS=127.0.0.1 PORT=1338 sudo ./install-service.sh
   ```

2. Give Caddy the Cloudflare DNS plugin (the apt build lacks it) and a scoped
   API token (Cloudflare → *Zone → DNS → Edit* for your zone):

   ```bash
   sudo caddy add-package github.com/caddy-dns/cloudflare
   echo 'CF_API_TOKEN=your-token-here' | sudo tee /etc/caddy/cloudflare.env
   sudo chmod 600 /etc/caddy/cloudflare.env
   sudo mkdir -p /etc/systemd/system/caddy.service.d
   printf '[Service]\nEnvironmentFile=/etc/caddy/cloudflare.env\n' | \
     sudo tee /etc/systemd/system/caddy.service.d/cloudflare.conf
   sudo systemctl daemon-reload
   ```

3. Install the Caddyfile and start Caddy:

   ```bash
   sudo cp Caddyfile /etc/caddy/Caddyfile   # edit the hostnames first
   sudo systemctl restart caddy
   ```

DNS A records for each hostname must point at the box and be set to **"DNS only"
(grey cloud)** in Cloudflare — its proxy does not forward port 1337. The console
is then at `https://<host>:1337`, served over `wss://` automatically.
