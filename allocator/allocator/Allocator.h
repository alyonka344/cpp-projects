#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

struct Pool {
    explicit Pool(const std::pair<int, int>& pair) {
        chunk_count = pair.first;
        chunk_size = pair.second;
        start_of_memory = new bool[chunk_size * chunk_count];
        free_chunks = new bool[chunk_count]{};
    }

    ~Pool() {
        delete[] start_of_memory;
        delete[] free_chunks;
    }

    bool* start_of_memory;
    size_t chunk_size{};
    size_t chunk_count{};
    bool* free_chunks;
};

template<typename T>
class Allocator {
public:
    typedef T value_type;
    typedef size_t size_type;
    typedef int32_t difference_type;
    typedef T* pointer;
    typedef const T* const_pointer;
    typedef T& reference;
    typedef const T& const_reference;

    struct ComparePools {
        bool operator()(const Pool* pool1, const Pool* pool2) const {
            return pool1->chunk_size < pool2->chunk_size;
        }
    };

    explicit Allocator(const std::vector<std::pair<int, int>>& pools) {
        pools_.resize(pools.size());
        for (int i = 0; i < pools_.size(); ++i) {
            pools_[i] = new Pool(pools[i]);
        }
        std::sort(pools_.begin(), pools_.end(), ComparePools());
    }

    template<typename AllocType>
    Allocator(const Allocator<AllocType>& copy_allocator) {
        pools_ = (copy_allocator.GetPools());
        destructor_counter_ = copy_allocator.GetDestructorCounter();
        (*destructor_counter_)++;
    }

    void deallocate(T* pointer, size_type n) {
        bool* tmp_pointer = reinterpret_cast<bool*>(pointer);
        size_type count_memory = 0;
        for (int i = 0; i < pools_.size(); ++i) {
            if (pools_[i]->start_of_memory <= tmp_pointer &&
                pools_[i]->start_of_memory + pools_[i]->chunk_size * pools_[i]->chunk_count > tmp_pointer) {
                count_memory = n * sizeof(T);
                size_type diff = tmp_pointer - pools_[i]->start_of_memory;
                size_type start_index = diff / pools_[i]->chunk_size;
                size_type end_index = start_index + count_memory / pools_[i]->chunk_size;
                if (end_index > pools_[i]->chunk_count) {
                    throw std::bad_alloc{};
                }
                for (size_type j = start_index; j <= end_index; ++j) {
                    pools_[i]->free_chunks[j] = false;
                }
            }
        }
        if (count_memory == 0) {
            throw std::bad_alloc{};
        }
    };

    T* allocate(int n) {
        int min_loss = INT32_MAX;
        size_type count_memory = n * sizeof(T);
        int pool_number = -1;
        int empty_chunk_index = -1;
        for (int i = 0; i < pools_.size(); ++i) {
            int loss = Loss(count_memory, pools_[i]->chunk_size);
            if (loss < min_loss) {
                int count_free = 0;
                for (int k = 0; k < pools_[i]->chunk_count; ++k) {
                    if (!pools_[i]->free_chunks[k]) {
                        ++count_free;
                        if (count_free * pools_[i]->chunk_size >= count_memory) {
                            min_loss = loss;
                            pool_number = i;
                            empty_chunk_index = k - count_free + 1;
                            break;
                        }
                    } else {
                        count_free = 0;
                    }
                }
            }
        }
        if (pool_number == -1) {
            throw std::bad_alloc{};
        }
        int i = 0;
        while (i * pools_[pool_number]->chunk_size < count_memory) {
            pools_[pool_number]->free_chunks[empty_chunk_index + i] = true;
            i++;
        }
        return reinterpret_cast<T*>(pools_[pool_number]->start_of_memory + empty_chunk_index * pools_[pool_number]->chunk_size);
    }

    std::vector<Pool*> GetPools() const {
        return pools_;
    }

    int32_t* GetDestructorCounter() const {
        return destructor_counter_;
    }

    template<typename U>
    bool operator==(const Allocator<U>& alloc) const {
        return (pools_ == alloc.GetPools());
    }

    template<typename U>
    bool operator!=(const Allocator<U>& alloc) const {
        return !(*this == alloc);
    }

    ~Allocator() {
        if (*destructor_counter_ == 0) {
            for (auto& i: pools_) {
                delete i;
            }
        }
        (*destructor_counter_)--;
    }

private:
    size_type Loss(size_type count_memory, size_type chunk_size) {
        return static_cast<size_type>(ceil(static_cast<double>(count_memory) / static_cast<double>(chunk_size))) *
               chunk_size - count_memory;
    }

    std::vector<Pool*> pools_;
    int32_t* destructor_counter_ = new int32_t{};
};
