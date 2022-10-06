#include "include/instructions.h"
#include "include/shale.h"

struct shaleCPU cpu;


int main(int argc, char const *argv[])
{
    initCPU(&cpu);
    printRegisters(&cpu);

    return 0;
}
