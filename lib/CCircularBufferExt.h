#pragma once

#include "Iterator.h"
#include <iterator>
#include<iostream>
#include <string>

template<typename ValueType, typename alloc = std::allocator<ValueType>>
class CCircularBufferExt {

private:

    ValueType* data;
    size_t size_;
    size_t capacity_;

    alloc allocator_;

    Iterator<ValueType> begin_;
    Iterator<ValueType> end_;

public:

    CCircularBufferExt() {
        size_ = 0;
        capacity_ = 1;
        data = allocator_.allocate(1);
        begin_ = Iterator<ValueType>(data, size_, data);
        end_ = begin_;
    }

    explicit CCircularBufferExt(uint64_t n) {
        data = allocator_.allocate(n * 2);
        size_ = 0;
        capacity_ = n * 2;
        begin_ = Iterator<ValueType>(data, size_, data);
        end_ = begin_;
    }

    CCircularBufferExt(size_t n, const ValueType& x) {
        data = allocator_.allocate(n * 2);
        capacity_ = n * 2;
        size_ = n;
        begin_ = Iterator<ValueType>(data, size_, data);
        end_ = begin_ + n;
        for (int i = 0; i < n; i++) {
            std::construct_at(&data[i], x);
        }
    }

    template<typename Iterator_, typename = std::iterator<std::input_iterator_tag, ValueType>>
    CCircularBufferExt(const Iterator_& b, const Iterator_& e) {
        capacity_ = (e - b) * 2;
        size_ = 0;
        data = allocator_.allocate(capacity_);
        begin_ = Iterator<ValueType>(data, this->size_, data);
        end_ = begin_;
        for (auto i = b; i < e; i++) {
            this->push_back(*i);
        }
    }

    CCircularBufferExt(const CCircularBufferExt& other) {
        data = allocator_.allocate(other.capacity_);
        size_ = other.size_;
        capacity_ = other.capacity_;

        begin_ = Iterator<ValueType>(data, this->size_, data);
        end_ = begin_ + size_;

        for (int i = 0; i < size_; i++) {
            std::construct_at(&*(begin_ + i), *(other.begin_ + i));
        }
    }

    CCircularBufferExt(const std::initializer_list<ValueType>& init_list) {
        data = allocator_.allocate(init_list.size() * 2);
        size_ = init_list.size();
        capacity_ = init_list.size() * 2;
        begin_ = Iterator<ValueType>(data, size_, data);
        end_ = begin_ + size_;
        for (int i = 0; i < init_list.size(); i++) {
            std::construct_at(&data[i], *(init_list.begin() + i));
        }
    }

    ~CCircularBufferExt() {
        if(capacity_ > 0) {
            std::destroy_n(data, size_);
            allocator_.deallocate(data, capacity_);
        }
    }

    Iterator<ValueType> begin() {
        return begin_;
    }

    Iterator<ValueType> end() {
        return end_;
    }

    bool operator==(const CCircularBufferExt& rhs) {
        return std::equal(begin_, end_, rhs.begin_, rhs.end_);
    }

    bool operator!=(const CCircularBufferExt& rhs) {
        return !(*this == rhs);
    }

    ValueType& operator[](size_t n) {
        return *(begin_ + n % size_);
    }

    void swap(CCircularBufferExt& other) {
        ValueType* temp = other.data;
        other.data = this->data;
        this->data = temp;
        std::swap(this->size_, other.size_);
        std::swap(this->capacity_, other.capacity_);
        Iterator<ValueType> buff = other.begin_;
        other.begin_ = begin_;
        begin_ = buff;
        buff = other.end_;
        other.end_ = end_;
        end_ = buff;
    }

    size_t max_size() {
        return std::allocator_traits<decltype(allocator_)>::max_size(allocator_) * sizeof(ValueType);
    }

    size_t size() {
        return size_;
    }

    bool empty() {
        return size_ == 0;
    }

    void reserve(size_t n) {
        if (n < capacity_) return;
        ValueType* new_arr = allocator_.allocate(n);
        for (size_t i = 0; i < size_; i++) {
            std::construct_at(&new_arr[i], data[i]);
        }
        if (capacity_ != 0) {
            std::destroy_n(data, capacity_ - 1);
            allocator_.deallocate(data, capacity_ - 1);
        }
        data = new_arr;
        capacity_ = n;
        begin_ = Iterator<ValueType>(data, size_, data);
        end_ = data + size_;
    }

    void push_back(const ValueType& el) {
        if (capacity_ == size_) {
            if (size_ == 0) reserve(2);
            reserve(size_ * 2);
        }
        std::construct_at(&*end_, el);
        size_++;
        begin_.SetSize(size_);
        end_.SetSize(size_);
        end_ += 1;
    }

    Iterator<ValueType> insert(const Iterator<ValueType>& i, const ValueType& t) {
        Iterator<ValueType> it = i;
        if (end_ == data + capacity_) {
            int64_t dist = it - begin_;
            reserve(2 * size_);
            it = begin_ + dist;
        }

        ValueType buff = *it;

        size_++;
        begin_.SetSize(size_);
        end_.SetSize(size_);
        end_ = begin_ + size_;

        for (auto j = end_ - 1; j > it; j -= 1) {
            std::construct_at(&*(j), *(j - 1));
        }

        std::construct_at(&*it, t);

        return it;
    }

    template<typename Iterator_, typename = std::iterator<std::input_iterator_tag, ValueType>>
    Iterator<ValueType> insert(const Iterator<ValueType>& p, const Iterator_& b, const Iterator_& e) {
        uint64_t delta = e - b;
        Iterator<ValueType> it = p;
        if (size_ + delta >= capacity_) {
            uint64_t dif = p - begin_;
            reserve((size_ + delta) * 2);
            it = begin_ + dif;
        }

        size_ += delta;
        begin_.SetSize(size_);
        end_.SetSize(size_);
        it.SetSize(size_);
        end_ = begin_ + size_;

        for (auto i = end_ - delta - 1; i >= it; i -= 1) {
            std::construct_at(&*(i + delta), *i);
        }

        for (int i = 0; i < delta; i++) {
            std::construct_at(&*(it + i), *(b + i));
        }

        return it;
    }

    Iterator<ValueType> insert(const Iterator<ValueType>& p, uint64_t n, const ValueType& t) {
        Iterator<ValueType> it = p;
        if (size_ + n>= capacity_) {
            uint64_t dif = p - begin_;
            reserve((size_ + n) * 2);
            it = begin_ + dif;
        }

        size_ += n;
        begin_.SetSize(size_);
        end_.SetSize(size_);
        it.SetSize(size_);
        end_ = begin_ + size_;

        for (auto i = end_ - n - 1; i >= it; i -= 1) {
            std::construct_at(&*(i + n), *i);
        }

        for (int i = 0; i < n; i++) {
            std::construct_at(&*(it + i), t);
        }

        return it;
    }

    Iterator<ValueType> insert(const Iterator<ValueType>& p, const std::initializer_list<ValueType>& init_list) {
        Iterator<ValueType> it = p;
        if (size_ + init_list.size() >= capacity_) {
            uint64_t dif = p - begin_;
            reserve((size_ + init_list.size()) * 2);
            it = begin_ + dif;
        }

        size_ += init_list.size();
        begin_.SetSize(size_);
        end_.SetSize(size_);
        end_ = begin_ + size_;

        for (auto i = end_ - init_list.size() - 1; i >= it; i -= 1) {
            std::construct_at(&*(i + init_list.size()), *i);
        }

        for (int i = 0; i < init_list.size(); i++) {
            std::construct_at(&*(it + i), *(init_list.begin() + i));
        }

        return it;
    }

    Iterator<ValueType> erase(const Iterator<ValueType>& q1, const Iterator<ValueType>& q2) {
        int64_t delta = q2 - q1;
        size_ -= delta;
        begin_.SetSize(size_);
        end_.SetSize(size_);

        for (Iterator<ValueType> i = q2; i < end_; i += 1) {
            if(i - (i - delta) <= i - begin_) {
                std::construct_at(&*(i - delta), *i);
            }
        }

        end_ -= delta;

        return q1;
    }

    Iterator<ValueType> erase(const Iterator<ValueType>& it) {
        end_ -= 1;
        size_--;
        begin_.SetSize(size_);
        end_.SetSize(size_);
        for (Iterator<ValueType> i = it; i < end_; i += 1) {
            std::construct_at(&*i, *(i + 1));
        }

        return it;
    }

    void assign(const std::initializer_list<ValueType>& init_list) {
        this->clear();
        data = allocator_.allocate(init_list.size());
        size_ = init_list.size();
        begin_ = Iterator<ValueType>(data, size_, data);
        end_ = begin_ + init_list.size();
        for (int i = 0; i < size_; i++) {
            std::construct_at(&*(begin_ + i), *(init_list.begin() + i));
        }
    }

    void assign(int64_t n, const ValueType& t) {
        this->clear();
        for (int i = 0; i < n; i++) {
            this->push_back(t);
        }
    }

    template<typename Iterator_, typename = std::iterator<std::input_iterator_tag, ValueType>>
    void assign(const Iterator_& b, const Iterator_& e) {
        this->clear();
        for (auto i = b; i < e; i++) {
            this->push_back(*i);
        }
    }

    void clear() {
        std::destroy_n(data, size_);
        allocator_.deallocate(data, capacity_ - 1);
        data = allocator_.allocate(1);
        size_ = 0;
        begin_ = Iterator<ValueType>(data, size_, data);
        end_ = begin_;
        capacity_ = 1;
    }

    size_t capacity(){
        return capacity_;
    }
};

template<typename ValueType>
void swap(CCircularBufferExt<ValueType>& a, CCircularBufferExt<ValueType>& b) {
    a.swap(b);
}