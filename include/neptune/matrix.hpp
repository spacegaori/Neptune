// include/neptune/matrix.hpp
#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <algorithm>
#include <cassert>
#include <cmath>
#include <concepts>
#include <cstddef>
#include <iostream>
#include <iterator>
#include <random>
#include <string>
#include <type_traits>
#include <vector>

float rand_float();
float sigmoidf(float x);

using Vector = std::vector<float>;
using Index = Vector::size_type;

class Matrix {
private:
    Index m_rows {};
    Index m_cols {};
    Vector m_elements {};
    
public:
    Matrix(Index rows = 0, Index cols = 0) : m_rows{ rows }, m_cols{ cols }, m_elements{ Vector(rows*cols, 0.0f) } {}
    Matrix(Index rows, Index cols, Vector elements) : m_rows{ rows }, m_cols{ cols }, m_elements{ elements } {}

    void alloc(Vector es)
    {
        m_elements = es;
    }

    auto at(Index i)
    {
        return m_elements.at(i);
    }

    auto capacity()
    {
        return m_elements.capacity();
    }

    Matrix col(Index c)
    {
        Matrix dst(m_rows, 1);
        for (Index i{ 0 }; i < m_rows; ++i)
        {
            dst.m_elements.at(i) = m_elements.at(c + i*m_cols);
        }

        return dst;
    }

    Matrix cols(Index begin, Index end)
    {
        assert(end > begin);
        Index cols{ end - begin + 1 };
        Matrix dst(m_rows, cols);

        for (Index i{ 0 }; i < m_rows; ++i)
        {
            for (Index j{ 0 }; j < cols; ++j)
            {
                Index col_index{ j+begin };
                dst.m_elements.at(i*cols+j) = m_elements.at(i*m_cols+col_index);
            }
        }
        return dst;
    }

    void copy(Matrix m)
    {
        m_rows = m.m_rows;
        m_cols = m.m_cols;
        m_elements.clear();
        m_elements = m.m_elements;
    }
    
    Matrix dot(Matrix m)
    {
        Matrix dst(m_rows, m.m_cols);
        assert(m_cols == m.m_rows);
        Index size{ m_cols };
        assert(dst.m_rows == m_rows);
        assert(dst.m_cols == m.m_cols);

        for (Index i{ 0 }; i < dst.m_rows; ++i) {
            for (Index j{ 0 }; j < dst.m_cols; ++j) {
                dst.m_elements.at(i*dst.m_cols+j) = 0.0f;
                for (Index k{ 0 }; k < size; ++k) {
                    dst.m_elements.at(i*dst.m_cols+j) += m_elements.at(i*m_cols+k) * m.m_elements.at(k*m.m_cols+j);
                }
            }
        }
        return dst;
    }

    void fill(float f)
    {
        m_elements = Vector(m_rows*m_cols, f);
    }

    Index getCols()
    {
        return m_cols;
    }

    Index getRows()
    {
        return m_rows;
    }
    
    void print(std::string_view name)
    {
        std::cout << name << " = [\n";
        for (Index i{ 0 }; i < m_rows; ++i) {
            for (Index j{ 0 }; j < m_cols; ++j) {
                std::cout << "  " << m_elements.at(i*m_cols+j) << " ";
            }
            std::cout << '\n';
        }
        std::cout << "]\n";
    }

    void rand(float low, float high)
    {
        m_elements.clear();
        for (Index i{ 0 }; i < m_rows*m_cols; ++i)
            m_elements.push_back(rand_float()*(high-low)+low);
    }

    Matrix row(Index r)
    {
        Matrix dst(1, m_cols);
        Index begin_offset{ r*m_cols };
        Index end_offset{ (r+1)*m_cols };
        Vector slice(m_elements.begin()+static_cast<long>(begin_offset), m_elements.begin()+static_cast<long>(end_offset));
        dst.alloc(slice);

        return dst;
    }

    void set(Index i, float f)
    {
        m_elements.at(i) = f;
    }

    void sig()
    {
        std::for_each(m_elements.begin(), m_elements.end(), [](float &f){ f = sigmoidf(f); });
    }

    auto size()
    {
        return m_elements.size();
    }

    void sub_at(Index i, float f)
    {
        m_elements.at(i) -= f;
    }

    void sum(Matrix m)
    {
        assert(m_rows == m.m_rows);
        assert(m_cols == m.m_cols);
        std::transform(m_elements.begin(), m_elements.end(), m.m_elements.begin(), m_elements.begin(), std::plus<float>());
    }

    void sum_at(Index i, float f)
    {
        m_elements.at(i) += f;
    }
};

float rand_float()
{
    std::mt19937 mt{ std::random_device{}() };
    std::uniform_real_distribution rand(0.0, 1.0);

    return rand(mt);
}

float sigmoidf(float f)
{
    return 1.0f / (1.0f + std::expf(-f));
}

#endif