#pragma once

#include "../CCircularBuffer/CCircularBuffer.h"

template<typename T, typename Allocator = std::allocator<T>>
class CCircularBufferExt : public CCircularBuffer<T, Allocator> {
public:
    using typename CCircularBuffer<int>::size_type;
    using typename CCircularBuffer<int>::difference_type;
    using typename CCircularBuffer<int>::value_type;
    using typename CCircularBuffer<int>::iterator;
    using typename CCircularBuffer<int>::const_iterator;
    using CCircularBuffer<T, Allocator>::max_size;
    using CCircularBuffer<T, Allocator>::size;
    using CCircularBuffer<T, Allocator>::begin;
    using CCircularBuffer<T, Allocator>::end;
    using CCircularBuffer<T, Allocator>::cbegin;
    using CCircularBuffer<T, Allocator>::cend;
    using CCircularBuffer<T, Allocator>::ChangeEndPointer;
    using CCircularBuffer<T, Allocator>::begin_;
    using CCircularBuffer<T, Allocator>::end_;

    CCircularBufferExt() : CCircularBuffer<T, Allocator>() {}

    explicit CCircularBufferExt(size_type n) : CCircularBuffer<T, Allocator>(n) {}

    CCircularBufferExt(size_type size, const value_type& value) : CCircularBuffer<T, Allocator>(size, value) {}

    CCircularBufferExt(const CCircularBufferExt& buffer_to_copy) : CCircularBuffer<T, Allocator>(buffer_to_copy) {}

    template<typename Iter,
            typename = std::enable_if<std::is_convertible_v<typename std::iterator_traits<Iter>::iterator_category,
                    std::input_iterator_tag>>>
    CCircularBufferExt(Iter i, Iter j) : CCircularBuffer<T, Allocator>(i, j) {}

    CCircularBufferExt(const std::initializer_list<value_type>& il) : CCircularBuffer<T, Allocator>(il) {}

    void resize() {
        CCircularBufferExt buffer(2 * max_size());
        ChangePointers(buffer, this->size());
        std::copy(begin(), end(), buffer.begin());

        *this = buffer;
    }

    iterator insert(const_iterator p, difference_type n, const value_type& t) {
        size_type offset = p - cbegin();
        while (size() + n > max_size()) {
            resize();
        }
        iterator it = begin() + offset;
        ChangeEndPointer(n);
        iterator current = end() - 1;

        while (current != it + (n - 1)) {
            *current = *(current - n);
            --current;
        }
        for (int i = 0; i < n; ++i) {
            *current = t;
            current--;
        }

        return it;
    }

    iterator insert(const_iterator p, const value_type& t) {
        return insert(p, 1, t);
    }

    template<typename Iter,
            typename = std::enable_if<std::is_convertible_v<typename std::iterator_traits<Iter>::iterator_category,
                    std::input_iterator_tag>>>
    iterator insert(const_iterator p, Iter i, Iter j) {
        difference_type n = j - i;
        iterator it = begin() + (p - cbegin());

        while (size() + n > max_size()) {
            resize();
        }

        ChangeEndPointer(n);
        iterator current = end() - 1;
        while (current != it + n - 1) {
            *current = *(current - n);
            current--;
        }
        for (int k = 0; k < n; ++k) {
            *it = *i;
            it++;
            i++;
        }

        return it - n;
    }

    iterator insert(const_iterator p, const std::initializer_list<value_type>& list) {
        return insert(p, list.begin(), list.end());
    }

    void push_front(value_type t) {
        if (size() == max_size()) {
            resize();
        }

        if (begin_ == this->start_of_memory_) {
            begin_ = this->finish_of_memory_;
            *begin_ = t;
        } else {
            --begin_;
            *begin_ = t;
        }
    }

    void push_back(value_type t) {
        if (size() == max_size()) {
            resize();
        }

        if (end_ == this->finish_of_memory_) {
            *end_ = t;
            end_ = this->start_of_memory_;
        } else {
            *end_ = t;
            ++end_;
        }
    }

private:
    void ChangePointers(CCircularBufferExt& buffer, size_type size_) {
        buffer.begin_ = buffer.start_of_memory_;
        buffer.end_ = buffer.start_of_memory_ + size_;
    }
};
