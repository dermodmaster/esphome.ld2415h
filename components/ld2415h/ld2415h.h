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

//class LD2415HComponent;

class LD2415HComponent : public Component, public uart::UARTDevice {
 public:
  LD2415HComponent() 
    : cmd_speed_angle_sense_    {0x43, 0x46, 0x01, 0x01, 0x00, 0x05, 0x0d, 0x0a},
      cmd_mode_rate_uom_        {0x43, 0x46, 0x02, 0x01, 0x01, 0x00, 0x0d, 0x0a},
      cmd_anti_vib_comp_        {0x43, 0x46, 0x03, 0x05, 0x00, 0x00, 0x0d, 0x0a},
      cmd_relay_duration_speed_ {0x43, 0x46, 0x04, 0x03, 0x01, 0x00, 0x0d, 0x0a},
      cmd_config_               {0x43, 0x46, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
      {}

  float get_setup_priority() const override { return setup_priority::HARDWARE; }

  void setup() override;
  void dump_config() override;
  void loop() override;

  void set_speed_sensor(sensor::Sensor *speed_sensor) { this->speed_sensor_ = speed_sensor; }

  void set_min_speed_threshold(uint8_t speed);
  void set_compensation_angle(uint8_t angle);
  void set_sensitivity(uint8_t sensitivity);
  void set_tracking_mode(TrackingMode mode);
  void set_tracking_mode(uint8_t mode);
  void set_sample_rate(uint8_t rate);
  void set_vibration_correction(uint8_t correction);
  void set_relay_trigger_duration(uint8_t duration);
  void set_relay_trigger_speed(uint8_t speed);  
  
 protected:
  sensor::Sensor *speed_sensor_{nullptr};

  // Configuration  
  uint8_t min_speed_threshold_ = 0;
  uint8_t compensation_angle_ = 0;
  uint8_t sensitivity_ = 0;
  TrackingMode tracking_mode_ = TrackingMode::APPROACHING_AND_RETREATING;
  uint8_t sample_rate_ = 0;
  UnitOfMeasure unit_of_measure_ = UnitOfMeasure::KPH;
  uint8_t vibration_correction_ = 0;
  uint8_t relay_trigger_duration_ = 0;
  uint8_t relay_trigger_speed_ = 0;
  NegotiationMode negotiation_mode_ = NegotiationMode::CUSTOM_AGREEMENT;

  // State
  uint8_t cmd_speed_angle_sense_[8];
  uint8_t cmd_mode_rate_uom_[8];
  uint8_t cmd_anti_vib_comp_[8];
  uint8_t cmd_relay_duration_speed_[8];
  uint8_t cmd_config_[8];

  bool update_speed_angle_sense_ = false;
  bool update_mode_rate_uom_ = false;
  bool update_anti_vib_comp_ = false;
  bool update_relay_duration_speed_ = false;
  bool update_config_ = false;

  char firmware_[20] = "";
  float speed_ = 0;
  bool approaching_ = 1;
  char response_buffer_[64];
  uint8_t response_buffer_index_ = 0;

  // Processing
  void issue_command_(const uint8_t cmd[], const uint8_t size);
  bool fill_buffer_(char c);
  void clear_remaining_buffer_(uint8_t pos);
  void parse_buffer_();
  void parse_config_();
  void parse_firmware_();
  void parse_speed_();
  void parse_config_param_(char* key, char* value);

  // Helpers
  TrackingMode i_to_TrackingMode_(uint8_t value);
  UnitOfMeasure i_to_UnitOfMeasure_(uint8_t value);
  NegotiationMode i_to_NegotiationMode_(uint8_t value);
  const char* TrackingMode_to_s_(TrackingMode value);
  const char* UnitOfMeasure_to_s_(UnitOfMeasure value);
  const char* NegotiationMode_to_s_(NegotiationMode value);

};

}  // namespace ld2415h
}  // namespace esphome