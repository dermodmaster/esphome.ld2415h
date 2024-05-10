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
  // This triggers current sensor configurations to be dumped
}

/*
uint8_t min_speed_reported_ = 1;    // 1 km/h
uint8_t angle_comp_ = 0;            // None
uint8_t sensitivity_ = 0;           // High
uint8_t tracking_mode_ = 1;         // Approaching
uint8_t sample_rate_ = 0;           // 22 fps
uint8_t unit_of_measure = 0;        // km/h
uint8_t vibration_correction = 5;   // 0-112
uint8_t relay_trigger_duration = 3; // 3 sec
uint8_t relay_trigger_speed = 1;    // 1 km/h
uint8_t negotiation_mode = 1;       // Custom Agreement

char firmware_[20] = "";
float velocity_ = 0;
bool approaching_ = 1;
*/
/*
void LD2415HComponent::update() {
  // Possibly setting config?
  //ESP_LOGV(TAG, "sending measurement request");
  //this->write_array(LD2415H_REQUEST, sizeof(LD2415H_REQUEST));


//  if (this->speed_sensor_ != nullptr)
//    this->speed_sensor_->publish_state(this->velocity_);


}
*/

void LD2415HComponent::dump_config() {
  issue_command_(LD2415H_CONFIG_CMD, sizeof(LD2415H_CONFIG_CMD));
  ESP_LOGCONFIG(TAG, "LD2415H:");
  ESP_LOGCONFIG(TAG, "  Firmware: %s", this->firmware_);
  ESP_LOGCONFIG(TAG, "  Minimum Speed Reported: %u", this->min_speed_reported_);
  ESP_LOGCONFIG(TAG, "  Angle Compensation: %u", this->angle_comp_);
  ESP_LOGCONFIG(TAG, "  Sensitivity: %u", this->sensitivity_);
  ESP_LOGCONFIG(TAG, "  Tracking Mode: %u", uint8_t(this->tracking_mode_));
  ESP_LOGCONFIG(TAG, "  Sampling Rate: %u", this->sample_rate_);
  ESP_LOGCONFIG(TAG, "  Unit of Measure: %u", uint8_t(this->unit_of_measure_));
  ESP_LOGCONFIG(TAG, "  Vibration Correction: %u", this->vibration_correction_);
  ESP_LOGCONFIG(TAG, "  Relay Trigger Duration: %u", this->relay_trigger_duration_);
  ESP_LOGCONFIG(TAG, "  Relay Trigger Speed: %u", this->relay_trigger_speed_);
  ESP_LOGCONFIG(TAG, "  Negotiation Mode: %u", uint8_t(this->negotiation_mode_));


  // This triggers current sensor configurations to be dumped
  //issue_command_(LD2415H_CONFIG_CMD, sizeof(LD2415H_CONFIG_CMD));

  //LOG_UART_DEVICE(this);
  //LOG_SENSOR("  ", "Speed", this->speed_sensor_);
  //LOG_UPDATE_INTERVAL(this);
  //this->check_uart_settings(9600);
}

void LD2415HComponent::loop() {
  // Process the stream from the sensor UART
  while (this->available()) {
    if (this->fill_buffer_(this->read())) {
      this->parse_buffer_();
    }
  }
}

void LD2415HComponent::issue_command_(const uint8_t cmd[], const uint8_t size) {
  // Don't assume the response buffer is empty, clear it before issuing a command.
  clear_remaining_buffer_(0);
  this->write_array(cmd, size);
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
      // Ignore these characters
      break;

    case '\n':
      // End of response
      if(this->response_buffer_index_ == 0)
        break;

      clear_remaining_buffer_(this->response_buffer_index_);
      ESP_LOGD(TAG, "Response Received:: %s", this->response_buffer_);
      return true;

    default:
      // Append to response
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
  char c = this->response_buffer_[0];

  switch(c) {
    case 'N':
      // Firmware Version
      //ESP_LOGD(TAG, "Firmware Response: %s", this->response_buffer_);
      this->parse_firmware_();
      break;
    case 'X':
      // Config Response
      //ESP_LOGD(TAG, "Config Response: %s", this->response_buffer_);
      this->parse_config_();
      break;
    case 'V':
      // Velocity
      //ESP_LOGD(TAG, "Velocity Response: %s", this->response_buffer_);
      this->parse_velocity_();
      break;

    default:
      ESP_LOGE(TAG, "Unknown Response: %s", this->response_buffer_);
      break;
  }
}

void LD2415HComponent::parse_config_() {
  // Example: "X1:01 X2:00 X3:05 X4:01 X5:00 X6:00 X7:05 X8:03 X9:01 X0:01"

  const char* delim = ": ";
  uint8_t token_len = 2;
  char* key;
  char* val;

  char* token = strtok(this->response_buffer_, delim);
  
  while (token != NULL)
  {
    if(std::strlen(token) != token_len) {
      ESP_LOGE(TAG, "Configuration key length invalid.");
      break;
    }
    key = token;

    token = strtok(NULL, delim);
    if(std::strlen(token) != token_len) {
      ESP_LOGE(TAG, "Configuration value length invalid.");
      break;
    }
    val = token;
    
    this->parse_config_param_(key, val);

    token = strtok(NULL, delim);
  }
}

void LD2415HComponent::parse_firmware_() {
    // Example: "No.:20230801E v5.0"

    const char* fw = strchr(this->response_buffer_, ':');

    if (fw != nullptr) {
      // Move p to the character after ':'
      ++fw;

      // Copy string into firmware
      std::strcpy(this->firmware_, fw);
    } else {
      ESP_LOGE(TAG, "Firmware value invalid.");
    }
}

void LD2415HComponent::parse_velocity_() {
    // Example: "V+001.9"

    const char* p = strchr(this->response_buffer_, 'V');

    if (p != nullptr) {
      ++p;
      this->approaching_ = (*p == '+');
      ++p;
      this->velocity_ = atof(p);

      ESP_LOGD(TAG, "Velocity updated: %f km/h", this->velocity_);
      
      if (this->speed_sensor_ != nullptr)
        this->speed_sensor_->publish_state(this->velocity_);

    } else {
      ESP_LOGE(TAG, "Firmware value invalid.");
    }
}

void LD2415HComponent::parse_config_param_(char* key, char* value) {
  if(std::strlen(key) != 2 || std::strlen(value) != 2 || key[0] != 'X') {
      ESP_LOGE(TAG, "Invalid Parameter %s:%s", key, value);
      return;
}

uint8_t v = std::stoi(value, nullptr, 16);

  switch(key[1]) {
    case '1':
      this->min_speed_reported_ = v;
      break;
    case '2':
      this->angle_comp_ = std::stoi(value, nullptr, 16);
      break;
    case '3':
      this->sensitivity_ = std::stoi(value, nullptr, 16);
      break;
    case '4':
      if(v >= int8_t(TrackingMode::ApproachingAndRetreating) && v <= uint8_t(TrackingMode::Restreating)) {
        this->tracking_mode_ = TrackingMode(v);
      } else {
        ESP_LOGE(TAG, "Invalid Value %s:%s", key, value);
      }
      break;
    case '5':
      this->sample_rate_ = v;
      break;
    case '6':
      if(v >= uint8_t(UnitOfMeasure::kph) && v <= uint8_t(UnitOfMeasure::mps)) {
        this->unit_of_measure_ = UnitOfMeasure(v);
      } else {
        ESP_LOGE(TAG, "Invalid Value %s:%s", key, value);
      }
      break;
    case '7':
      this->vibration_correction_ = v;
      break;
    case '8':
      this->relay_trigger_duration_ = v;
      break;
    case '9':
      this->relay_trigger_speed_ = v;
      break;
    case '0':
      if(v >= uint8_t(NegotiationMode::CustomAgreement) && v <= uint8_t(NegotiationMode::StandardProtocol)) {
        this->negotiation_mode_ = NegotiationMode(v);
      } else {
        ESP_LOGE(TAG, "Invalid Value %s:%s", key, value);
      }
      break;
    default:
      ESP_LOGD(TAG, "Unknown Parameter %s:%s", key, value);
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