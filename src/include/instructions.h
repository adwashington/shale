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

struct instruction {
    enum opcode opcode;
    char *mnemonic;
    uint8_t length;
    void (*operation)(); 
};


