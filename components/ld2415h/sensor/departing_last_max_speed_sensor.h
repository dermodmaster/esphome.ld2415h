#pragma once

#include "../ld2415h.h"
#include "esphome/components/sensor/sensor.h"

namespace esphome {
namespace ld2415h {

class DepartingLastMaxSpeedSensor : public Component, public sensor::Sensor {
 public:
  void dump_config() override;
  void set_last_max_speed(double speed) {
    if (this->get_state() != speed) {
      this->publish_state(speed);
    }
  }
};

}  // namespace ld2415h
}  // namespace esphome