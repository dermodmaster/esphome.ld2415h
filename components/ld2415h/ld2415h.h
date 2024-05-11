#pragma once

#include "esphome/core/component.h"
#include "esphome/components/uart/uart.h"
#include "esphome/components/sensor/sensor.h"

namespace esphome {
namespace ld2415h {

enum class TrackingMode {
  APPROACHING_AND_RETREATING = 0x00,
  APPROACHING = 0x01,
  RETREATING = 0x02
};

enum class UnitOfMeasure {
  KPH = 0x00,
  MPH = 0x01,
  MPS = 0x02
};

enum class NegotiationMode {
  CUSTOM_AGREEMENT = 0x01,
  STANDARD_PROTOCOL = 0x02
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
  
  uint8_t min_speed_reported_ = 0;
  uint8_t angle_comp_ = 0;
  uint8_t sensitivity_ = 0;
  TrackingMode tracking_mode_ = TrackingMode::APPROACHING_AND_RETREATING;
  uint8_t sample_rate_ = 0;
  UnitOfMeasure unit_of_measure_ = UnitOfMeasure::KPH;
  uint8_t vibration_correction_ = 0;
  uint8_t relay_trigger_duration_ = 0;
  uint8_t relay_trigger_speed_ = 0;
  NegotiationMode negotiation_mode_ = NegotiationMode::CUSTOM_AGREEMENT;

  char firmware_[20] = "";
  float speed_ = 0;
  bool approaching_ = 1;

  char response_buffer_[64];
  uint8_t response_buffer_index_ = 0;

  void issue_command_(const uint8_t cmd[], const uint8_t size);
  bool fill_buffer_(char c);
  void clear_remaining_buffer_(uint8_t pos);
  void parse_buffer_();
  void parse_config_();
  void parse_firmware_();
  void parse_speed_();
  void parse_config_param_(char* key, char* value);

  TrackingMode i_to_TrackingMode_(uint8_t value);
  const char* TrackingMode_to_s_(TrackingMode value);
  UnitOfMeasure i_to_UnitOfMeasure_(uint8_t value);
  const char* UnitOfMeasure_to_s_(UnitOfMeasure value);
  NegotiationMode i_to_NegotiationMode_(uint8_t value);
  const char* NegotiationMode_to_s_(NegotiationMode value);

};

}  // namespace ld2415h
}  // namespace esphome