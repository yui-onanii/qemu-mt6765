#include "qemu/osdep.h"
#include "qapi/error.h"
#include "hw/qdev-core.h"
#include "hw/boards.h"
#include "hw/arm/mt6765.h"
#include "qom/object.h"

static void redmi9a_init(MachineState *machine)
{
    DeviceState *mt6762g;

    // (almost) identical SoCs with slightly slower clock
    mt6762g = qdev_new(TYPE_MT6765);
    object_property_add_child(OBJECT(machine), "soc", OBJECT(mt6762g));
    qdev_realize_and_unref(DEVICE(mt6762g), NULL, &error_fatal);
}

static void redmi9a_machine_init(MachineClass *mc)
{
    mc->desc = "Xiaomi Redmi 9A (MT6762G)";
    mc->init = redmi9a_init;  // must have
}

DEFINE_MACHINE("redmi9a", redmi9a_machine_init)
