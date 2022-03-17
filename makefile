SOURCES := $(shell find src -type f -name *.c)
HEADERS := $(shell find include -type f -name *.h)
OBJECTS := $(patsubst src/%,obj/%,$(SOURCES:.c=.o))
RELOBJECTS := $(patsubst src/%,obj/release/%,$(SOURCES:.c=.o))

LIBS :=

all: libcommon.a

libcommon-dbg.a: $(OBJECTS)
	ar -rc $@ $(OBJECTS)
	ranlib $@

libcommon.a: $(RELOBJECTS)
	ar -rc $@ $(RELOBJECTS)
	ranlib $@

obj/%.o: src/%.c $(HEADERS)
	@mkdir -p obj
	gcc -c -o $@ $< -Wall -g -Iinclude

obj/release/%.o: src/%.c $(HEADERS)
	@mkdir -p obj/release
	gcc -c -o $@ $< -Wall -Werror -O2 -Iinclude


clean:
	rm -rf obj/*.o
	rm -rf libcommon.a libcommon-dbg.a
	rm -rf obj/release/*.o

.PHONY: clean

install: libcommon.a install_headers
	cp libcommon.a ../planet-client
	cp libcommon.a ../planet-server

insall_dbg: libcommon-dbg.a install_headers
	cp libcommon-dbg.a ../planet-client
	cp libcommon-dbg.a ../planet-server

install_headers: $(HEADERS)
	rm -rf ../planet-client/include/common
	rm -rf ../planet-server/include/common
	cp -r include ../planet-client/include/common
	cp -r include ../planet-server/include/common
