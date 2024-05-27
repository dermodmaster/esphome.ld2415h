#include "compensation_angle_number.h"

namespace esphome {
namespace ld2415h {

void CompensationAngleNumber::control(float angle) {
  this->publish_state(angle);
  this->parent_->set_compensation_angle(angle);
}

}  // namespace ld2415h
}  // namespace esphome
