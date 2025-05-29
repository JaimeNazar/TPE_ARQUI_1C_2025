#!/bin/bash
qemu-system-x86_64 -audiodev pa,id=speaker -machine pcspk-audiodev=speaker -hda Image/x64BareBonesImage.qcow2 -m 512 
