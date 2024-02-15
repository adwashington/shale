#include "include/instructions.h"
#include "include/shale.h"

struct shaleCPU cpu;
uint8_t memory[5] = {MVIS, 0XF0, 0xFF, 0x1F, HLT};

int main(int argc, char const *argv[])
{
    initCPU(&cpu);
    cpu.memory = memory; 
    printRegisters(&cpu);
    execute(&cpu);   

    return 0;
}
