sudo docker run -d \
	--read-only -v $HOME/wargames:/root/wargames \
	-w /root/wargames \
	--restart unless-stopped \
	-p 31337:31337 \
	wargames:nogpt \
	/root/wargames/dialer_start.sh
