#include <iostream>
#include <string>
#include <GLFW/glfw3.h>
using namespace std;

typedef unsigned char ubyte_t;
typedef unsigned int uint_t;


struct elf_resource {
    const ubyte_t&  _start;
    const ubyte_t&  _end;
    const size_t&   _size;

    inline const ubyte_t* begin() const {
        return &_start;
    }

    inline const ubyte_t* end() const {
        return &_end;
    }

    inline size_t size() const {
        return _size;
    }

    inline elf_resource(const ubyte_t& start, const ubyte_t& end, const size_t& size) : _start(start), _end(end), _size(size) {}
};


extern ubyte_t _binary_app_strings_start;
extern ubyte_t _binary_app_strings_end;
extern size_t _binary_app_strings_size;

extern ubyte_t _binary_shaders_position_vert_start;
extern ubyte_t _binary_shaders_position_vert_end;
extern size_t  _binary_shaders_position_vert_size;

extern ubyte_t _binary_shaders_position_frag_start;
extern ubyte_t _binary_shaders_position_frag_end;
extern size_t  _binary_shaders_position_frag_size;

const uint_t APP_STRINGS = 0;
const uint_t SHADERS_POSITION_VERT = 1;
const uint_t SHADERS_POSITION_FRAG = 2;

const elf_resource resource_entries[] = {
    elf_resource(_binary_app_strings_start, _binary_app_strings_end, _binary_app_strings_size),
    elf_resource(_binary_shaders_position_vert_start, _binary_shaders_position_vert_end, _binary_shaders_position_vert_size),
    elf_resource(_binary_shaders_position_frag_start, _binary_shaders_position_frag_end, _binary_shaders_position_frag_size)
};

namespace resources {

    std::string load_string(uint_t res_id);
    size_t get_resource_size(uint_t res_id);

    size_t get_resource_size(uint_t res_id) {
        return resource_entries[res_id].size();
    }

    std::string load_string(uint_t res_id) {
        const elf_resource& res = resource_entries[res_id];
        return std::string(res.begin(), res.end());
    }

}



int main()
{
    std::string app_name = resources::load_string(APP_STRINGS);
    std::string vert_shader = resources::load_string(SHADERS_POSITION_VERT);
    std::string frag_shader = resources::load_string(SHADERS_POSITION_FRAG);

    std::cout << app_name << std::endl;

//    char* begin = &_binary_app_strings_start;
//    char* end = &_binary_app_strings_end;

//    GLFWwindow* window;

//    /* Initialize the library */
//    if (!glfwInit())
//        return -1;

//    /* Create a windowed mode window and its OpenGL context */
//    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
//    if (!window)
//    {
//        glfwTerminate();
//        return -1;
//    }

//    /* Make the window's context current */
//    glfwMakeContextCurrent(window);

//    /* Loop until the user closes the window */
//    while (!glfwWindowShouldClose(window))
//    {
//        /* Render here */

//        /* Swap front and back buffers */
//        glfwSwapBuffers(window);

//        /* Poll for and process events */
//        glfwPollEvents();
//    }

//    glfwTerminate();
    return 0;
}

