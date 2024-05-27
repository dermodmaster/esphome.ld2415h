import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import binary_sensor
from esphome.const import (
    CONF_ID,
    CONF_BINARY_SENSOR,
)
from .. import ld2415h_ns, LD2415HComponent, CONF_LD2415H_ID

ApproachingBinarySensor = ld2415h_ns.class_(
    "ApproachingBinarySensor", binary_sensor.BinarySensor
)

CONFIG_SCHEMA = cv.All(
    cv.COMPONENT_SCHEMA.extend(
        {
            cv.GenerateID(): cv.declare_id(ApproachingBinarySensor),
            cv.GenerateID(CONF_LD2415H_ID): cv.use_id(LD2415HComponent),
            cv.Optional(CONF_BINARY_SENSOR): binary_sensor.binary_sensor_schema(
                ApproachingBinarySensor,
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
