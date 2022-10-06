#pragma once
#include <stdint.h>
#include "instructions.h"

enum {
    R0,
    R1,
    R2,
    R3,
    R4,
    R5,
    R6,
    R7, 
    SP,
    FP, 
    PC, 
    FLAGS,
    REGISTERS
};

struct shaleCPU{
    uint16_t registers[REGISTERS];
};

void initCPU(struct shaleCPU *cpu);
void printRegisters(struct shaleCPU *cpu);
