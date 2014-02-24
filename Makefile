all: imx_usb

BUILDHOST := $(shell uname -s)
BUILDHOST := $(patsubst CYGWIN_%,CYGWIN,$(BUILDHOST))
.PHONY: test

ifneq ($(BUILDHOST),CYGWIN)
CFLAGS = `pkg-config --cflags libusb-1.0`
CXXFLAGS += -I/usr/local/include/
else
CFLAGS = -I/usr/include/libusb-1.0
endif

CFLAGS += -g -pg -fprofile-arcs -ftest-coverage -Wno-write-strings
CXXFLAGS += -g -pg -fprofile-arcs -ftest-coverage -Wno-write-strings

%.o : %.cpp
	$(CC) -c $*.cpp -o $@ -Wno-trigraphs -pipe -ggdb -Wall $(CFLAGS)

%.o : %.c
	$(CC) -c $*.c -o $@ -Wstrict-prototypes -Wno-trigraphs -pipe -ggdb $(CFLAGS)

imx_usb: imx_usb.o 
	$(CC) -o $@ $@.o -lusb-1.0 --coverage

install: imx_usb
	mkdir -p ${DESTDIR}/usr/bin/
	install -m755 imx_usb ${DESTDIR}/usr/bin/imx_usb

clean:
	rm -f imx_usb imx_usb.o imx_usb_test.o test


test: imx_usb_test.o imx_usb.o
	$(CXX) -o $@ $^  -lCppUTest -lusb-1.0 --coverage


