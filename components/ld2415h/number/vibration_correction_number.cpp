#include "vibration_correction_number.h"

namespace esphome {
namespace ld2415h {

VibrationCorrectionNumber::VibrationCorrectionNumber(uint8_t correction) : correction_(correction) {}

void VibrationCorrectionNumber::control(uint8_t correction) {
  this->publish_state(correction);
  this->parent_->set_vibration_correction(this->correction_);
}

}  // namespace ld2415h
}  // namespace esphome
