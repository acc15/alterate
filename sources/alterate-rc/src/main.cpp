#include <iostream>
#include <vector>
#include <cstring>

#define BOOST_FILESYSTEM_NO_DEPRECATED
#include <boost/filesystem.hpp>

#include <alterate/types.h>

using namespace alterate;
using namespace boost::filesystem;

struct rc_args {
    const ch_t* res_dir;
    const ch_t* out_dir;
    const ch_t* res_ns;
    std::vector<const ch_t*> input_list;
};

int_t parse_args(int_t argc, const ch_t* argv[], rc_args& args) {

    args.res_dir = "";
    args.out_dir = "";
    args.res_ns = nullptr;

    int nextArgType = 0;

    std::vector<const ch_t*> input_list;
    for (unsigned int i=0; i<argc; i++) {

        const char* arg = argv[i];
        switch (nextArgType) {
        case 1:
            args.res_dir = arg;
            break;

        case 2:
            args.out_dir = arg;
            break;

        case 3:
            args.res_ns = arg;
            break;

        default:
            if (strcmp(arg, "-d") == 0) {
                nextArgType = 1;
            } else if (strcmp(arg, "-o") == 0) {
                nextArgType = 2;
            } else if (strcmp(arg, "-n") == 0) {
                nextArgType = 3;
            } else {
                input_list.push_back(arg);
            }
            break;
        }
    }

    return 0;
}

void process_directory(const path& p) {

    directory_iterator end;
    boost::system::error_code err;
    directory_iterator iter(p, err);
    if (err) {
        std::cerr << "can't read " << p << " directory " << err.message() << std::endl;
        return;
    }
    for (directory_iterator iter(p); iter != end; iter++) {

        const directory_entry& entry = *iter;

        if (is_directory(entry.path())) {
            process_directory(entry.path());
            continue;
        }
        std::cout << (*iter) << std::endl;
    }

}

int_t main(int_t argc, const ch_t* argv[])
{

    rc_args args;
    int_t code = parse_args(argc, argv, args);
    if (code != 0) {
        return code;
    }

    process_directory(args.res_dir);

    return 0;
}
