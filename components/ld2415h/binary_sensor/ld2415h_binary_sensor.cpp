#include "ld2415h_binary_sensor.h"
#include "esphome/core/helpers.h"
#include "esphome/core/log.h"

namespace esphome {
namespace ld2415h {

static const char *const TAG = "LD2415H.binary_sensor";

void LD2415HBinarySensor::dump_config() {
  ESP_LOGCONFIG(TAG, "LD2415H Binary Sensor:");
  LOG_BINARY_SENSOR("  ", "Approaching", this->approaching_binary_sensor_);
}

}  // namespace ld2415h
}  // namespace esphome
