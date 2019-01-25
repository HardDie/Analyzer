PKG_NAME:=libubox
PKG_RELEASE=2

CWD = $(shell pwd)/$(PKG_NAME)

CMAKE_OPTIONS += \
	-DBUILD_LUA=OFF \
	-DBUILD_EXAMPLES=OFF

build: bin
	make -C bin all

bin:
	mkdir bin
	tar -xzf $(PKG_NAME).tar.gz
	cd bin && cmake $(CWD) $(CMAKE_OPTIONS)

clean :
	rm -rf $(PKG_NAME) bin
