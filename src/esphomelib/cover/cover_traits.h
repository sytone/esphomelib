//
// Created by Otto Winter on 29.12.17.
//

#ifndef ESPHOMELIB_COVER_COVER_TRAITS_H
#define ESPHOMELIB_COVER_COVER_TRAITS_H

namespace esphomelib
{

namespace cover
{

/// CoverTraits - This class represents the capabilities/feature set of a cover.
class CoverTraits
{
public:
  /// Construct an empty CoverTraits object. All features will be marked unsupported.
  CoverTraits();

  /// Construct a CoverTraits object with the provided tilt support.
  CoverTraits(bool tilt);

  /// Return if this cover supports tilt.
  bool supports_tilt() const;

  /// Set whether this fan supports oscillation.
  void set_tilt(bool tilt);

protected:
  bool tilt_;
};

} // namespace cover

} // namespace esphomelib

#endif //ESPHOMELIB_COVER_COVER_TRAITS_H
