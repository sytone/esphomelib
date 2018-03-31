//
// Created by Otto Winter on 26.11.17.
//

#ifndef ESPHOMELIB_SENSOR_MQTT_COVER_COMPONENT_H
#define ESPHOMELIB_SENSOR_MQTT_COVER_COMPONENT_H

#include "esphomelib/cover/cover.h"
#include "esphomelib/mqtt/mqtt_component.h"
#include "esphomelib/helpers.h"

namespace esphomelib {

namespace cover {

class MQTTCoverComponent : public mqtt::MQTTComponent {
 public:
  /** Construct this MQTTCoverComponent instance with the provided friendly_name and cover
   *
   * @param friendly_name The friendly name that should be advertised to Home Assistant.
   * @param cover The cover, this can be null to disable automatic setup.
   */
  MQTTCoverComponent(std::string friendly_name, Cover *cover);

  // ========== INTERNAL METHODS ==========
  // (In most use cases you won't need these)
  /// Override setup.
  void setup() override;

  /** This will create a callback that can be used to register this MQTTComponent
   * with the cover.
   *
   * For example:
   *
   * cover->add_new_value_callback(mqtt->create_new_data_callback());
   *
   * However, you normally don't need to worry about this as the Application instance
   * takes care of all of this.
   *
   * @return A new callback that can be registered to the cover.
   */
  cover_callback_t create_new_data_callback();

 protected:
  /// Override for MQTTComponent, returns "cover".
  std::string component_type() const override;

  /// Internal method, convert the value, accuracy pair to string
  /// and send them via MQTT.
  void push_out_value(float value, int8_t accuracy_decimals);

};

} // namespace cover

} // namespace esphomelib

#endif //ESPHOMELIB_SENSOR_MQTT_SENSOR_COMPONENT_H
