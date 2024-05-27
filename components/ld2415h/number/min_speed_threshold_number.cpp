#include "min_speed_threshold_number.h"

namespace esphome {
namespace ld2415h {

void MinSpeedThresholdNumber::control(uint8_t speed) {
  this->publish_state(speed);
  this->parent_->set_min_speed_threshold(speed);
}

}  // namespace ld2415h
}  // namespace esphome
