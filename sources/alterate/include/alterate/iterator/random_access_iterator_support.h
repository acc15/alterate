#pragma once

namespace alterate {
    namespace iterator {

        template <typename Derived, 
                  typename ValueType, 
                  typename SizeType = alterate::uint_t, 
                  typename Reference = ValueType&>
        class random_access_iterator_support {
        private:

            typedef Derived derived_type;

            derived_type& derived() {
                return *static_cast<derived_type *>(this);
            }

            derived_type const& derived() const {
                return *static_cast<derived_type const*>(this);
            }


        public:
            typedef ValueType value_type;
            typedef SizeType size_type;
            typedef Reference reference;

            //
            // requires following interface from derived():
            //
            // size_type size() const {return ...; }
            // reference operator[](size_type const& index) { return ...; }
            // const reference operator[](size_type const& index) const { return ...; }
            //

            // TODO
//             iterator begin() {
// 
//             }
// 
//             iterator end() {
// 
//             }
// 
//             const_iterator begin() const {
// 
//             }
// 
//             const_iterator end() const {
// 
//             }
// 
//             const_iterator cbegin() const {
// 
//             }
// 
//             const_iterator cend() const {
// 
//             }
// 
// 
//             reverse_iterator rbegin() {
// 
//             }
// 
//             reverse_iterator rend() {
// 
//             }
// 
//             const_reverse_iterator rbegin() const {
// 
//             }
// 
//             const_reverse_iterator rend() const {
// 
//             }
// 
//             const_reverse_iterator crbegin() const {
// 
//             }
// 
//             const_reverse_iterator crend() const {
// 
//             }


        };


    }

}