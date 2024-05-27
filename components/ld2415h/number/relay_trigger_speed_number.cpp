#include "relay_trigger_speed_number.h"

namespace esphome {
namespace ld2415h {

void RelayTriggerSpeedNumber::control(uint8_t speed) {
  this->publish_state(speed);
  this->parent_->set_relay_trigger_speed(speed);
}

}  // namespace ld2415h
}  // namespace esphome
