include config.mk

PKG_NAME:=analyzer
CC = cc

obj = \
	bin/main.o \
	bin/input_arguments.o \
	bin/pcap_setup.o \
	bin/packet_parser.o \
	bin/notification_loop.o

LDFLAGS=-L../out
CFLAGS=-I./include -I../libs/libpcap/libpcap -I../libs/ubus/ubus -I../libs/libubox -I../libs/libjson-c

all: lib bin

lib:
	@if [ ! -d out ]; then mkdir out; fi
	$(MAKE) -C libs

bin:
	cd $(PKG_NAME) && LDFLAGS="$(LDFLAGS)" CFLAGS="$(CFLAGS)" ./configure --host=$(HOST)
	cd $(PKG_NAME) && make

clean :
	$(MAKE) -C $(PKG_NAME) clean
	$(MAKE) -C libs clean
