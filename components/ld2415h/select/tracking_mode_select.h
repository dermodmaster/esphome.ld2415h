#pragma once

#include "esphome/components/select/select.h"
#include "../ld2415h.h"

namespace esphome {
namespace ld2415h {

class TrackingModeSelect : public Component, select::Select, public Parented<LD2415HComponent> {
 public:
  TrackingModeSelect() = default;

 protected:
  void control(const std::string &value) override;
};

}  // namespace ld2415h
}  // namespace esphome
