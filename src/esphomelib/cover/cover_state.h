//
// Created by Otto Winter on 29.12.17.
//

#ifndef ESPHOMELIB_COVER_COVER_STATE_H
#define ESPHOMELIB_COVER_COVER_STATE_H

#include <functional>

#include "esphomelib/helpers.h"
#include "esphomelib/cover/cover_traits.h"

namespace esphomelib
{

namespace cover
{

using cover_send_callback_t = std::function<void()>;

class CoverState
{
public:
  void add_send_callback(const cover_send_callback_t &send_callback);
  void add_update_callback(const cover_send_callback_t &update_callback);

  std::string get_state() const;
  void set_state(std::string state);

  uint32_t get_tilt_min() const;
  void set_tilt_min(uint32_t tilt_min);
  uint32_t get_tilt_max() const;
  void set_tilt_max(uint32_t tilt_max);
  uint32_t get_tilt_opened_value() const;
  void set_tilt_opened_value(uint32_t tilt_opened_value);
  uint32_t get_tilt_closed_value() const;
  void set_tilt_closed_value(uint32_t tilt_closed_value);

  uint32_t get_tilt() const;
  void set_tilt(uint32_t tilt);

  const CoverTraits &get_traits() const;
  void set_traits(const CoverTraits &traits);

  void load_from_preferences(const std::string &friendly_name);
  void save_to_preferences(const std::string &friendly_name);

protected:
  std::string state_{""};
  uint32_t tilt_min_;
  uint32_t tilt_max_;
  uint32_t tilt_opened_value_;
  uint32_t tilt_closed_value_;
  uint32_t tilt_;

  CoverTraits traits_{};
  CallbackManager<void()> send_callback_{};
  CallbackManager<void()> update_callback_{};
};

} // namespace cover

} // namespace esphomelib

#endif //ESPHOMELIB_COVER_COVER_STATE_H
