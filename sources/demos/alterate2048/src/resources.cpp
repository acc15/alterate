#include "resources.h"

using namespace alterate;

extern ubyte_t _binary_app_strings_start;
extern ubyte_t _binary_app_strings_end;
extern size_t _binary_app_strings_size;

extern ubyte_t _binary_shaders_position_vert_start;
extern ubyte_t _binary_shaders_position_vert_end;
extern size_t  _binary_shaders_position_vert_size;

extern ubyte_t _binary_shaders_position_frag_start;
extern ubyte_t _binary_shaders_position_frag_end;
extern size_t  _binary_shaders_position_frag_size;

namespace alterate2048 {
    namespace resources {

        const alterate::resources::resource_entry APP_STRINGS(
                _binary_app_strings_start,
                _binary_app_strings_end,
                _binary_app_strings_size);
        const alterate::resources::resource_entry SHADERS_POSITION_VERT(
                _binary_shaders_position_vert_start,
                _binary_shaders_position_vert_end,
                _binary_shaders_position_vert_size);
        const alterate::resources::resource_entry SHADERS_POSITION_FRAG(
                _binary_shaders_position_frag_start,
                _binary_shaders_position_frag_end,
                _binary_shaders_position_frag_size);

    }
}

