#pragma once

#include "esphome/components/number/number.h"
#include "../ld2415h.h"

namespace esphome {
namespace ld2415h {

class CompensationAngleNumber : public number::Number, public Parented<LD2415HComponent> {
 public:
  CompensationAngleNumber(uint8_t angle);

 protected:
  uint8_t angle_;
  void control(uint8_t angle) override;
};

}  // namespace ld2415h
}  // namespace esphome
