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

    // // Default constructor
    // constexpr Matrix() noexcept = default;
    // constexpr explicit Matrix(allocator_type const& a) noexcept
    //     : elements_( a )
    // {
    //     for (auto &e : elements_) {
    //         std::cout << e << ' ';
    //     }
    //     std::cout << '\n';
    // }

    // Copy constructor
    constexpr Matrix(Matrix const&) = default;
    constexpr Matrix(Matrix const& m, allocator_type const& a)
        : elements_( m.elements_, a )
        , rows_{ m.rows_ }
        , cols_{ m.cols_ }
    {
        std::cout << "Matrix const& m, allocator_type const& a\n";
    }
    constexpr Matrix(row_index_type r, col_index_type c, Matrix const& m)
        : Matrix{ r, c, m, allocator_type{} }
    {
        std::cout << "Matrix(row_index_type r, col_index_type c, Matrix const& m)\n";
    }
    constexpr Matrix(row_index_type r, col_index_type c, Matrix const& m, allocator_type const& a)
        : elements_( m.elements_, a )
        , rows_{ r }
        , cols_{ c }
    {
        assert(rows_ * cols_ == m.rows_ * m.cols_);
        std::cout << "Matrix(row_index_type r, col_index_type c, Matrix const& m, allocator_type const& a)\n";
    }

    // Move constructor
    constexpr Matrix(Matrix&&) noexcept = default;
    constexpr Matrix(Matrix&& m, allocator_type const& a)
        : elements_( std::move(m.elements_), a )
        , rows_{ m.rows_ }
        , cols_{ m.cols_ }
    {
        std::cout << "Matrix(Matrix&& m, allocator_type const& a)\n";
    }
    constexpr Matrix(row_index_type r, col_index_type c, Matrix&& m)
        : Matrix{ r, c, m, allocator_type{} }
    {
        std::cout << "Matrix(row_index_type r, col_index_type c, Matrix&& m)\n";
    }
    constexpr Matrix(row_index_type r, col_index_type c, Matrix&& m, allocator_type const& a)
        : elements_( std::move(m.elements_), a )
        , rows_{ r }
        , cols_{ c }
    {
        assert(rows_ * cols_ == m.rows_ * m.cols_);
        std::cout << "Matrix(row_index_type r, col_index_type c, Matrix&& m, allocator_type const& a)\n";
    }

    constexpr Matrix(row_index_type r, col_index_type c, value_type v = 0)
        : Matrix{ r, c, v, allocator_type{} }
    {
        assert(r > 0);
        assert(c > 0);
        std::cout << "Matrix(row_index_type r, col_index_type c, value_type v = 0)\n";
    }
    constexpr Matrix(row_index_type r, col_index_type c, value_type v, allocator_type const& a)
        : elements_(r * c, v, a)
        , rows_{ r }
        , cols_{ c }
    {
        std::cout << "Matrix(row_index_type r, col_index_type c, value_type v, allocator_type const& a)\n";
    }

    constexpr Matrix(row_index_type r, col_index_type c, init_list_type il)
        : Matrix{ r, c, il, allocator_type{} }
    {
        assert(r * c == il.size());
        std::cout << "Matrix(row_index_type r, col_index_type c, init_list_type il)\n";

    }
    constexpr Matrix(row_index_type r, col_index_type c, init_list_type il, allocator_type const& a)
        : elements_(il, a)
        , rows_{ r }
        , cols_{ c }
    {
        std::cout << "Matrix(row_index_type r, col_index_type c, init_list_type il, allocator_type const& a)\n";
    }

    template <std::ranges::input_range R>
        requires std::convertible_to<std::ranges::range_reference_t<R>, value_type>
    Matrix(row_index_type r, col_index_type c, R&& elements)
        : Matrix{ r, c, elements, allocator_type{} }
    {
        std::cout << "Matrix(row_index_type r, col_index_type c, R&& elements)\n";
    }
    template <std::ranges::input_range R>
        requires std::convertible_to<std::ranges::range_reference_t<R>, value_type>
    Matrix(row_index_type r, col_index_type c, R&& elements, allocator_type const& a)
        : elements_(r * c, a)
        , rows_{ r }
        , cols_{ c }
    {
        std::cout << "Matrix(row_index_type r, col_index_type c, R&& elements, allocator_type const& a)\n";

        std::ranges::copy( std::forward<R>(elements), elements_.begin() );
    }

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
        // return std::submdspan(ms, index, std::full_extent);
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

        auto size{ cols() };

        for (row_index_type i{ 0 }; i < rows(); ++i) {
            for (col_index_type j{ 0 }; j < m.cols(); ++j) {
                value_type temp{ 0 };
                for (size_type k{ 0 }; k < size; ++k) {
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

            row_index_type r{ m.rows() };
            col_index_type c{ m.cols() };

            out << '[';
            for(size_type i{ 0 }; i < r; ++i)
            {
                if (i != 0)
                    oss << ' ';
                oss << '[';

                for(size_type j{ 0 }; j < c; ++j)
                {
                    oss << m[i, j];
                    if (j != (c - 1))
                        oss << ' ';
                }
                oss << ']';
                if (i != (r - 1))
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