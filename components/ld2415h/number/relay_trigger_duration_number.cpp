#include "relay_trigger_duration_number.h"

namespace esphome {
namespace ld2415h {

void RelayTriggerDurationNumber::control(uint8_t duration) {
  this->publish_state(duration);
  this->parent_->set_relay_trigger_duration(duration);
}

}  // namespace ld2415h
}  // namespace esphome
