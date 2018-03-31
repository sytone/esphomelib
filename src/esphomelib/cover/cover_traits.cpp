//
// Created by Otto Winter on 29.12.17.
//

#include "esphomelib/cover/cover_traits.h"

namespace esphomelib {

  namespace cover {

    CoverTraits::CoverTraits()
        : tilt_(false) {}

    CoverTraits::CoverTraits(bool tilt)
        : tilt_(tilt) {}

    bool CoverTraits::supports_tilt() const {
      return this->tilt_;
    }
    
    void CoverTraits::set_tilt(bool tilt) {
      this->tilt_ = tilt;
    }

  } // namespace cover

} // namespace esphomelib
