#include "gtest/gtest.h"
#include "buffer.hpp"

TEST(BufferIteratorDeref, Mut)
{
    int a = 5;
    sbuf::Buffer<int, 5>::Iterator iterator(&a);
    EXPECT_EQ(*iterator, 5);
}

TEST(BufferIteratorDeref, Const)
{
    int a = 5;
    sbuf::Buffer<int, 5>::ConstIterator iterator(&a);
    EXPECT_EQ(*iterator, 5);
}

struct Struct
{
    int a;
    int b;
};

TEST(BufferIteratorArrow, Mut)
{
    Struct a = {2, 5};
    sbuf::Buffer<Struct, 5>::Iterator iterator(&a);
    EXPECT_EQ(iterator->a, a.a);
}

TEST(BufferIteratorArrow, Const)
{
    Struct a = {2, 5};
    sbuf::Buffer<Struct, 5>::ConstIterator iterator(&a);
    EXPECT_EQ(iterator->a, a.a);
}

TEST(BufferIteratorEqual, MutEq)
{
    int a = 1;
    sbuf::Buffer<int, 5>::Iterator iteratorA(&a);
    sbuf::Buffer<int, 5>::Iterator iteratorB(&a);
    EXPECT_EQ(iteratorA, iteratorB);
}

TEST(BufferIteratorEqual, MutNe)
{
    int a = 1;
    int b = 1;
    sbuf::Buffer<int, 5>::Iterator iteratorA(&a);
    sbuf::Buffer<int, 5>::Iterator iteratorB(&b);
    EXPECT_NE(iteratorA, iteratorB);
}

TEST(BufferIteratorEqual, ConstEq)
{
    int a = 1;
    sbuf::Buffer<int, 5>::ConstIterator iteratorA(&a);
    sbuf::Buffer<int, 5>::ConstIterator iteratorB(&a);
    EXPECT_EQ(iteratorA, iteratorB);
}

TEST(BufferIteratorEqual, ConstNe)
{
    int a = 1;
    int b = 1;
    sbuf::Buffer<int, 5>::ConstIterator iteratorA(&a);
    sbuf::Buffer<int, 5>::ConstIterator iteratorB(&b);
    EXPECT_NE(iteratorA, iteratorB);
}