#include "include/shale.h"
#include <stdio.h>


const struct instruction instructions[256] = {
    {NOP, 1, nop},
};

void initCPU(struct shaleCPU *cpu) {
    for (int i = 0; i < REGISTERS; i++) {
        cpu->registers[i] = 0;
    }  
}

void printRegisters(struct shaleCPU *cpu) {
    for (int i = 0; i < SP; i++) {
        printf("R%i   : %04x", i, cpu->registers[i]);
        (i % 2 != 0) ? printf("\n") : printf("\t");
    }
    printf("SP   : %04X\n", cpu->registers[SP]); 
    printf("FP   : %04X\n", cpu->registers[FP]); 
    printf("FLAGS: %04X\n", cpu->registers[FLAGS]); 
}


void nop(void) {}