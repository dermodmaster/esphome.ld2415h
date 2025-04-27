import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import sensor
from esphome.const import (
    CONF_ID,
    CONF_SPEED,
    DEVICE_CLASS_SPEED,
    STATE_CLASS_MEASUREMENT,
    UNIT_KILOMETER_PER_HOUR,
)
from .. import ld2415h_ns, LD2415HComponent, CONF_LD2415H_ID

SpeedSensor = ld2415h_ns.class_("SpeedSensor", sensor.Sensor)
ApproachingSpeedSensor = ld2415h_ns.class_("ApproachingSpeedSensor", sensor.Sensor)
DepartingSpeedSensor = ld2415h_ns.class_("DepartingSpeedSensor", sensor.Sensor)
ApproachingLastMaxSpeedSensor = ld2415h_ns.class_("ApproachingLastMaxSpeedSensor", sensor.Sensor)
DepartingLastMaxSpeedSensor = ld2415h_ns.class_("DepartingLastMaxSpeedSensor", sensor.Sensor)
VelocitySensor = ld2415h_ns.class_("VelocitySensor", sensor.Sensor)

ICON_SPEEDOMETER = "mdi:speedometer"

CONF_APPROACHING_SPEED = "approaching_speed"
CONF_DEPARTING_SPEED = "departing_speed"
CONF_APPROACHING_LAST_MAX_SPEED = "approaching_last_max_speed"
CONF_DEPARTING_LAST_MAX_SPEED = "departing_last_max_speed"
CONF_VELOCITY = "velocity"

CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.declare_id(LD2415HComponent),
    cv.Required(CONF_LD2415H_ID): cv.use_id(LD2415HComponent),
    cv.Optional(CONF_SPEED): sensor.sensor_schema(
        SpeedSensor,
        device_class=DEVICE_CLASS_SPEED,
        state_class=STATE_CLASS_MEASUREMENT,
        unit_of_measurement=UNIT_KILOMETER_PER_HOUR,
        icon=ICON_SPEEDOMETER,
        accuracy_decimals=1,
    ),
    cv.Optional(CONF_APPROACHING_SPEED): sensor.sensor_schema(
        ApproachingSpeedSensor,
        device_class=DEVICE_CLASS_SPEED,
        state_class=STATE_CLASS_MEASUREMENT,
        unit_of_measurement=UNIT_KILOMETER_PER_HOUR,
        icon=ICON_SPEEDOMETER,
        accuracy_decimals=1,
    ),
    cv.Optional(CONF_DEPARTING_SPEED): sensor.sensor_schema(
        DepartingSpeedSensor,
        device_class=DEVICE_CLASS_SPEED,
        state_class=STATE_CLASS_MEASUREMENT,
        unit_of_measurement=UNIT_KILOMETER_PER_HOUR,
        icon=ICON_SPEEDOMETER,
        accuracy_decimals=1,
    ),
    cv.Optional(CONF_APPROACHING_LAST_MAX_SPEED): sensor.sensor_schema(
        ApproachingLastMaxSpeedSensor,
        device_class=DEVICE_CLASS_SPEED,
        state_class=STATE_CLASS_MEASUREMENT,
        unit_of_measurement=UNIT_KILOMETER_PER_HOUR,
        icon=ICON_SPEEDOMETER,
        accuracy_decimals=1,
    ),
    cv.Optional(CONF_DEPARTING_LAST_MAX_SPEED): sensor.sensor_schema(
        DepartingLastMaxSpeedSensor,
        device_class=DEVICE_CLASS_SPEED,
        state_class=STATE_CLASS_MEASUREMENT,
        unit_of_measurement=UNIT_KILOMETER_PER_HOUR,
        icon=ICON_SPEEDOMETER,
        accuracy_decimals=1,
    ),
    cv.Optional(CONF_VELOCITY): sensor.sensor_schema(
        VelocitySensor,
        device_class=DEVICE_CLASS_SPEED,
        state_class=STATE_CLASS_MEASUREMENT,
        unit_of_measurement=UNIT_KILOMETER_PER_HOUR,
        icon=ICON_SPEEDOMETER,
        accuracy_decimals=1,
    ),
}).extend(cv.COMPONENT_SCHEMA)



#async def to_code(config):
#    var = cg.new_Pvariable(config[CONF_ID])
#    await cg.register_component(var, config)
#    if speed := config.get(CONF_SPEED):
#        sens = await sensor.new_sensor(speed)
#        cg.add(var.set_speed_sensor(sens))
#    ld2415h = await cg.get_variable(config[CONF_LD2415H_ID])
#    cg.add(ld2415h.register_listener(var))


async def to_code(config):
    ld2415h_component = await cg.get_variable(config[CONF_LD2415H_ID])
    #var = cg.new_Pvariable(config[CONF_ID])
    #await cg.register_component(var, config)

    if speed := config.get(CONF_SPEED):
        sens = await sensor.new_sensor(speed)
        await cg.register_parented(sens, config[CONF_LD2415H_ID])
        cg.add(ld2415h_component.set_speed_sensor(sens))

    if approaching_speed := config.get(CONF_APPROACHING_SPEED):
        sens = await sensor.new_sensor(approaching_speed)
        await cg.register_parented(sens, config[CONF_LD2415H_ID])
        cg.add(ld2415h_component.set_approaching_speed_sensor(sens))

    if departing_speed := config.get(CONF_DEPARTING_SPEED):
        sens = await sensor.new_sensor(departing_speed)
        await cg.register_parented(sens, config[CONF_LD2415H_ID])
        cg.add(ld2415h_component.set_departing_speed_sensor(sens))

    if approaching_last_max_speed := config.get(CONF_APPROACHING_LAST_MAX_SPEED):
        sens = await sensor.new_sensor(approaching_last_max_speed)
        await cg.register_parented(sens, config[CONF_LD2415H_ID])
        cg.add(ld2415h_component.set_approaching_last_max_speed_sensor(sens))

    if departing_last_max_speed := config.get(CONF_DEPARTING_LAST_MAX_SPEED):
        sens = await sensor.new_sensor(departing_last_max_speed)
        await cg.register_parented(sens, config[CONF_LD2415H_ID])
        cg.add(ld2415h_component.set_departing_last_max_speed_sensor(sens))

    if velocity := config.get(CONF_VELOCITY):
        sens = await sensor.new_sensor(velocity)
        await cg.register_parented(sens, config[CONF_LD2415H_ID])
        cg.add(ld2415h_component.set_velocity_sensor(sens))

    #cg.add(ld2415h_component.register_listener(var))
