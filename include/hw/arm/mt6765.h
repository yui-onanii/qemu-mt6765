#ifndef MT6765_H
#define MT6765_H

#include "exec/hwaddr.h"
#include "hw/qdev-core.h"
#include "target/arm/cpu.h"
#include "qom/object.h"

#define TYPE_MT6765 "mt6765"

/* memory-mapped peripheral I/O (MMIO) */
enum {
    MT6765_DEV_SDRAM,
};

OBJECT_DECLARE_SIMPLE_TYPE(Mt6765State, MT6765)

struct Mt6765State {
    /*< private >*/
    DeviceState parent_obj;
    /*< public >*/

    ARMCPU cpu;
    const hwaddr *memmap;
};

#endif
