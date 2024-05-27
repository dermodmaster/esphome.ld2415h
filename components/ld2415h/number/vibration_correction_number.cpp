#include "vibration_correction_number.h"

namespace esphome {
namespace ld2415h {

void VibrationCorrectionNumber::control(float correction) {
  this->publish_state(correction);
  this->parent_->set_vibration_correction(correction);
}

}  // namespace ld2415h
}  // namespace esphome
