#include <stdint.h>
#pragma once

enum opcode {
    NOP,
    MVIS,
    MVIHB,
    MVILB,
    MVS,
    MVHB,
    MVLB,
    MVRS,
    MVRHB,
    MVRLB,
    CMP,
    JMP,
    ADD,
    SUB,
    PSH,
    POP,
    HLT,
};

enum addressing_modes {
    Immediate_8,
    Immediate_16,
    Register_16_16,
    Register_8_8,
    Register_16_8,
    Register_8_16,
    Absolute,
    Indexed_16_16,
    Indexed_8_8,
    Indexed_16_8,
    Indexed_8_16,
    Relative,
    None
};

struct instruction {
    enum opcode opcode;
    char *mnemonic;
    uint8_t length;
    enum addressing_modes addressing_mode;
    void (*operation)(); 
};


