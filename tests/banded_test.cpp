#include "gtest/gtest.h"
#include "solvant/base/banded_matrix.hpp"

template <std::size_t N>
using triband = solvant::base::banded_matrix<double, N, 3>;

template <std::size_t N>
using quinband = solvant::base::banded_matrix<double, N, 5>;

template <std::size_t N>
using septband = solvant::base::banded_matrix<double, N, 7>;

template <std::size_t N>
using thirtband = solvant::base::banded_matrix<double, N, 13>;

TEST(banded_matrix, in_band) {
    quinband<10> a;
    ASSERT_TRUE(a.in_band(1, 1));
}

TEST(banded_matrix, diagonal_constant_init) {
    triband<5> a({1, 2, 3});
    ASSERT_EQ(a(0, 0), 2);
    ASSERT_EQ(a(0, 1), 3);
    ASSERT_EQ(a(1, 0), 1);
    ASSERT_EQ(a(1, 1), 2);

    quinband<7> b({1, 2, 3, 4, 5});
    ASSERT_EQ(b(0, 0), 3);
    ASSERT_EQ(b(1, 1), 3);
    ASSERT_EQ(b(1, 0), 2);
    ASSERT_EQ(b(2, 0), 1);
}

TEST(banded_matrix, identity_matrix_multiplication) {
    triband<7> id({0, 1, 0});
    triband<7> b({1, 1, 1});
    quinband<7> c;

    matrix_prod(id, b, c);

    for (int i = 0; i < 7; ++i) {
        for (int j = 0; j < 7; ++j) {
            // obtaining references via (i,j) is naughty! 
            // so just continue 
            if(std::abs(i-j) > 1) continue;
            ASSERT_EQ(c(i,j), 1);
        }
    }
}

