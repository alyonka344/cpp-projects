#pragma once

#include <utility>

template<typename Type1, typename Type2>
class ZipClass {
public:
    typedef typename Type1::value_type first_value_type;
    typedef typename Type2::value_type second_value_type;
    typedef Type1* first_pointer;
    typedef Type2* second_pointer;
    typedef typename Type1::iterator first_iterator;
    typedef typename Type2::iterator second_iterator;

    class Iterator {
        typedef std::input_iterator_tag iterator_category;
        typedef ptrdiff_t difference_type;

    public:
        Iterator(typename Type1::iterator first_iterator, typename Type2::iterator second_iterator) {
            first_iterator_ = first_iterator;
            second_iterator_ = second_iterator;
        }

        std::pair<first_value_type, second_value_type> operator*() {
            return std::pair<first_value_type, second_value_type>(*first_iterator_, *second_iterator_);
        }

        Iterator& operator++() {
            ++first_iterator_;
            ++second_iterator_;
            return *this;
        }

        Iterator operator++(int) {
            Iterator copy;
            copy.first_iterator_ = first_iterator_;
            copy.second_iterator_ = second_iterator_;
            ++first_iterator_;
            ++second_iterator_;
            return copy;
        }

        bool operator!=(Iterator other) {
            return first_iterator_ != other.first_iterator_ || second_iterator_ != other.second_iterator_;
        }


    private:
        typename Type1::iterator first_iterator_;
        typename Type2::iterator second_iterator_;
    };

    ZipClass(Type1& first_container, Type2& second_container) {
        first_container_ = &first_container;
        second_container_ = &second_container;
    };

    Iterator begin() {
        return Iterator((*first_container_).begin(), (*second_container_).begin());
    }

    Iterator end() {
        typename Type1::iterator first_iterator = (*first_container_).begin();
        typename Type2::iterator second_iterator = (*second_container_).begin();
        while (first_iterator != (*first_container_).end() && second_iterator != (*second_container_).end()) {
            ++first_iterator;
            ++second_iterator;
        }
        return Iterator(first_iterator, second_iterator);
    }

private:
    first_pointer first_container_;
    second_pointer second_container_;
};