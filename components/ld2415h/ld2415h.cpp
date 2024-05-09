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

bool LD2415HComponent::fill_buffer_(char c) {
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

  this->response_buffer_index_ = 0;
}

void LD2415HComponent::parse_buffer_() {

  /*
  [00:07:09][D][uart_debug:158]: <<< "\xFF\xFF\r\n"
  [00:07:09][D][uart_debug:158]: <<< "No.:20230801E v5.0\r\n"
  [00:07:09][D][uart_debug:158]: <<< "X1:01 X2:00 X3:05 X4:01 X5:00 X6:00 X7:05 X8:03 X9:01 X0:01\r\n"
  */

  char c = this->response_buffer_[0];

  switch(c) {
    case 'N':
      // Firmware Version
      ESP_LOGD(TAG, "Firmware Response: %s", this->response_buffer_);
      break;
    case 'X':
      // Config Response
      ESP_LOGD(TAG, "Config Response: %s", this->response_buffer_);
      this->parse_config_();
      break;
    case 'V':
      // Velocity
      ESP_LOGD(TAG, "Speed Response: %s", this->response_buffer_);
      break;

    default:
      ESP_LOGD(TAG, "Unknown Response: %s", this->response_buffer_);
      break;
  }
}

void LD2415HComponent::parse_config_() {
  // Sample: "X1:01 X2:00 X3:05 X4:01 X5:00 X6:00 X7:05 X8:03 X9:01 X0:01"
  char delim[] = ": ";
  uint8_t token_len = 2;
  char key[token_len+1] = "";
  char val[token_len+1] = "";

  char* token = strtok(this->response_buffer_, delim);
  
  while (token != NULL)
  {
    std::strncpy(key, token, token_len);

    token = strtok(NULL, delim);
    std::strncpy(val, token, token_len);
    
    ESP_LOGD(TAG, "Storing Key:Value :: %s:%s", key, val);
    store_config_(key, val);

    token = strtok(NULL, delim);
  }

}

void LD2415HComponent::store_config_(char* key, char* value) {
  if(sizeof(key) != 2 || sizeof(value) != 2 || key[0] != 'X')
      ESP_LOGE(TAG, "Invalid Parameter %s:%s", key, value);
      return;

  switch(key[1]) {
    case '1':
      this->min_speed_reported_ = std::stoi(value, nullptr, 16);
      break;
    case '2':
      this->angle_comp_ = std::stoi(value, nullptr, 16);
      break;
    case '3':
      this->sensitivity_ = std::stoi(value, nullptr, 16);
      break;
    case '4':
      this->tracking_mode_ = std::stoi(value, nullptr, 16);
      break;
    case '5':
      this->sample_rate_ = std::stoi(value, nullptr, 16);
      break;
    case '6':
      this->unit_of_measure = std::stoi(value, nullptr, 16);
      break;
    case '7':
      this->vibration_correction = std::stoi(value, nullptr, 16);
      break;
    case '8':
      this->relay_trigger_duration = std::stoi(value, nullptr, 16);
      break;
    case '9':
      this->relay_trigger_speed = std::stoi(value, nullptr, 16);
      break;
    case '0':
      this->negotiation_mode = std::stoi(value, nullptr, 16);
      break;
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