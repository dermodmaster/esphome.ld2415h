#include "tracking_mode_select.h"

namespace esphome {
namespace ld2415h {

void TrackingModeSelect::control(const std::string &value) {
  this->publish_state(value);
  this->parent_->set_tracking_mode(state);
}

}  // namespace ld2415h
}  // namespace esphome
