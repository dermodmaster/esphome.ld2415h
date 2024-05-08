#include "ld2415h.h"
#include "esphome/core/log.h"

namespace esphome {
namespace ld2415h {

static const char *const TAG = "ld2415h";

static const uint8_t LD2415H_RESPONSE_SPEED_LENGTH = 9;
static const uint8_t LD2415H_RESPONSE_SPEED_FOOTER[] = {0x0D, 0x0A};
static const uint8_t LD2415H_CONFIG_REQUEST[] = {0x43, 0x46, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

/* TODO ::
     * Define Commands as consts
     * Create function to send cmd and params
     * Create controls that expose settings
     * Setup should initialize settings
     * In loop constantly reading bytes into an array
     * When \n is encountered, parse array and reset loop
     * parse array should interpret response and update internal settings
     * If not read available set speed to 0km/h

     * Create Detected Sensor?
     * If not read available and last read was 1km/h then set detected to false
     * Create Last Top Speed Sensor
     * While Detected, if speed is greater than top speed update top speed
*/




void LD2415HComponent::setup() {
  // because this implementation is currently rx-only, there is nothing to setup
}

//void LD2415HComponent::update() {
  // Possibly setting config?
  //ESP_LOGV(TAG, "sending measurement request");
  //this->write_array(LD2415H_REQUEST, sizeof(LD2415H_REQUEST));
//}

float LD2415HComponent::get_setup_priority() const { return setup_priority::DATA; }

void LD2415HComponent::dump_config() {
  ESP_LOGCONFIG(TAG, "LD2415H:");
  //LOG_UART_DEVICE(this);
  LOG_SENSOR("  ", "Speed", this->speed_sensor_);
  LOG_UPDATE_INTERVAL(this);
  this->check_uart_settings(9600);


  this->write_array(LD2415H_CONFIG_REQUEST, sizeof(LD2415H_CONFIG_REQUEST));
/*
  this->write_byte(LD2415H_CONFIG_REQUEST[0]);
  this->write_byte(LD2415H_CONFIG_REQUEST[1]);
  this->write_byte(LD2415H_CONFIG_REQUEST[2]);
  this->write_byte(LD2415H_CONFIG_REQUEST[3]);
  this->write_byte(LD2415H_CONFIG_REQUEST[4]);
  this->write_byte(LD2415H_CONFIG_REQUEST[5]);
  this->write_byte(LD2415H_CONFIG_REQUEST[6]);
  this->write_byte(LD2415H_CONFIG_REQUEST[7]);
  this->write_byte(LD2415H_CONFIG_REQUEST[8]);
  this->write_byte(LD2415H_CONFIG_REQUEST[9]);
  this->write_byte(LD2415H_CONFIG_REQUEST[10]);
  this->write_byte(LD2415H_CONFIG_REQUEST[11]);
  this->write_byte(LD2415H_CONFIG_REQUEST[12]);
*/
/*
[00:07:09][D][uart_debug:158]: <<< "\xFF\xFF\r\n"
[00:07:09][D][uart_debug:158]: <<< "No.:20230801E v5.0\r\n"
[00:07:09][D][uart_debug:158]: <<< "X1:01 X2:00 X3:05 X4:01 X5:00 X6:00 X7:05 X8:03 X9:01 X0:01\r\n"
*/

}


void LD2415HComponent::loop() {
/*
  while (this->available()) {
    // Sample output:  V+002.6\r\n
    // commands start with "CF"
    // Need to read until \r\n then update speed.

    // Code below is checking for a complete record and resetting when done.
    this->read_byte(&this->data_[this->data_index_]);
    auto check = this->check_byte_();
    if (!check.has_value()) {
      // finished
      this->parse_data_();
      this->data_index_ = 0;
    } else {
      // next byte
      this->data_index_++;
    }
  }
*/
}

/*
optional<bool> LD2415HComponent::check_byte_() const {
  uint8_t index = this->data_index_;
  uint8_t byte = this->data_[index];

  // Check if value is end of speed message
  if (index + 1 == LD2415H_RESPONSE_SPEED_LENGTH) {
    return byte == LD2415H_RESPONSE_SPEED_FOOTER[1];
  }

  return false;
}


void LD2415HComponent::parse_data_() {
  const int speed = this->get_16_bit_uint_(5);

  ESP_LOGD(TAG, "Got Speed: %d km/h", speed);

  if (this->speed_sensor_ != nullptr) {
    this->speed_sensor_->publish_state(speed);
  }
*/


/*
  char byteArray[] = "V+002.6\r\n";

  // Extract bytes 3-7 (index 2-6) and store them in a string
  char floatStr[6];
  std::memcpy(floatStr, &byteArray[2], 5);
  floatStr[5] = '\0'; // Null-terminate the string

  // Convert the string to a float
  float floatValue = std::atof(floatStr);

  // Output the result
  std::cout << "Parsed float value: " << floatValue << std::endl;

}
*/

}  // namespace ld2415h
}  // namespace esphome