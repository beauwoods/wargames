#!/bin/bash


#install dependencies
sudo apt install git

#uncomment below if you only want to run locally
#sudo apt install espeak
#echo you are running Python Version
#python --version
#sudo apt install python3-pip
#pip install shell-gpt

#comment below if you only want to run locally
sudo apt install docker

#install web console, gotty
#comment below if you don't want to publish to the web
sudo apt install gotty

#install shell-gpt WOPR role
#uncomment below to run locally and with shell gpt
#cp C/src/WOPR.json ~/.config/shell_gpt/roles

#build the appropriate docker image
#commment below if you only want to run locally
sudo docker build -t wargames:nogpt - < Dockerfile-nogpt
sudo docker build -t wargames:shellgpt - < Dockerfile-shellgpt

#compile and install C code
gcc C/src/imsai8080.c -o ./imsai8080
gcc C/src/school.c -o ./school
gcc C/src/dialer.c -o ./dialer
gcc C/src/pan-am.c -o ./pan-am
gcc C/src/bank.c -o ./bank
gcc C/src/wopr.c -o ./wopr

#install data files
cp C/src/*.txt ./

echo install complete






