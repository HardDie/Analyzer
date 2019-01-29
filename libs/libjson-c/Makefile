include ../../config.mk

PKG_NAME:=json-c
PKG_VERSION:=0.13.1
PKG_RELEASE:=2

HOST_CFLAGS += -Wno-implicit-fallthrough
CONFIGURE_ARGS += \
	--disable-static \
	ac_cv_func_malloc_0_nonnull=yes \
	ac_cv_func_realloc_0_nonnull=yes

build: bin
	cd $(PKG_NAME) && make V=0 -j
	cp $(PKG_NAME)/.libs/*.so* bin/
	ln -sf $(PKG_NAME) json

bin:
	mkdir bin
	tar -xzf $(PKG_NAME).tar.gz
	cd $(PKG_NAME) && patch -p1 -i "../configure.ac.patch"
	cd $(PKG_NAME) && NOCONFIGURE=1 ./autogen.sh
	cd $(PKG_NAME) && CFLAGS=$(HOST_CFLAGS) ./configure $(CONFIGURE_ARGS) --host=$(HOST)

install:
	cp $(PKG_NAME)/.libs/*.so* ../../out/

clean:
	rm -rf $(PKG_NAME) bin json

