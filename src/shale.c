#include "include/shale.h"
#include <stdio.h>
#include <string.h>

#define reg_s(reg) CPU->registers[reg].hl
#define reg_b(reg, byte) (CPU->registers[reg].byte)
#define read_pc() read_byte(CPU->memory, CPU->registers[PC].hl)

const struct instruction instructions[256] = {
    {NOP, "NOP", 1, None, nop},
    {MVIS, "MOV", 4, Immediate_16, move_short_immediate},
    {MVIHB, "MOV", 3, Immediate_8, move_byte_immediate},
    {MVILB, "MOV", 3, Immediate_8, move_byte_immediate}
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

union instruction_format get_addressing_mode_ops(struct shaleCPU *CPU, enum addressing_modes addressing_mode) {
    union instruction_format format;
    memset(&format, 0, sizeof(format));
    uint64_t instruction = 0; 
    switch (addressing_mode) {
    case Immediate_8:
    case Immediate_16:
        
        memcpy(&instruction, &CPU->memory[reg_s(PC) + 1], instructions[reg_s(PC) + 1].length - 1);
        format.imm16.dest = (instruction & 0xF00000) >> 20;
        format.imm16.immd16 = (instruction & 0x0FFFF0) >>  4;
        format.imm16.flags = (instruction & 0x00000F);
        break;
    
    default:
        break;
    }
    return format;
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

void increment_pc(struct shaleCPU *CPU) {
    enum opcode op = read_pc();
    reg_s(PC) += instructions[op].length;
}

void nop(struct shaleCPU *CPU) {
    increment_pc(CPU);
}

void move_byte_immediate(struct shaleCPU *CPU) {
    uint8_t dest = reg_s(PC) % FP + 1;
    uint16_t src = reg_s(PC) + 1;
    uint8_t val = read_byte(CPU->memory, src);
    if(read_pc() == MVIHB) {
        reg_b(dest, h) = val;
    }
    else {
        reg_b(dest, l) = val;
    }
    increment_pc(CPU);
}

void move_short_immediate(struct shaleCPU *CPU) {
    get_addressing_mode_ops(CPU, instructions[read_pc(CPU)].addressing_mode);
    uint8_t dest = reg_s(PC) % FP + 1;
    uint16_t src = reg_s(PC) + 2;
    reg_s(dest) = read_short(CPU->memory, src);
    increment_pc(CPU);
}

void execute(struct shaleCPU *CPU){
    enum opcode op = read_pc();
    while (op != HLT) {
        instructions[op].operation(CPU);
        printRegisters(CPU);
        op = read_pc();
    }
    return;
}