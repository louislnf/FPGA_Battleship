/*
 * memory.c
 *
 *  Created on: 22 nov. 2018
 *      Author: lenief_lou
 */

#include "memory.h"
#include "system.h"
#include "io.h"

void writeMemory(unsigned char adress, unsigned char value) {
	IOWR_16DIRECT(MEMORY_BASE, 2*adress, value);
}

void cleanMemory() {
	printf("Cleaning the memory\n");
	unsigned char adr = 0, zero = 0;
	for (adr = 0; adr<255; adr++) {
		writeMemory(adr, zero);
	}
	printf("Done cleaning the memory\n");
}
