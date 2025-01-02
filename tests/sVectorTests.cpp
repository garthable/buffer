#include "gtest/gtest.h"
#include "sVector.hpp"

TEST(SVectorConstructor, DefaultConstructor) 
{
    svec::SVector<int, 10> SVector;
    ASSERT_EQ(SVector.size(), 0) << "Size was not initialized properly or size function is not returning size properly";
}

TEST(SVectorConstructor, InitializationListConstructor) 
{
    svec::SVector<int, 10> SVector({1, 2, 3});
    ASSERT_EQ(SVector.size(), 3) << "Size was not initialized properly or size function is not returning size properly";

    EXPECT_EQ(SVector[0], 1) << "Failed to set SVector[0] to 1 from initialization list!";
    EXPECT_EQ(SVector[1], 2) << "Failed to set SVector[1] to 2 from initialization list!";
    EXPECT_EQ(SVector[2], 3) << "Failed to set SVector[2] to 3 from initialization list!";
}

TEST(SVectorConstructor, CopyConstructor) 
{
    svec::SVector<int, 10> SVectorA({1, 2, 3});
    svec::SVector<int, 10> SVectorB(SVectorA);
    ASSERT_EQ(SVectorB.size(), 3) << "Size was not initialized properly or size function is not returning size properly";

    EXPECT_EQ(SVectorB[0], 1) << "Failed to set SVectorB[0] to 1 from initialization list!";
    EXPECT_EQ(SVectorB[1], 2) << "Failed to set SVectorB[1] to 2 from initialization list!";
    EXPECT_EQ(SVectorB[2], 3) << "Failed to set SVectorB[2] to 3 from initialization list!";

    // Ensure a deepcopy was performed
    SVectorB[0] = 4;
    SVectorB[1] = 5;
    SVectorB[2] = 6;

    EXPECT_TRUE(SVectorA[0] == 1) << "Failed to deep copy SVectorA!";
    EXPECT_TRUE(SVectorA[1] == 2) << "Failed to deep copy SVectorA!";
    EXPECT_TRUE(SVectorA[2] == 3) << "Failed to deep copy SVectorA!";
    EXPECT_TRUE(SVectorB[0] == 4) << "Failed to set SVectorB[0] to 4";
    EXPECT_TRUE(SVectorB[1] == 5) << "Failed to set SVectorB[1] to 5";
    EXPECT_TRUE(SVectorB[2] == 6) << "Failed to set SVectorB[2] to 6";
}

TEST(SVectorConstructor, MoveConstructor)
{
    svec::SVector<int, 10> SVector(svec::SVector<int, 10>({1, 2, 3}));
    ASSERT_EQ(SVector.size(), 3) << "Size was not initialized properly or size function is not returning size properly";

    EXPECT_EQ(SVector[0], 1) << "Failed to set SVector[0] to 1 from move!";
    EXPECT_EQ(SVector[1], 2) << "Failed to set SVector[1] to 2 from move!";
    EXPECT_EQ(SVector[2], 3) << "Failed to set SVector[2] to 3 from move!";
}

TEST(SVectorEqualities, List)
{
    svec::SVector<int, 3> SVector({1, 2, 3});
    std::initializer_list<int> listA({1, 2, 3});
    EXPECT_EQ(SVector, listA);

    std::initializer_list<int> listB({1, 2, 3, 4});
    EXPECT_NE(SVector, listB);

    std::initializer_list<int> listC({1, 2, 4});
    EXPECT_NE(SVector, listC);
}

TEST(SVectorEqualities, SVector)
{
    svec::SVector<int, 4> SVectorA({1, 2, 3});
    svec::SVector<int, 4> SVectorB({1, 2, 3});
    EXPECT_EQ(SVectorA, SVectorB);

    svec::SVector<int, 4> SVectorC({1, 2, 3, 4});
    EXPECT_NE(SVectorA, SVectorC);

    svec::SVector<int, 4> SVectorD({1, 2, 4});
    EXPECT_NE(SVectorA, SVectorD);
}

TEST(SVectorGet, Size)
{
    const svec::SVector<int, 10> SVectorA({1, 2, 3});
    EXPECT_EQ(SVectorA.size(), 3) << "Size function reporting size of SVector {1, 2, 3} to be " + std::to_string(SVectorA.size());

    const svec::SVector<int, 10> SVectorB({1, 2, 3, 4, 5});
    EXPECT_EQ(SVectorB.size(), 5) << "Size function reporting size of SVector {1, 2, 3, 4, 5} to be " + std::to_string(SVectorB.size());
}

TEST(SVectorGet, Capacity)
{
    const svec::SVector<int, 5> SVectorA;
    EXPECT_EQ(SVectorA.capacity(), 5) << "Capacity function reporting svec::SVector<int, 5> to have capacity of " + std::to_string(SVectorA.capacity());

    const svec::SVector<int, 10> SVectorB;
    EXPECT_EQ(SVectorB.capacity(), 10) << "Capacity function reporting svec::SVector<int, 10> to have capacity of " + std::to_string(SVectorB.capacity());
}

TEST(SVectorGet, Index)
{
    svec::SVector<int, 5> SVector({1, 2, 3, 4, 5});
    for (int i = 0; i < 5; i++)
    {
        EXPECT_EQ(SVector[i], i + 1);
    }
}

TEST(SVectorGet, ConstIndex)
{
    const svec::SVector<int, 5> SVector({1, 2, 3, 4, 5});
    for (int i = 0; i < 5; i++)
    {
        EXPECT_EQ(SVector[i], i + 1);
    }
}

TEST(SVectorGet, Back)
{
    svec::SVector<int, 5> SVector({1, 2, 3, 4, 5});
    EXPECT_EQ(SVector.back(), 5);
}

TEST(SVectorGet, BackConst)
{
    const svec::SVector<int, 5> SVector({1, 2, 3, 4, 5});
    EXPECT_EQ(SVector.back(), 5);
}

TEST(SVectorGet, Front)
{
    svec::SVector<int, 5> SVector({1, 2, 3, 4, 5});
    EXPECT_EQ(SVector.front(), 1);
}

TEST(SVectorGet, FrontConst)
{
    const svec::SVector<int, 5> SVector({1, 2, 3, 4, 5});
    EXPECT_EQ(SVector.front(), 1);
}

TEST(SVectorSet, InitializationListSet)
{
    svec::SVector<int, 10> SVector = {1, 2, 3};
    ASSERT_EQ(SVector.size(), 3) << "Size was not initialized properly or size function is not returning size properly";

    EXPECT_EQ(SVector[0], 1);
    EXPECT_EQ(SVector[1], 2);
    EXPECT_EQ(SVector[2], 3);
}

TEST(SVectorSet, xValueSVectorSet)
{
    svec::SVector<int, 10> SVector = svec::SVector<int, 10>({1, 2, 3});
    ASSERT_EQ(SVector.size(), 3) << "Size was not initialized properly or size function is not returning size properly";

    EXPECT_EQ(SVector[0], 1);
    EXPECT_EQ(SVector[1], 2);
    EXPECT_EQ(SVector[2], 3);
}

TEST(SVectorSet, lValueSVectorSet)
{
    svec::SVector<int, 10> SVectorA({1, 2, 3});
    svec::SVector<int, 10> SVectorB = SVectorA;
    ASSERT_EQ(SVectorB.size(), 3) << "Size was not initialized properly or size function is not returning size properly";

    EXPECT_EQ(SVectorB[0], 1) << "Failed to set SVector[0] to 1 from equals!";
    EXPECT_EQ(SVectorB[1], 2) << "Failed to set SVector[1] to 2 from equals!";
    EXPECT_EQ(SVectorB[2], 3) << "Failed to set SVector[2] to 3 from equals!";
}

TEST(SVectorSet, IndexSet)
{
    svec::SVector<int, 5> SVector({1, 2, 3, 4, 5});
    for (int i = 0; i < 5; i++)
    {
        SVector[i]--;
    }
    for (int i = 0; i < 5; i++)
    {
        EXPECT_EQ(SVector[i], i);
    }
}

TEST(SVectorIterator, BeginMut)
{
    svec::SVector<int, 10> SVector({1, 2, 3, 4, 5});
    auto iterator = SVector.begin();
    EXPECT_EQ(*iterator, 1);
}

TEST(SVectorIterator, BeginConst)
{
    const svec::SVector<int, 10> SVector({1, 2, 3, 4, 5});
    auto iterator = SVector.begin();
    EXPECT_EQ(*iterator, 1);
}

TEST(SVectorIterator, EndMut)
{
    svec::SVector<int, 10> SVector({1, 2, 3, 4, 5});
    auto iterator = SVector.end();
    EXPECT_EQ(*(iterator - 1), 5);
}

TEST(SVectorIterator, EndConst)
{
    const svec::SVector<int, 10> SVector({1, 2, 3, 4, 5});
    auto iterator = SVector.end();
    EXPECT_EQ(*(iterator - 1), 5);
}

TEST(SVectorSet, PushBack)
{
    svec::SVector<int, 10> SVectorA({1, 2, 3, 4});
    svec::SVector<int, 10> SVectorB({1, 2, 3, 4, 5});

    SVectorA.pushBack(5);
    EXPECT_EQ(SVectorA, SVectorB);
}

TEST(SVectorSet, PushFront)
{
    svec::SVector<int, 10> SVectorA({2, 3, 4, 5});
    svec::SVector<int, 10> SVectorB({1, 2, 3, 4, 5});

    SVectorA.pushFront(1);
    EXPECT_EQ(SVectorA, SVectorB);
}

TEST(SVectorSet, PopBack)
{
    svec::SVector<int, 10> SVectorA({1, 2, 3, 4, 5});
    svec::SVector<int, 10> SVectorB({1, 2, 3, 4});

    SVectorA.popBack();

    EXPECT_EQ(SVectorA, SVectorB);
}

TEST(SVectorSet, PopFront)
{
    svec::SVector<int, 10> SVectorA({1, 2, 3, 4, 5});
    svec::SVector<int, 10> SVectorB({2, 3, 4, 5});

    SVectorA.popFront();

    EXPECT_EQ(SVectorA, SVectorB);
}

TEST(SVectorSet, Insert)
{
    svec::SVector<int, 10> SVectorA({1, 2, 4, 5});
    svec::SVector<int, 10> SVectorB({1, 2, 3, 4, 5});

    SVectorA.insert(2, 3);

    EXPECT_EQ(SVectorA, SVectorB);

    svec::SVector<int, 10> SVectorC({2, 3, 4, 5});
    svec::SVector<int, 10> SVectorD({1, 2, 3, 4, 5});

    SVectorC.insert(0, 1);

    EXPECT_EQ(SVectorC, SVectorD);

    svec::SVector<int, 10> SVectorE({1, 2, 3, 4});
    svec::SVector<int, 10> SVectorF({1, 2, 3, 4, 5});

    SVectorE.insert(4, 5);

    EXPECT_EQ(SVectorE, SVectorF);
}

TEST(SVectorSet, Erase)
{
    svec::SVector<int, 10> SVectorA({1, 2, 4, 5});
    svec::SVector<int, 10> SVectorB({1, 2, 3, 4, 5});

    SVectorB.erase(2);

    EXPECT_EQ(SVectorA, SVectorB);

    svec::SVector<int, 10> SVectorC({2, 3, 4, 5});
    svec::SVector<int, 10> SVectorD({1, 2, 3, 4, 5});

    SVectorD.erase(0);

    EXPECT_EQ(SVectorC, SVectorD);

    svec::SVector<int, 10> SVectorE({1, 2, 3, 4});
    svec::SVector<int, 10> SVectorF({1, 2, 3, 4, 5});

    SVectorF.erase(4);

    EXPECT_EQ(SVectorE, SVectorF);
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

TEST(SVectorSet, EmplaceBack)
{
    svec::SVector<Struct, 10> SVectorA({Struct(1, 1)});
    svec::SVector<Struct, 10> SVectorB({Struct(1, 1), Struct(2, 2)});

    SVectorA.emplaceBack(2, 2);

    EXPECT_EQ(SVectorA, SVectorB);
}

TEST(SVectorSet, EmplaceFront)
{
    svec::SVector<Struct, 10> SVectorA({Struct(2, 2)});
    svec::SVector<Struct, 10> SVectorB({Struct(1, 1), Struct(2, 2)});

    SVectorA.emplaceFront(1, 1);

    EXPECT_EQ(SVectorA, SVectorB);
}

TEST(SVectorSet, Emplace)
{
    svec::SVector<Struct, 10> SVectorA({Struct(1, 1), Struct(3, 3)});
    svec::SVector<Struct, 10> SVectorB({Struct(1, 1), Struct(2, 2), Struct(3, 3)});

    SVectorA.emplace(1, 2, 2);

    EXPECT_EQ(SVectorA, SVectorB);

    svec::SVector<Struct, 10> SVectorC({Struct(2, 2), Struct(3, 3)});
    svec::SVector<Struct, 10> SVectorD({Struct(1, 1), Struct(2, 2), Struct(3, 3)});

    SVectorC.emplace(0, 1, 1);

    EXPECT_EQ(SVectorC, SVectorD);

    svec::SVector<Struct, 10> SVectorE({Struct(1, 1), Struct(2, 2)});
    svec::SVector<Struct, 10> SVectorF({Struct(1, 1), Struct(2, 2), Struct(3, 3)});

    SVectorE.emplace(2, 3, 3);

    EXPECT_EQ(SVectorE, SVectorF);
}

struct StructNoEqualsOrPrint
{
    StructNoEqualsOrPrint() {};
    StructNoEqualsOrPrint(int a, int b) : a(a), b(b) {}
    int a, b;
};

// Compiler check
TEST(SVectorSFINAE, NoEqualsOrPrint)
{
    svec::SVector<StructNoEqualsOrPrint, 10> SVector({StructNoEqualsOrPrint(1, 1)});

    EXPECT_EQ(SVector, SVector);
}

struct Generic {};

TEST(SVectorSFINAE, GenericTest)
{
    svec::SVector<Generic, 10> SVector({(Generic){}});

    EXPECT_EQ(SVector, SVector);
    EXPECT_EQ(SVector.size(), 1);
}

#include <algorithm>

TEST(SVectorAlgorithm, FindMut)
{
    svec::SVector<int, 10> SVector({1, 2, 3, 4, 5});
    auto iterator = std::find(SVector.begin(), SVector.end(), 2);

    EXPECT_EQ(*iterator, 2);
}

TEST(SVectorAlgorithm, FindConst)
{
    const svec::SVector<int, 10> SVector({1, 2, 3, 4, 5});
    auto iterator = std::find(SVector.begin(), SVector.end(), 2);

    EXPECT_EQ(*iterator, 2);
}

TEST(SVectorAlgorithm, HeapSort)
{
    svec::SVector<int, 10> SVectorA({5, 3, 2, 4, 1});
    svec::SVector<int, 9> SVectorB({1, 2, 3, 4, 5});

    std::make_heap(SVectorA.begin(), SVectorA.end());
    std::sort_heap(SVectorA.begin(), SVectorA.end());

    EXPECT_EQ(SVectorA, SVectorB);
}