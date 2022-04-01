SOURCES := $(shell find src -type f -name *.c)
HEADERS := $(shell find include -type f -name *.h)
OBJECTS := $(patsubst src/%,obj/%,$(SOURCES:.c=.o))
RELOBJECTS := $(patsubst src/%,obj/release/%,$(SOURCES:.c=.o))
RUST_LIB := target/release/libcommon.a
RUST_LIB_DBG := target/debug/libcommon.a
RUST_SOURCES := $(shell find src -type f -name *.rs)

LIBS :=

all: libcommon.a

libcommon-dbg.a: $(OBJECTS) $(RUST_LIB_DBG)
	ar --output obj x $(RUST_LIB_DBG)
	ar -rc $@ obj/*.o
	ranlib $@

libcommon.a: $(RELOBJECTS) $(RUST_LIB)
	ar --output obj/release x $(RUST_LIB)
	ar -rc $@ obj/release/*.o
	ranlib $@

obj/%.o: src/%.c $(HEADERS)
	@mkdir -p obj
	gcc -c -o $@ $< -Wall -g -Iinclude

obj/release/%.o: src/%.c $(HEADERS)
	@mkdir -p obj/release
	gcc -c -o $@ $< -Wall -Werror -O2 -Iinclude

$(RUST_LIB): $(RUST_SOURCES)
	cargo build --release

$(RUST_LIB_DBG): $(RUST_SOURCES)
	cargo build

clean:
	rm -rf obj/*.o
	rm -rf libcommon.a libcommon-dbg.a
	rm -rf obj/release/*.o
	rm -rf target/debug/libcommon.a
	rm -rf target/release/libcommon.a

.PHONY: clean

install: libcommon.a install_headers
	cp libcommon.a ../planet-client
	cp libcommon.a ../planet-server

install_dbg: libcommon-dbg.a install_headers
	cp libcommon-dbg.a ../planet-client
	cp libcommon-dbg.a ../planet-server

install_headers: $(HEADERS)
	rm -rf ../planet-client/include/common
	rm -rf ../planet-server/include/common
	cp -r include ../planet-client/include/common
	cp -r include ../planet-server/include/common
