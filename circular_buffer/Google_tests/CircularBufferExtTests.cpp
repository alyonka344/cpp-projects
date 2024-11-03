#include "gtest/gtest.h"
#include "../CCircularBufferExt/CCircularBufferExt.h"

TEST(CCIRCULAR_BUFFER_EXT_TEST, CONSTRUCTOR_TEST_1) {
    CCircularBufferExt<int> buffer;
    ASSERT_TRUE(buffer.empty());
}

TEST(CCIRCULAR_BUFFER_EXT_TEST, CONSTRUCTOR_TEST_2) {
    CCircularBufferExt<int> buffer(10);
    ASSERT_TRUE(buffer.max_size() == 10);
    ASSERT_TRUE(buffer.empty());
}

TEST(CCIRCULAR_BUFFER_EXT_TEST, CONSTRUCTOR_TEST_3) {
    std::vector<int> vector = {1, 2, 3, 4, 5};
    CCircularBufferExt<int> buffer({1, 2, 3, 4, 5});
    ASSERT_TRUE(std::equal(buffer.begin(), buffer.end(), vector.begin(), vector.end()));
    ASSERT_FALSE(buffer.empty());
    ASSERT_TRUE(buffer.size() == 5);
    ASSERT_TRUE(buffer.max_size() == 5);
}

TEST(CCIRCULAR_BUFFER_EXT_TEST, CONSTRUCTOR_TEST_4) {
    std::vector<int> vector = {1, 2, 3, 4, 5};
    CCircularBufferExt<int> buffer = {1, 2, 3, 4, 5};
    ASSERT_TRUE(std::equal(buffer.begin(), buffer.end(), vector.begin(), vector.end()));
    ASSERT_FALSE(buffer.empty());
    ASSERT_TRUE(buffer.size() == 5);
    ASSERT_TRUE(buffer.max_size() == 5);
}

TEST(CCIRCULAR_BUFFER_EXT_TEST, CONSTRUCTOR_TEST_5) {
    std::vector<int> vector = {1, 2, 3, 4, 5};
    CCircularBufferExt<int> buffer(vector.begin() + 1, vector.end() - 1);
    ASSERT_TRUE(std::equal(buffer.begin(), buffer.end(), vector.begin() + 1, vector.end() - 1));
    ASSERT_FALSE(buffer.empty());
    ASSERT_TRUE(buffer.size() == 3);
    ASSERT_TRUE(buffer.max_size() == 3);
}

TEST(CCIRCULAR_BUFFER_EXT_TEST, CONSTRUCTOR_TEST_6) {
    CCircularBufferExt<int> buffer_to_copy = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    CCircularBufferExt<int> buffer(buffer_to_copy);
    ASSERT_TRUE(buffer == buffer_to_copy);
    *buffer.begin() = 222;
    ASSERT_TRUE(buffer != buffer_to_copy);
    ASSERT_FALSE(buffer.empty());
    ASSERT_TRUE(buffer.size() == 9);
    ASSERT_TRUE(buffer.max_size() == 9);
}

TEST(CCIRCULAR_BUFFER_EXT_TEST, CONSTRUCTOR_TEST_7) {
    std::vector<int> vector(10, 239);
    CCircularBufferExt<int> buffer(10, 239);
    ASSERT_TRUE(std::equal(buffer.begin(), buffer.end(), vector.begin(), vector.end()));
    *buffer.begin() = 222;
    ASSERT_FALSE(std::equal(buffer.begin(), buffer.end(), vector.begin(), vector.end()));
    ASSERT_FALSE(buffer.empty());
    ASSERT_TRUE(buffer.size() == 10);
    ASSERT_TRUE(buffer.max_size() == 10);
}

TEST(CCIRCULAR_BUFFER_EXT_TEST, PUSH_BACK_TEST) {
    CCircularBufferExt<int> buffer(10);
    buffer.push_back(1);
    ASSERT_TRUE(buffer.max_size() == 10);
    ASSERT_TRUE(buffer[0] == 1);
    ASSERT_TRUE(buffer.size() == 1);
    ASSERT_FALSE(buffer.empty());
}

TEST(CCIRCULAR_BUFFER_EXT_TEST, OPERATOR_TEST) {
    CCircularBufferExt<int> buffer_to_copy = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    CCircularBufferExt<int> buffer = buffer_to_copy;
    ASSERT_TRUE(buffer == buffer_to_copy);
    *buffer.begin() = 222;
    ASSERT_TRUE(buffer != buffer_to_copy);
    ASSERT_FALSE(buffer.empty());
    ASSERT_TRUE(buffer.size() == 9);
    ASSERT_TRUE(buffer.max_size() == 9);
}

TEST(CCIRCULAR_BUFFER_EXT_TEST, ALGORITHM_TEST_1) {
    CCircularBufferExt<int> buffer = {1, 2, -10, 4, 9, 6, 3, 0, -9};
    CCircularBufferExt<int> buffer2 = {-10, -9, 0, 1, 2, 3, 4, 6, 9};
    ASSERT_FALSE(buffer == buffer2);

    std::sort(buffer.begin(), buffer.end());

    ASSERT_TRUE(buffer == buffer2);
}

TEST(CCIRCULAR_BUFFER_EXT_TEST, ALGORITHM_TEST_2) {
    CCircularBufferExt<int> buffer = {1, 2, -10, 4, 9, 6, 3, 0, -9};
    CCircularBufferExt<int> buffer2 = {-9, 0, 3, 6, 9, 4, -10, 2, 1};
    ASSERT_FALSE(buffer == buffer2);

    std::reverse(buffer.begin(), buffer.end());

    ASSERT_TRUE(buffer == buffer2);
}

TEST(CCIRCULAR_BUFFER_EXT_TEST, SWAP_TEST) {
    std::vector vector = {1, 6, 1, 7, 0, -1, -199};

    CCircularBufferExt<int> buffer;
    CCircularBufferExt<int> buffer1 = {1, 6, 1, 7, 0, -1, -199};

    buffer.swap(buffer1);

    ASSERT_TRUE(std::equal(buffer.begin(), buffer.end(), vector.begin(), vector.end()));
    ASSERT_TRUE(buffer1.empty());
}

TEST(CCIRCULAR_BUFFER_EXT_TEST, INSERT_TEST_1) {
    CCircularBufferExt<int> buffer1 = {1, 2, 3, 4, 5, 6, 7, 8};

    CCircularBufferExt<int> buffer2(10);

    CCircularBufferExt<int>::iterator it = buffer2.insert(buffer2.cbegin(), buffer1.cbegin() + 1, buffer1.cend() - 1);
    std::vector<int> vector = {2, 3, 4, 5, 6, 7};
    ASSERT_TRUE(std::equal(buffer2.begin(), buffer2.end(), vector.begin(), vector.end()));
    ASSERT_TRUE(buffer2.begin() == it);
}

TEST(CCIRCULAR_BUFFER_EXT_TEST, INSERT_TEST_2) {
    CCircularBufferExt<int> buffer1 = {1, 2, 3, 4, 5, 6, 7, 8};
    CCircularBufferExt<int>::iterator it = buffer1.insert(buffer1.cbegin(), 1);
    std::vector<int> vector = {1, 1, 2, 3, 4, 5, 6, 7, 8};

    ASSERT_TRUE(std::equal(buffer1.begin(), buffer1.end(), vector.begin(), vector.end()));
    ASSERT_TRUE(buffer1.max_size() == 16);
    ASSERT_TRUE(it == buffer1.begin());
}

TEST(CCIRCULAR_BUFFER_EXT_TEST, INSERT_TEST_3) {
    CCircularBufferExt<int> buffer3 = {1, 2, 3, 4, 5, 6, 7, 8};
    buffer3.pop_front();
    buffer3.pop_front();
    buffer3.push_back(9);
    CCircularBufferExt<int>::iterator it = buffer3.insert(buffer3.cbegin(), 6, -1);
    std::vector<int> vector = {-1, -1, -1, -1, -1, -1, 3, 4, 5, 6, 7, 8, 9};

    ASSERT_TRUE(std::equal(buffer3.begin(), buffer3.end(), vector.begin(), vector.end()));
    ASSERT_TRUE(it == buffer3.begin());
}


TEST(CCIRCULAR_BUFFER_EXT_TEST, INSERT_TEST_4) {
    CCircularBufferExt<int> buffer3 = {1, 2, 3, 4, 5, 6, 7, 8};
    buffer3.pop_front();
    buffer3.pop_front();
    buffer3.pop_back();

    CCircularBufferExt<int>::iterator it = buffer3.insert(buffer3.cbegin(), 3, -1);
    std::vector<int> vector = {-1, -1, -1, 3, 4, 5, 6, 7};

    ASSERT_TRUE(std::equal(buffer3.begin(), buffer3.end(), vector.begin(), vector.end()));
    ASSERT_TRUE(it == buffer3.begin());
}

TEST(CCIRCULAR_BUFFER_EXT_TEST, INSERT_TEST_5) {
    CCircularBufferExt<int> buffer3 = {1, 2, 3, 4, 5, 6, 7, 8};
    buffer3.pop_front();
    buffer3.pop_front();
    buffer3.pop_back();

    CCircularBufferExt<int>::iterator it = buffer3.insert(buffer3.cbegin() + 3, -1);
    std::vector<int> vector = {3, 4, 5, -1, 6, 7};

    ASSERT_TRUE(std::equal(buffer3.begin(), buffer3.end(), vector.begin(), vector.end()));
    ASSERT_TRUE(it == buffer3.begin() + 3);
}

TEST(CCIRCULAR_BUFFER_EXT_TEST, INSERT_TEST_6) {
    CCircularBufferExt<int> buffer3(10);
    for (int i = 0; i < 5; ++i) {
        buffer3.push_back(i + 1);
    }
    CCircularBufferExt<int> buffer4 = {1, 2, 3, 4, 5, 6, 7, 8};

    CCircularBufferExt<int>::iterator it = buffer3.insert(buffer3.cbegin() + 3, buffer4.begin() + 3, buffer4.end());
    std::vector<int> vector = {1, 2, 3, 4, 5, 6, 7, 8, 4, 5};

    ASSERT_TRUE(std::equal(buffer3.begin(), buffer3.end(), vector.begin(), vector.end()));
    ASSERT_TRUE(it == buffer3.begin() + 3);
}

TEST(CCIRCULAR_BUFFER_EXT_TEST, ERASE_TEST_1) {
    CCircularBufferExt<int> buffer1 = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    buffer1.erase(buffer1.cbegin() + 4);
    std::vector<int> vector = {0, 1, 2, 3, 5, 6, 7, 8, 9};
    ASSERT_TRUE(std::equal(buffer1.begin(), buffer1.end(), vector.begin(), vector.end()));
}

TEST(CCIRCULAR_BUFFER_EXT_TEST, ERASE_TEST_2) {
    CCircularBufferExt<int> buffer1 = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    buffer1.erase(buffer1.cend());
    std::vector<int> vector = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    ASSERT_TRUE(std::equal(buffer1.begin(), buffer1.end(), vector.begin(), vector.end()));
}

TEST(CCIRCULAR_BUFFER_EXT_TEST, ERASE_TEST_3) {
    CCircularBufferExt<int> buffer1 = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    buffer1.pop_front();
    buffer1.pop_front();
    buffer1.push_back(10);
    buffer1.push_back(11);

    buffer1.erase(buffer1.cbegin() + 1, buffer1.cend() - 1);
    std::vector<int> vector = {2, 11};
    ASSERT_TRUE(std::equal(buffer1.begin(), buffer1.end(), vector.begin(), vector.end()));
}

TEST(CCIRCULAR_BUFFER_EXT_TEST, ERASE_TEST_4) {
    CCircularBufferExt<int> buffer1 = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    buffer1.pop_front();
    buffer1.pop_front();
    buffer1.push_back(10);
    buffer1.push_back(11);

    buffer1.erase(buffer1.cbegin(), buffer1.cend());
    ASSERT_TRUE(buffer1.empty());
}

TEST(CCIRCULAR_BUFFER_EXT_TEST, ASSIGN_TEST_1) {
    std::vector<int> vector = {1, 4, 3, 6, 7, 3, 7, 9, 0};
    CCircularBufferExt<int> buffer;

    buffer.assign(vector.begin(), vector.begin() + 1);
    ASSERT_TRUE(std::equal(buffer.begin(), buffer.end(), vector.begin(), vector.begin() + 1));
}

TEST(CCIRCULAR_BUFFER_EXT_TEST, ASSIGN_TEST_2) {
    std::vector<int> vector = {1, 4, 3, 6, 7, 3, 7, 9, 0};
    CCircularBufferExt<int> buffer;

    buffer.assign({1, 4, 3, 6, 7, 3, 7, 9, 0});
    ASSERT_TRUE(std::equal(buffer.begin(), buffer.end(), vector.begin(), vector.end()));
}

TEST(CCIRCULAR_BUFFER_EXT_TEST, ASSIGN_TEST_3) {
    std::vector<int> vector = {1, 4, 3, 6, 7, 3, 7, 9, 0};
    CCircularBufferExt<int> buffer(10);

    buffer.assign(vector.cbegin(), vector.cend());
    ASSERT_TRUE(std::equal(buffer.begin(), buffer.end(), vector.begin(), vector.end()));
}

TEST(CCIRCULAR_BUFFER_EXT_TEST, ASSIGN_TEST_5) {
    std::vector<int> vector = {5, 5, 5};
    CCircularBufferExt<int> buffer = {9, 8, 7, 6, 5, 4, 3, 2};

    buffer.assign(3, 5);
    ASSERT_TRUE(std::equal(buffer.begin(), buffer.end(), vector.begin(), vector.end()));
}

TEST(CCIRCULAR_BUFFER_EXT_TEST, PUSHBACK_TEST_1) {
    CCircularBufferExt<int> buffer;
    buffer.push_back(1);
    buffer.push_back(2);
    buffer.push_back(3);

    std::vector<int> vector;
    ASSERT_TRUE(std::equal(buffer.begin(), buffer.end(), vector.begin(), vector.end()));
}

TEST(CCIRCULAR_BUFFER_EXT_TEST, PUSHBACK_TEST_2) {
    CCircularBufferExt<int> buffer(10);

    for (int i = 0; i < 6; ++i) {
        buffer.push_back(i);
    }

    std::vector<int> vector = {0, 1, 2, 3, 4, 5};
    ASSERT_TRUE(std::equal(buffer.begin(), buffer.end(), vector.begin(), vector.end()));
}

TEST(CCIRCULAR_BUFFER_EXT_TEST, PUSHBACK_TEST_3) {
    CCircularBufferExt<int> buffer(2);

    for (int i = 0; i < 6; ++i) {
        buffer.push_back(i);
    }

    std::vector<int> vector = {0, 1, 2, 3, 4, 5};
    ASSERT_TRUE(std::equal(buffer.begin(), buffer.end(), vector.begin(), vector.end()));
}

TEST(CCIRCULAR_BUFFER_EXT_TEST, PUSHFRONT_TEST_1) {
    CCircularBufferExt<int> buffer;
    buffer.push_front(1);
    buffer.push_front(2);
    buffer.push_front(3);

    std::vector<int> vector;
    ASSERT_TRUE(std::equal(buffer.begin(), buffer.end(), vector.begin(), vector.end()));
}

TEST(CCIRCULAR_BUFFER_EXT_TEST, PUSHFRONT_TEST_2) {
    CCircularBufferExt<int> buffer(10);

    for (int i = 0; i < 6; ++i) {
        buffer.push_front(i);
    }

    std::vector<int> vector = {5, 4, 3, 2, 1, 0};
    ASSERT_TRUE(std::equal(buffer.begin(), buffer.end(), vector.begin(), vector.end()));
}

TEST(CCIRCULAR_BUFFER_EXT_TEST, PUSHFRONT_TEST_3) {
    CCircularBufferExt<int> buffer(2);

    for (int i = 0; i < 6; ++i) {
        buffer.push_front(i);
    }

    std::vector<int> vector = {5, 4, 3, 2, 1, 0};
    ASSERT_TRUE(std::equal(buffer.begin(), buffer.end(), vector.begin(), vector.end()));
}

TEST(CCIRCULAR_BUFFER_EXT_TEST, POPBACK_TEST_1) {
    CCircularBufferExt<int> buffer(2);

    buffer.push_back(1);
    buffer.pop_back();
    ASSERT_TRUE(buffer.empty());

    buffer.pop_back();
    buffer.pop_back();
    ASSERT_TRUE(buffer.empty());
}

TEST(CCIRCULAR_BUFFER_EXT_TEST, POPBACK_TEST_2) {
    CCircularBufferExt<int> buffer(10);

    for (int i = 0; i < 5; ++i) {
        buffer.push_back(i);
    }
    buffer.pop_back();
    buffer.pop_back();

    std::vector<int> vector = {0, 1, 2};
    ASSERT_TRUE(std::equal(buffer.begin(), buffer.end(), vector.begin(), vector.end()));
}

TEST(CCIRCULAR_BUFFER_EXT_TEST, POPBACK_TEST_3) {
    CCircularBufferExt<int> buffer;
    buffer.pop_back();
    buffer.pop_back();
    buffer.pop_back();
    ASSERT_TRUE(buffer.empty());
}

TEST(CCIRCULAR_BUFFER_EXT_TEST, POPFRONT_TEST_1) {
    CCircularBufferExt<int> buffer(2);

    buffer.push_back(1);
    buffer.pop_front();
    ASSERT_TRUE(buffer.empty());

    buffer.pop_front();
    buffer.pop_front();
    ASSERT_TRUE(buffer.empty());
}

TEST(CCIRCULAR_BUFFER_EXT_TEST, POPFRONT_TEST_2) {
    CCircularBufferExt<int> buffer(10);

    for (int i = 0; i < 5; ++i) {
        buffer.push_back(i);
    }
    buffer.pop_front();
    buffer.pop_front();

    std::vector<int> check = {2, 3, 4};
    ASSERT_TRUE(std::equal(buffer.begin(), buffer.end(), check.begin(), check.end()));
}

TEST(CCIRCULAR_BUFFER_EXT_TEST, POPFRONT_TEST_3) {
    CCircularBufferExt<int> buffer;
    buffer.pop_front();
    buffer.pop_front();
    buffer.pop_front();
    ASSERT_TRUE(buffer.empty());
}