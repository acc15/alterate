#include <iostream>
#include <list>
#include <cstring>

#include "rc.h"

int main(int argc, const char* argv[]) {
    using namespace alterate;

    std::list<const char*> args;
    std::copy(argv+1, argv+argc, std::back_inserter(args));

    if (args.empty()) {
        std::cerr << "Command not specified" << std::endl;
        return -1;
    }

    const char* cmd = args.front();
    args.pop_front();

    if (strcmp(cmd, "rc") == 0) {
        return alterate::generate_resources(args);
    } else {
        std::cerr << "Unknown command: " << cmd << std::endl;
    }

    return 0;
}
