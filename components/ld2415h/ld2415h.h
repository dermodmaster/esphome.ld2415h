#pragma once

#include "esphome/core/component.h"
#include "esphome/components/uart/uart.h"
#include "esphome/components/sensor/sensor.h"

namespace esphome {
namespace ld2415h {

enum class TrackingMode {
  ApproachingAndRetreating = 0x00,
  Approaching = 0x01,
  Restreating = 0x02
};

enum class UnitOfMeasure {
  kph = 0x00,
  mph = 0x01,
  mps = 0x02
};

enum class NegotiationMode {
  CustomAgreement = 0x01,
  StandardProtocol = 0x02
};



class LD2415HComponent;

class LD2415HComponent : public Component, public uart::UARTDevice {
 public:
  float get_setup_priority() const override { return setup_priority::HARDWARE; }

  void setup() override;
  //void update() override;
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
  
  uint8_t min_speed_reported_ = 1;
  uint8_t angle_comp_ = 0;
  uint8_t sensitivity_ = 0;
  TrackingMode tracking_mode_ = TrackingMode::Approaching;
  uint8_t sample_rate_ = 0;
  UnitOfMeasure unit_of_measure_ = UnitOfMeasure::kph;
  uint8_t vibration_correction_ = 5;
  uint8_t relay_trigger_duration_ = 3;
  uint8_t relay_trigger_speed_ = 1;
  NegotiationMode negotiation_mode_ = NegotiationMode::CustomAgreement;

  char firmware_[20] = "";
  float velocity_ = 0;
  bool approaching_ = 1;

  char response_buffer_[64];
  uint8_t response_buffer_index_ = 0;

  void issue_command_(const uint8_t cmd[], const uint8_t size);
  bool fill_buffer_(char c);
  void clear_remaining_buffer_(uint8_t pos);
  void parse_buffer_();
  void parse_config_();
  void parse_firmware_();
  void parse_velocity_();
  void parse_config_param_(char* key, char* value);
};

}  // namespace ld2415h
}  // namespace esphome