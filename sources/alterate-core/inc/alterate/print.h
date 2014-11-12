#pragma once

namespace alterate {

    template <typename Stream, typename Container>
    Stream& print_container(const Container& container, Stream& stream) {
        stream << '[';
        bool needComma = false;
        for (typename Container::const_iterator iter = container.begin(); iter != container.end(); iter++) {
            if (needComma) {
                stream << ", ";
            }
            stream << (*iter);
            needComma = true;
        }
        stream << ']';
        return stream;
    }

}
