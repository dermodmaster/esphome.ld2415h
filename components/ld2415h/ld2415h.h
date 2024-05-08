#pragma once

#include "esphome/core/component.h"
#include "esphome/components/uart/uart.h"
#include "esphome/components/sensor/sensor.h"

namespace esphome {
namespace ld2415h {

class LD2415HComponent : public PollingComponent, public uart::UARTDevice {
 public:
  LD2415HComponent() = default;

  void set_speed_sensor(sensor::Sensor *speed_sensor) { this->speed_sensor_ = speed_sensor; }
  void setup() override;
  void dump_config() override;
  void loop() override;
  void update() override;

  float get_setup_priority() const override;

 protected:
  optional<bool> check_byte_() const;
  void parse_data_();
  
  sensor::Sensor *speed_sensor_{nullptr};

  uint8_t data_[20];
  uint8_t data_index_{0};
  uint32_t last_transmission_{0};
};

}  // namespace ld2415h
}  // namespace esphome