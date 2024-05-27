#include "sensitivity_number.h"

namespace esphome {
namespace ld2415h {

SensitivityNumber::SensitivityNumber(uint8_t sensitivity) : sensitivity_(sensitivity) {}

void SensitivityNumber::control(uint8_t sensitivity) {
  this->publish_state(sensitivity);
  this->parent_->set_sensitivity(this->sensitivity_);
}

}  // namespace ld2415h
}  // namespace esphome
