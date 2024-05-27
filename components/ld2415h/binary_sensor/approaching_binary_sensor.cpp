#include "approaching_binary_sensor.h"
#include "esphome/core/helpers.h"
#include "esphome/core/log.h"

namespace esphome {
namespace ld2415h {

static const char *const TAG = "LD2415H.approaching_binary_sensor";

void ApproachingBinarySensor::dump_config() {
  ESP_LOGCONFIG(TAG, "Approaching BinarySensor:");
  LOG_SENSOR("  ", "Approaching", this->approaching_binary_sensor_);
}

}  // namespace ld2415h
}  // namespace esphome
