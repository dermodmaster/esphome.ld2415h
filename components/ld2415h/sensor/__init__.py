import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import sensor
from esphome.const import CONF_ID, DEVICE_CLASS_SPEED, UNIT_KILOMETER_PER_HOUR
from .. import ld2415h_ns, LD2415HComponent, CONF_LD2415H_ID

LD2415HSensor = ld2415h_ns.class_("LD2415HSensor", sensor.Sensor, cg.Component)

CONF_OBJECT_SPEED = "object_speed"

CONFIG_SCHEMA = cv.All(
    cv.COMPONENT_SCHEMA.extend(
        {
            cv.GenerateID(): cv.declare_id(LD2415HSensor),
            cv.GenerateID(CONF_LD2415H_ID): cv.use_id(LD2415HComponent),
            cv.Optional(CONF_OBJECT_SPEED): sensor.sensor_schema(
                device_class=DEVICE_CLASS_SPEED,
                unit_of_measurement=UNIT_KILOMETER_PER_HOUR,
                accuracy_decimals=1,
                icon="mdi:speedometer",
            ),
        }
    ),
)


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    if CONF_OBJECT_SPEED in config:
        sens = await sensor.new_sensor(config[CONF_OBJECT_SPEED])
        cg.add(var.set_speed_sensor(sens))
    ld2415h = await cg.get_variable(config[CONF_LD2415H_ID])
    cg.add(ld2415h.register_listener(var))
