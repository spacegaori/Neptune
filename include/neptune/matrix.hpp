// include/neptune/matrix.hpp
#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <algorithm>
#include <array>
#include <cassert>
#include <cmath>
#include <concepts>
#include <cstddef>
#include <format>
#include <functional>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <random>
#include <string>
#include <type_traits>
#include <vector>

namespace Neptune {

using Vector = std::vector<float>;
using Index = Vector::size_type;
class Matrix {
private:
    Index rows_{};
    Index cols_{};
    Vector elements_{};
    
public:
    Matrix(Index rows = 0, Index cols = 0, float f = 0.0f) : rows_{ rows }, cols_{ cols }, elements_{ Vector(rows*cols, f) } {}
    Matrix(Index rows, Index cols, Vector elements) : rows_{ rows }, cols_{ cols }, elements_{ elements }
    {
        assert(rows*cols == std::size(elements));
    }

    float& operator() (Index row, Index col)
    {
        assert(row*cols_ + col < rows_*cols_);
        assert(row >= 0);
        assert(col >= 0);
        return elements_.at(row*cols_ + col);
    }

    float& operator[] (Index index)
    {
        assert(index >= 0 && index < std::size(elements_));
        return elements_.at(index);
    }

    friend std::ostream& operator<<(std::ostream& out, const Matrix& matrix)
    {
        assert(0 < std::size(matrix.elements_));
        out << std::fixed;
        out << std::setprecision(4);

        Index rows{ matrix.rows_ };
        Index cols{ matrix.cols_ };

        out << '[';
        for(Index i{ 0 }; i < rows; ++i)
        {
            if (i != 0)
                out << ' ';
            out << '[';

            for(Index j{ 0 }; j < cols; ++j)
            {
                out << matrix.elements_.at(i*cols+j);
                if (j != (cols - 1))
                    out << ' ';
            }
            out << ']';
            if (i != (rows - 1))
                out << '\n';
        }
        out << ']';
        return out;

    }

    bool operator! () const {
        return (rows_*cols_ > 0);
    }

    friend Matrix operator+(const Matrix& m, const Matrix& n) {
        assert(m.rows_ == n.rows_);
        assert(m.cols_ == n.cols_);
        Vector u = m.elements_;
        Vector v = n.elements_;
        std::transform(u.cbegin(), u.cend(), v.cbegin(), u.begin(), std::plus<float>());

        return Matrix{ m.rows_, m.cols_, u };
    }

    friend Matrix operator+(const Matrix& m, float value) {
        Vector v = m.elements_;
        std::transform(v.cbegin(), v.cend(), v.begin(), [value](float f){ return f + value; });

        return Matrix{ m.rows_, m.cols_, v };
    }

    friend Matrix operator-(const Matrix& m, const Matrix& n) {
        assert(m.rows_ == n.rows_);
        assert(m.cols_ == n.cols_);
        Vector u = m.elements_;
        Vector v = n.elements_;
        std::transform(u.cbegin(), u.cend(), v.cbegin(), u.begin(), std::minus<float>());

        return Matrix{ m.rows_, m.cols_, u };
    }

    friend Matrix operator-(const Matrix& m, float value) {
        Vector v = m.elements_;
        std::transform(v.cbegin(), v.cend(),v.begin(), [value](float f){return f - value;});

        return Matrix{ m.rows_, m.cols_, v };
    }

    Matrix operator-() const {
        Matrix negativeMat = *this;
        std::transform(negativeMat.elements_.cbegin(), negativeMat.elements_.cend(), negativeMat.elements_.begin(), std::negate<float>());

        return negativeMat;
    }

    void alloc(Vector elements)
    {
        assert(rows_*cols_ == std::size(elements));
        elements_ = elements;
    }

    auto capacity()
    {
        return elements_.capacity();
    }

    Matrix dot(Matrix m)
    {
        Matrix dst(rows_, m.cols_);
        assert(cols_ == m.rows_);
        Index size{ cols_ };
        assert(dst.rows_ == rows_);
        assert(dst.cols_ == m.cols_);

        for (Index i{ 0 }; i < dst.rows_; ++i) {
            for (Index j{ 0 }; j < dst.cols_; ++j) {
                dst.elements_.at(i*dst.cols_+j) = 0.0f;
                for (Index k{ 0 }; k < size; ++k) {
                    dst.elements_.at(i*dst.cols_+j) += elements_.at(i*cols_+k) * m.elements_.at(k*m.cols_+j);
                }
            }
        }
        return dst;
    }

    Matrix col(Index c)
    {
        Matrix dst(rows_, 1);
        for (Index i{ 0 }; i < rows_; ++i)
        {
            dst.elements_.at(i) = elements_.at(c + i*cols_);
        }

        return dst;
    }

    Index getCols()
    {
        return cols_;
    }

    Index getRows()
    {
        return rows_;
    }

    void rand(float low, float high)
    {
        std::mt19937 mt{ std::random_device{}() };
        std::uniform_real_distribution rand(0.0, 1.0);

        for (Index i{ 0 }; i < rows_*cols_; ++i)
            elements_[i] = (rand(mt)*(high-low)+low);
    }

    Matrix row(Index r)
    {
        Matrix dst(1, cols_);
        Index begin_offset{ r*cols_ };
        Index end_offset{ (r+1)*cols_ };
        Vector slice(elements_.begin()+static_cast<long>(begin_offset), elements_.begin()+static_cast<long>(end_offset));
        dst.alloc(slice);

        return dst;
    }

    void setDimension(Index rows, Index cols)
    {
        rows_ = rows;
        cols_ = cols;
    }

    void sigmoid()
    {
        std::for_each(elements_.begin(), elements_.end(), [](float &f){ f = 1.0f / (1.0f + std::exp(-f)); });
    }

    auto size()
    {
        return elements_.size();
    }
};

}

#endif