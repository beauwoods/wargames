sudo env "PATH=$PATH:$HOME/go/bin" \
	gotty \
	-p 1337 \
	--title-format joshua@WOPR \
	--ws-origin joshua.falken.org \
	--close-timeout 1 \
	-w \
	\
	docker run -it \
	-v ~/wargames:/root/wargames \
	-v ~/.config/shell_gpt:/root/.config/shell_gpt \
	-w /root/wargames \
	--rm wargames:nogpt \
	/root/wargames/wopr
