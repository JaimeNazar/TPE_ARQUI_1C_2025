include Makefile.inc

MAIN_DATA=0001-userDataModule.bin

all: userCodeModule userDataModule

userCodeModule:
	cd shell; make

userDataModule:
	printf "This is sample data." >> $(MAIN_DATA) && dd if=/dev/zero bs=1 count=1 >> $(MAIN_DATA)

clean:
	cd shell; make clean
	rm -rf *.bin


.PHONY: userCodeModule all clean
