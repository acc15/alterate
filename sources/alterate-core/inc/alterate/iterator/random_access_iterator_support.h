#pragma once

#include <boost/iterator/iterator_facade.hpp>
#include <boost/iterator/reverse_iterator.hpp>
#include <boost/assert.hpp>

#include <alterate/iterator/random_access_iterator.h>

namespace alterate {
namespace iterator {
        
//
// requires following interface from <Derived> container:
//
// size_type size() const {return ...; }
// reference operator[](size_type const& index) { return ...; }
// const reference operator[](size_type const& index) const { return ...; }
//

template <typename ContainerType, typename ValueType>
class random_access_iterator_support {
private:
    typedef ContainerType container_type;

    container_type& container() {
        return *static_cast<container_type*>(this);
    }

    const container_type& container() const {
        return *static_cast<const container_type*>(this);
    }

public:
    typedef ValueType value_type;

    typedef random_access_iterator<container_type, value_type>                iterator;
    typedef random_access_iterator<const container_type, const value_type>    const_iterator;
    typedef boost::reverse_iterator<iterator>                               reverse_iterator;
    typedef boost::reverse_iterator<const_iterator>                         const_reverse_iterator;

    iterator begin() {
        return iterator(container());
    }

    iterator end() {
        return iterator(container(), container().size());
    }

    const_iterator begin() const {
        return const_iterator(container());
    }

    const_iterator end() const {
        return const_iterator(container(), container().size());
    }

    const_iterator cbegin() const {
        return const_iterator(container());
    }

    const_iterator cend() const {
        return const_iterator(container(), container().size());
    }

    reverse_iterator rbegin() {
        return reverse_iterator(end());
    }

    reverse_iterator rend() {
        return reverse_iterator(begin());
    }

    const_iterator rbegin() const {
        return const_reverse_iterator(end());
    }

    const_iterator rend() const {
        return const_reverse_iterator(begin());
    }

    const_iterator crbegin() const {
        return const_reverse_iterator(end());
    }

    const_iterator crend() const {
        return const_reverse_iterator(begin());
    }

};

}
}
