#include "../include/leon/vectordyn.h"
#include "../include/leon/vector.h"

#include <iostream>
#include "expect.h"

int main() {
    test("VectorDyn – Basic Arithmetic", []() {
        VectorDyn<> v1({3, 4, 5});
        VectorDyn<> v2({7, -12, 2});

        expect(v1+v2).toEqual(VectorDyn<>({10, -8, 7}));
        expect(v1-v2).toEqual(VectorDyn<>({-4, 16, 3}));
        expect(v1*v2).toEqual(VectorDyn<>({21, -48, 10}));

        expect(v1*5).toEqual(VectorDyn<>({15, 20, 25}));
        expect(v1*5.0).toEqual(VectorDyn<>({15, 20, 25}));
        expect(v1*5.0f).toEqual(VectorDyn<>({15, 20, 25}));
    });
    test("Vector – Basic Arithmetic", []() {
        Vector<3> v1({3, 4, 5});
        Vector<3> v2({7, -12, 2});

        expect(v1+v2).toEqual(Vector<3>({10, -8, 7}));
        expect(v1-v2).toEqual(Vector<3>({-4, 16, 3}));
        expect(v1*v2).toEqual(Vector<3>({21, -48, 10}));

        expect(v1*5).toEqual(Vector<3>({15, 20, 25}));
        expect(v1*5.0).toEqual(Vector<3>({15, 20, 25}));
        expect(v1*5.0f).toEqual(Vector<3>({15, 20, 25}));

        expect(v1/5).toEqual(Vector<3>({0.6, 0.8, 1.0}));
    });
    test("VectorDyn – Basic Operations", []() {
        VectorDyn<> v1({3,4,5});
        VectorDyn<> v2({7,8,9});
        VectorDyn<> v3({1,2});
        VectorDyn<> v4({1,2,3,4});

        expect(v1).toEqual(VectorDyn<>({3,4,5}));

        v1 = v2;

        expect(v1).toEqual(VectorDyn<>({7,8,9}));
        expect(v2).toEqual(VectorDyn<>({7,8,9}));

        v2[1] = 28;

        expect(v1).toEqual(VectorDyn<>({7,8,9}));
        expect(v2).toEqual(VectorDyn<>({7,28,9}));

        v1 = v4;

        expect(v1).toEqual(VectorDyn<>({1,2,3,4}));
        expect(v4).toEqual(VectorDyn<>({1,2,3,4}));

        v1 = v3;

        expect(v1).toEqual(VectorDyn<>({1,2}));
        expect(v3).toEqual(VectorDyn<>({1,2}));
    });


    return 0;
}
