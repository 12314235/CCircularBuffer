#pragma once
#include "Iterator.h"


template<typename ValueType, typename alloc = std::allocator<ValueType>>
class CCircularBuffer {

private:

    ValueType* data;
    size_t size_;
    size_t capacity_;

    alloc allocator_;

    Iterator<ValueType> begin_;
    Iterator<ValueType> end_;

public:

    CCircularBuffer() {
        size_ = 0;
        data = allocator_.allocate(0);
        capacity_ = 0;
        begin_ = Iterator<ValueType>(data, size_, data);
        end_ = data;
    }

    CCircularBuffer(size_t n, const ValueType& x) {
        data = allocator_.allocate(n);
        size_ = n;
        capacity_ = n;
        begin_ = Iterator<ValueType>(data, size_, data);
        end_ = begin_ + n;
        for (int i = 0; i < n; i++) {
            std::construct_at(&*(begin_ + i), x);
        }
    }

    CCircularBuffer(const std::initializer_list<ValueType>& init_list) {
        data = allocator_.allocate(init_list.size());
        size_ = init_list.size();
        capacity_ = size_;
        begin_ = Iterator<ValueType>(data, size_, data);
        end_ = begin_ + init_list.size();
        for (int i = 0; i < size_; i++) {
            std::construct_at(&*(begin_ + i), *(init_list.begin() + i));
        }
    }

    template<typename Iterator_, typename = std::iterator<std::input_iterator_tag, ValueType>>
    CCircularBuffer(const Iterator_& b, const Iterator_& e) {
        size_ = e - b;
        data = allocator_.allocate(size_);
        begin_ = Iterator<ValueType>(data, size_, data);
        end_ = begin_ + size_;
        capacity_ = size_;
        for (int i = 0; i < size_; i++) {
            std::construct_at(&*(begin_ + i), *(b + i));
        }
    }

    CCircularBuffer(uint64_t n) {
        data = allocator_.allocate(n);
        capacity_ = n;
        size_ = 0;
        begin_ = Iterator<ValueType>(data, size_, data);
        end_ = begin_;
    }

    CCircularBuffer(const CCircularBuffer& other) {
        data = allocator_.allocate(other.size_);
        size_ = other.size_;
        capacity_ = size_;
        begin_ = Iterator<ValueType>(data, size_, data);
        end_ = begin_ + size_;

        for (int i = 0; i < size_; i++) {
            std::construct_at(&*(begin_ + i), *(other.begin_ + i));
        }
    }

    ~CCircularBuffer() {
        std::destroy_n(data, size_);
        allocator_.deallocate(data, size_);
    }

    Iterator<ValueType> begin() {
        return begin_;
    }

    Iterator<ValueType> end() {
        return end_;
    }

    bool operator==(const CCircularBuffer& rhs) {
        return std::equal(begin_, end_, rhs.begin_, rhs.end_);
    }

    bool operator!=(const CCircularBuffer& rhs) {
        return !(*this == rhs);
    }

    ValueType& operator[](size_t n) {
        return *(begin_ + n % size_);
    }

    void swap(CCircularBuffer& other) {
        ValueType* temp = other.data;
        other.data = this->data;
        this->data = temp;
        std::swap(this->size_, other.size());
        std::swap(this->capacity_, other.capacity());
        Iterator<ValueType> buff = other.begin_;
        other.begin_ = begin_;
        begin_ = buff;
        buff = other.end_;
        other.end_ = end_;
        end_ = buff;
    }

    Iterator<ValueType> insert(const Iterator<ValueType>& p, const ValueType& t) {

        for(Iterator<ValueType> i = end_ - 1; i >= p; i-=1){
            if (i == begin_ + capacity_ - 1){
                std::construct_at(&*begin_, *i);
            }
            else{
                std::construct_at(&*(i+1), *i);
            }
        }

        if(end_ <= begin_ + capacity_ - 1){
            size_++;
            begin_.SetSize(size_);
            end_.SetSize(size_);
            end_ += 1;
        }

        Iterator<ValueType> i = p;

        std::construct_at(&*i, t);

        return p;
    }

    template<typename Iterator_, typename = std::iterator<std::input_iterator_tag, ValueType>>
    Iterator<ValueType> insert(const Iterator<ValueType>& p, const Iterator_& b, const Iterator_& e){
        size_t delta = e - b;

        for(Iterator<ValueType> i = end_ - 1; i >= p; i -= 1){
            if(i >= begin_ + capacity_ - delta){
                std::construct_at(&*(begin_ + (delta - ((begin_ + capacity_) - i))), *i);
            }
            else{
                std::construct_at(&*(i + delta), *i);
            }
        }

        for(size_t i = 0; i < delta; i++){
            std::construct_at(&*(p + i), *(b + i));
        }

        return p;
    }

    Iterator<ValueType> insert(const Iterator<ValueType>& p, const std::initializer_list<ValueType>& init_list){
        size_t delta = init_list.size();

        for(Iterator<ValueType> i = end_ - 1; i >= p; i -= 1){
            if(i >= begin_ + capacity_ - delta){
                std::construct_at(&*(begin_ + (delta - ((begin_ + capacity_) - i))), *i);
            }
            else{
                std::construct_at(&*(i + delta), *i);
            }
        }

        for(size_t i = 0; i < delta; i++){
            std::construct_at(&*(p + i), *(init_list.begin() + i));
        }

        return p;
    }

    Iterator<ValueType> insert(const Iterator<ValueType>& p, uint64_t n, const ValueType& t) {
        size_t delta = n;

        for(Iterator<ValueType> i = end_ - 1; i >= p; i -= 1){
            if(i >= begin_ + capacity_ - delta){
                std::construct_at(&*(begin_ + (delta - ((begin_ + capacity_) - i))), *i);
            }
            else{
                std::construct_at(&*(i + delta), *i);
            }
        }

        for(size_t i = 0; i < delta; i++){
            std::construct_at(&*(p + i), t);
        }

        return p;
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
        size_--;

        for (Iterator<ValueType> i = it; i < end_ - 1; i += 1) {
            std::construct_at(&*i, *(i + 1));
        }

        end_ -= 1;
        begin_.SetSize(size_);
        end_.SetSize(size_);

        return it;
    }

    void assign(const std::initializer_list<ValueType>& init_list){
        if(init_list.size() > capacity_){
            throw std::runtime_error("Error: Init_List size too big");
        }
        this->clear();
        size_ = init_list.size();
        begin_.SetSize(size_);
        end_.SetSize(size_);
        end_ = begin_ + size_;
        for(int i = 0; i < init_list.size(); i++){
            std::construct_at(&*(begin_ + i), *(init_list.begin() + i));
        }
    }

    template<typename Iterator_, typename = std::iterator<std::input_iterator_tag, ValueType>>
    void assign(const Iterator_& b, const Iterator_& e) {
        this->clear();
        if(e - b > capacity_){
            throw std::runtime_error("Error: Init_List size too big");
        }
        for (auto i = b; i < e; i++) {
            this->push_back(*i);
        }
    }

    void assign(int64_t n, const ValueType& t) {
        if(n > capacity_){
            throw std::runtime_error("Error: Init_List size too big");
        }
        this->clear();
        for (int i = 0; i < n; i++) {
            this->push_back(t);
        }
    }

    void push_back(const ValueType& x){
        if(end_ == begin_ + capacity_){
            throw std::runtime_error("Error: Overflow");
        }
        else{
            std::construct_at(&*(begin_ + size_), x);
            size_++;
            begin_.SetSize(size_);
            end_.SetSize(size_);
            end_ += 1;
        }
    }

    size_t max_size() {
        return capacity_;
    }

    bool empty() {
        return size_ == 0;
    }

    size_t& capacity(){
        return capacity_;
    }

    size_t& size() {
        return size_;
    }

    void clear() {
        std::destroy_n(data, size_);
        allocator_.deallocate(data, capacity_);
        data = allocator_.allocate(capacity_);
        begin_ = Iterator<ValueType>(data, 0, data);
        end_ = begin_;
        size_ = 0;
    }

};

template<typename ValueType>
void swap(CCircularBuffer<ValueType>& a, CCircularBuffer<ValueType>& b) {
    a.swap(b);
}