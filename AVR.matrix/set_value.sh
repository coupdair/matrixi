#!/bin/bash

value=1
value=$1

sed 's/VALUE=123/VALUE='$value'/' Makefile.TEMPLATE > Makefile
make clean
make
make upload
cp -p Makefile.TEMPLATE Makefile

