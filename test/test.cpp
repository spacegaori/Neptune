// test/test.cpp
#include <neptune.hpp>
#include <gtest/gtest.h>

// TEST(NeptuneTest, MatrixInitialization0)
// {
//     Matrix m{ 3, 2 };
//     Vector v{ 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f };
//     m = v;

//     Matrix n{ 3, 2, v };

//     ASSERT_EQ(m.size(), n.size());

//     for (int i{ 0 }; i <m.size(); ++i)
//     {
//         EXPECT_EQ(m.at(i), n.at(i)) << "Matrices m and n differ at index " << i;
//     }
// }

// TEST(NeptuneTest, MatrixInitialization0)
// {
//     Matrix m{ 3, 2 };
//     Vector v{ 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f };
//     m.alloc(v);

//     Matrix n{ 3, 2, v };

//     ASSERT_EQ(m.size(), n.size());

//     for (int i{ 0 }; i <m.size(); ++i)
//     {
//         EXPECT_EQ(m.at(i), n.at(i)) << "Matrices m and n differ at index " << i;
//     }
// }

// TEST(NeptuneTest, MatrixInitialization1)
// {
//     Matrix m{ 3, 2 };
//     Vector u{ 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f };
//     m.alloc(u);

//     Vector v{ 1.0f, 2.0f, 4.0f, 3.0f, 5.0f, 6.0f };
//     Matrix n{ 3, 2, v };

//     ASSERT_EQ(m.size(), n.size());

//     for (int i{ 0 }; i <m.size(); ++i)
//     {
//         EXPECT_EQ(m.at(i), n.at(i)) << "Matrices m and n differ at index " << i;
//     }
// }


// TEST(NeptuneTest, MatrixInitialization2)
// {
//     Vector v{ 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f };
//     Matrix n{ 3, 2, v };

//     Matrix o{ 3, 2 };
//     o.set(0, 1.0f);
//     o.set(1, 2.0f);
//     o.set(2, 3.0f);
//     o.set(3, 4.0f);
//     o.set(4, 5.0f);
//     o.set(5, 6.0f);

//     ASSERT_EQ(n.size(), o.size());

//     for (int i{ 0 }; i <n.size(); ++i)
//     {
//         EXPECT_EQ(n.at(i), o.at(i)) << "Matrices n and o differ at index " << i;
//     }
// }

// TEST(NeptuneTest, MatrixInitialization3)
// {
//     Vector v{ 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f };
//     Matrix n{ 3, 2, v };

//     Matrix o{ 3, 2 };
//     o.set(0, 1.0f);
//     o.set(1, 2.0f);
//     o.set(2, 4.0f);
//     o.set(3, 3.0f);
//     o.set(4, 5.0f);
//     o.set(5, 6.0f);

//     ASSERT_EQ(n.size(), o.size());

//     for (int i{ 0 }; i <n.size(); ++i)
//     {
//         EXPECT_EQ(n.at(i), o.at(i)) << "Matrices n and o differ at index " << i;
//     }
// }


// TEST(NeptuneTest, MatrixInitialization4)
// {
//     Matrix m{ 3, 2 };
//     Vector v{ 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f };
//     m.alloc(v);

//     Matrix o{ 3, 2 };
//     o.set(0, 1.0f);
//     o.set(1, 2.0f);
//     o.set(2, 3.0f);
//     o.set(3, 4.0f);
//     o.set(4, 5.0f);
//     o.set(5, 6.0f);

//     ASSERT_EQ(m.size(), o.size());

//     for (int i{ 0 }; i <m.size(); ++i)
//     {
//         EXPECT_EQ(m.at(i), o.at(i)) << "Matrices m and o differ at index " << i;
//     }
// }

// TEST(NeptuneTest, MatrixInitialization5)
// {
//     Matrix m{ 3, 2 };
//     Vector v{ 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f };
//     m.alloc(v);

//     Matrix o{ 3, 2 };
//     o.set(0, 1.0f);
//     o.set(1, 2.0f);
//     o.set(2, 4.0f);
//     o.set(3, 3.0f);
//     o.set(4, 5.0f);
//     o.set(5, 6.0f);

//     ASSERT_EQ(m.size(), o.size());

//     for (int i{ 0 }; i <m.size(); ++i)
//     {
//         EXPECT_EQ(m.at(i), o.at(i)) << "Matrices m and o differ at index " << i;
//     }
// }