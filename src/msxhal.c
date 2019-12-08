#include "msxhal.h"

volatile uint8_t current_segment_a;
volatile uint8_t current_segment_b;
volatile uint8_t current_segment_c;
volatile uint8_t current_segment_d;

void msxhal_init() {

	__asm
		di
	__endasm;

	current_segment_a = 0;
	current_segment_b = 1;
	current_segment_c = 2;
	current_segment_d = 3;

	__asm
		push ix
		ld ix,#0
		add ix,sp

		ld a,#0x00
		ld (#0x5000),a ; // Konami5 mapper init
		ld (#0x5000),a ; // Konami5 mapper init
		ld (#0x5000),a ; // Konami5 mapper init
		ld (#0x5000),a ; // Konami5 mapper init

		inc a
		ld (#0x7000),a ; // Konami5 mapper init
		ld (#0x7000),a ; // Konami5 mapper init
		ld (#0x7000),a ; // Konami5 mapper init
		ld (#0x7000),a ; // Konami5 mapper init

		inc a
		ld (#0x9000),a ; // Konami5 mapper init
		ld (#0x9000),a ; // Konami5 mapper init
		ld (#0x9000),a ; // Konami5 mapper init
		ld (#0x9000),a ; // Konami5 mapper init

		inc a
		ld (#0xB000),a ; // Konami5 mapper init
		ld (#0xB000),a ; // Konami5 mapper init
		ld (#0xB000),a ; // Konami5 mapper init
		ld (#0xB000),a ; // Konami5 mapper init

		pop ix
	__endasm;
}
