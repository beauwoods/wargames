# joshua

This repo is a lightly modified version of the quite excellent [Wargames Simulator by zompiexx](https://github.com/zompiexx/wargames/tree/9574b6a63c4f9f3df18da44355deb2aec1326efe) (which is still being actively built and updated, so will differ significantly), done in a hurry for **[DEF CON 31](https://defcon.org/html/defcon-31/dc-31-index.html)**. The following adaptations were made to original code (going from memory here):

* Added support to run this in Docker, to isolate each environment/install for security.
* Create custom Docker containers with minimal installed packages to reduce size, memory, processor, and attack surface.
* Installed the webconsole [gotty](https://github.com/yudai/gotty) and added scripts (`web-wopr.sh` and `web-dialer.sh`) to publish via the web.
* Added a script (`term-dialer.sh`) to publish the dialer via telnet.
* Stripped out the audio, since it kept throwing console errors when published to telnet and web (though it would be fantastic if that worked).
* Added an extra "game" that directed people who found it to a private event.
* Updated WOPR.json to attempt to get people to the private event (though ended up scrapping the Script-GPT component).
