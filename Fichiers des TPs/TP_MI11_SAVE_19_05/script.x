OUTPUT_FORMAT("elf32-littlearm", "elf32-bigarm",
	      "elf32-littlearm")
OUTPUT_ARCH(arm)
ENTRY(_start)

SECTIONS
{
			
	. = 0;
	
	.text : { 
			*(.text) 
			*(.rodata) 
			. = ALIGN(4);
		}
	
	text_end = LOADADDR(.text) + SIZEOF(.text);
	data_start = ADDR(.data);
	.data 0x8000000 : AT(text_end) { 
			*(.data)
			. = ALIGN(4);
		}
	data_end = 	LOADADDR(.data) + SIZEOF(.data);
	
	bss_start = ADDR(.data) + SIZEOF(.data);
	.bss bss_start : { 
			*(.bss) 
			*(COMMON)
			. = ALIGN(4);
		}
	bss_end = ADDR(.bss) + SIZEOF(.bss);
}
