PKG_NAME:=analyzer
CC = cc

obj = \
	bin/main.o \
	bin/input_arguments.o \
	bin/pcap_setup.o \
	bin/packet_parser.o \
	bin/notification_loop.o

CFLAGS=-Wall -Werror
LIBS+= -lpthread
LIBS+= -L./libs/libpcap/bin -lpcap
LIBS+= -L./libs/ubus/bin -lubus
LIBS+= -L./libs/libubox/bin -lblobmsg_json -lubox
LIBS+= -L./libs/libjson-c/bin -ljson-c

INCLUDE:= -I./include
INCLUDE+= -I./libs/libpcap/libpcap
INCLUDE+= -I./libs/ubus/ubus -I./libs/libubox/
INCLUDE+= -I./libs/libjson-c


all : lib bin/$(PKG_NAME)

lib :
	$(MAKE) -C libs

bin/$(PKG_NAME) : $(obj)
	$(CC) $(CFLAGS) $(INCLUDE) $(obj) -o bin/$(PKG_NAME) $(LIBS)

bin/%.o : src/%.c
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean :
	rm -f $(obj) bin/$(PKG_NAME)
	$(MAKE) -C libs clean
