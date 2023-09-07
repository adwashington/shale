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
    Immediate,
    Register,
    Absolute,
    Indirect,
    Indexed,
    None
};

struct instruction {
    enum opcode opcode;
    char *mnemonic;
    uint8_t length;
    enum addressing_modes addressing_mode;
    void (*operation)(); 
};


