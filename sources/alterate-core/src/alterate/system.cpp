#include <boost/predef.h>

#include <alterate/system.h>

#if BOOST_OS_LINUX

#include <unistd.h>

namespace alterate {
std::string get_executable_path() {
    const size_t PATH_MAX = 1024;

    /*
        Some OS-specific interfaces:

        Mac OS X: _NSGetExecutablePath() (man 3 dyld)
        Linux: readlink /proc/self/exe
        Solaris: getexecname()
        FreeBSD: sysctl CTL_KERN KERN_PROC KERN_PROC_PATHNAME -1
        FreeBSD if it has procfs: readlink /proc/curproc/file (FreeBSD doesn't have procfs by default)
        NetBSD: readlink /proc/curproc/exe
        DragonFly BSD: readlink /proc/curproc/file
        Windows: GetModuleFileName() with hModule = NULL
    */

    char executable_path[PATH_MAX];
    ssize_t result = readlink("/proc/self/exe", executable_path, PATH_MAX);
    if (result == -1) {
        return std::string();
    }
    return std::string(executable_path, result);
}
}

#elif BOOST_OS_WINDOWS

#include <windows.h>

namespace alterate {
std::string get_executable_path() {
    const size_t PATH_MAX = 1024;

    /*
        Some OS-specific interfaces:

        Mac OS X: _NSGetExecutablePath() (man 3 dyld)
        Linux: readlink /proc/self/exe
        Solaris: getexecname()
        FreeBSD: sysctl CTL_KERN KERN_PROC KERN_PROC_PATHNAME -1
        FreeBSD if it has procfs: readlink /proc/curproc/file (FreeBSD doesn't have procfs by default)
        NetBSD: readlink /proc/curproc/exe
        DragonFly BSD: readlink /proc/curproc/file
        Windows: GetModuleFileName() with hModule = NULL
    */

    char executable_path[PATH_MAX];
    DWORD result = GetModuleFileName(NULL, executable_path, PATH_MAX);
    if (result == 0) {
        return std::string();
    }
    return std::string(executable_path, result);
}
}
#elif BOOST_OS_MACOS


#else
namespace alterate {
std::string get_executable_path() {
    return std::string();
}
}
#endif

namespace alterate {

std::string get_executable_name() {

    std::string executable_path = get_executable_path();

    size_t end_pos = std::string::npos, start_pos = executable_path.length();
    for (std::string::reverse_iterator iter = executable_path.rbegin(); iter != executable_path.rend(); iter++) {
        char ch = (*iter);
        if (ch == '/' || ch == '\\') {
            break;
        }
        --start_pos;
        if (ch == '.' && end_pos == std::string::npos) {
            end_pos = start_pos;
        }
    }
    return executable_path.substr(start_pos, end_pos);
}

}
