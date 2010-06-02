#variable hold here
#note!: make x86_64 arch only
CC=gcc
CXX=g++
AR=ar
Copt=-c -O2 -fPIC -I../include
Cld=-shared
Aropt=cr
target=clib.so
target_static=clib.a
cfile= string.c string2.c opt.c stdlib.c clib.c  ednumber.c x86d.c
depfile=syscall_def.c dirent.c iofile2.c
cother=cmath.c
objects=$(addsuffix .o,$(basename $(cfile)))
depobj=$(addsuffix .o,$(basename $(depfile)))
installpath=$(prefix)/lib64
includepath=$(prefix)/usr/include/clib
#end of variable
all: clib cliba
clib: obj
	$(CC) $(Cld) $(objects) $(depobj) $(other) -o $(target)
cliba:
	$(AR) $(Aropt) $(target_static) $(objects)
obj: config
	$(CC) -std=c99 -c -fPIC $(cother) -I../include
	$(CC) -std=c99 $(Copt) $(cfile)
	$(CC) $(Copt) $(depfile)
config:
	./chseries
clean: 
	rm -f *.o
	rm -f $(target) $(target_static)

install:
	@echo install to $(installpath)
	@install -v $(target) $(installpath) 
	@mkdir -p $(includepath)
	@install -v ../include/* $(includepath)
win:
	$(CC) $(Copt) $(cfile) 
	$(CC) $(Cld) $(objects) -o clib.dll 
	$(AR) $(Aropt) clib.a $(objects)
	@echo "now use make wininstall to install to system"
	@echo hand your own copy clib.a to dir
wininstall:
	@copy clib.dll $(windir)\system32
	@echo "clib has been install in $(windir)\system32"

