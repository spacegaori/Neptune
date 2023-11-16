// xor/src/main.cpp
#include <neptune.hpp>

int main()
{
    constexpr float eps{ 1e-1 };
    constexpr float rate{ 1e-1 };

    Neptune::NN<2, 2, 1> nn{};
    Neptune::NN<2, 2, 1> g{};

    nn.rand();

    Neptune::Matrix ti{ 4, 2, { 0, 0, 0, 1, 1, 0, 1, 1 } };
    Neptune::Matrix to{ 4, 1, { 0, 1, 1, 0 } };
        
    nn.forward();
    std::cout << "Cost: " << nn.cost(ti, to) << '\n';
    for (Neptune::Index i{ 0 }; i < 60*1000; ++i) {
        nn.finite_diff(g, eps, ti, to);
        nn.learn(g, rate);
        std::cout << "Cost: " << nn.cost(ti, to) << '\n';
    }

    for (Neptune::Index i{ 0 }; i < 2; ++i) {
        for(Neptune::Index j{ 0 }; j < 2; ++j) {
            nn[0](0, 0) = i;
            nn[0](0, 1) = j;
            nn.forward();
            std::cout << i << " ^ " << j << " = " << nn[nn.getCount()](0, 0) << '\n';
        }
    }

    return 0;
}