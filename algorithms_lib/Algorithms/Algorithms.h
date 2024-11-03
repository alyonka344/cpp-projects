#pragma once

#include <cstdio>
#include <iterator>

namespace Algorithm {

    template<typename InputIterator, typename Predicate>
    bool all_of(InputIterator begin, InputIterator end, Predicate predicate) {
        while (begin != end) {
            if (!predicate(*begin)) {
                return false;
            }
            ++begin;
        }
        return true;
    }

    template<typename InputIterator, typename Predicate>
    bool any_of(InputIterator begin, InputIterator end, Predicate predicate) {
        while (begin != end) {
            if (predicate(*begin)) {
                return true;
            }
            ++begin;
        }
        return false;
    }

    template<typename InputIterator, typename Predicate>
    bool none_of(InputIterator begin, InputIterator end, Predicate predicate) {
        while (begin != end) {
            if (predicate(*begin)) {
                return false;
            }
            ++begin;
        }
        return true;
    }

    template<typename InputIterator, typename Predicate>
    bool one_of(InputIterator begin, InputIterator end, Predicate predicate) {
        size_t counter = 0;
        while (begin != end) {
            if (predicate(*begin)) {
                ++counter;
            }
            ++begin;
        }

        return counter == 1;
    }

    template<typename InputIterator, typename Comparator>
    bool is_sorted(InputIterator begin, InputIterator end, Comparator comp) {
        InputIterator prev;
        while (begin != end) {
            prev = begin;
            if (++begin != end && !comp(*prev, *begin)) {
                return false;
            }
        }
        return true;
    }

    template<typename InputIterator, typename Predicate>
    bool is_partitioned(InputIterator begin, InputIterator end, Predicate predicate) {
        if (std::distance(begin, end) == 0) {
            return false;
        }
        bool curr_predicate = predicate(*begin);
        int changes = 0;
        while (begin != end) {
            if (predicate(*begin) != curr_predicate) {
                changes++;
                curr_predicate = predicate(*begin);
            }
            ++begin;
        }

        return changes == 1;
    }

    template<typename InputIterator, typename CellType>
    InputIterator find_not(InputIterator begin, InputIterator end, CellType element) {
        while (begin != end) {
            if (*begin != element) {
                return begin;
            }
            ++begin;
        }
        return begin;
    }

    template<typename InputIterator, typename CellType>
    InputIterator find_backward(InputIterator begin, InputIterator end, CellType element, std::input_iterator_tag) {
        InputIterator to_return = end;
        while (begin != end) {
            if (*begin == element) {
                to_return = begin;
            }
            ++begin;
        }
        return to_return;
    }

    template<typename BidirectionalIterator, typename CellType>
    BidirectionalIterator find_backward(BidirectionalIterator begin, BidirectionalIterator end, CellType element,
                                        std::bidirectional_iterator_tag) {
        BidirectionalIterator end_copy = end;
        while (begin != end) {
            if (*(--end) == element) {
                return end;
            }
        }
        return end_copy;
    }

    template<typename Iterator, typename CellType>
    Iterator find_backward(Iterator begin, Iterator end, CellType element) {
        return find_backward(begin, end, element, typename Iterator::iterator_category());
    }

    template<typename InputIterator, typename Comparator>
    bool is_palindrome(InputIterator begin, InputIterator end, Comparator comp, std::input_iterator_tag) {
        int distance = std::distance(begin, end) - 1;
        InputIterator last;
        for (int i = distance; i > 0; i -= 2) {
            last = begin;
            for (int j = 0; j < i; ++j) {
                ++last;
            }
            if (!comp(*begin, *last)) {
                return false;
            }
            ++begin;
        }
        return true;
    }

    template<typename BidirectionalIterator, typename Comparator>
    bool is_palindrome(BidirectionalIterator begin, BidirectionalIterator end, Comparator comp,
                       std::bidirectional_iterator_tag) {
        int distance = std::distance(begin, end);
        --end;
        for (int i = 0; i < distance / 2; ++i) {
            if (!comp(*begin, *end)) {
                return false;
            }
            ++begin;
            --end;
        }
        return true;
    }

    template<typename Iterator, typename Comparator = std::equal_to<>>
    bool is_palindrome(Iterator begin, Iterator end, Comparator comp = std::equal_to<>()) {
        return is_palindrome(begin, end, comp, typename Iterator::iterator_category());
    }

}