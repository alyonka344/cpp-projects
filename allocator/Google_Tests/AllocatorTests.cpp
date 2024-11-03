#include "gtest/gtest.h"
#include "../allocator/Allocator.h"

#include <list>
#include <vector>

TEST(AllocatorTest, PushBackVectorTest1) {
    auto alloc = Allocator<int>({{1, 4}});
    std::vector<int, Allocator<int>> vec(alloc);

    vec.push_back(1);

    ASSERT_TRUE(vec[0] == 1);
}

TEST(AllocatorTest, PushBackVectorTest2) {
    auto alloc = Allocator<int>({{1, 4}});
    std::vector<int, Allocator<int>> vec(alloc);

    EXPECT_THROW({
                     vec.push_back(1);
                     vec.push_back(1);
                 }, std::bad_alloc);

    ASSERT_TRUE(vec[0] == 1);
}

TEST(AllocatorTest, PushBackVectorTest3) {
    auto alloc = Allocator<int>({{2, 64}});
    std::vector<int, Allocator<int>> vec(alloc);
    std::vector<int> vec1 = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    EXPECT_NO_THROW({
                        for (int i = 0; i < 10; ++i) {
                            vec.push_back(i);
                        }
                    });

    ASSERT_TRUE(std::equal(vec.begin(), vec.end(), vec1.begin()));
}

TEST(AllocatorTest, PushBackVectorTest4) {
    auto alloc = Allocator<int>({{1, 64},
                                 {1, 64}});
    std::vector<int, Allocator<int>> vec(alloc);
    std::vector<int> vec1 = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    EXPECT_NO_THROW({
                        for (int i = 0; i < 10; ++i) {
                            vec.push_back(i);
                        }
                    });

    ASSERT_TRUE(std::equal(vec.begin(), vec.end(), vec1.begin()));
}

TEST(AllocatorTest, DeallocateVectorTest1) {
    auto alloc = Allocator<int>({{1, 4},
                                 {1, 8}});
    std::vector<int, Allocator<int>> vec(alloc);
    std::vector<int, Allocator<int>> vec1(alloc);

    EXPECT_NO_THROW({
                        for (int i = 0; i < 2; ++i) {
                            vec.push_back(i);
                        }
                        int* ptr = &vec[0];
                        alloc.deallocate(ptr, 1);
                        vec1.push_back(10);
                    });

    ASSERT_TRUE(vec1[0] == 10 && vec[0] == 0 && vec[1] == 1);
}

TEST(AllocatorTest, DifferentTypeTest1) {
    Allocator<float> alloc = Allocator<float>({{1, 8},
                                               {1, 8}});
    std::vector<int, Allocator<int>> vec(alloc);

    EXPECT_NO_THROW({
                        vec.push_back(1);
                        vec.push_back(2);
                    });

    ASSERT_TRUE(vec[0] == 1 && vec[1] == 2);
}

TEST(AllocatorTest, DifferentTypeTest2) {
    Allocator<float> alloc = Allocator<float>({{1, 8},
                                               {1, 8}});
    Allocator<bool> alloc1 = Allocator<bool>(alloc);

    std::vector<int, Allocator<int>> vec(alloc);
    std::vector<int, Allocator<int>> vec1(alloc1);

    EXPECT_NO_THROW({
                        vec1 = vec;
                    });
}

TEST(AllocatorTest, DeallocateVectorTest2) {
    auto alloc = Allocator<int>({{1, 16},
                                 {1, 16}});
    std::vector<int, Allocator<int>> vec(alloc);
    std::vector<int, Allocator<int>> vec1(alloc);

    EXPECT_NO_THROW({
                        for (int i = 0; i < 3; ++i) {
                            vec.push_back(i);
                        }
                        int* ptr = &vec[0];
                        alloc.deallocate(ptr, 1);
                        vec1.push_back(10);
                    });

    ASSERT_TRUE(vec1[0] == 10 && vec[0] == 10 && vec[1] == 1);
}

TEST(AllocatorTest, CopyConstructorTest1) {
    auto alloc = Allocator<int>({{1, 16},
                                 {1, 16}});
    auto alloc1 = Allocator<int>(alloc);
    std::vector<int, Allocator<int>> vec(alloc);
    std::vector<int, Allocator<int>> vec1(alloc1);

    EXPECT_NO_THROW({
                        for (int i = 0; i < 3; ++i) {
                            vec.push_back(i);
                        }
                        int* ptr = &vec[0];
                        alloc.deallocate(ptr, 1);
                        vec1.push_back(10);
                    });

    ASSERT_TRUE(vec1[0] == 10 && vec[0] == 10 && vec[1] == 1);
}

TEST(AllocatorTest, PushBackListTest1) {
    Allocator<int> alloc = Allocator<int>({{1, 24}});
    std::list<int, Allocator<int>> list(alloc);

    list.push_back(100);

    ASSERT_EQ(*list.begin(), 100);
}

TEST(AllocatorTest, PushBackListTest2) {
    Allocator<int> alloc = Allocator<int>({{1, 24}});
    std::list<int, Allocator<int>> list(alloc);

    EXPECT_THROW({
                     list.push_back(5);
                     list.push_back(9);
                 }, std::bad_alloc);

    ASSERT_EQ(*list.begin(), 5);
}
