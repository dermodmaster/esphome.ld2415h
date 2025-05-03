#pragma once
#include "esphome/components/number/number.h"
#include "../ld2415h.h"

namespace esphome {
namespace ld2415h {

class TimeoutDurationNumber : public number::Number, public Parented<LD2415HComponent> {
 protected:
  void control(float ms) override {
    this->publish_state(ms);
    this->parent_->set_timeout_duration((uint32_t)ms);
  }
};

}  // namespace ld2415h
}  // namespace esphome
