#include "qemu/osdep.h"
#include "hw/boards.h"

static void redmi9a_init(MachineState *machine)
{
}

static void redmi9a_machine_init(MachineClass *mc)
{
    mc->desc = "Xiaomi Redmi 9A";
    mc->init = redmi9a_init;  // must have
}

DEFINE_MACHINE("redmi9a", redmi9a_machine_init)
