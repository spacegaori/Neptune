// include/neptune/matrix.hpp
#pragma once

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <iomanip>
#include <iostream>
#include <limits>
#include <mdspan>
#include <numeric>
#include <ranges>
#include <sstream>
#include <utility>
#include <vector>

namespace Neptune {

template<typename T>
class Matrix
{
    using value_type        = T;
    using container_type    = std::pmr::vector<value_type>;
    using index_type        = container_type::size_type;
    using row_index_type    = container_type::size_type;
    using col_index_type    = container_type::size_type;
    
private:
    container_type elements_{};
    row_index_type rows_{};
    col_index_type cols_{};

    auto operator[](index_type i) & noexcept      -> value_type& {
        return elements_[i];
    }

    auto operator[](index_type i) const& noexcept -> const value_type& {
        return elements_[i];
    }

public:
    using allocator_type    = container_type::allocator_type;
    using init_list_type    = std::initializer_list<value_type>;

    using iterator          = container_type::iterator;
    using const_iterator    = container_type::const_iterator;

    constexpr Matrix() noexcept = delete;
    constexpr Matrix(Matrix const&) = default;
    constexpr Matrix(Matrix const& m, allocator_type const& a)
        : elements_( m.elements_, a )
        , rows_{ m.rows_ }
        , cols_{ m.cols_ }
    {}
    constexpr Matrix(row_index_type r, col_index_type c, Matrix const& m)
        : Matrix{ r, c, m, allocator_type{} }
    {
        assert(rows() * cols() == m.rows() * m.cols());
    }
    constexpr Matrix(row_index_type r, col_index_type c, Matrix const& m, allocator_type const& a)
        : elements_( m.elements_, a )
        , rows_{ r }
        , cols_{ c }
    {
        assert(r > 0);
        assert(c > 0);
    }

    constexpr Matrix(Matrix&&) noexcept = default;
    constexpr Matrix(Matrix&& m, allocator_type const& a)
        : elements_( std::move(m.elements_), a )
        , rows_{ m.rows_ }
        , cols_{ m.cols_ }
    {
        assert(rows() * cols() == m.rows() * m.cols());
    }
    constexpr Matrix(row_index_type r, col_index_type c, Matrix&& m)
        : Matrix{ r, c, m, allocator_type{} }
    {
        assert(r > 0);
        assert(c > 0);
    }
    constexpr Matrix(row_index_type r, col_index_type c, Matrix&& m, allocator_type const& a)
        : elements_( std::move(m.elements_), a )
        , rows_{ r }
        , cols_{ c }
    {
        assert(rows() * cols() == m.rows() * m.cols());
    }

    constexpr ~Matrix() = default;

    constexpr Matrix(row_index_type r, col_index_type c)
        : Matrix{ r, c, allocator_type{} }
    {
    }
    constexpr Matrix(row_index_type r, col_index_type c, allocator_type const& a)
        : elements_(r * c, a)
        , rows_{ r }
        , cols_{ c }
    {
        assert(r > 0);
        assert(c > 0);
    }

    constexpr Matrix(row_index_type r, col_index_type c, value_type v)
        : Matrix{ r, c, v, allocator_type{} }
    {}
    constexpr Matrix(row_index_type r, col_index_type c, value_type v, allocator_type const& a)
        : elements_(r * c, v, a)
        , rows_{ r }
        , cols_{ c }
    {
        assert(r > 0);
        assert(c > 0);
    }

    constexpr Matrix(row_index_type r, col_index_type c, init_list_type il)
        : Matrix{ r, c, il, allocator_type{} }
    {}
    constexpr Matrix(row_index_type r, col_index_type c, init_list_type il, allocator_type const& a)
        : elements_(il, a)
        , rows_{ r }
        , cols_{ c }
    {
        assert(r > 0);
        assert(c > 0);
        assert(r * c == il.size());
    }

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
        assert(r > 0);
        assert(c > 0);

        std::ranges::copy( std::forward<R>(elements), elements_.begin() );
    }

    constexpr auto operator=(Matrix const&) -> Matrix& = default;
    constexpr auto operator=(Matrix&&) noexcept(
        std::allocator_traits<allocator_type>::propagate_on_container_move_assignment::value or
        std::allocator_traits<allocator_type>::is_always_equal::value) -> Matrix& = default;

    constexpr auto begin() noexcept         -> iterator         { return elements_.begin(); }
    constexpr auto cbegin() const noexcept  -> const_iterator   { return elements_.cbegin(); }
    constexpr auto end() noexcept           -> iterator         { return elements_.end(); }
    constexpr auto cend() const noexcept    -> const_iterator   { return elements_.cend(); }

    constexpr auto rows() & noexcept        -> index_type&          { return rows_; }
    constexpr auto rows() const& noexcept   -> const index_type&    { return rows_; }
    constexpr auto cols() & noexcept        -> index_type&          { return cols_; }
    constexpr auto cols() const& noexcept   -> const index_type&    { return cols_; }

    constexpr auto view()      & noexcept { return std::mdspan{ elements_.data(), rows_, cols_ }; }
    constexpr auto view() const& noexcept { return std::mdspan{ elements_.data(), rows_, cols_ }; }

    auto operator[](row_index_type r, col_index_type c) & noexcept      -> value_type& {
        return view()[r, c];
    }

    auto operator[](row_index_type r, col_index_type c) const& noexcept -> const value_type& {
        return view()[r, c];
    }

    auto operator+=(value_type v) & noexcept   -> Matrix& {
        for (auto& e : (*this)) {
            e += v;
        }

        return (*this);
    }
    auto operator+(value_type v) & noexcept   -> Matrix& {
        return (*this) += v;
    }
    auto operator+=(Matrix const& m) & noexcept   -> Matrix& {
        index_type i{ 0 };
        for (auto& e : (*this)) {
            e += m[i];
            ++i;
        }

        return (*this);
    }
    auto operator+(Matrix const& m) & noexcept   -> Matrix& {
        return (*this) += m;
    }
    auto operator-=(value_type v) & noexcept   -> Matrix& {
        for (auto& e : (*this)) {
            e -= v;
        }

        return (*this);
    }
    auto operator-(value_type v) & noexcept   -> Matrix& {
        return (*this) -= v;
    }
    auto operator-=(Matrix const& m) & noexcept   -> Matrix& {
        index_type i{ 0 };
        for (auto& e : (*this)) {
            e -= m[i];
            ++i;
        }

        return (*this);
    }
    auto operator-(Matrix const& m) & noexcept   -> Matrix& {
        return (*this) -= m;
    }
    auto operator*=(value_type v) & noexcept   -> Matrix& {
        for (auto& e : (*this)) {
            e *= v;
        }

        return (*this);
    }
    auto operator*(value_type v) & noexcept   -> Matrix& {
        return (*this) *= v;
    }
    auto operator*=(Matrix const& m) & noexcept   -> Matrix& {
        index_type i{ 0 };
        for (auto& e : (*this)) {
            e *= m[i];
            ++i;
        }

        return (*this);
    }
    auto operator*(Matrix const& m) & noexcept   -> Matrix& {
        return (*this) *= m;
    }

    auto operator/=(value_type v) & noexcept   -> Matrix& {
        for (auto& e : (*this)) {
            e /= v;
        }

        return (*this);
    }
    auto operator/(value_type v) & noexcept   -> Matrix& {
        return (*this) /= v;
    }
    auto operator/=(Matrix const& m) & noexcept   -> Matrix& {
        index_type i{ 0 };
        for (auto& e : (*this)) {
            e /= m[i];
            ++i;
        }

        return (*this);
    }
    auto operator/(Matrix const& m) & noexcept   -> Matrix& {
        return (*this) /= m;
    }

    auto row(row_index_type r) noexcept -> Matrix {
        container_type row{};
        row.reserve(cols());

        for (index_type i{ 0 }; i < cols(); ++i) {
            row.push_back((*this)[r, i]);
        }
        
        return Matrix{ 1, cols(), row };
    }

    auto col(col_index_type c) noexcept -> Matrix {
        container_type col{};
        col.reserve(rows());

        for (index_type i{ 0 }; i < rows(); ++i) {
            col.push_back((*this)[i, c]);
        }

        return Matrix{ rows(), 1, col };
    }

    auto dot(Matrix const& m) noexcept -> Matrix {
        Matrix p{ rows(), m.cols() };

        for (row_index_type i{ 0 }; i < rows(); ++i) {
            for (col_index_type j{ 0 }; j < m.cols(); ++j) {
                value_type temp{ 0 };
                for (index_type k{ 0 }; k < cols(); ++k) {
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
            for (index_type i{ 0 }; i < m.rows(); ++i)
            {
                if (i != 0)
                    oss << ' ';
                oss << '[';

                for (index_type j{ 0 }; j < m.cols(); ++j)
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