include ../../config.mk

PKG_NAME:=ubus
PKG_RELEASE:=1

CWD = $(shell pwd)/$(PKG_NAME)

CMAKE_OPTIONS += \
	-DCMAKE_TOOLCHAIN_FILE=$(CMAKE_TOOLCHAIN_FILE) \
	-DBUILD_LUA=OFF \
	-DBUILD_EXAMPLES=OFF \
	-Dubox_include_dir=../../libubox/ \
	-Dubox_library=../../libubox/bin/libubox.so \
	-Dblob_library=../../libubox/bin/libblobmsg_json.so \
	-Djson=../../libjson-c/bin/libjson-c.so

build: bin
	make -C bin all -j

bin:
	mkdir bin
	tar -xzf $(PKG_NAME).tar.gz
	cd bin && cmake $(CWD) $(CMAKE_OPTIONS)

install:
	cp bin/*.so ../../out/

clean :
	rm -rf $(PKG_NAME) bin
