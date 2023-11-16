// include/neptune/nn.hpp

#ifndef NN_HPP
#define NN_HPP
#include "matrix.hpp"

namespace Neptune {
    
using Matrices = std::vector<Neptune::Matrix>;
using Indices = std::vector<Index>;
template<Index... Shape>
class NN {
private:
    Index count_{};
    Indices architecture_{};
    Matrices weights_{};
    Matrices biases_{};
    Matrices activations_{};

public:
    NN() : count_{ sizeof...(Shape) - 1 }, architecture_{ Shape... } {
        assert(sizeof...(Shape) > 0);

        weights_.reserve(count_);
        biases_.reserve(count_);
        activations_.reserve(count_ + 1);

        activations_[0] = Neptune::Matrix{ 1, architecture_[0] }; 
        for (Index i{ 1 }; i < sizeof...(Shape); ++i) {
            weights_[i - 1] = Neptune::Matrix{ activations_[i - 1].getCols(), architecture_[i] };
            biases_[i - 1]  = Neptune::Matrix{ 1, architecture_[i] };
            activations_[i] = Neptune::Matrix{ 1, architecture_[i] };
        }
    }

    Matrix& operator[] (Index index) {
        return activations_[index];
    }

    friend std::ostream& operator<<(std::ostream& out, const NN& nn) {
        out << std::fixed;
        out << std::setprecision(4);
        out << "nn\n[";
        for (Neptune::Index i{ 0 }; i < nn.count_; ++i) {
            if (i != 0)
                out << ' ';
            out << "\nw[" << i << "]\n" << nn.weights_[i] << '\n';
            out << "\nb[" << i << "]\n" << nn.biases_[i];
            if (i != (nn.count_ - 1))
                out << '\n';
        }
        out << ']';

        out << "a\n[";
        for (Neptune::Index j{ 0 }; j < nn.count_ + 1; ++j)
        {
            if (j != 0)
                out << ' ';
            out << "\na[" << j << "]\n" << nn.activations_[j];
            if (j != (nn.count_ - 1))
                out << '\n';
        }
        return out;
    }

    float cost(Matrix ti, Matrix to) {
        assert(ti.getRows() == to.getRows());
        assert(to.getCols() == activations_[count_].getCols());
        Index n{ ti.getRows() };

        float c{ 0.0f };
        for (Index i{ 0 }; i < n; ++i)
        {
            Matrix x{ ti.row(i) };
            Matrix y{ to.row(i) };

            activations_[0] = x;
            forward();

            Index q{ to.getCols() };
            for (Index j{ 0 }; j < q; ++j)
            {
                float d{ activations_[count_][j] - y[j] };
                c += d*d;
            }

        }
        return (c / n);
    }

    void finite_diff(NN& g, float eps, Matrix ti, Matrix to) {
        float saved{};
        float c{ cost(ti, to) };
        for (Index i{ 0 }; i < count_; ++i) {
            for (Index j{ 0 }; j < weights_[i].getRows(); ++j) {
                for (Index k{ 0 }; k < weights_[i].getCols(); ++k) {
                    saved = weights_[i](j, k);
                    weights_[i](j, k) += eps;
                    g.weights_[i](j, k) = (cost(ti, to) - c) / eps;
                    weights_[i](j, k) = saved;
                }
            }

            for (Index j{ 0 }; j < biases_[i].getRows(); ++j) {
                for (Index k{ 0 }; k < biases_[i].getCols(); ++k) {
                    saved = biases_[i](j, k);
                    biases_[i](j, k) += eps;
                    g.biases_[i](j, k) = (cost(ti, to) - c) / eps;
                    biases_[i](j, k) = saved;
                }
            }
        }
    }

    void forward() {
        for (Index i{ 0 }; i < count_; ++i) {
            activations_[i + 1] = activations_[i].dot(weights_[i]);
            activations_[i + 1] = activations_[i + 1] + biases_[i];
            activations_[i + 1].sigmoid();
        }
    }

    Index getCount() {
        return count_;
    }

    void learn(NN& g, float rate) {
        for (Index i{ 0 }; i < count_; ++i) {
            for (Index j{ 0 }; j < weights_[i].getRows(); ++j) {
                for (Index k{ 0 }; k < weights_[i].getCols(); ++k) {
                    weights_[i](j, k) -= rate*g.weights_[i](j, k);
                }
            }

            for (Index j{ 0 }; j < biases_[i].getRows(); ++j) {
                for (Index k{ 0 }; k < biases_[i].getCols(); ++k) {
                    biases_[i](j, k) -= rate*g.biases_[i](j, k);
                }
            }
        }
    }

    void rand(float low = 0.0f, float high = 1.0f) {
        for (Index i{ 0 }; i < count_; ++i) {
            weights_[i].rand(low, high);
            biases_[i].rand(low, high);
        }
    }
};

}
#endif