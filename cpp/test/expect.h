#ifndef __EXPECT_H__
#define __EXPECT_H__

#include <iostream>
#include <string>
#include <vector>
#include "../include/leon/console_colors.h"
#include "../include/leon/vector.h"

std::string curTitle = "";
uint failedTests = 0;

typedef void (*test_func)(void);

#define error(s, ...) {fprintf(stderr, "   %s✕ Failed – %s", console_colors::RED, console_colors::RESET); fprintf(stderr, s, ##__VA_ARGS__); failedTests++;}


template<typename T>
class ExpectFunc {
public:
    ExpectFunc(const T& cur_): cur(cur_) {}

    void toEqual(const T& other, double eps = 1e-5) const;

private:
    const T& cur;
};


void test(const std::string& title, test_func f) {
    failedTests = 0;
    curTitle = title;

    printf("%sRunning test suite %s%s:%s\n", console_colors::BOLDBLUE, console_colors::MAGENTA, title.c_str(), console_colors::RESET);

    f();

    if (failedTests == 0)
        printf("%sTest suite for %s: All passed!%s\n", console_colors::GREEN, title.c_str(), console_colors::RESET);
    else
        printf("%sTest suite for %s: %u failed!%s\n", console_colors::BOLDRED, title.c_str(), failedTests, console_colors::RESET);
}

template<typename T>
ExpectFunc<T> expect(const T& t) {
    return ExpectFunc<T>(t);
}


// VectorDyn specialization
template<> void ExpectFunc<VectorDyn<>>::toEqual(const VectorDyn<>& other, double eps) const {
    if (cur.size() != other.size()) {
        error("Sizes not equal (%d != %d) for Vectors\n", cur.size(), other.size());
        return;
    }

    for (uint i = 0; i < cur.size(); i++) {
        if (std::abs(cur[i] - other[i]) > eps) {
            error("Vectors index %d: %.3f != %.3f\n", i, cur[i], other[i]);
        }
    }
}

// Double specialization
template<> void ExpectFunc<double>::toEqual(const double& other, double eps) const {
    if (std::abs(cur - other) > eps)
        error("%.3f != %.3f\n", cur, other);
}

// Float specialization
template<> void ExpectFunc<float>::toEqual(const float& other, double eps) const {
    if (std::abs(cur - other) > eps)
        error("%.3f != %.3f\n", cur, other);
}

// Integer specialization
template<> void ExpectFunc<int>::toEqual(const int& other, double eps) const {
    if (cur != other)
        error("%d != %d\n", cur, other);
}


#endif