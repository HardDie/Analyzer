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
	cp $(PKG_NAME)/libpcap.so.1.9.0 bin/
	cd bin && ln -sf libpcap.so.1.9.0 libpcap.so.1
	cd bin && ln -sf libpcap.so.1.9.0 libpcap.so

bin:
	mkdir bin
	tar -xzf $(PKG_NAME).tar.gz
	cd $(PKG_NAME) && ./configure $(CONFIGURE_ARGS)

install:
	cp $(PKG_NAME)/libpcap.so.1.9.0 ../../out/
	cd ../../out/ && ln -sf libpcap.so.1.9.0 libpcap.so.1
	cd ../../out/ && ln -sf libpcap.so.1.9.0 libpcap.so

clean:
	rm -rf $(PKG_NAME) bin
