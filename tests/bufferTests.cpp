#include "gtest/gtest.h"
#include "buffer.hpp"

TEST(BufferConstructor, DefaultConstructor) 
{
    sbuf::Buffer<int, 10> buffer;
    ASSERT_EQ(buffer.size(), 0) << "Size was not initialized properly or size function is not returning size properly";
}

TEST(BufferConstructor, InitializationListConstructor) 
{
    sbuf::Buffer<int, 10> buffer({1, 2, 3});
    ASSERT_EQ(buffer.size(), 3) << "Size was not initialized properly or size function is not returning size properly";

    EXPECT_EQ(buffer[0], 1) << "Failed to set buffer[0] to 1 from initialization list!";
    EXPECT_EQ(buffer[1], 2) << "Failed to set buffer[1] to 2 from initialization list!";
    EXPECT_EQ(buffer[2], 3) << "Failed to set buffer[2] to 3 from initialization list!";
}

TEST(BufferConstructor, CopyConstructor) 
{
    sbuf::Buffer<int, 10> bufferA({1, 2, 3});
    sbuf::Buffer<int, 10> bufferB(bufferA);
    ASSERT_EQ(bufferB.size(), 3) << "Size was not initialized properly or size function is not returning size properly";

    EXPECT_EQ(bufferB[0], 1) << "Failed to set bufferB[0] to 1 from initialization list!";
    EXPECT_EQ(bufferB[1], 2) << "Failed to set bufferB[1] to 2 from initialization list!";
    EXPECT_EQ(bufferB[2], 3) << "Failed to set bufferB[2] to 3 from initialization list!";

    // Ensure a deepcopy was performed
    bufferB[0] = 4;
    bufferB[1] = 5;
    bufferB[2] = 6;

    EXPECT_TRUE(bufferA[0] == 1) << "Failed to deep copy bufferA!";
    EXPECT_TRUE(bufferA[1] == 2) << "Failed to deep copy bufferA!";
    EXPECT_TRUE(bufferA[2] == 3) << "Failed to deep copy bufferA!";
    EXPECT_TRUE(bufferB[0] == 4) << "Failed to set bufferB[0] to 4";
    EXPECT_TRUE(bufferB[1] == 5) << "Failed to set bufferB[1] to 5";
    EXPECT_TRUE(bufferB[2] == 6) << "Failed to set bufferB[2] to 6";
}

TEST(BufferConstructor, MoveConstructor)
{
    sbuf::Buffer<int, 10> buffer(sbuf::Buffer<int, 10>({1, 2, 3}));
    ASSERT_EQ(buffer.size(), 3) << "Size was not initialized properly or size function is not returning size properly";

    EXPECT_EQ(buffer[0], 1) << "Failed to set buffer[0] to 1 from move!";
    EXPECT_EQ(buffer[1], 2) << "Failed to set buffer[1] to 2 from move!";
    EXPECT_EQ(buffer[2], 3) << "Failed to set buffer[2] to 3 from move!";
}

TEST(BufferEqualities, List)
{
    sbuf::Buffer<int, 3> buffer({1, 2, 3});
    std::initializer_list<int> listA({1, 2, 3});
    EXPECT_EQ(buffer, listA);

    std::initializer_list<int> listB({1, 2, 3, 4});
    EXPECT_NE(buffer, listB);

    std::initializer_list<int> listC({1, 2, 4});
    EXPECT_NE(buffer, listC);
}

TEST(BufferEqualities, Buffer)
{
    sbuf::Buffer<int, 4> bufferA({1, 2, 3});
    sbuf::Buffer<int, 4> bufferB({1, 2, 3});
    EXPECT_EQ(bufferA, bufferB);

    sbuf::Buffer<int, 4> bufferC({1, 2, 3, 4});
    EXPECT_NE(bufferA, bufferC);

    sbuf::Buffer<int, 4> bufferD({1, 2, 4});
    EXPECT_NE(bufferA, bufferD);
}

TEST(BufferGet, Size)
{
    const sbuf::Buffer<int, 10> bufferA({1, 2, 3});
    EXPECT_EQ(bufferA.size(), 3) << "Size function reporting size of buffer {1, 2, 3} to be " + std::to_string(bufferA.size());

    const sbuf::Buffer<int, 10> bufferB({1, 2, 3, 4, 5});
    EXPECT_EQ(bufferB.size(), 5) << "Size function reporting size of buffer {1, 2, 3, 4, 5} to be " + std::to_string(bufferB.size());
}

TEST(BufferGet, Capacity)
{
    const sbuf::Buffer<int, 5> bufferA;
    EXPECT_EQ(bufferA.capacity(), 5) << "Capacity function reporting sbuf::Buffer<int, 5> to have capacity of " + std::to_string(bufferA.capacity());

    const sbuf::Buffer<int, 10> bufferB;
    EXPECT_EQ(bufferB.capacity(), 10) << "Capacity function reporting sbuf::Buffer<int, 10> to have capacity of " + std::to_string(bufferB.capacity());
}

TEST(BufferGet, Index)
{
    sbuf::Buffer<int, 5> buffer({1, 2, 3, 4, 5});
    for (int i = 0; i < 5; i++)
    {
        EXPECT_EQ(buffer[i], i + 1);
    }
}

TEST(BufferGet, ConstIndex)
{
    const sbuf::Buffer<int, 5> buffer({1, 2, 3, 4, 5});
    for (int i = 0; i < 5; i++)
    {
        EXPECT_EQ(buffer[i], i + 1);
    }
}

TEST(BufferGet, Back)
{
    sbuf::Buffer<int, 5> buffer({1, 2, 3, 4, 5});
    EXPECT_EQ(buffer.back(), 5);
}

TEST(BufferGet, BackConst)
{
    const sbuf::Buffer<int, 5> buffer({1, 2, 3, 4, 5});
    EXPECT_EQ(buffer.back(), 5);
}

TEST(BufferGet, Front)
{
    sbuf::Buffer<int, 5> buffer({1, 2, 3, 4, 5});
    EXPECT_EQ(buffer.front(), 1);
}

TEST(BufferGet, FrontConst)
{
    const sbuf::Buffer<int, 5> buffer({1, 2, 3, 4, 5});
    EXPECT_EQ(buffer.front(), 1);
}

TEST(BufferSet, InitializationListSet)
{
    sbuf::Buffer<int, 10> buffer = {1, 2, 3};
    ASSERT_EQ(buffer.size(), 3) << "Size was not initialized properly or size function is not returning size properly";

    EXPECT_EQ(buffer[0], 1);
    EXPECT_EQ(buffer[1], 2);
    EXPECT_EQ(buffer[2], 3);
}

TEST(BufferSet, xValueBufferSet)
{
    sbuf::Buffer<int, 10> buffer = sbuf::Buffer<int, 10>({1, 2, 3});
    ASSERT_EQ(buffer.size(), 3) << "Size was not initialized properly or size function is not returning size properly";

    EXPECT_EQ(buffer[0], 1);
    EXPECT_EQ(buffer[1], 2);
    EXPECT_EQ(buffer[2], 3);
}

TEST(BufferSet, lValueBufferSet)
{
    sbuf::Buffer<int, 10> bufferA({1, 2, 3});
    sbuf::Buffer<int, 10> bufferB = bufferA;
    ASSERT_EQ(bufferB.size(), 3) << "Size was not initialized properly or size function is not returning size properly";

    EXPECT_EQ(bufferB[0], 1) << "Failed to set buffer[0] to 1 from equals!";
    EXPECT_EQ(bufferB[1], 2) << "Failed to set buffer[1] to 2 from equals!";
    EXPECT_EQ(bufferB[2], 3) << "Failed to set buffer[2] to 3 from equals!";
}

TEST(BufferSet, IndexSet)
{
    sbuf::Buffer<int, 5> buffer({1, 2, 3, 4, 5});
    for (int i = 0; i < 5; i++)
    {
        buffer[i]--;
    }
    for (int i = 0; i < 5; i++)
    {
        EXPECT_EQ(buffer[i], i);
    }
}

TEST(BufferIterator, BeginMut)
{
    sbuf::Buffer<int, 10> buffer({1, 2, 3, 4, 5});
    auto iterator = buffer.begin();
    EXPECT_EQ(*iterator, 1);
}

TEST(BufferIterator, BeginConst)
{
    const sbuf::Buffer<int, 10> buffer({1, 2, 3, 4, 5});
    auto iterator = buffer.begin();
    EXPECT_EQ(*iterator, 1);
}

TEST(BufferIterator, EndMut)
{
    sbuf::Buffer<int, 10> buffer({1, 2, 3, 4, 5});
    auto iterator = buffer.end();
    EXPECT_EQ(*(iterator - 1), 5);
}

TEST(BufferIterator, EndConst)
{
    const sbuf::Buffer<int, 10> buffer({1, 2, 3, 4, 5});
    auto iterator = buffer.end();
    EXPECT_EQ(*(iterator - 1), 5);
}

TEST(BufferSet, PushBack)
{
    sbuf::Buffer<int, 10> bufferA({1, 2, 3, 4});
    sbuf::Buffer<int, 10> bufferB({1, 2, 3, 4, 5});

    bufferA.pushBack(5);
    EXPECT_EQ(bufferA, bufferB);
}

TEST(BufferSet, PushFront)
{
    sbuf::Buffer<int, 10> bufferA({2, 3, 4, 5});
    sbuf::Buffer<int, 10> bufferB({1, 2, 3, 4, 5});

    bufferA.pushFront(1);
    EXPECT_EQ(bufferA, bufferB);
}

TEST(BufferSet, Pop)
{
    sbuf::Buffer<int, 10> bufferA({1, 2, 3, 4, 5});
    sbuf::Buffer<int, 10> bufferB({1, 2, 3, 4});

    bufferA.pop();

    EXPECT_EQ(bufferA, bufferB);
}

TEST(BufferSet, Insert)
{
    sbuf::Buffer<int, 10> bufferA({1, 2, 4, 5});
    sbuf::Buffer<int, 10> bufferB({1, 2, 3, 4, 5});

    bufferA.insert(2, 3);

    EXPECT_EQ(bufferA, bufferB);

    sbuf::Buffer<int, 10> bufferC({2, 3, 4, 5});
    sbuf::Buffer<int, 10> bufferD({1, 2, 3, 4, 5});

    bufferC.insert(0, 1);

    EXPECT_EQ(bufferC, bufferD);

    sbuf::Buffer<int, 10> bufferE({1, 2, 3, 4});
    sbuf::Buffer<int, 10> bufferF({1, 2, 3, 4, 5});

    bufferE.insert(4, 5);

    EXPECT_EQ(bufferE, bufferF);
}

TEST(BufferSet, Erase)
{
    sbuf::Buffer<int, 10> bufferA({1, 2, 4, 5});
    sbuf::Buffer<int, 10> bufferB({1, 2, 3, 4, 5});

    bufferB.erase(2);

    EXPECT_EQ(bufferA, bufferB);

    sbuf::Buffer<int, 10> bufferC({2, 3, 4, 5});
    sbuf::Buffer<int, 10> bufferD({1, 2, 3, 4, 5});

    bufferD.erase(0);

    EXPECT_EQ(bufferC, bufferD);

    sbuf::Buffer<int, 10> bufferE({1, 2, 3, 4});
    sbuf::Buffer<int, 10> bufferF({1, 2, 3, 4, 5});

    bufferF.erase(4);

    EXPECT_EQ(bufferE, bufferF);
}

struct Struct
{
    Struct() {};
    Struct(int a, int b) : a(a), b(b) {}
    int a, b;

    bool operator==(Struct s) const
    {
        return a == s.a && b == s.b;
    }
    friend std::ostream& operator<<(std::ostream &out, const Struct& obj)
    {
        out << "( " << obj.a << ", " << obj.b << " )";
        return out;
    }
};

TEST(BufferSet, EmplaceBack)
{
    sbuf::Buffer<Struct, 10> bufferA({Struct(1, 1)});
    sbuf::Buffer<Struct, 10> bufferB({Struct(1, 1), Struct(2, 2)});

    bufferA.emplaceBack(2, 2);

    EXPECT_EQ(bufferA, bufferB);
}

TEST(BufferSet, EmplaceFront)
{
    sbuf::Buffer<Struct, 10> bufferA({Struct(2, 2)});
    sbuf::Buffer<Struct, 10> bufferB({Struct(1, 1), Struct(2, 2)});

    bufferA.emplaceFront(1, 1);

    EXPECT_EQ(bufferA, bufferB);
}

TEST(BufferSet, Emplace)
{
    sbuf::Buffer<Struct, 10> bufferA({Struct(1, 1), Struct(3, 3)});
    sbuf::Buffer<Struct, 10> bufferB({Struct(1, 1), Struct(2, 2), Struct(3, 3)});

    bufferA.emplace(1, 2, 2);

    EXPECT_EQ(bufferA, bufferB);

    sbuf::Buffer<Struct, 10> bufferC({Struct(2, 2), Struct(3, 3)});
    sbuf::Buffer<Struct, 10> bufferD({Struct(1, 1), Struct(2, 2), Struct(3, 3)});

    bufferC.emplace(0, 1, 1);

    EXPECT_EQ(bufferC, bufferD);

    sbuf::Buffer<Struct, 10> bufferE({Struct(1, 1), Struct(2, 2)});
    sbuf::Buffer<Struct, 10> bufferF({Struct(1, 1), Struct(2, 2), Struct(3, 3)});

    bufferE.emplace(2, 3, 3);

    EXPECT_EQ(bufferE, bufferF);
}

struct StructNoEqualsOrPrint
{
    StructNoEqualsOrPrint() {};
    StructNoEqualsOrPrint(int a, int b) : a(a), b(b) {}
    int a, b;
};

// Compiler check
TEST(BufferSFINAE, NoEqualsOrPrint)
{
    sbuf::Buffer<StructNoEqualsOrPrint, 10> buffer({StructNoEqualsOrPrint(1, 1)});

    EXPECT_EQ(buffer, buffer);
}

struct Generic {};

TEST(BufferSFINAE, Generic)
{
    sbuf::Buffer<Generic, 10> buffer({(Generic){}});

    EXPECT_EQ(buffer, buffer);
    EXPECT_EQ(buffer.size(), 1);
}