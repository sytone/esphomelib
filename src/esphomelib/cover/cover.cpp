//
// Created by Otto Winter on 26.11.17.
//

#include "esphomelib/cover/cover.h"

#include "esphomelib/log.h"

namespace esphomelib {

namespace cover {

static const char *TAG = "cover::cover";

void Cover::add_new_value_callback(cover_callback_t callback) {
  this->callback_.add(std::move(callback));
}

void Cover::push_new_value(float value, int8_t accuracy_decimals) {
  this->callback_.call(value, accuracy_decimals);
}
std::string Cover::unit_of_measurement() {
  return "";
}
std::string Cover::icon() {
  return "";
}
uint32_t Cover::update_interval() {
  return 0;
}

PollingCoverComponent::PollingCoverComponent(uint32_t update_interval)
    : PollingComponent(update_interval) {}
uint32_t PollingCoverComponent::update_interval() {
  return this->get_update_interval();
}

} // namespace cover

} // namespace esphomelib
