PKG_NAME:=libpcap
PKG_VERSION:=1.9.0
PKG_RELEASE:=1

CONFIGURE_ARGS += \
	--enable-shared \
	--disable-yydebug \
	--with-pcap=linux \
	--without-septel \
	--without-dag \
	--without-libnl \
	--without-snf \
	--disable-dbus \
	--disable-bluetooth

build: bin
	cd $(PKG_NAME) && make -j
	cp $(PKG_NAME)/libpcap.so* bin/

bin:
	mkdir bin
	tar -xzf $(PKG_NAME).tar.gz
	cd $(PKG_NAME) && ./configure $(CONFIGURE_ARGS)

clean :
	rm -rf $(PKG_NAME) bin
