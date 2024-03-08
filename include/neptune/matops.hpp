// #pragma once

#include "matrix.hpp"
#include <random>

namespace Neptune {

template <typename T>
void randomize(Matrix<T> &m) {
    static std::mt19937 mt{ std::random_device{}() };
    static std::uniform_real_distribution<T> urd(0, 1);

    for (auto &e : m) {
        e = urd(mt);
    }
}

template <typename T>
void sigmoid(Matrix<T> &m) {
    std::ranges::for_each(m, [](T &e){ e = 1 / (1 + std::exp(-e)); });
}

}