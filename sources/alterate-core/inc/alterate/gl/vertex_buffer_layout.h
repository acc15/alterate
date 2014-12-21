#pragma once

#include <vector>

#include <boost/assert.hpp>

#include <alterate/gl/gl_inc.h>
#include <alterate/defs.h>

namespace alterate {
namespace gl {

class vertex_buffer_layout {
public:
    struct layout_attribute {
        GLenum type;
        size_t next_offset;
    };


private:
    std::vector<layout_attribute> _attrs;

    inline void check_attr(size_t attr) const {
        BOOST_ASSERT_MSG(attr < _attrs.size(), "Illegal attribute index");
    }

public:

    static size_t get_type_size(GLenum type);

    vertex_buffer_layout();
    vertex_buffer_layout(const std::initializer_list<layout_attribute>& attrs);

    vertex_buffer_layout& attribute(GLenum type, size_t count);

    /**
     * Computes total size in bytes of attribute
     * @param attr attribute index
     * @return total size in bytes of attribute
     */
    size_t size(size_t attr) const;
    
    /**
     * Computes count of elements in attribute
     * @param attr attribute index
     * @return count of elements of attribute
     */
    size_t count(size_t attr) const;
    
    /**
     * Returns type of attribute
     * @param attr attribute index
     * @return type of attribute
     */
    GLenum type(size_t attr) const;
    
    /**
     * Returns total offset in bytes for specified attribute
     * @param attr attribute index
     * @return total offset in bytes for specified attribute
     */
    size_t offset(size_t attr) const;
    
    /**
     * Computes total offset in bytes for specified attribute from buffer beggining
     * @param attr attribute index
     * @param index index of layout
     * @return total offset in bytes for specified attribute from buffer beggining
     */
    size_t offset(size_t attr, size_t index) const;

    /**
     * Returns stride of buffer
     * @return stride of buffer
     */
    size_t stride() const;

    /**
     * Computes attribute index by offset
     * @param offset offset
     * @return attribute index
     */
    size_t attribute_by_offset(size_t offset) const;
    
};


}
}
