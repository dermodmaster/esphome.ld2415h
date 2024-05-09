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
  sensor::Sensor *speed_sensor_{nullptr};
  
  uint8_t min_speed_reported_ = 1;    // 1 km/h
  uint8_t angle_comp_ = 0;            // None
  uint8_t sensitivity_ = 0;           // High
  uint8_t tracking_mode_ = 1;         // Approaching
  uint8_t sample_rate_ = 0;           // 22 fps
  uint8_t unit_of_measure = 0;        // km/h
  uint8_t vibration_correction = 5;   // 0-112
  uint8_t relay_trigger_duration = 3; // 3 sec
  uint8_t relay_trigger_speed = 1;    // 1 km/h
  uint8_t negotiation_mode = 1;       // Custom Agreement

  char* firmware = nullptr;
  float velocity = 0;
  bool approaching = 1;

  char response_buffer_[64];
  uint8_t response_buffer_index_{0};

  void issue_command_(const uint8_t cmd[], const uint8_t size);
  bool fill_buffer_(char c);
  void clear_remaining_buffer_(uint8_t pos);
  void parse_buffer_();
  void parse_config_();
  void parse_firmware_();
  void parse_velocity_();
  void render_config_(char* key, char* value);
};

}  // namespace ld2415h
}  // namespace esphome