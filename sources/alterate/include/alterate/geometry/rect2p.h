

namespace alterate {
    namespace geometry {

        template <typename T>
        class rect2p {

        public:
            typedef T value_type;

            T l, t, r, b;

            value_type center_x() const {
                return (l + r) / 2;
            }

            value_type center_y() const {
                return (t + b) / 2;
            }

            value_type half_width() const {
                return width() / 2;
            }

            value_type half_height() const {
                return height() / 2;
            }

            value_type left() const {
                return l;
            }

            value_type top() const {
                return t;
            }

            value_type right() const {
                return r;
            }

            value_type bottom() const {
                return b;
            }

            value_type width() const {
                return r - l;
            }

            value_type height() const {
                return b - t;
            }

        };


    }
}