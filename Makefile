CC_FILES    := $(wildcard src/*.cc)
OBJ_FILES   := $(addprefix obj/,$(notdir $(CC_FILES:.cc=.o)))
CC_FLAGS    := -g
LIBRARY     := libcfat.so
#.1.0.0 
LIBRARYSL   := libcfat.so
all:  lib/$(LIBRARYSL)

obj/%.o: src/%.cc
	gcc `root-config --libs --cflags` $(CC_FLAGS) -c -fPIC -o $@ $< -I interface


lib/$(LIBRARY).1.0.0:  $(OBJ_FILES)
	gcc -shared -Wl,-soname,$(LIBRARY) -g -fPIC -o $@ $^ 

lib/$(LIBRARYSL): lib/$(LIBRARY).1.0.0 
	if [[ -f $@ ]]; then rm $@; fi;
	ln -s $(LIBRARY).1.0.0 $@ 

.PHONY: clean

clean:
	rm obj/*
	rm lib/*