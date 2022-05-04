#!/bin/sh

# create key and pem
#sh cert_privatekey.sh

cd .. && rm -Rfv build

mkdir build && chmod 777 build && cd build

#cmake .. -DOPENSSL_ROOT_DIR=/opt/TLSGate -DOPENSSL_LIBRARIES=/opt/TLSGate/lib && make

cmake .. && make

mkdir data
echo "" > client.json

chmod 777 .
