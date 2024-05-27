#include "sensitivity_number.h"

namespace esphome {
namespace ld2415h {

void SensitivityNumber::control(uint8_t sensitivity) {
  this->publish_state(sensitivity);
  this->parent_->set_sensitivity(sensitivity);
}

}  // namespace ld2415h
}  // namespace esphome
