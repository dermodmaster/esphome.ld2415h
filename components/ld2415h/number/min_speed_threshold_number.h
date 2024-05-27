#pragma once

#include "esphome/components/number/number.h"
#include "../ld2415h.h"

namespace esphome {
namespace ld2415h {

class MinSpeedThresholdNumber : public number::Number, public Parented<LD2415HComponent> {
 public:
  MinSpeedThresholdNumber(uint8_t speed);

 protected:
  uint8_t speed_;
  void control(uint8_t speed) override;
};

}  // namespace ld2415h
}  // namespace esphome
