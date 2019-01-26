PKG_NAME:=libubox
PKG_RELEASE=2

CWD = $(shell pwd)/$(PKG_NAME)

CMAKE_OPTIONS += \
	-DBUILD_LUA=OFF \
	-DBUILD_EXAMPLES=OFF \
	-Djson=../../libjson-c/bin/libjson-c.so \
	-DJSON_PATH=../../libjson-c

build: bin
	make -C bin all -j

bin:
	mkdir bin
	tar -xzf $(PKG_NAME).tar.gz
	cd $(PKG_NAME) && patch -p1 -i "../CMake.patch"
	cd bin && cmake $(CWD) $(CMAKE_OPTIONS)

install:
	cp bin/*.so ../../out/

clean :
	rm -rf $(PKG_NAME) bin
