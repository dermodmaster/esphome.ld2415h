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

MULTI_CONF = True

ld2415h_ns = cg.esphome_ns.namespace("ld2415h")
LD2415HComponent = ld2415h_ns.class_("LD2415HComponent", cg.Component, uart.UARTDevice)

CONF_LD2415H_ID = "ld2415h_id"

CONF_MIN_SPEED_THRESHOLD = "min_speed_threshold"
CONF_COMPENSATION_ANGLE = "compensation_angle"
CONF_SENSITIVITY = "sensitivity"
#CONF_TRACKING_MODE = "tracking_mode"
#CONF_SAMPLE_RATE = "sample_rate"
CONF_VIBRATION_CORRECTION = "vibration_correction"
CONF_RELAY_TRIGGER_DURATION = "relay_trigger_duration"
CONF_RELAY_TRIGGER_SPEED = "relay_trigger_speed"

CONFIG_SCHEMA = (
    cv.Schema(
        {
            cv.GenerateID(): cv.declare_id(LD2415HComponent),
            #cv.Optional(CONF_SPEED): sensor.sensor_schema(
            #    device_class=DEVICE_CLASS_SPEED,
            #    state_class=STATE_CLASS_MEASUREMENT,
            #    unit_of_measurement=UNIT_KILOMETER_PER_HOUR,
            #    icon="mdi:speedometer",
            #    accuracy_decimals=1,
            #),
            cv.Optional(CONF_MIN_SPEED_THRESHOLD, default=1): cv.int_range(1, 255),
            cv.Optional(CONF_COMPENSATION_ANGLE, default=0): cv.int_range(0, 255),
            cv.Optional(CONF_SENSITIVITY, default=5): cv.int_range(1, 255),
            #cv.Optional(CONF_TRACKING_MODE, default=1): cv.int_range(0, 2),
            #cv.Optional(CONF_SAMPLE_RATE, default=1): cv.int_range(0, 255),
            cv.Optional(CONF_VIBRATION_CORRECTION, default=5): cv.int_range(0, 112),
            cv.Optional(CONF_RELAY_TRIGGER_DURATION, default=3): cv.int_range(0, 255),
            cv.Optional(CONF_RELAY_TRIGGER_SPEED, default=1): cv.int_range(0, 255),
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

    #if speed := config.get(CONF_SPEED):
    #    sens = await sensor.new_sensor(speed)
    #    cg.add(var.set_speed_sensor(sens))

    cg.add(var.set_min_speed_threshold(config[CONF_MIN_SPEED_THRESHOLD]))
    cg.add(var.set_compensation_angle(config[CONF_COMPENSATION_ANGLE]))
    cg.add(var.set_sensitivity(config[CONF_SENSITIVITY]))
    #cg.add(var.set_tracking_mode(config[CONF_TRACKING_MODE]))
    #cg.add(var.set_sample_rate(config[CONF_SAMPLE_RATE]))
    cg.add(var.set_vibration_correction(config[CONF_VIBRATION_CORRECTION]))
    cg.add(var.set_relay_trigger_duration(config[CONF_RELAY_TRIGGER_DURATION]))
    cg.add(var.set_relay_trigger_speed(config[CONF_RELAY_TRIGGER_SPEED]))
