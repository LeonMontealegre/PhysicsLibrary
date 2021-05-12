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


    return 0;
}
