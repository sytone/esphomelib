//
// Created by Otto Winter on 29.12.17.
//

#include "esphomelib/cover/cover_state.h"
#include "esphomelib/esppreferences.h"

namespace esphomelib {

namespace cover {

std::string CoverState::get_state() const {
  return this->state_;
}
void CoverState::set_state(std::string state) {
  this->state_ = state;
  this->send_callback_.call();
  this->update_callback_.call();
}

uint32_t esphomelib::cover::CoverState::get_tilt_min() const {
  return this->tilt_min_;
}
void CoverState::set_tilt_min(uint32_t tilt_min) {
  this->tilt_min_ = tilt_min;
  this->send_callback_.call();
  this->update_callback_.call();
}
uint32_t esphomelib::cover::CoverState::get_tilt_max() const {
  return this->tilt_max_;
}
void CoverState::set_tilt_max(uint32_t tilt_max) {
  this->tilt_max_ = tilt_max;
  this->send_callback_.call();
  this->update_callback_.call();
}
uint32_t esphomelib::cover::CoverState::get_tilt_opened_value() const {
  return this->tilt_opened_value_;
}
void CoverState::set_tilt_opened_value(uint32_t tilt_opened_value) {
  this->tilt_opened_value_ = tilt_opened_value;
  this->send_callback_.call();
  this->update_callback_.call();
}
uint32_t esphomelib::cover::CoverState::get_tilt_min() const {
  return this->tilt_min_;
}
void CoverState::set_tilt_min(uint32_t tilt_min) {
  this->tilt_min_ = tilt_min;
  this->send_callback_.call();
  this->update_callback_.call();
}





const FanTraits &CoverState::get_traits() const {
  return this->traits_;
}
void CoverState::set_traits(const CoverTraits &traits) {
  this->traits_ = traits;
}
void CoverState::add_send_callback(const fan_send_callback_t &send_callback) {
  this->send_callback_.add(send_callback);
}
void CoverState::add_update_callback(const fan_send_callback_t &update_callback) {
  this->update_callback_.add(update_callback);
}
void CoverState::load_from_preferences(const std::string &friendly_name) {
  this->set_state(global_preferences.get_bool(friendly_name, "state", false));
  this->set_oscillating(global_preferences.get_bool(friendly_name, "oscillating", false));
  this->set_speed(static_cast<Speed>(global_preferences.get_int32(friendly_name, "speed", SPEED_HIGH)));
}
void CoverState::save_to_preferences(const std::string &friendly_name) {
  global_preferences.put_bool(friendly_name, "state", this->get_state());
  global_preferences.put_bool(friendly_name, "oscillating", this->is_oscillating());
  global_preferences.put_int32(friendly_name, "speed", this->get_speed());
}

} // namespace fan

} // namespace esphomelib
