#
# Copyright (C) 2006-2013 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

PKG_NAME:=libpcap
PKG_VERSION:=1.9.0
PKG_RELEASE:=1

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.gz
PKG_SOURCE_URL:=http://www.tcpdump.org/release/
PKG_HASH:=2edb88808e5913fdaa8e9c1fcaf272e19b2485338742b5074b9fe44d68f37019
PKG_FIXUP:=patch-libtool

PKG_MAINTAINER:=Felix Fietkau <nbd@nbd.name>

PKG_INSTALL:=1
PKG_BUILD_PARALLEL:=1
PKG_LICENSE:=BSD-3-Clause

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

all :
	@ if [ ! -f $(PKG_SOURCE) ]; then wget $(PKG_SOURCE_URL)$(PKG_SOURCE); fi
	@ if [ ! -d $(PKG_NAME)-$(PKG_VERSION) ]; then tar -xzf $(PKG_SOURCE); fi
	cd $(PKG_NAME)-$(PKG_VERSION) && ./configure $(CONFIGURE_ARGS)
	cd $(PKG_NAME)-$(PKG_VERSION) && make -j
	cp $(PKG_NAME)-$(PKG_VERSION)/libpcap.so* ../../bin/
	cp -r $(PKG_NAME)-$(PKG_VERSION)/pcap ../../include/

clean :
	rm -rf $(PKG_SOURCE) $(PKG_NAME)-$(PKG_VERSION) ../../bin/libpcap.so* ../../include/pcap
