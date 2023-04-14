#include "include/shale.h"
#include <stdio.h>

const struct instruction instructions[256] = {
    {NOP, "NOP", 1, nop},
    {MVIS, "MOV", 4, move_short_immediate}
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

void move_short_immediate(struct shaleCPU *CPU) {
    uint8_t dest = CPU->registers[PC].hl + 1;
    uint16_t src = CPU->registers[PC].hl + 2;
    CPU->registers[dest].hl = read_short(CPU->memory, src);
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