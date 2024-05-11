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
AUTO_LOAD = ["sensor"]

ld2415h_ns = cg.esphome_ns.namespace("ld2415h")
LD2415HComponent = ld2415h_ns.class_("LD2415HComponent", cg.Component, uart.UARTDevice)

CONFIG_SCHEMA = (
    cv.Schema(
        {
            cv.GenerateID(): cv.declare_id(LD2415HComponent),
            cv.Optional(CONF_SPEED): sensor.sensor_schema(
                device_class=DEVICE_CLASS_SPEED,
                state_class=STATE_CLASS_MEASUREMENT,
                unit_of_measurement=UNIT_KILOMETER_PER_HOUR,
                icon="mdi:speedometer",
                accuracy_decimals=1,
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

    if speed := config.get(CONF_SPEED):
        sens = await sensor.new_sensor(speed)
        cg.add(var.set_speed_sensor(sens))