#ifndef __LIST_H__
#define __LIST_H__

#include <iostream>
#include "utils.h"

template<typename T>
class List {
public:
    List(uint N_): N(N_), data(new T[N_]) {}
    List(uint N_, const T*const data): List(N_) {
        for (uint i = 0; i < N; i++)
            data[i] = data[i];
    }
    List(const std::initializer_list<T>& vals_): List(vals_.size()) {
        uint i = 0;
        for (auto val : vals_) {
            if (i >= N) { // out of bounds
                std::cout << "LIST: OUT OF BOUNDS" << std::endl;
                throw 1;
            }
            data[i] = val;
            i++;
        }
    }
    List(const List& l): List(l.N) {
        for (uint i = 0; i < N; i++)
            data[i] = l.data[i];
    }
    ~List() {
        delete [] data;
    }

    T& operator [] (int i) {
        if (i < 0) i += N; // list[-1] = last element
        return data[i];
    }
    const T& operator [] (int i) const {
        if (i < 0) i += N; // list[-1] = last element
        return data[i];
    }


    uint size() const {
        return N;
    }

    static List linspace(const T& a, const T& b, const uint N=50, bool inclusive = false) {
        uint extra = (inclusive ? 1 : 0);
        List li(N + extra);
        for (uint i = 0; i < N + extra; i++)
            li[i] = a + (b-a)/(N) * i;
        return li;
    }

private:
    uint N;
    T* data;

};

#endif