//
// Created by Otto Winter on 29.12.17.
//

#ifndef ESPHOMELIB_COVER_COVER_TRAITS_H
#define ESPHOMELIB_COVER_COVER_TRAITS_H

namespace esphomelib
{

  namespace cover
  {

    class CoverTraits
    {
      public:
        CoverTraits();
        CoverTraits(bool tilt);

        bool supports_tilt() const;
        void set_tilt(bool tilt);

      protected:
        bool tilt_;
    };

  } // namespace cover

} // namespace esphomelib

#endif //ESPHOMELIB_COVER_COVER_TRAITS_H
