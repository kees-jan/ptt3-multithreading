# In this directory, type one of the following:
#   make
#   make all

SUBDIRS = library

all: $(SUBDIRS)

ifeq "$(wildcard /usr/lib/x86_64-linux-gnu/libgtest.a)" ""
library: .gtest
endif

$(SUBDIRS):
	$(MAKE) -C $@ 

clean:
	make -C library clean && rm -rf gtest .gtest

.gtest:
	mkdir -p gtest
	cd gtest && cmake /usr/src/googletest/googletest
	$(MAKE) -C gtest
	touch .gtest

.PHONY: all $(SUBDIRS) clean
