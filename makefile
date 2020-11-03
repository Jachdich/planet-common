install:
	rm -rf ../planet-client/include/common
	rm -rf ../planet-server/include/common
	cp -r include ../planet-client/include/common
	cp -r include ../planet-server/include/common

install_only_libs: common.a
	cp common.a ../planet-client
	cp common.a ../planet-server
