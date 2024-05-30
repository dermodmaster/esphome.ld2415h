import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import binary_sensor
from esphome.const import (
    CONF_ID,
    CONF_BINARY_SENSOR,
    DEVICE_CLASS_MOVING,
    STATE_CLASS_MEASUREMENT,
)
from .. import ld2415h_ns, LD2415HComponent, CONF_LD2415H_ID

LD2415HBinarySensor = ld2415h_ns.class_(
    "LD2415HBinarySensor", binary_sensor.BinarySensor, cg.Component
)

ICON_APPROACHING = "mdi:arrow-left-right"

CONFIG_SCHEMA = cv.All(
    cv.COMPONENT_SCHEMA.extend(
        {
            cv.GenerateID(): cv.declare_id(LD2415HBinarySensor),
            cv.GenerateID(CONF_LD2415H_ID): cv.use_id(LD2415HComponent),
            cv.Optional(CONF_BINARY_SENSOR): binary_sensor.binary_sensor_schema(
                device_class=DEVICE_CLASS_MOVING,
                state_class=STATE_CLASS_MEASUREMENT,
                icon=ICON_APPROACHING,
            ),
        }
    ),
)


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    if approaching := config.get(CONF_BINARY_SENSOR):
        sens = await binary_sensor.new_binary_sensor(approaching)
        cg.add(var.set_approaching_sensor(sens))
    ld2415h = await cg.get_variable(config[CONF_LD2415H_ID])
    cg.add(ld2415h.register_listener(var))
