#pragma once

// it's better to use boost instead of std::chrono until Microsoft find time
// https://connect.microsoft.com/VisualStudio/feedback/details/719443/

#include <boost/chrono.hpp>

namespace alterate {
namespace timing {

template <typename T, typename Clock = boost::chrono::high_resolution_clock>
class timer {
public:
    typedef Clock clock;

private:

    typedef typename clock::time_point time_point;

    bool       _started = false;
    time_point _last_time;

public:

    bool started() const {
        return _started;
    }

    void start() {
        _started = true;
        _last_time = clock::now();
    }

    template <typename Ratio = boost::ratio<1>, typename Rep = T>
    Rep elapsed() const {
        typedef boost::chrono::duration<Rep, Ratio> duration;
        duration diff = clock::now() - _last_time;
        return diff.count();
    }

    template <typename Ratio = boost::ratio<1>, typename Rep = T>
    Rep reset() {
        typedef boost::chrono::duration<Rep, Ratio> duration;
        if (!_started) {
            start();
            return 0;
        }
        time_point now = clock::now();
        duration diff = now - _last_time;
        _last_time = now;
        return diff.count();
    }

    void stop() {
        _started = false;
    }

};


}
}
