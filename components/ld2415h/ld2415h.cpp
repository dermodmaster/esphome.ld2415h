#include "ld2415h.h"
#include "esphome/core/log.h"

namespace esphome {
namespace ld2415h {

static const char *const TAG = "ld2415h";

static const uint8_t LD2415H_CONFIG_CMD[] = {0x43, 0x46, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

static const uint8_t LD2415H_RESPONSE_FOOTER[] = {0x0D, 0x0A};


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

void LD2415HComponent::update() {
  // Possibly setting config?
  //ESP_LOGV(TAG, "sending measurement request");
  //this->write_array(LD2415H_REQUEST, sizeof(LD2415H_REQUEST));
}

void LD2415HComponent::dump_config() {
  ESP_LOGCONFIG(TAG, "LD2415H:");

  // Don't assume the buffer is full, clear it before issuing command.
  clear_remaining_buffer_(0);
  this->write_array(LD2415H_CONFIG_CMD, sizeof(LD2415H_CONFIG_CMD));

  //LOG_UART_DEVICE(this);
  //LOG_SENSOR("  ", "Speed", this->speed_sensor_);
  //LOG_UPDATE_INTERVAL(this);
  //this->check_uart_settings(9600);
}

void LD2415HComponent::loop() {
  while (this->available()) {
    if (this->fill_buffer_(this->read())) {
      this->parse_buffer_();
    }
  }
}

/*
void LD2415HComponent::parse_data_() {
  const int speed = this->get_16_bit_uint_(5);

  ESP_LOGD(TAG, "Got Speed: %d km/h", speed);

  if (this->speed_sensor_ != nullptr) {
    this->speed_sensor_->publish_state(speed);
  }
*/

bool LD2415HComponent::fill_buffer_(uint8_t c) {
  switch(c) {
    case 0x00:
    case 0xFF:
    case '\r':
      break;

    case '\n':
      if(this->response_buffer_index_ == 0) break;

      clear_remaining_buffer_(this->response_buffer_index_);
      return true;

    default:
      this->response_buffer_[this->response_buffer_index_] = c;
      this->response_buffer_index_++;
      break;
  }

  return false;
}

void LD2415HComponent::clear_remaining_buffer_(uint8_t pos) {
  while(pos < sizeof(this->response_buffer_)) {
        this->response_buffer_[pos] = 0x00;
        pos++;
  }
/*
  while(this->response_buffer_index_ < sizeof(this->response_buffer_)) {
        this->response_buffer_[this->response_buffer_index_] = 0x00;
        this->response_buffer_index_++;
  }
*/

  this->response_buffer_index_ = 0;
}

void LD2415HComponent::parse_buffer_() {

  /*
  [00:07:09][D][uart_debug:158]: <<< "\xFF\xFF\r\n"
  [00:07:09][D][uart_debug:158]: <<< "No.:20230801E v5.0\r\n"
  [00:07:09][D][uart_debug:158]: <<< "X1:01 X2:00 X3:05 X4:01 X5:00 X6:00 X7:05 X8:03 X9:01 X0:01\r\n"
  */

  uint8_t c = this->response_buffer_[0];

  switch(c) {
    case 'N':
      // Firmware Version
      ESP_LOGD(TAG, "Firmware Response: %s", this->response_buffer_);
      break;
    case 'X':
      // Config Response
      ESP_LOGD(TAG, "Config Response: %s", this->response_buffer_);
      this->parse_config_(this->response_buffer_);
      break;
    case 'V':
      // Velocity
      ESP_LOGD(TAG, "Speed Response: %s", this->response_buffer_);
      break;

    default:
      uint8_t len = 0;
      while(len < sizeof(this->response_buffer_)) {
        if (this->response_buffer_[len] == 0x00) break;
        len++;
      }

      ESP_LOGD(TAG, "Unknown Response Length: %i", len);
      //ESP_LOGD(TAG, "Unknown Response: %x", this->response_buffer_);
      ESP_LOGD(TAG, "Unknown Response: %s", this->response_buffer_);
      break;
  }
}

void LD2415HComponent::parse_config_(std::string cfg) {
  /*
  "X1:01 X2:00 X3:05 X4:01 X5:00 X6:00 X7:05 X8:03 X9:01 X0:01"
  */
 
  /*
    int min_speed_reported_ = 1;    // 1 km/h
    int angle_comp_ = 0;            // None
    int sensitivity_ = 0;           // High
    int tracking_mode_ = 1;         // Approaching
    int sample_rate_ = 0;           // 22 fps
    int unit_of_measure = 0;        // km/h
    int vibration_correction = 5;   // 0-112
    int relay_trigger_duration = 3; // 3 sec
    int relay_trigger_speed = 1;    // 1 km/h
    int negotiation_mode = 1;       // Custom Agreement
  */
  ESP_LOGD(TAG, "Length: %i", cfg.length());

  std::string d = ' '; // Parameter Delimeter
  int p = s.find(delimiter); // Delimeter Position

  for(int i = 0; i <> npos; i = p) {
    std::string param = s.substr(i, s.find(d));
    
    ESP_LOGD(TAG, "Param: %s", param);
  }
}

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