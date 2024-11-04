#include "qemu/osdep.h"
#include "qapi/error.h"
#include "hw/qdev-core.h"
#include "hw/arm/mt6765.h"
#include "qom/object.h"
#include "target/arm/cpu-qom.h"

static void mt6765_init(Object *obj)
{
    Mt6765State *s = MT6765(obj);

    // TODO: Add all 8 cores
    object_initialize_child(obj, "cpu", &s->cpu,
                            ARM_CPU_TYPE_NAME("cortex-a53"));
}

static void mt6765_realize(DeviceState *dev, Error **errp)
{
    Mt6765State *s = MT6765(dev);

    qdev_realize(DEVICE(&s->cpu), NULL, &error_fatal);
}

static void mt6765_class_init(ObjectClass *oc, void *data)
{
    DeviceClass *dc = DEVICE_CLASS(oc);

    dc->realize = mt6765_realize;
}

static const TypeInfo mt6765_types[] = {
    {
        .name           = TYPE_MT6765,
        .parent         = TYPE_DEVICE,
        .instance_size  = sizeof(Mt6765State),
        .instance_init  = mt6765_init,
        .class_init     = mt6765_class_init,
    },
};

DEFINE_TYPES(mt6765_types)
