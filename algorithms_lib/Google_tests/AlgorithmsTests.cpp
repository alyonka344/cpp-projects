#include "../Algorithms/Algorithms.h"
#include "../Algorithms/zip.h"
#include "../Algorithms/xrange.h"

#include "gtest/gtest.h"

#include <forward_list>

TEST(XRANGE_TESTS, TEST_1) {
    std::vector<int> vec;
    for (auto x: xrange(4)) {
        vec.push_back(x);
    }

    std::vector<int> vector = {0, 1, 2, 3};
    ASSERT_TRUE(std::equal(vec.begin(), vec.end(), vector.begin(), vector.end()));
}

TEST(XRANGE_TESTS, TEST_2) {
    std::vector<int> vec;
    for (auto x: xrange(-7)) {
        vec.push_back(x);
    }

    std::vector<int> vector = {0, -1, -2, -3, -4, -5, -6};
    ASSERT_TRUE(std::equal(vec.begin(), vec.end(), vector.begin(), vector.end()));
}

TEST(XRANGE_TESTS, TEST_3) {
    std::vector<double> vec;
    for (auto x: xrange(-6.0, 10.5)) {
        vec.push_back(x);
    }

    std::vector<double> vector = {-6, -5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    ASSERT_TRUE(std::equal(vec.begin(), vec.end(), vector.begin(), vector.end()));
}

TEST(XRANGE_TESTS, TEST_4) {
    std::vector<double> vec;
    for (auto x: xrange(9.5, -3.5)) {
        vec.push_back(x);
    }

    std::vector<double> vector = {9.5, 8.5, 7.5, 6.5, 5.5, 4.5, 3.5, 2.5, 1.5, 0.5, -0.5, -1.5, -2.5};
    ASSERT_TRUE(std::equal(vec.begin(), vec.end(), vector.begin(), vector.end()));
}

TEST(XRANGE_TESTS, TEST_5) {
    std::vector<int> vec;
    for (auto x: xrange(1, 7, 2)) {
        vec.push_back(x);
    }

    std::vector<int> vector = {1, 3, 5};
    ASSERT_TRUE(std::equal(vec.begin(), vec.end(), vector.begin(), vector.end()));
}

TEST(XRANGE_TESTS, TEST_6) {
    std::vector<int> vec;
    for (auto x: xrange(7, 1, -2)) {
        vec.push_back(x);
    }

    std::vector<int> vector = {7, 5, 3};
    ASSERT_TRUE(std::equal(vec.begin(), vec.end(), vector.begin(), vector.end()));
}

TEST(XRANGE_TESTS, TEST_7) {
    std::vector<int> vec;
    for (auto x: xrange(0)) {
        vec.push_back(x);
    }

    ASSERT_TRUE(vec.empty());
}


TEST(XRANGE_TESTS, TEST_8) {
    std::vector<int> vec = {0, 1, 2, 3, 4, 5};
    auto x = xrange(6);
    std::vector<int> vec2(x.begin(), x.end());

    ASSERT_EQ(vec, vec2);
}

TEST(XRANGE_TESTS, EMPTY_TEST) {
    std::vector<int> vec;
    for (auto x: xrange(1, 1)) {
        vec.push_back(x);
    }

    ASSERT_TRUE(vec.empty());
}

TEST(ZIP_TEST, TEST_1) {
    std::vector<int> v = {2, 3, 9};
    std::initializer_list<char> l = {'*', '#', '9', '\\'};

    std::vector<std::pair<int, char>> vec;
    std::vector<std::pair<int, char>> vector = {{2, '*'}, {3, '#'}, {9, '9'}};
    for(auto it: zip(v, l)){
        vec.push_back(it);
    }

    ASSERT_TRUE(std::equal(vec.begin(), vec.end(), vector.begin(), vector.end()));
}

TEST(ZIP_TEST, TEST_2) {
    std::vector<int> v;
    std::initializer_list<char> l = {'*', '#', '9', '\\'};

    std::vector<std::pair<int, char>> vec;
    std::vector<std::pair<int, char>> vector = {{2, '*'}, {3, '#'}, {9, '9'}};
    for(auto it: zip(v, l)){
        vec.push_back(it);
    }

    ASSERT_TRUE(vec.empty());
}

struct LeastSix {
    template<typename T>
    bool operator()(T x) {
        return x < 6;
    }
};

struct EvenNumber {
    template <typename T>
    bool operator()(T x){
        return x % 2 == 0;
    }
};

struct Mod5 {
    template <typename T>
    bool operator()(T a, T b) {
        return a % 5 == b % 5;
    }
};

TEST(ALGORITHM_TEST, ALL_OF_1) {
    std::forward_list<int> list = {2, 4, 4, 8, 12};
    ASSERT_TRUE(Algorithm::all_of(list.begin(), list.end(), EvenNumber()));
}

TEST(ALGORITHM_TEST, ALL_OF_2) {
    std::forward_list<int> list = {1, 4, 5, 6, 8};
    ASSERT_FALSE(Algorithm::all_of(list.begin(), list.end(), EvenNumber()));
}

TEST(ALGORITHM_TEST, ALL_OF_3) {
    std::forward_list<int> list = {1, 3, 5, 7, 9, 10};
    ASSERT_TRUE(Algorithm::all_of(list.begin(), list.begin(), EvenNumber()));
}

TEST(ALGORITHM_TEST, ALL_OF_4) {
    std::forward_list<int> list = {2, 4, 4, 5, 1};
    ASSERT_TRUE(Algorithm::all_of(list.begin(), list.end(), LeastSix()));
}

TEST(ALGORITHM_TEST, ALL_OF_5) {
    std::forward_list<int> list = {2, 4, 4, 50, 1};
    ASSERT_FALSE(Algorithm::all_of(list.begin(), list.end(), LeastSix()));
}

TEST(ALGORITHM_TEST, ALL_OF_6) {
    std::forward_list<int> list;
    ASSERT_TRUE(Algorithm::all_of(list.begin(), list.end(), LeastSix()));
}

TEST(ALGORITHM_TEST, ANY_OF_1) {
    std::forward_list<int> list = {1, 0, 5, 7, 9};
    ASSERT_TRUE(Algorithm::any_of(list.begin(), list.end(), EvenNumber()));
}

TEST(ALGORITHM_TEST, ANY_OF_2) {
    std::forward_list<int> list = {3, 7, 5, 3, 1, 9, 9};
    ASSERT_FALSE(Algorithm::any_of(list.begin(), list.end(), EvenNumber()));
}

TEST(ALGORITHM_TEST, ANY_OF_3) {
    std::forward_list<int> list = {1, 3, 5, 7, 9, 10};
    ASSERT_FALSE(Algorithm::any_of(list.begin(), list.begin(), EvenNumber()));
}

TEST(ALGORITHM_TEST, ANY_OF_4) {
    std::forward_list<int> list = {2, 4, 4, 5, 1};
    ASSERT_TRUE(Algorithm::any_of(list.begin(), list.end(), LeastSix()));
}

TEST(ALGORITHM_TEST, ANY_OF_5) {
    std::forward_list<int> list = {2, 4, 4, 50, 1};
    ASSERT_TRUE(Algorithm::any_of(list.begin(), list.end(), LeastSix()));
}

TEST(ALGORITHM_TEST, ANY_OF_6) {
    std::forward_list<int> list;
    ASSERT_FALSE(Algorithm::any_of(list.begin(), list.end(), LeastSix()));
}

TEST(ALGORITHM_TEST, NONE_OF_1) {
    std::forward_list<int> list = {1, 1, 3, 5, 7, 9};
    ASSERT_TRUE(Algorithm::none_of(list.begin(), list.end(), EvenNumber()));
}

TEST(ALGORITHM_TEST, NONE_OF_2) {
    std::forward_list<int> list;
    ASSERT_TRUE(Algorithm::none_of(list.begin(), list.end(), EvenNumber()));
}

TEST(ALGORITHM_TEST, NONE_OF_3) {
    std::forward_list<int> list = {1, 1, 3, 5, 7, 0};
    ASSERT_FALSE(Algorithm::none_of(list.begin(), list.end(), EvenNumber()));
}

TEST(ALGORITHM_TEST, NONE_OF_4) {
    std::forward_list<int> list = {11, 51, 13, 25, 7, 10};
    ASSERT_TRUE(Algorithm::none_of(list.begin(), list.end(), LeastSix()));
}

TEST(ALGORITHM_TEST, ONE_OF_1) {
    std::forward_list<int> list = {15, 10, 13, 5, 7, 10};
    ASSERT_TRUE(Algorithm::one_of(list.begin(), list.end(), LeastSix()));
}

TEST(ALGORITHM_TEST, ONE_OF_2) {
    std::forward_list<int> list = {14};
    ASSERT_FALSE(Algorithm::one_of(list.begin(), list.end(), LeastSix()));
}

TEST(ALGORITHM_TEST, ONE_OF_3) {
    std::forward_list<int> list = {8, 13, 3, 11, 5};
    ASSERT_FALSE(Algorithm::one_of(list.begin(), list.end(), LeastSix()));
}

TEST(ALGORITHM_TEST, FIND_NOT_1) {
    std::forward_list<int> list(3, 3);
    auto it = Algorithm::find_not(list.begin(), list.end(), 3);
    ASSERT_EQ(it, list.end());
}

TEST(ALGORITHM_TEST, FIND_NOT_2) {
    std::forward_list<int> list = {1, 1, 1, 10, 5, 6, 1, 7};
    auto it = Algorithm::find_not(list.begin(), list.end(), 1);
    ASSERT_EQ(*it, 10);
    ASSERT_EQ(*(++it), 5);
}

TEST(ALGORITHM_TEST, IS_SORTED_1) {
    std::forward_list<int> list = {7, 6, 5, 5, 4, 1};
    ASSERT_TRUE(Algorithm::is_sorted(list.begin(), list.end(), std::greater_equal<>()));
}

TEST(ALGORITHM_TEST, IS_SORTED_2) {
    std::forward_list<int> list = {5, 6, 5, 5, 4, 1};
    ASSERT_FALSE(Algorithm::is_sorted(list.begin(), list.end(), std::greater_equal<>()));
}

TEST(ALGORITHM_TEST, IS_SORTED_3) {
    std::forward_list<int> list;
    ASSERT_TRUE(Algorithm::is_sorted(list.begin(), list.end(), std::greater_equal<>()));
}

TEST(ALGORITHM_TEST, IS_PARTITIONED_1) {
    std::forward_list<int> list = {1, 3, 5, 6, 6, 6};
    ASSERT_TRUE(Algorithm::is_partitioned(list.begin(), list.end(), EvenNumber()));
}

TEST(ALGORITHM_TEST, IS_PARTITIONED_2) {
    std::forward_list<int> list = {1, 3, 5, 6, 6, 1};
    ASSERT_FALSE(Algorithm::is_partitioned(list.begin(), list.end(), EvenNumber()));
}

TEST(ALGORITHM_TEST, IS_PARTITIONED_3) {
    std::forward_list<int> list = {1, 3, 5};
    ASSERT_FALSE(Algorithm::is_partitioned(list.begin(), list.end(), EvenNumber()));
}

TEST(ALGORITHM_TEST, IS_PARTITIONED_4) {
    std::forward_list<int> list = {2, 6, 6 ,6, 6, 88, 100};
    ASSERT_FALSE(Algorithm::is_partitioned(list.begin(), list.end(), EvenNumber()));
}

TEST(ALGORITHM_TEST, IS_PARTITIONED_5) {
    std::forward_list<int> list;
    ASSERT_FALSE(Algorithm::is_partitioned(list.begin(), list.end(), EvenNumber()));
}

TEST(ALGORITHM_TEST, FIND_BACKWARD_1) {
    std::forward_list<int> list = {1, 2, 9, 0, 88, 77, 1, 543};
    auto it = Algorithm::find_backward(list.begin(), list.end(), 1);
    ASSERT_EQ(*it, 1);
    ASSERT_EQ(*(++it), 543);
}

TEST(ALGORITHM_TEST, FIND_BACKWARD_2) {
    std::forward_list<int> list = {1, 2, 9, 4, 88, 77, 1, 543};
    auto it = Algorithm::find_backward(list.begin(), list.end(), 0);
    ASSERT_EQ(it, list.end());
}

TEST(ALGORITHM_TEST, IS_PALINDROME_1) {
    std::forward_list<int> list = {1, 3, 3, 5, 1};
    ASSERT_FALSE(Algorithm::is_palindrome(list.begin(), list.end()));
}

TEST(ALGORITHM_TEST, IS_PALINDROME_2) {
    std::forward_list<int> list = {1, 5, 3, 5, 1};
    ASSERT_TRUE(Algorithm::is_palindrome(list.begin(), list.end()));
}

TEST(ALGORITHM_TEST, IS_PALINDROME_3) {
    std::forward_list<int> list;
    ASSERT_TRUE(Algorithm::is_palindrome(list.begin(), list.end()));
}

TEST(ALGORITHM_TEST, IS_PALINDROME_4) {
    std::forward_list<int> list = {1};
    ASSERT_TRUE(Algorithm::is_palindrome(list.begin(), list.end()));
}

TEST(ALGORITHM_TEST, IS_PALINDROME_5) {
    std::forward_list<int> list = {1, 13, 2, 3, 11};
    ASSERT_TRUE(Algorithm::is_palindrome(list.begin(), list.end(), Mod5()));
}

TEST(ALGORITHM_TEST, IS_PALINDROME_6) {
    std::vector<int> list = {10, 6, 4, 14, 1, 15};
    ASSERT_TRUE(Algorithm::is_palindrome(list.begin(), list.end(), Mod5()));
}