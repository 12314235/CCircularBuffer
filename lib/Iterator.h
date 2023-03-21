#pragma once
#include <iterator>

template<typename ValueType>
class Iterator : public std::iterator<std::random_access_iterator_tag, ValueType> {
private:

    ValueType* p;
    ValueType* begin_;
    size_t size_;

public:

    Iterator() = default;

    Iterator(ValueType* p) : p(p) {

    }

    Iterator(ValueType* p, int size_, ValueType* begin_) : p(p), size_(size_), begin_(begin_) {

    }

    Iterator(const Iterator& other) : p(other.p), begin_(other.begin_), size_(other.size_) {

    }

    ~Iterator() = default;

    Iterator& operator+=(int64_t n) {
        if((begin_ + size_) - this->p < n) {
            this->p = begin_ + (n - ((begin_ + size_) - this->p));
        }
        else {
            this->p += n;
        }
        return *this;
    }

    void operator=(ValueType val) {
        *p = val;
    }

    Iterator operator+(int64_t n) const {
        Iterator temp = *this;
        return temp += n;
    }

    Iterator& operator-=(int64_t n) {
        if(this->p - begin_ < n){
            this->p = (begin_ + size_) - (n - (this->p - begin_));
        }
        else{
            this->p -= n;
        }
        return *this;
    }

    Iterator operator-(int64_t n) {
        Iterator temp = *this;

        return temp -= n;
    }

    ValueType& operator*() {
        return *p;
    }

    int64_t operator-(const Iterator<ValueType>& other) const {
        typename std::iterator_traits<Iterator>::difference_type tmp = std::distance(this->p, other.p);

        return -tmp;
    }

    ValueType& operator[](int64_t n) const {
        ValueType& tmp = *(this->p + n);
        return tmp;
    }

    bool operator<(const Iterator<ValueType>& rhs) const {
        typename std::iterator_traits<Iterator>::difference_type compare = std::distance(rhs, *this);
        return compare < 0;
    }

    bool operator>(const Iterator<ValueType>& rhs) const {
        typename std::iterator_traits<Iterator>::difference_type compare = std::distance(rhs, *this);
        return compare > 0;
    }

    bool operator>=(const Iterator<ValueType>& rhs) const {
        return !(*this < rhs);
    }

    bool operator<=(const Iterator<ValueType>& rhs) const {
        return !(*this > rhs);
    }

    bool operator==(const Iterator<ValueType>& other) const {
        return this->p == other.p;
    }

    bool operator!=(const Iterator<ValueType>& other) const {
        return !(*this == other);
    }

    void operator--(){
        if(this->p == begin_){
            this->p = begin_ + size_;
        }
        else {
            this->p -= 1;
        }
    }

    void operator++() {
        if(p == begin_ + size_){
            this->p = begin_;
        }
        else {
            this->p += 1;
        }
    }

    friend std::ostream& operator<<(std::ostream& stream, const Iterator<ValueType>& it) {
        stream << *it.p;

        return stream;
    }

    void SetSize(size_t size){
        this->size_ = size;
    }

    ValueType* GetPtr(){
        return this->p;
    }
};