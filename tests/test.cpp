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

TEST(BufferSet, Push)
{

}

TEST(BufferSet, Pop)
{
    int v = 0;
    std::iterator<std::input_iterator_tag, int> a();
}

TEST(BufferSet, Insert)
{
    
}

TEST(BufferSet, Erase)
{
    
}