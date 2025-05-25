include Makefile.inc

MAIN_DATA=0001-mainDataModule.bin

all: mainModule mainDataModule

mainModule:
	cd shell; make

mainDataModule:
	printf "This is sample data." >> $(MAIN_DATA) && dd if=/dev/zero bs=1 count=1 >> $(MAIN_DATA)

clean:
	cd shell; make clean
	rm -rf *.bin


.PHONY: mainModule all clean
