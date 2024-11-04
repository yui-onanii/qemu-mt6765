#include "qemu/osdep.h"
#include "hw/qdev-core.h"
#include "hw/arm/mt6765.h"
#include "qom/object.h"

static const TypeInfo mt6765_types[] = {
    {
        .name   = TYPE_MT6765,
        .parent = TYPE_DEVICE,
    },
};

DEFINE_TYPES(mt6765_types)
