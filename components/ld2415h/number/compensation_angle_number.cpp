#include "compensation_angle_number.h"

namespace esphome {
namespace ld2415h {

CompensationAngleNumber::CompensationAngleNumber(uint8_t angle) : angle_(angle) {}

void CompensationAngleNumber::control(uint8_t angle) {
  this->publish_state(angle);
  this->parent_->set_compensation_angle(this->angle_);
}

}  // namespace ld2415h
}  // namespace esphome
