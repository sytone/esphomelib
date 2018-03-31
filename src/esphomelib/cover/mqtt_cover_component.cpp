//
// Created by Otto Winter on 26.11.17.
//

#include "esphomelib/cover/mqtt_cover_component.h"

#include "esphomelib/espmath.h"
#include "esphomelib/log.h"
#include "esphomelib/component.h"

namespace esphomelib
{

namespace cover
{

static const char *TAG = "cover::mqtt";

void MQTTCoverComponent::setup()
{
  ESP_LOGCONFIG(TAG, "Setting up MQTT Cover '%s'", this->friendly_name_.c_str());

  this->send_discovery([&](JsonBuffer &buffer, JsonObject &root) {},true, false); // enable state topic, disable command topic
}

cover_callback_t MQTTCoverComponent::create_new_data_callback()
{
  return [this](float value, int8_t accuracy_decimals) {
    // This stores the current value after each filter step.
    float current_value = value;

    ESP_LOGV(TAG, "'%s': Received new value %f with accuracy %d",
             this->friendly_name_.c_str(), value, accuracy_decimals);

    for (unsigned int i = 0; i < this->filters_.size(); i++)
    {
      // Apply the filter
      Filter *filter = this->filters_[i];
      auto optional_value = filter->new_value(current_value);
      if (!optional_value.defined)
      {
        ESP_LOGV(TAG, "'%s':  Filter #%u aborted chain",
                 this->friendly_name_.c_str(), i);
        // The filter aborted the chain
        return;
      }
      ESP_LOGV(TAG, "'%s':  Filter #%u %.2f -> %.2f",
               this->friendly_name_.c_str(), i, current_value, optional_value.value);
      current_value = optional_value.value;
    }

    if (this->override_accuracy_decimals_.defined)
      // Override accuracy_decimals if we were told to
      accuracy_decimals = this->override_accuracy_decimals_;

    // All filters succeeded, push out the result.
    this->push_out_value(current_value, accuracy_decimals);
  };
}

std::string MQTTCoverComponent::component_type() const
{
  return "cover";
}

void MQTTCoverComponent::set_unit_of_measurement(const std::string &unit_of_measurement)
{
  this->unit_of_measurement_ = unit_of_measurement;
}

void MQTTCoverComponent::set_expire_after(uint32_t expire_after)
{
  this->expire_after_ = expire_after;
}

void MQTTCoverComponent::push_out_value(float value, int8_t accuracy_decimals)
{
  ESP_LOGD(TAG, "'%s': Pushing out value %f with accuracy %d",
           this->friendly_name_.c_str(), value, accuracy_decimals);
  auto multiplier = float(pow10(accuracy_decimals));
  float value_rounded = roundf(value * multiplier) / multiplier;
  char tmp[32];
  dtostrf(value_rounded, 0, uint8_t(std::max(0, int(accuracy_decimals))), tmp);
  this->send_message(this->get_state_topic(), tmp);
}
const std::string &MQTTCoverComponent::get_unit_of_measurement() const
{
  return this->unit_of_measurement_;
}
const Optional<uint32_t> &MQTTCoverComponent::get_expire_after() const
{
  return this->expire_after_;
}
void MQTTCoverComponent::disable_expire_after()
{
  this->expire_after_ = Optional<uint32_t>();
}
std::vector<Filter *> MQTTCoverComponent::get_filters() const
{
  return this->filters_;
}
void MQTTCoverComponent::add_filter(Filter *filter)
{
  this->filters_.push_back(filter);
}
void MQTTCoverComponent::clear_filters()
{
  this->filters_.clear();
}
const Optional<int8_t> &MQTTCoverComponent::get_override_accuracy_decimals() const
{
  return override_accuracy_decimals_;
}
void MQTTCoverComponent::override_accuracy_decimals(int8_t override_accuracy_decimals)
{
  this->override_accuracy_decimals_ = override_accuracy_decimals;
}
void MQTTCoverComponent::add_lambda_filter(lambda_filter_t filter)
{
  this->add_filter(new LambdaFilter(std::move(filter)));
}
void MQTTCoverComponent::add_offset_filter(float offset)
{
  this->add_filter(new OffsetFilter(offset));
}
void MQTTCoverComponent::add_sliding_window_average_filter(size_t window_size, size_t send_every)
{
  this->add_filter(new SlidingWindowMovingAverageFilter(window_size, send_every));
}
void MQTTCoverComponent::add_exponential_moving_average_filter(float alpha, size_t send_every)
{
  this->add_filter(new ExponentialMovingAverageFilter(alpha, send_every));
}
MQTTCoverComponent::MQTTCoverComponent(std::string friendly_name, Cover *cover)
    : MQTTComponent(std::move(friendly_name))
{
  if (cover == nullptr)
    // Disable automatic initialization
    return;

  cover->add_new_value_callback(this->create_new_data_callback());
  // By default, smooth over the last 15 values using sliding window moving average.
  this->add_sliding_window_average_filter(15, 15);
  // By default, expire after 30 missed values, or two full missed sliding windows.
  if (cover->update_interval() > 0)
  {
    // If this is a polling cover
    uint32_t expire_after = cover->update_interval() * 30;
    this->set_expire_after(expire_after);
  }
  this->set_unit_of_measurement(cover->unit_of_measurement());
}
void MQTTCoverComponent::add_multiply_filter(float multiplier)
{
  this->add_filter(new MultiplyFilter(multiplier));
}
void MQTTCoverComponent::add_filters(const std::vector<Filter *> &filters)
{
  this->filters_.insert(this->filters_.end(), filters.begin(), filters.end());
}
void MQTTCoverComponent::set_filters(const std::vector<Filter *> &filters)
{
  this->filters_.clear();
  this->add_filters(filters);
}
void MQTTCoverComponent::add_filter_out_value_filter(float values_to_filter_out)
{
  this->add_filter(new FilterOutValueFilter(values_to_filter_out));
}
void MQTTCoverComponent::set_icon(const std::string &icon)
{
  this->icon_ = icon;
}
const std::string &MQTTCoverComponent::get_icon() const
{
  return this->icon_;
}

} // namespace cover

} // namespace esphomelib
