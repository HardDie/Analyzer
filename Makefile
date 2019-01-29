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
	@if [ ! -d $(PKG_NAME)_build ]; then cp -rf $(PKG_NAME) $(PKG_NAME)_build; fi
	cd $(PKG_NAME)_build && LDFLAGS="$(LDFLAGS)" CFLAGS="$(CFLAGS)" ./configure --host=$(HOST)
	cd $(PKG_NAME)_build && make

clean :
	rm -rf out $(PKG_NAME)_build
	$(MAKE) -C libs clean
