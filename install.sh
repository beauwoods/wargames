#!/bin/bash


## install dependencies
sudo apt install git -y

## uncomment below if you only want to run locally
#sudo apt install espeak
#echo you are running Python Version
#python --version
#sudo apt install python3-pip
#pip install shell-gpt

## comment below if you only want to run locally
sudo apt install ca-certificates curl gnupg -y
sudo install -m 0755 -d /etc/apt/keyrings
curl -fsSL https://download.docker.com/linux/ubuntu/gpg | sudo gpg --dearmor -o /etc/apt/keyrings/docker.gpg
sudo chmod a+r /etc/apt/keyrings/docker.gpg
echo \
  "deb [arch="$(dpkg --print-architecture)" signed-by=/etc/apt/keyrings/docker.gpg] https://download.docker.com/linux/ubuntu \
  "$(. /etc/os-release && echo "$VERSION_CODENAME")" stable" | \
  sudo tee /etc/apt/sources.list.d/docker.list > /dev/null
sudo apt update
sudo apt install docker-ce docker-ce-cli containerd.io docker-buildx-plugin docker-compose-plugin -y

## install web console, gotty, through Golang
## comment below if you don't want to publish to the web
sudo apt install golang-go -y
go install github.com/sorenisanerd/gotty@latest

## Clone the github repo
git clone https://github.com/beauwoods/wargames.git

## Change into the `wargames` directory
cd wargames

## Change into a different branch of the github code, if necessary
git checkout defcon31

## install shell-gpt WOPR role
## uncomment below to run locally and with shell gpt
#cp C/src/WOPR.json ~/.config/shell_gpt/roles

## build the appropriate docker image
## commment below if you only want to run locally
sudo docker build -t wargames:nogpt - < Dockerfile-nogpt
sudo docker build -t wargames:shellgpt - < Dockerfile-shellgpt

## compile and install C code
## First ensure the ncurses library is installed
sudo apt install libncurses-dev
gcc C/src/imsai8080.c -o ./imsai8080
gcc C/src/school.c -o ./school
gcc C/src/dialer.c -o ./dialer
gcc C/src/pan-am.c -o ./pan-am
gcc C/src/bank.c -o ./bank
gcc C/src/wopr.c -o ./wopr

## install data files
cp C/src/*.txt ./

echo install complete






