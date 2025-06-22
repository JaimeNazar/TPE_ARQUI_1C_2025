ASM=nasm
BMFS_MBR=bmfs_mbr.sys
PXESTART=pxestart.sys
PURE64=pure64.sys

RES ?= "1024,768,24,0x0000"

all: bmfs_mbr.sys pxestart.sys pure64.sys
$(BMFS_MBR):
	$(ASM) src/bootsectors/bmfs_mbr.asm -o $(BMFS_MBR)
$(PXESTART):
	$(ASM) src/bootsectors/pxestart.asm -o $(PXESTART)
$(PURE64):
	cd src; $(ASM) pure64.asm -D URES="$(RES)" -o ../$(PURE64)
clean:
	rm -rf *.sys
.PHONY: all clean
