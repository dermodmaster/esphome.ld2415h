import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import uart, sensor
from esphome.const import (
    CONF_ID,
    CONF_SPEED,
    DEVICE_CLASS_SPEED, 
    STATE_CLASS_MEASUREMENT,
    UNIT_KILOMETER_PER_HOUR,
)

CODEOWNERS = ["@cptskippy"]

DEPENDENCIES = ["uart"]

ld2415h_ns = cg.esphome_ns.namespace("ld2415h")
LD2415HComponent = ld2415h_ns.class_("LD2415HComponent", cg.Component, uart.UARTDevice)


#LD2415HSensor = ld2415h_ns.class_("LD2415HSensor", sensor.Sensor, cg.Component)

#CONF_OBJECT_SPEED = "object_speed"

CONFIG_SCHEMA = (
    cv.Schema(
        {
            cv.GenerateID(): cv.declare_id(LD2415HComponent),
            cv.Optional(CONF_SPEED): sensor.sensor_schema(
                unit_of_measurement=UNIT_KILOMETER_PER_HOUR,
                accuracy_decimals=1,
                device_class=DEVICE_CLASS_SPEED,
                state_class=STATE_CLASS_MEASUREMENT,
                icon="mdi:speedometer",
            ),
        }   
    )
    .extend(uart.UART_DEVICE_SCHEMA)
    .extend(cv.COMPONENT_SCHEMA)
)

FINAL_VALIDATE_SCHEMA = uart.final_validate_device_schema(
    "ld2415h_uart",
    require_tx=True,
    require_rx=True,
    parity="NONE",
    stop_bits=1,
)


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await uart.register_uart_device(var, config)

    #if CONF_OBJECT_SPEED in config:
    #    sens = await sensor.new_sensor(config[CONF_OBJECT_SPEED])
    #    cg.add(var.set_speed_sensor(sens))

    if speed := config.get(CONF_SPEED):
        sens = await sensor.new_sensor(speed)
        cg.add(var.set_speed_sensor(sens))

    #ld2415h = await cg.get_variable(config[CONF_LD2415H_ID])
    #cg.add(ld2415h.register_listener(var))
