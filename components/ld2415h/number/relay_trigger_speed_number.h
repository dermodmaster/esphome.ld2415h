#pragma once

#include "esphome/components/number/number.h"
#include "../ld2415h.h"

namespace esphome {
namespace ld2415h {

class RelayTriggerSpeedNumber : public number::Number, public Parented<LD2415HComponent> {
 public:
  RelayTriggerSpeedNumber() = default;

 protected:
  void control(float speed) override;
};

}  // namespace ld2415h
}  // namespace esphome
