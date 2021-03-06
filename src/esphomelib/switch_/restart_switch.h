//
//  restart_switch.h
//  esphomelib
//
//  Created by Otto Winter on 29.03.18.
//  Copyright © 2018 Otto Winter. All rights reserved.
//

#ifndef ESPHOMELIB_RESTART_SWITCH_H
#define ESPHOMELIB_RESTART_SWITCH_H

#include "esphomelib/switch_/switch.h"

namespace esphomelib {

namespace switch_ {

/// A simple switch that restarts the device when triggered.
class RestartSwitch : public Switch {
 public:
  void turn_on() override;
  void turn_off() override;
  std::string icon() override;
};

} // namespace switch_

} // namespace esphomelib

#endif //ESPHOMELIB_RESTART_SWITCH_H
