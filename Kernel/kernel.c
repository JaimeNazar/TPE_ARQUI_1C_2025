#include <stdint.h>
#include <string.h>
#include <lib.h>
#include <moduleLoader.h>
#include <naiveConsole.h>
#include <styledConsole.h>
#include <idtLoader.h>
#include <soundDriver.h>
extern uint8_t text;
extern uint8_t rodata;
extern uint8_t data;
extern uint8_t bss;
extern uint8_t endOfKernelBinary;
extern uint8_t endOfKernel;

static const uint64_t PageSize = 0x1000;

static void * const userCodeModuleAddress = (void*)0xA00000;
static void * const userDataModuleAddress = (void*)0xB00000;

typedef int (*EntryPoint)();


void clearBSS(void * bssAddress, uint64_t bssSize)
{
	memset(bssAddress, 0, bssSize);
}

void * getStackBase()
{
	return (void*)(
		(uint64_t)&endOfKernel
		+ PageSize * 8				//The size of the stack itself, 32KiB
		- sizeof(uint64_t)			//Begin at the top of the stack
	);
}

void * initializeKernelBinary()
{
	char buffer[10];

	ncPrint("[x64BareBones]");
	ncNewline();

	ncPrint("CPU Vendor:");
	ncPrint(cpuVendor(buffer));
	ncNewline();

	ncPrint("[Loading modules]");
	ncNewline();
	void * moduleAddresses[] = {
		userCodeModuleAddress,
		userDataModuleAddress
	};

	loadModules(&endOfKernelBinary, moduleAddresses);
	ncPrint("[Done]");
	ncNewline();
	ncNewline();

	ncPrint("[Initializing kernel's binary]");
	ncNewline();

	clearBSS(&bss, &endOfKernel - &bss);

	ncPrint("  text: 0x");
	ncPrintHex((uint64_t)&text);
	ncNewline();
	ncPrint("  rodata: 0x");
	ncPrintHex((uint64_t)&rodata);
	ncNewline();
	ncPrint("  data: 0x");
	ncPrintHex((uint64_t)&data);
	ncNewline();
	ncPrint("  bss: 0x");
	ncPrintHex((uint64_t)&bss);
	ncPrint(" (size: 0x");
	ncPrintDec(&endOfKernel - &bss);
	ncPrint(" bytes)");
	ncNewline();

	ncPrint("[Done]");
	ncNewline();
	ncNewline();
	return getStackBase();
}

uint8_t getHours() {
	return rtc(4);
}

uint8_t getMinutes() {
	return rtc(2);
}

uint8_t getSeconds() {
	return rtc(0);
}

void printTime(){
	scPrint("Current time: ", 0x0F);
	scPrintHex(getHours(), 0x0F);	// In Universal Standard Time
	scPrint(":", 0x0F);
	scPrintHex(getMinutes(), 0x0F);
	scPrint(":", 0x0F);
	scPrintHex(getSeconds(), 0x0F);

	scNewline();
}

int main()
{	
	load_idt();
	videoInitialize();
	bell(1000, 300);
	((EntryPoint)userCodeModuleAddress)();
	
	return 0;
}
