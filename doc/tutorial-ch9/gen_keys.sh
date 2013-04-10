#!/bin/sh

if [ ! -f ssl_key.pem ]
then
	openssl genrsa -out ssl_key.pem 1024
fi

if [ ! -f ssl_cert.pem ]
then
	openssl req -days 365 -out ssl_cert.pem -new -x509 -key ssl_key.pem
fi

