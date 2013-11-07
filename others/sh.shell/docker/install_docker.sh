#!/bin/bash
sudo sh -c "wget -qO- https://get.docker.io/gpg | apt-key add -"
sudo sh -c "echo deb http://git.docker.io/ubuntu docker main/"
sudo apt-get update
sudo apt-get install lxc-docker
sudo docker run -i -t ubuntu /bin/bash 
