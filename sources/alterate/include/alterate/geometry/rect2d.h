

namespace alterate {
    namespace geometry {

        template <typename T>
        class rect2d {

        public:
            typedef T value_type;

            T l, t, w, h;

            rect2d& offset(const T& xoff, const T& yoff) {
                l += xoff;
                t += yoff;
                return *this;
            }

            value_type center_x() const {
                return l + half_width();
            }

            value_type center_y() const {
                return t + half_height();
            }

            value_type half_width() const {
                return w / 2;
            }

            value_type half_height() const {
                return h / 2;
            }

            value_type left() const {
                return l;
            }

            value_type top() const {
                return t;
            }

            value_type right() const {
                return l + w;
            }

            value_type bottom() const {
                return t + h;
            }

            value_type width() const {
                return w;
            }

            value_type height() const {
                return h;
            }

        };


    }
}