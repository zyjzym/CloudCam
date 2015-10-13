
TARGET = pc 
DEBUG = no


EXEC := mem_test

FILES = main mem 

SRCS = $(addsuffix .c, $(FILES))
OBJS = $(addsuffix .o, $(FILES))

ifeq ($(TARGET),arm)
SQLITEHOME := ../../lib/sqlitelib
OPENSSLHOME := ../../lib/openssllib
CC := arm-linux-gcc
LDFLAGS += -L../../lib/share_lib
else
#SQLITEHOME := /usr/local/sqlite
#OPENSSLHOME := /usr/local/openssl
CC := gcc
#LDFLAGS += -L../../share_lib_pc
endif

ifeq ($(DEBUG),yes)
CFLAGS += -g -Wall -Wstrict-prototypes
else
CFLAGS += -Wall -Wstrict-prototypes
endif

ifeq ($(TLS), yes)
CFLAGS += -DTLS_VERSION
endif

#CFLAGS += -I$(SQLITEHOME)/include
#CFLAGS += $(GLOBAL_MACROS)
#CFLAGS += -I../../comm_include
#CFLAGS += -I$(OPENSSLHOME)/include

DFLAGS := -D__USE_XOPEN -D_GNU_SOURCE

#LDFLAGS += -L$(SQLITEHOME)/lib
#LDLIBS := -lsqlite3

#LDFLAGS += -L$(OPENSSLHOME)/lib
#LDLIBS += -lssl
#LDLIBS += -lcrypto

#LDLIBS += -lpublic
#LDLIBS += -ldbpwd
#LDLIBS += -lpthread


$(EXEC):$(OBJS)
	$(CC) $(LDFLAGS) -o $@ $(OBJS) $(LDLIBS)
ifeq ($(TARGET),arm)	
	cp -f $(EXEC) ../../bin/
endif

%.o : %.c
	$(CC) $(CFLAGS) $(DFLAGS) -MD -c -o $@ $<

clean:
	rm -f *.o
	rm -f *.d
	rm -f *.gdb
	rm -f $(EXEC)
	rm -f *~

