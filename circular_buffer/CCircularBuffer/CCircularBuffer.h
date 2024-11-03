#pragma once

#include <iostream>

template<typename T, typename Allocator = std::allocator<T>>
class CCircularBuffer {
public:
    typedef ptrdiff_t difference_type;
    typedef size_t size_type;

    template<typename TypeForIterator>
    class Iterator {
    public:
        typedef typename std::random_access_iterator_tag iterator_category;
        typedef TypeForIterator value_type;
        typedef TypeForIterator& reference;
        typedef const TypeForIterator& const_reference;
        typedef TypeForIterator* pointer;

        Iterator() = default;

        Iterator(pointer copy_of_iterator, const CCircularBuffer& circular_buffer) {
            circular_buffer_ = &circular_buffer;
            memory_cell_ = copy_of_iterator;
        };


    public:
        Iterator& operator++() {
            if (memory_cell_ == circular_buffer_->end_) {
                memory_cell_ = circular_buffer_->begin_;
            } else if (memory_cell_ == circular_buffer_->finish_of_memory_) {
                memory_cell_ = circular_buffer_->start_of_memory_;
            } else {
                ++memory_cell_;
            }
            return *this;
        }

        Iterator operator++(int) {
            pointer copy_of_iterator = memory_cell_;

            if (memory_cell_ == circular_buffer_->end_) {
                memory_cell_ = circular_buffer_->begin_;
            } else if (memory_cell_ == circular_buffer_->finish_of_memory_) {
                memory_cell_ = circular_buffer_->start_of_memory_;
            } else {
                ++memory_cell_;
            }

            return Iterator(copy_of_iterator, *circular_buffer_);
        }

        Iterator& operator--() {
            if (memory_cell_ == circular_buffer_->begin_) {
                memory_cell_ = circular_buffer_->end_;
            } else if (memory_cell_ == circular_buffer_->start_of_memory_) {
                memory_cell_ = circular_buffer_->finish_of_memory_;
            } else {
                --memory_cell_;
            }
            return *this;
        }

        Iterator operator--(int) {
            pointer copy_of_iterator = memory_cell_;

            if (memory_cell_ == circular_buffer_->begin_) {
                memory_cell_ = circular_buffer_->end_;
            } else if (memory_cell_ == circular_buffer_->start_of_memory_) {
                memory_cell_ = circular_buffer_->finish_of_memory_;
            } else {
                --memory_cell_;
            }

            return Iterator(copy_of_iterator, *circular_buffer_);
        }

        Iterator& operator+=(int number) {
            for (int i = 0; i < number; ++i) {
                (*this)++;
            }
            if (number < 0) {
                return (*this -= -number);
            }
            return *this;
        };

        Iterator& operator-=(int number) {
            for (int i = 0; i < number; ++i) {
                (*this)--;
            }
            if (number < 0) {
                return (*this += -number);
            }
            return *this;
        };

        Iterator operator+(difference_type number) {
            Iterator copy_of_iterator = *this;
            copy_of_iterator += number;
            return copy_of_iterator;
        }

        Iterator operator-(difference_type number) {
            Iterator copy_of_iterator = *this;
            copy_of_iterator -= number;
            return copy_of_iterator;
        }

        bool operator==(const Iterator& iterator) const {
            return memory_cell_ == iterator.memory_cell_;
        }

        bool operator!=(const Iterator& iterator) const {
            return memory_cell_ != iterator.memory_cell_;
        }

        bool operator>(const Iterator& iterator) const {
            return AdditionalPointer(memory_cell_) > AdditionalPointer(iterator.memory_cell_);
        }

        bool operator<(const Iterator& iterator) const {
            return AdditionalPointer(memory_cell_) < AdditionalPointer(iterator.memory_cell_);
        }

        bool operator>=(const Iterator& iterator) {
            return *this > iterator || *this == iterator;
        }

        bool operator<=(const Iterator& iterator) {
            return *this < iterator || *this == iterator;
        }

        reference operator*() const {
            return *memory_cell_;
        }

        difference_type operator-(const Iterator& iterator) const {
            return AdditionalPointer(memory_cell_) - AdditionalPointer(iterator.memory_cell_);
        }

        reference operator[](int number) {
            Iterator copy = *this;
            copy += number;
            return *(copy.memory_cell_);
        }

    private:
        pointer memory_cell_;
        const CCircularBuffer* circular_buffer_;

        pointer AdditionalPointer(const pointer pointer_to_change) const {
            pointer copy = pointer_to_change;
            if (pointer_to_change < circular_buffer_->begin_) {
                copy = circular_buffer_->finish_of_memory_ + (pointer_to_change - circular_buffer_->start_of_memory_) +
                       1;
            }
            return copy;
        };
    };

    typedef typename std::allocator_traits<Allocator>::template rebind_alloc<T> template_allocator;
    typedef T* pointer;
    typedef T value_type;
    typedef T& reference;
    typedef const T& const_reference;
    typedef CCircularBuffer<T, Allocator>::Iterator<T> iterator;
    typedef CCircularBuffer<T, Allocator>::Iterator<const T> const_iterator;

    iterator begin() const {
        return iterator(begin_, *this);
    }

    const_iterator cbegin() const {
        return const_iterator(begin_, *this);
    }

    iterator end() const {
        return iterator(end_, *this);
    }

    const_iterator cend() const {
        return const_iterator(end_, *this);
    }

    size_type max_size() const {
        return finish_of_memory_ - start_of_memory_;
    }

    size_type size() const {
        return end() - begin();
    }

    bool empty() const {
        return begin_ == end_;
    }

    CCircularBuffer() {
        start_of_memory_ = nullptr;
        finish_of_memory_ = nullptr;
        end_ = nullptr;
        begin_ = nullptr;
    }

    ~CCircularBuffer() {
        if (start_of_memory_ != nullptr) {
            allocator_.deallocate(start_of_memory_, max_size() + 1);
        }
        start_of_memory_ = nullptr;
        finish_of_memory_ = nullptr;
        end_ = nullptr;
        begin_ = nullptr;

    }

    CCircularBuffer(const CCircularBuffer& buffer_to_copy) {
        start_of_memory_ = allocator_.allocate(buffer_to_copy.max_size() + 1);
        finish_of_memory_ = start_of_memory_ + buffer_to_copy.max_size();
        begin_ = start_of_memory_ + (buffer_to_copy.begin_ - buffer_to_copy.start_of_memory_);
        end_ = start_of_memory_ + (buffer_to_copy.end_ - buffer_to_copy.start_of_memory_);
        std::copy(buffer_to_copy.begin(), buffer_to_copy.end(), begin());
    }

    explicit CCircularBuffer(size_type size) {
        start_of_memory_ = allocator_.allocate(size + 1);
        finish_of_memory_ = start_of_memory_ + size;
        begin_ = start_of_memory_;
        end_ = start_of_memory_;
    }

    CCircularBuffer(size_type size, const value_type& value) : CCircularBuffer(size) {
        end_ = begin_ + size;
        for (auto& element: *this) {
            element = value;
        }
    }

    template<typename Iter,
            typename = std::enable_if<std::is_convertible_v<typename std::iterator_traits<Iter>::iterator_category,
                    std::input_iterator_tag>>>
    CCircularBuffer(Iter i, Iter j) : CCircularBuffer(j - i) {
        end_ = begin_ + (j - i);
        for (auto& element: *this) {
            element = *(i++);
        }
    }

    CCircularBuffer(const std::initializer_list<value_type>& il) : CCircularBuffer(il.begin(), il.end()) {};


    CCircularBuffer& operator=(const CCircularBuffer& buffer_to_copy) {
        if (start_of_memory_ != nullptr) {
            allocator_.deallocate(start_of_memory_, max_size() + 1);
        }
        start_of_memory_ = allocator_.allocate(buffer_to_copy.max_size() + 1);
        finish_of_memory_ = start_of_memory_ + buffer_to_copy.max_size();
        begin_ = start_of_memory_ + (buffer_to_copy.begin_ - buffer_to_copy.start_of_memory_);
        end_ = start_of_memory_ + (buffer_to_copy.end_ - buffer_to_copy.start_of_memory_);
        std::copy(buffer_to_copy.begin(), buffer_to_copy.end(), begin());
        return *this;
    }

    CCircularBuffer& operator=(const std::initializer_list<value_type>& il) {
        *this = CCircularBuffer(il);
        return *this;
    }

    bool operator==(const CCircularBuffer& buffer) const {
        return std::equal(begin(), end(), buffer.begin(), buffer.end());
    }

    bool operator!=(const CCircularBuffer& buffer) const {
        return !(*this == buffer);
    }

    void swap(CCircularBuffer& buffer) {
        std::swap(start_of_memory_, buffer.start_of_memory_);
        std::swap(finish_of_memory_, buffer.finish_of_memory_);
        std::swap(end_, buffer.end_);
        std::swap(begin_, buffer.begin_);
    }

    void clear() {
        begin_ = start_of_memory_;
        end_ = start_of_memory_;
    }

    template<typename Iter,
            typename = std::enable_if<std::is_convertible_v<typename std::iterator_traits<Iter>::iterator_category,
                    std::input_iterator_tag>>>
    void assign(Iter i, Iter j) {
        clear();
        *this = CCircularBuffer(i, j);
    }

    void assign(const std::initializer_list<value_type>& il) {
        clear();
        *this = CCircularBuffer(il);
    }

    void assign(size_type size, const value_type& value) {
        clear();
        *this = CCircularBuffer(size, value);
    }

    iterator erase(const_iterator q1, const_iterator q2) {
        iterator it = begin() + (q1 - cbegin());
        size_type offset = q2 - q1;
        if (q1 >= cend() || (q2 - 1) < cbegin()) {
            return end();
        }
        iterator next = begin();
        while (next != end()) {
            next = it + offset;
            *(it++) = *next;
        }
        ChangeEndPointer(-offset);
        it = begin() + (q2 - cbegin()) - offset;
        return it;
    }

    iterator erase(const_iterator q) {
        return erase(q, q + 1);
    }


    iterator insert(const_iterator p, difference_type n, const value_type& t) {
        iterator it = begin() + (p - cbegin());
        if ((size() + n) > max_size()) {
            n = max_size() - size();
        }
        if (n == 0) {
            return end();
        }
        ChangeEndPointer(n);
        iterator current = end() - 1;
        while (current != it + n - 1) {
            *current = *(current - n);
            current--;
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
        if ((size() + n) > max_size()) {
            n = max_size() - size();
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

    virtual iterator insert(const_iterator p, const std::initializer_list<value_type>& list) {
        return insert(p, list.begin(), list.end());
    }

    reference front() {
        return *(begin());
    }

    reference back() {
        return *(end() - 1);
    }

    virtual void push_front(value_type t) {
        if (size() != max_size()) {
            if (begin_ == start_of_memory_) {
                begin_ = finish_of_memory_;
                *begin_ = t;
            } else {
                --begin_;
                *begin_ = t;
            }
        }
    }

    virtual void push_back(value_type t) {
        if (size() != max_size()) {
            if (end_ == finish_of_memory_) {
                *end_ = t;
                end_ = start_of_memory_;
            } else {
                *end_ = t;
                ++end_;
            }
        }
    }

    void pop_front() {
        if (size() != 0) {
            if (begin_ == finish_of_memory_) {
                begin_ = start_of_memory_;
            } else {
                ++begin_;
            }
        }
    }

    void pop_back() {
        if (size() != 0) {
            if (end_ == start_of_memory_) {
                end_ = finish_of_memory_;
            } else {
                --end_;
            }
        }
    }

    reference operator[](size_type pos) {
        return *(begin() + pos);
    }

    reference at(size_type pos) {
        if (pos >= size()) {
            throw std::exception{};
        }
        return *(begin() + pos);
    }

protected:
    void ChangeEndPointer(difference_type n) {
        if (n > 0) {
            int dist = finish_of_memory_ - end_;
            if (n > dist) {
                n -= dist;
                end_ = start_of_memory_ + n - 1;
            } else {
                end_ += n;
            }
        } else {
            int dist = end_ - start_of_memory_;
            n = -n;
            if (n > dist) {
                n -= dist;
                end_ = finish_of_memory_ - (n - 1);
            } else {
                end_ -= n;
            }
        }
    }

    pointer start_of_memory_;
    pointer finish_of_memory_;
    pointer end_;
    pointer begin_;
    template_allocator allocator_;
};


template<typename T, typename Allocator = std::allocator<T>>
void swap(CCircularBuffer<T, Allocator>& a, CCircularBuffer<T, Allocator>& b) {
    a.swap(b);
}