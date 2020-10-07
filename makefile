SOURCES := $(shell find src -type f -name *.cpp)
HEADERS := $(shell find include -type f -name *.h)
OBJECTS := $(patsubst src/%,obj/%,$(SOURCES:.cpp=.o))

common.a: $(OBJECTS)
	ar ru common.a $(OBJECTS)
	ranlib common.a

#obj:
#	mkdir -p obj

obj/%.o: src/%.cpp $(HEADERS)# obj
	g++ -c -o $@ $< -Wall -Werror -g -std=c++17 -Iinclude

obj/FastNoise.o: src/FastNoise.cpp
	g++ -c -o $@ $< -Wall -g -O3 -std=c++11 -Iinclude

install: common.a
	cp common.a ../planet-client
	cp common.a ../planet-server

	rm -rf ../planet-client/include/common
	rm -rf ../planet-server/include/common
	cp -r include ../planet-client/include/common
	cp -r include ../planet-server/include/common

install_only_libs: common.a
	cp common.a ../planet-client
	cp common.a ../planet-server

clean:
	rm obj/*.o
	rm common.a

.PHONY: clean
