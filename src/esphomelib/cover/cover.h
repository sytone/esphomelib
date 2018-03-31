//
// Created by Otto Winter on 26.11.17.
//

#ifndef ESPHOMELIB_COVER_COVER_H
#define ESPHOMELIB_COVER_COVER_H

#include <functional>

#include "esphomelib/component.h"
#include "esphomelib/helpers.h"

namespace esphomelib {

namespace cover {

using cover_callback_t = std::function<void(float, int8_t)>;

const std::string UNIT_OF_MEASUREMENT_CELSIUS = "°C";
const std::string UNIT_OF_MEASUREMENT_PERCENT = "%";
const std::string UNIT_OF_MEASUREMENT_VOLT = "V";
const std::string UNIT_OF_MEASUREMENT_METER = "m";

// Home Assistant will set this itself because of unit of measurement.
const std::string ICON_TEMPERATURE = "";
const std::string ICON_HUMIDITY = "mdi:water-percent";
const std::string ICON_VOLTAGE = "mdi:flash";
const std::string ICON_DISTANCE = "mdi:arrow-expand-vertical";

/** Base-class for all covers.
 *
 * A cover has unit of measurement and can use push_new_value to send out a new value with the specified accuracy.
 */
class Cover {
 public:
  // ========== OVERRIDE METHODS ==========
  // (You'll only need this when creating your own custom cover)
  /** Push a new value to the MQTT front-end.
   *
   * Note that you should publish the raw value here, i.e. without any rounding as the user
   * can later override this accuracy.
   *
   * @param value The floating point value.
   * @param accuracy_decimals The accuracy in decimal points. The user can customize this.
   */
  void push_new_value(float value, int8_t accuracy_decimals);

  /** Override this to set the Home Assistant unit of measurement for this cover.
   *
   * Return "" to disable this feature.
   *
   * @return The icon of this cover, for example "°C".
   */
  virtual std::string unit_of_measurement();

  /** Override this to set the Home Assistant icon for this cover.
   *
   * Return "" to disable this feature.
   *
   * @return The icon of this cover, for example "mdi:battery".
   */
  virtual std::string icon();

  /// Return with which interval the cover is polled. Return 0 for non-polling mode.
  virtual uint32_t update_interval();

  // ========== INTERNAL METHODS ==========
  // (In most use cases you won't need these)
  /// The MQTT cover class uses this to register itself as a listener for new values.
  void add_new_value_callback(cover_callback_t callback);

 protected:
  CallbackManager<void(float, int8_t)> callback_{};
};

class PollingCoverComponent : public PollingComponent, public cover::Cover {
 public:
  explicit PollingCoverComponent(uint32_t update_interval);

  uint32_t update_interval() override;
};

} // namespace cover

} // namespace esphomelib


#endif //ESPHOMELIB_COVER_COVER_H
