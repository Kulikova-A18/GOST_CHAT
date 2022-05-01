#!/bin/sh

# create key and pem
sh cert_privatekey.sh

cd .. && mkdir build && cd build
cmake ..
make

mkdir data
echo "" > client.json