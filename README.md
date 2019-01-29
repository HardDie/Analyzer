## Info
Application for capture incoming UDP packets from specified interface

**Libs:**
* pcap : for capture packets from raw socket
* json-c : for ubus and assemble messages
* libubox : for ubus some blob works
* ubus : tools server and listener, API for sending messages

## Build:
make

## Start ubus server:
./libs/ubus/bin/ubusd

## Start ubus listener:
./libs/ubus/bin/ubus listen

## Start application:
* LD_LIBRARY_PATH="./out" ./analyzer/analyzer
* or
* LD_LIBRARY_PATH="./libs/libpcap/bin:./libs/ubus/bin:./libs/libubox/bin:./libs/libjson-c/bin" ./analyzer/analyzer

## Setup Debian 7:
apt-get install make gcc cmake flex bison autogen autoconf libtool

## Cross-compiling
Setup config.mk and cross-linux-gcc.cmake
