#pragma once

#include "../ld2415h.h"
#include "esphome/components/binary_sensor/binary_sensor.h"

namespace esphome {
namespace ld2415h {

class LD2415HBinarySensor : public LD2415HListener, public Component, binary_sensor::BinarySensor {
 public:
  void dump_config() override;
  void set_approaching_sensor(sensor::BinarySensor *binary_sensor) { 
    this->approaching_binary_sensor_ = binary_sensor; 
  }
  void on_approach(bool approaching) override {
    if (this->approaching_binary_sensor_ != nullptr) {
      if (this->approaching_binary_sensor_->get_state() != approaching) {
        this->approaching_binary_sensor_->publish_state(approaching);
      }
    }
  }

 protected:
  binary_sensor::BinarySensor *approaching_binary_sensor_{nullptr};
};

}  // namespace ld2415h
}  // namespace esphome
