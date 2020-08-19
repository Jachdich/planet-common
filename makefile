SOURCES := $(shell find src -type f -name *.cpp)
HEADERS := $(shell find include -type f -name *.h)
OBJECTS := $(patsubst src/%,obj/%,$(SOURCES:.cpp=.o))

common.a: $(OBJECTS)
	ar ru common.a $<
	ranlib common.a

obj/%.o: src/%.cpp $(HEADERS)
	g++ -c -o $@ $< -Wall -g -std=c++11 -Iinclude

obj/FastNoise.o: src/FastNoise.cpp
	g++ -c -o $@ $< -Wall -g -O3 -std=c++11 -Iinclude

install: common.a
	cp common.a ../planet-client
	cp common.a ../planet-server
	cp -r include ../planet-client/include/common
	cp -r include ../planet-server/include/common
clean:
	rm obj/*.o
	rm common.a

.PHONY: clean
