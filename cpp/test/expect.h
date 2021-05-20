#ifndef __EXPECT_H__
#define __EXPECT_H__

#include <iostream>
#include <string>
#include <vector>
#include "../include/leon/console_colors.h"
#include "../include/leon/vectordyn.h"
#include "../include/leon/matrixdyn.h"

std::string curTitle = "";
uint failedTests = 0;
uint subTestCount = 0;

int curTestLine;
char* curTestFile;

typedef void (*test_func)(void);

#define error(s, ...) {fprintf(stderr, "   %s✕ Test #%d Failed (File %s, line %d) – %s", console_colors::RED, subTestCount, __FILE__, __LINE__, console_colors::RESET); fprintf(stderr, s, ##__VA_ARGS__); failedTests++; errored = true;}
#define success() { if (!errored) fprintf(stderr, "   %s✓ Test #%d Succeeded%s\n", console_colors::GREEN, subTestCount, console_colors::RESET);}


template<typename T>
class ExpectFunc {
public:
    ExpectFunc(const T& cur_): cur(cur_), errored(false) {}

    void toEqual(const T& other, double eps = 1e-5);

private:
    const T& cur;
    bool errored;
};


void test(const std::string& title, test_func f) {
    failedTests = 0;
    subTestCount = 0;
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
template<> void ExpectFunc<VectorDyn<>>::toEqual(const VectorDyn<>& other, double eps) {
    subTestCount++;
    if (cur.size() != other.size()) {
        error("Sizes not equal (%d != %d) for Vectors\n", cur.size(), other.size());
        return;
    }

    for (uint i = 0; i < cur.size(); i++) {
        if (std::abs(cur[i] - other[i]) > eps) {
            error("Vectors index %d: %.3f != %.3f\n", i, cur[i], other[i]);
        }
    }
    success();
}

// MatrixDyn specialization
template<> void ExpectFunc<MatrixDyn<>>::toEqual(const MatrixDyn<>& other, double eps) {
    subTestCount++;
    uint M = cur.num_rows();
    uint N = cur.num_cols();
    if (N != other.num_cols() || M != other.num_rows()) {
        error("Sizes not equal ([%d x %d] != [%d x %d]) for Matrices\n", M, N, other.num_rows(), other.num_cols());
        return;
    }

    for (uint i = 0; i < N; i++) {
        for (uint j = 0; j < M; j++) {
            if (std::abs(cur[i][j] - other[i][j]) > eps) {
                error("Matrices index [%d, %d]: %.3f != %.3f\n", i, j, cur[i][j], other[i][j]);
            }
        }
    }
    success();
}

// Double specialization
template<> void ExpectFunc<double>::toEqual(const double& other, double eps) {
    subTestCount++;
    if (std::abs(cur - other) > eps)
        error("%.3f != %.3f\n", cur, other);
    success();
}

// Float specialization
template<> void ExpectFunc<float>::toEqual(const float& other, double eps) {
    subTestCount++;
    if (std::abs(cur - other) > eps)
        error("%.3f != %.3f\n", cur, other);
    success();
}

// Integer specialization
template<> void ExpectFunc<int>::toEqual(const int& other, double eps) {
    subTestCount++;
    if (cur != other)
        error("%d != %d\n", cur, other);
    success();
}


#endif