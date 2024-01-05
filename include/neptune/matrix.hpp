// include/neptune/matrix.hpp
#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <cassert>
#include <cmath>
#include <cstddef>
#include <iomanip>
#include <iostream>
#include <limits>
#include <mdspan>
#include <numeric>
#include <print>
#include <random>
#include <ranges>
#include <sstream>
#include <utility>
#include <vector>

namespace Neptune {

template<typename T>
class Matrix
{
    using value_type = T;
    using container_type = std::pmr::vector<value_type>;
    using row_index_type = container_type::size_type;
    using col_index_type = container_type::size_type;
    
private:
    container_type  elements_{};
    row_index_type  rows_{};
    col_index_type  cols_{};

public:
    using size_type = container_type::size_type;
    using allocator_type = container_type::allocator_type;
    using init_list_type = std::initializer_list<value_type>;

    constexpr Matrix(row_index_type r, col_index_type c, value_type v = 0)
        : Matrix{ r, c, v, allocator_type{} }
    {
        assert(r > 0);
        assert(c > 0);
    }
    constexpr Matrix(row_index_type r, col_index_type c, value_type v, allocator_type const& a)
        : elements_(r * c, v, a)
        , rows_{ r }
        , cols_{ c }
    {}

    constexpr Matrix(row_index_type r, col_index_type c, init_list_type il)
        : Matrix{ r, c, il, allocator_type{} }
    {
        assert(r * c == il.size());
    }
    constexpr Matrix(row_index_type r, col_index_type c, init_list_type il, allocator_type const& a)
        : elements_(il, a)
        , rows_{ r }
        , cols_{ c }
    {}

    template <std::ranges::input_range R>
        requires std::convertible_to<std::ranges::range_reference_t<R>, value_type>
    Matrix(row_index_type r, col_index_type c, R&& elements)
        : Matrix{ r, c, elements, allocator_type{} }
    {}
    template <std::ranges::input_range R>
        requires std::convertible_to<std::ranges::range_reference_t<R>, value_type>
    Matrix(row_index_type r, col_index_type c, R&& elements, allocator_type const& a)
        : elements_(r * c, a)
        , rows_{ r }
        , cols_{ c }
    {
        std::ranges::copy( std::forward<R>(elements), elements_.begin() );
    }

    constexpr Matrix(Matrix const&) = default;
    constexpr Matrix(Matrix const& m, allocator_type const& a)
        : elements_( m.elements_, a )
        , rows_{ m.rows_ }
        , cols_{ m.cols_ }
    {}
    constexpr Matrix(row_index_type r, col_index_type c, Matrix const& m)
        : Matrix{ r, c, m, allocator_type{} }
    {
        assert(rows_ * cols_ == m.rows_ * m.cols_);
    }
    constexpr Matrix(row_index_type r, col_index_type c, Matrix const& m, allocator_type const& a)
        : elements_( m.elements_, a )
        , rows_{ r }
        , cols_{ c }
    {}

    constexpr Matrix(Matrix&&) noexcept = default;
    constexpr Matrix(Matrix&& m, allocator_type const& a)
        : elements_( std::move(m.elements_), a )
        , rows_{ m.rows_ }
        , cols_{ m.cols_ }
    {}
    constexpr Matrix(row_index_type r, col_index_type c, Matrix&& m)
        : Matrix{ r, c, m, allocator_type{} }
    {
        assert(rows_ * cols_ == m.rows_ * m.cols_);
    }
    constexpr Matrix(row_index_type r, col_index_type c, Matrix&& m, allocator_type const& a)
        : elements_( std::move(m.elements_), a )
        , rows_{ r }
        , cols_{ c }
    {}

    constexpr auto max_size() const& noexcept -> size_type { return elements_.max_size; }

    constexpr auto rows() & noexcept -> size_type { return rows_; }

    constexpr auto rows() const& noexcept -> size_type { return rows_; }

    constexpr auto cols() & noexcept -> size_type { return cols_; }

    constexpr auto cols() const& noexcept -> size_type {  return cols_; }

    auto operator[](row_index_type r, col_index_type c) & noexcept -> value_type& {
        auto v{ std::mdspan{ elements_.data(), rows(), cols() } };

        return v[r, c];
    }

    auto operator[](row_index_type r, col_index_type c) const& noexcept -> const value_type& {
        auto v{ std::mdspan{ elements_.data(), rows(), cols() } };

        return v[r, c];
    }

    auto row(row_index_type r) noexcept -> Matrix {
        container_type row{};
        row.reserve(cols());

        for (size_type i{ 0 }; i < cols(); ++i) {
            row.push_back((*this)[r, i]);
        }
        
        return Matrix{ 1, cols(), row };
    }

    auto col(col_index_type c) noexcept -> Matrix {
        container_type col{};
        col.reserve(rows());

        for (size_type i{ 0 }; i < rows(); ++i) {
            col.push_back((*this)[i, c]);
        }

        return Matrix{ rows(), 1, col };
    }

    auto dot(Matrix const& m) noexcept -> Matrix {
        Matrix p{ rows(), m.cols() };

        for (row_index_type i{ 0 }; i < rows(); ++i) {
            for (col_index_type j{ 0 }; j < m.cols(); ++j) {
                value_type temp{ 0 };
                for (size_type k{ 0 }; k < cols(); ++k) {
                    temp += (*this)[i, k] * m[k, j];
                }
                p[i, j] = temp;
            }
        }
                
        return p;
    }

    template <typename Char, typename Traits>
    friend auto operator<<(std::basic_ostream<Char, Traits>& out, Matrix const& m) -> std::basic_ostream<Char, Traits>& 
    {
        if (out)
        {
            auto oss = std::ostringstream{};
            oss.imbue(std::locale::classic());

            oss << std::fixed;
            oss << std::setprecision(2);

            out << '[';
            for (size_type i{ 0 }; i < m.rows(); ++i)
            {
                if (i != 0)
                    oss << ' ';
                oss << '[';

                for (size_type j{ 0 }; j < m.cols(); ++j)
                {
                    oss << m[i, j];
                    if (j != (m.cols() - 1))
                        oss << ' ';
                }
                oss << ']';
                if (i != (m.rows() - 1))
                    oss << '\n';
            }
            oss << ']';

            out << std::move(oss).str().c_str();
        }

        return out;
    }
};

}

#endif