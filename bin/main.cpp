#include <iostream>
#include <vector>
#include <iterator>
#include "../lib/CCircularBuffer.h"
#include "../lib/CCircularBufferExt.h"


struct Circle {
    int x;
    int y;
    int r;

    Circle(int x, int y, int r) {
        this->x = x;
        this->y = y;
        this->r = r;
    }

    Circle(const Circle& other) {
        this->x = other.x;
        this->y = other.y;
        this->r = other.r;
    }

    ~Circle() {

    }

    const Circle& operator+(const Circle& other) {
        Circle* res = new Circle(x, y, r);
        res->x += other.x;
        res->y += other.y;
        res->r += other.r;

        return *res;
    }

    void print() {
        std::cout << x << '\n';
        std::cout << y << '\n';
        std::cout << r << '\n';
    }
};

int main()
{
    CCircularBuffer<int> buff = CCircularBuffer<int>({1, 2, 3, 4});

    buff.push_back(5);
    buff.push_back(6);

    for(auto i : buff){
        std::cout << i << ' ';
    }
}
