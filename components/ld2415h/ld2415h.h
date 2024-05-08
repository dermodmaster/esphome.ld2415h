#pragma once

#include "esphome/core/component.h"
#include "esphome/components/uart/uart.h"
#include "esphome/components/sensor/sensor.h"

namespace esphome {
namespace ld2415h {

class LD2415HComponent : public PollingComponent, public uart::UARTDevice {
 public:
  //LD2415HComponent() = default;

  void setup() override;
  //void update() override;
  float get_setup_priority() const override;
  void dump_config() override;
  void loop() override;

  void set_speed_sensor(sensor::Sensor *speed_sensor) { this->speed_sensor_ = speed_sensor; }

/*
  void on_speed(uint16_t speed) override {
    if (this->speed_sensor_ != nullptr) {
      if (this->speed_sensor_->get_state() != speed) {
        this->speed_sensor_->publish_state(speed);
      }
    }
  }
*/


 protected:
  sensor::Sensor *speed_sensor_{nullptr};
/*
  optional<bool> check_byte_() const;
*/

  uint8_t response_buffer_[64];
  uint8_t response_buffer_index_{0};

  void parse_buffer_();
  bool parse_(char c);
};

}  // namespace ld2415h
}  // namespace esphome