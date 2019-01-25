PKG_NAME:=ubus
PKG_RELEASE:=1

CWD = $(shell pwd)/$(PKG_NAME)

CMAKE_OPTIONS += \
	-DBUILD_LUA=OFF \
	-DBUILD_EXAMPLES=OFF \
	-Dubox_include_dir=../../libubox/ \
	-Dubox_library=../../libubox/bin/libubox.so \
	-Dblob_library=../../libubox/bin/libblobmsg_json.so

build: bin
	make -C bin all -j

bin:
	mkdir bin
	tar -xzf ubus.tar.gz
	cd bin && cmake $(CWD) $(CMAKE_OPTIONS)

clean :
	rm -rf $(PKG_NAME) bin
