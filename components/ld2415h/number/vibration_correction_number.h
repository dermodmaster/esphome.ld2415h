#pragma once

#include "esphome/components/number/number.h"
#include "../ld2415h.h"

namespace esphome {
namespace ld2415h {

class VibrationCorrectionNumber : public number::Number, public Parented<LD2415HComponent> {
 public:
  VibrationCorrectionNumber(uint8_t correction);

 protected:
  uint8_t correction_;
  void control(uint8_t correction) override;
};

}  // namespace ld2415h
}  // namespace esphome
