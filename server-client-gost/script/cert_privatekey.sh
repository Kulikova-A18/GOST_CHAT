#!/bin/sh

# delete old
echo delete old /etc/ssl/private/server_gost_privateKey.pem ...
rm /etc/ssl/private/server_gost_privateKey.pem
echo ok

echo delete old /etc/ssl/certs/server_gost_ca.pem ...
rm /etc/ssl/certs/server_gost_ca.pem
echo ok

# creating a certificate and private key 
echo creating /etc/ssl/certs/server_gost_ca.pem ...
openssl genrsa -out /etc/ssl/private/server_gost_privateKey.pem 4096
echo ok

echo creating /etc/ssl/certs/server_gost_ca.pem ...
openssl req -new -x509 -nodes -days 3600 -key /etc/ssl/private/server_gost_privateKey.pem -out /etc/ssl/certs/server_gost_ca.pem -subj "/C=RU/ST=Krasnoyarsk/O=SFU Inc./OU=SFU Certificate Authority/CN=SFU Intermediate Clients CA"
echo ok
