PKG_NAME:=json-c
PKG_VERSION:=0.13.1
PKG_RELEASE:=2

HOST_CFLAGS += -Wno-implicit-fallthrough
CONFIGURE_ARGS += \
	--disable-static \
    --enable-threading

build: bin
	cd $(PKG_NAME) && make -j
	cp $(PKG_NAME)/.libs/*.so* bin/
	ln -sf $(PKG_NAME) json

bin:
	mkdir bin
	tar -xzf $(PKG_NAME).tar.gz
	cd $(PKG_NAME) && NOCONFIGURE=1 ./autogen.sh
	cd $(PKG_NAME) && CFLAGS=$(HOST_CFLAGS) ./configure $(CONFIGURE_ARGS)

clean:
	rm -rf $(PKG_NAME) bin
	rm -f json

