

namespace alterate {
    namespace geometry {

        template <typename T>
        class rect2r {

        public:
            typedef T value_type;

            T cx, cy, hw, hh;

            value_type center_x() const {
                return cx;
            }

            value_type center_y() const {
                return cy;
            }

            value_type half_width() const {
                return hw;
            }

            value_type half_height() const {
                return hh;
            }

            value_type left() const {
                return cx - hw;
            }

            value_type top() const {
                return cy - hh;
            }

            value_type right() const {
                return cx + hw;
            }

            value_type bottom() const {
                return cy + hh;
            }

            value_type width() const {
                return hw + hw;
            }

            value_type height() const {
                return hh + hh;
            }

        };


    }
}