PKG_NAME:=analyzer
CC = cc

obj = \
	bin/main.o \
	bin/input_arguments.o

CFLAGS=-Wall -Werror
LIBS:=-L./bin/ -lpcap
INCLUDE:=-I./include -I./include/pcap


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
