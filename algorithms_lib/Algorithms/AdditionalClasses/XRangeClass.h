template<typename Type>
class XRangeClass {
public:
    typedef Type value_type;

    class Iterator {
    public:
        typedef Type value_type;
        typedef std::input_iterator_tag iterator_category;
        typedef ptrdiff_t difference_type;
        typedef Type* pointer;
        typedef Type& reference;

        explicit Iterator(value_type cell, value_type step) {
            cell_ = cell;
            step_ = step;
        };

        Iterator& operator++() {
            cell_ += step_;
            return *this;
        }

        Iterator operator++(int) {
            value_type copy = cell_;
            cell_ += step_;
            return Iterator(copy, step_);
        }

        Type operator*() {
            return cell_;
        }

        bool operator!=(const Iterator& other) {
            if ((step_ > 0 && cell_ >= other.cell_) || (step_ < 0 && cell_ <= other.cell_) || step_ == 0) {
                return false;
            }
            return true;
        }


    private:
        value_type cell_;
        value_type step_;
    };

    XRangeClass(value_type begin, value_type end, value_type step) {
        begin_ = begin;
        end_ = end;
        step_ = step;
    };

    Iterator begin() {
        return Iterator(begin_, step_);
    }

    Iterator end() {
        return Iterator(end_, step_);
    }

private:
    value_type begin_{};
    value_type end_{};
    value_type step_{};
};
