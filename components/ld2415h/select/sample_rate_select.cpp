#include "sample_rate_select.h"

namespace esphome {
namespace ld2415h {

void SampleRateSelect::control(const std::string &value) {
  this->publish_state(value);
  this->parent_->set_sample_rate(state);
}

}  // namespace ld2415h
}  // namespace esphome
