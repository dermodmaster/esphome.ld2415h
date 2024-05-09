#pragma once

#include "esphome/core/component.h"
#include "esphome/components/uart/uart.h"
#include "esphome/components/sensor/sensor.h"

namespace esphome {
namespace ld2415h {

class LD2415HComponent;

class LD2415HComponent : public PollingComponent, public uart::UARTDevice {
 public:
  float get_setup_priority() const override { return setup_priority::HARDWARE; }

  //LD2415HComponent() = default;

  void setup() override;
  void update() override;
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
  
  int min_speed_reported_ = 1;    // 1 km/h
  int angle_comp_ = 0;            // None
  int sensitivity_ = 0;           // High
  int tracking_mode_ = 1;         // Approaching
  int sample_rate_ = 0;           // 22 fps
  int unit_of_measure = 0;        // km/h
  int vibration_correction = 5;   // 0-112
  int relay_trigger_duration = 3; // 3 sec
  int relay_trigger_speed = 1;    // 1 km/h
  int negotiation_mode = 1;       // Custom Agreement


  sensor::Sensor *speed_sensor_{nullptr};
/*
  optional<bool> check_byte_() const;
*/

  uint8_t response_buffer_[64];
  uint8_t response_buffer_index_{0};

  bool fill_buffer_(uint8_t c);
  void clear_remaining_buffer_(uint8_t pos);
  void parse_buffer_();

  void parse_config_(uint8_t* c);
};

}  // namespace ld2415h
}  // namespace esphome