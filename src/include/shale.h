#pragma once
#include <stdint.h>
#include "instructions.h"

union reg{
    uint16_t hl;
    struct
    {
        uint8_t l;
        uint8_t h;
    };
};

enum flags {
    Carry = 1,
    Zero = 2,
    Sign = 4,
    Negative = 8
};

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
    union reg registers[REGISTERS];
    uint8_t *memory;
};

void initCPU(struct shaleCPU *cpu);
void printRegisters(struct shaleCPU *cpu);
void execute(struct shaleCPU *cpu);
extern void nop();
extern void move_short_immediate();
