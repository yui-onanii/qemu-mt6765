#ifndef MT6765_H
#define MT6765_H

#include "hw/qdev-core.h"
#include "target/arm/cpu.h"
#include "qom/object.h"

#define TYPE_MT6765 "mt6765"

OBJECT_DECLARE_SIMPLE_TYPE(Mt6765State, MT6765)

struct Mt6765State {
    /*< private >*/
    DeviceState parent_obj;
    /*< public >*/

    ARMCPU cpu;
};

#endif
