sudo env "PATH=$PATH" \
	gotty -p 1337 -w \
	docker run -it \
	--read-only -v ./wargames:/root/wargames \
	-w /root/wargames \
	--rm wargames:nogpt \
	/root/wargames/dialer
