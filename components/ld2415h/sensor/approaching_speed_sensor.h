#pragma once

#include "../ld2415h.h"
#include "esphome/components/sensor/sensor.h"

namespace esphome {
namespace ld2415h {

class ApproachingSpeedSensor : public Component, public sensor::Sensor {
 public:
  void dump_config() override;
  void publish_speed(double speed) {
    this->publish_state(speed);
  }
};

}  // namespace ld2415h
}  // namespace esphome