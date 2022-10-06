#include <stdint.h>
#pragma once

enum opcode {
    NOP,
};

struct instruction {
    enum opcode opcode;
    uint8_t length;
    void *operation; 
};


