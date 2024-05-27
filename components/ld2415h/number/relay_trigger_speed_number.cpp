#include "relay_trigger_speed_number.h"

namespace esphome {
namespace ld2415h {

RelayTriggerSpeedNumber::RelayTriggerSpeedNumber(uint8_t speed) : speed_(speed) {}

void RelayTriggerSpeedNumber::control(uint8_t speed) {
  this->publish_state(speed);
  this->parent_->set_relay_trigger_speed(this->speed_);
}

}  // namespace ld2415h
}  // namespace esphome
