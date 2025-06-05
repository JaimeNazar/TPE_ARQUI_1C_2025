include Makefile.inc

USER_DATA=0001-userDataModule.bin

MODULE=0000-userCodeModule.bin
SOURCES_ASM=$(wildcard asm/*.asm)
OBJECTS=$(SOURCES:.c=.o)
OBJECTS_ASM=$(SOURCES_ASM:.asm=.o)
GCCFLAGS += -mfpmath=sse -msse
LOADEROBJECT=$(LOADERSRC:.asm=.o)
STATICLIBS=

SOURCES = $(wildcard *.c) \
          $(wildcard shell/*.c) \
          $(wildcard pongis/*.c)

all:$(MODULE) userDataModule 

$(MODULE): $(OBJECTS) $(STATICLIBS) $(OBJECTS_ASM)
	$(LD) $(LDFLAGS) -T userCodeModule.ld -o $(MODULE) $(OBJECTS) $(OBJECTS_ASM) $(STATICLIBS)

%.o: %.c
	$(GCC) $(GCCFLAGS) -I./include -I./shell/include -I./pongis/include -c $< -o $@

%.o : %.asm
	$(ASM) $(ASMFLAGS) $< -o $@

userDataModule:
	printf "This is sample data." >> $(USER_DATA) && dd if=/dev/zero bs=1 count=1 >> $(USER_DATA)

clean:
	rm -rf asm/*.o c/*.o *.o
	rm -rf *.bin


.PHONY: userCodeModule all clean
