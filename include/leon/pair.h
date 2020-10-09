#ifndef __PAIR_H__
#define __PAIR_H__

template<typename A, typename B>
class Pair {
public:
    Pair(A& a_, B& b_): a(a_), b(b_) {}

    A& first() { return A; }
    B& second() { return B; }
private:
    A a;
    B b;
};

#endif