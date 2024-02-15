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

enum instruction_flags {
    IF_High_Byte       = 3,
    IF_Sign            = 2,
    IF_Direction       = 1,
    IF_Size            = 6,
    IF_High_Byte_Dst   = 4,
    IF_High_Byte_Base  = 3,
    IF_High_Byte_Index = 0,
    IF_High_Byte_Src   = 7,
    IF_Extension       = 5,
};

struct instruction_format_immd8 {
    uint8_t dest;
    uint8_t immd8;
    uint8_t flags;
};

struct instruction_format_immd16 {
    uint8_t dest;
    uint16_t immd16;
    uint8_t flags;
};

struct instruction_format_pc_rel {
    uint8_t dest;
    int16_t sImmd8;
    uint8_t flags;
};

struct instruction_format_abs {
    uint8_t dest;
    uint16_t immd16;
};

struct instruction_format_ind {
    uint8_t dest;
    uint8_t base;
    uint8_t index;
    int16_t sImmd16;
    uint8_t flags;
};

struct instruction_format_reg {
    uint8_t dest;
    uint8_t src;
    uint8_t flags;
};

union instruction_format {
  struct instruction_format_immd8  immd8;
  struct instruction_format_immd16 imm16;
  struct instruction_format_pc_rel pc_rel;
  struct instruction_format_abs    abs;
  struct instruction_format_ind    ind;
  struct instruction_format_reg    reg;
};

struct instruction {
    enum opcode opcode;
    char *mnemonic;
    uint8_t length;
    enum addressing_modes addressing_mode;
    void (*operation)(); 
};


