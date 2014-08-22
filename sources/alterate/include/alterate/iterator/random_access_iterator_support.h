#pragma once

#include <boost/iterator/iterator_facade.hpp>
#include <boost/iterator/reverse_iterator.hpp>

#include <alterate/pattern/crtp_support.h>

namespace alterate {
    namespace iterator {
        
        //
        // requires following interface from <Derived> container:
        //
        // size_type size() const {return ...; }
        // reference operator[](size_type const& index) { return ...; }
        // const reference operator[](size_type const& index) const { return ...; }
        //
        
        template <typename ContainerType, typename DifferenceType = ::alterate::int_t>
        class random_access_iterator: boost::iterator_facade<
            random_access_iterator<ContainerType>,
            typename ContainerType::value_type, 
            boost::random_access_traversal_tag, 
            typename ContainerType::value_type&,
            DifferenceType> 
        {
        public:
            typedef ContainerType                           container_type;
            typedef typename container_type::size_type      size_type;
            
        private:
            container_type* container_ptr;
            size_type position;
            
        public:
            random_access_iterator(size_type position = size_type()) : 
                random_access_iterator::container_ptr(nullptr),
                random_access_iterator::position(position) {
            }
        
            random_access_iterator(container_type& container, size_type position = size_type()) : 
                random_access_iterator::container_ptr(&container),
                random_access_iterator::position(position) {
            }
            
            friend class boost::iterator_core_access;
            
            reference dereference() const {
                return (*container_ptr)[position];
            }
            
            bool_t equal(random_access_iterator const& other) const {
                return container_ptr == other.container_ptr && position == other.position;
            }
            
            void increment() {
                ++position;
            }
            
            void decrement() {
                --position;
            }
            
            void advance(difference_type n) {
                position += n;
            }
            
            difference_type distance_to(scalar_iterator const& other) const {
                return other.position - position;
            }
        };
        
        template <typename Derived, 
                  typename ValueType, 
                  typename SizeType = alterate::uint_t, 
                  typename Reference = ValueType&>
        class random_access_iterator_support: private ::alterate::pattern::crtp_support<Derived> {
        public:
            typedef ValueType value_type;
            typedef SizeType size_type;
            typedef Reference reference;
            
            typedef random_access_iterator<derived_type>        iterator;
            typedef random_access_iterator<const derived_type>  const_iterator;
            typedef boost::reverse_iterator<iterator>           reverse_iterator;
            typedef boost::reverse_iterator<const_iterator>     const_reverse_iterator;
            
            iterator begin() {
                return iterator(derived());
            }
            
            iterator end() {
                return iterator(derived(), size());
            }
            
            const_iterator begin() const {
                return const_iterator(derived());
            }
            
            const_iterator end() const {
                return const_iterator(derived(), size());
            }
            
            const_iterator cbegin() const {
                return const_iterator(derived());
            }
            
            const_iterator cend() const {
                return const_iterator(derived(), size());
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