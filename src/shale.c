#include "include/shale.h"
#include <stdio.h>

#define reg_s(reg) CPU->registers[reg].hl
#define reg_b(reg, byte) (CPU->registers[reg].byte)

const struct instruction instructions[256] = {
    {NOP, "NOP", 1, None, nop},
    {MVIS, "MOV", 4, Immediate, move_short_immediate},
    {MVIHB, "MOV", 4, Immediate, move_byte_immediate},
    {MVILB, "MOV", 4, Immediate, move_byte_immediate}
};

void initCPU(struct shaleCPU *cpu) {
    for (int i = 0; i < REGISTERS; i++) {
        cpu->registers[i].hl = 0;
    }  
}

void printRegisters(struct shaleCPU *cpu) {
    for (int i = 0; i < SP; i++) {
        printf("R%i   : %04x", i, cpu->registers[i].hl);
        (i % 2 != 0) ? printf("\n") : printf("\t");
    }
    printf("SP   : %04X\n", cpu->registers[SP].hl); 
    printf("FP   : %04X\n", cpu->registers[FP].hl); 
    printf("PC   : %04X\n", cpu->registers[PC].hl);
    printf("FLAGS: %04X\n\n", cpu->registers[FLAGS].hl); 
}

uint8_t read_byte(uint8_t *memory, uint16_t addr) {
    return memory[addr];
}

void write_byte(uint8_t *memory, uint8_t value ,uint16_t addr) {
    memory[addr] = value;
}

uint16_t read_short(uint8_t *memory, uint16_t addr) {
    return memory[addr] | memory[addr + 1] << 8;
}

void write_short(uint8_t *memory, uint16_t value ,uint16_t addr) {
    memory[addr] = value;
}

enum opcode read_pc(struct shaleCPU *CPU) {
    return CPU->memory[CPU->registers[PC].hl];
}

void increment_pc(struct shaleCPU *CPU) {
    enum opcode op = read_pc(CPU);
    CPU->registers[PC].hl += instructions[op].length;
}

void nop(struct shaleCPU *CPU) {
    increment_pc(CPU);
}

void move_byte_immediate(struct shaleCPU *CPU) {
    uint8_t dest = reg_s(PC) % FP + 1;
    uint16_t src = reg_s(PC) + 1;
    uint8_t val = read_byte(CPU->memory, src);
    if(read_pc(CPU) == MVIHB) {
        reg_b(dest, h) = val;
    }
    else {
        reg_b(dest, l) = val;
    }
    increment_pc(CPU);
}

void move_short_immediate(struct shaleCPU *CPU) {
    uint8_t dest = reg_s(PC) % FP + 1;
    uint16_t src = reg_s(PC) + 2;
    reg_s(dest) = read_short(CPU->memory, src);
    increment_pc(CPU);
}

void execute(struct shaleCPU *CPU){
    enum opcode op = read_pc(CPU);
    while (op != HLT) {
        instructions[op].operation(CPU);
        printRegisters(CPU);
        op = read_pc(CPU);
    }
    return;
}