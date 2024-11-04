#include "qemu/osdep.h"
#include "qemu/units.h"
#include "qapi/error.h"
#include "exec/address-spaces.h"
#include "exec/memory.h"
#include "hw/qdev-core.h"
#include "hw/boards.h"
#include "hw/arm/boot.h"
#include "hw/arm/mt6765.h"
#include "target/arm/cpu-qom.h"
#include "qom/object.h"

static struct arm_boot_info redmi9a_binfo;

static void redmi9a_init(MachineState *machine)
{
    Mt6765State *mt6762g;

    // (almost) identical SoCs with slightly slower clock
    mt6762g = MT6765(qdev_new(TYPE_MT6765));
    object_property_add_child(OBJECT(machine), "soc", OBJECT(mt6762g));
    qdev_realize_and_unref(DEVICE(mt6762g), NULL, &error_fatal);

    // mount SDRAM to its location
    memory_region_add_subregion(get_system_memory(),
                                mt6762g->memmap[MT6765_DEV_SDRAM],
                                machine->ram);

    redmi9a_binfo.ram_size = machine->ram_size;
    redmi9a_binfo.loader_start = mt6762g->memmap[MT6765_DEV_SDRAM];
    // this also loads DTB, and overriding the /memory node appropriately
    arm_load_kernel(&mt6762g->cpu, machine, &redmi9a_binfo);
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
    mc->default_ram_size = 4 * GiB;
    mc->default_ram_id = "redmi9a.ram";  // needed for some reason
}

DEFINE_MACHINE("redmi9a", redmi9a_machine_init)
