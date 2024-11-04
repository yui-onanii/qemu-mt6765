#include "qemu/osdep.h"
#include "qapi/error.h"
#include "hw/qdev-core.h"
#include "hw/boards.h"
#include "hw/arm/mt6765.h"
#include "target/arm/cpu-qom.h"
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
    static const char * const valid_cpu_types[] = {
        ARM_CPU_TYPE_NAME("cortex-a53"),
        NULL
    };

    mc->desc = "Xiaomi Redmi 9A (MT6762G)";
    mc->init = redmi9a_init;  // must have
    // FIXME: {min,max,default}_cpus omitted as 1
    // default_cpu_type defaults to the only valid one
    mc->valid_cpu_types = valid_cpu_types;
}

DEFINE_MACHINE("redmi9a", redmi9a_machine_init)
