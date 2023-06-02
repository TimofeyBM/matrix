#include <gtest/gtest.h>
#include <iostream>
#include <string>
#include <vector>
#include "bmstu_matrix.h"

TEST(Constructor, Default) {
    bmstu::matrix<int> my_matrix;
//    ASSERT_EQ(my_matrix.r_count(), 1); Проверка кол-ва строк
//    ASSERT_EQ(my_matrix.c_count(), 1); Проверка кол-ва столбцов
//    ASSERT_EQ(my_matrix.size(), 1);   Проверка кол-ва элементов
    ASSERT_EQ(my_matrix(0, 0), 0);
}

TEST(Constructor, Parameter) {
    bmstu::matrix<int> my_matrix(4, 5);
//    ASSERT_EQ(my_matrix.r_count(), 4); Проверка кол-ва строк
//    ASSERT_EQ(my_matrix.c_count(), 5); Проверка кол-ва столбцов
//    ASSERT_EQ(my_matrix.size(), 20);   Проверка кол-ва элементов
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 5; ++j) {
            ASSERT_EQ(my_matrix(i, j), 0);
        }
    }
}

TEST(Constructor, IList) {
    bmstu::matrix my_matrix({1, 2, 3, 4, 5, 6}, 2, 3);
//    ASSERT_EQ(my_matrix.r_count(), 2); Проверка кол-ва строк
//    ASSERT_EQ(my_matrix.c_count(), 3); Проверка кол-ва столбцов
//    ASSERT_EQ(my_matrix.size(), 6);   Проверка кол-ва элементов
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 3; ++j) {
            ASSERT_EQ(my_matrix(i, j), i * 3 + j + 1);
        }
    }

    ASSERT_THROW(bmstu::matrix bad_matrix({1, 2, 3, 4, 5}, 2, 3), std::out_of_range);
}

TEST(Operator, LeftShift) {
    bmstu::matrix my_matrix({1, 2, 3, 4, 5, 6}, 2, 3);
    std::stringstream ss;
    ss << my_matrix;
    ASSERT_STREQ(ss.str().c_str(), "1 2 3 \r\n4 5 6 \r\n");
}

TEST(Operator, Subscript) {
    const bmstu::matrix my_matrix_1({1, 2, 3, 4, 5, 6}, 2, 3);
    std::vector line_1_1 = my_matrix_1[1];
    std::vector correct({4, 5, 6});
    for (int i = 0; i < 3; ++i) {
        ASSERT_EQ(line_1_1[i], correct[i]);
    }

    line_1_1[0] = 0;
    line_1_1[1] = 1;
    line_1_1[2] = 2;
    std::vector line_1_2 = my_matrix_1[1];
    for (int i = 0; i < 3; ++i) {
        ASSERT_EQ(line_1_1[i], i);
        ASSERT_EQ(line_1_2[i], i + 4);
    }

    bmstu::matrix my_matrix_2({1, 2, 3, 4, 5, 6}, 2, 3);
    std::vector line_2_1 = my_matrix_2[1];
    for (int i = 0; i < 3; ++i) {
        ASSERT_EQ(*line_2_1[i], correct[i]);
    }

    *line_2_1[0] = 0;
    *line_2_1[1] = 1;
    *line_2_1[2] = 2;
    std::vector line_2_2 = my_matrix_2[1];
    for (int i = 0; i < 3; ++i) {
        ASSERT_EQ(*line_2_1[i], i);
        ASSERT_EQ(*line_2_2[i], i);
    }
}


TEST(Method, det) {
    bmstu::matrix good_matrix({1, 0, 2, 1, 3, 4, -1, 3, 2, 5, -3, 2, -4, 5, -7, 2, 3, 19, 5, 8, 5, -3, -5, -1, 4}, 5,
                              5);
    ASSERT_EQ(good_matrix.det(), -240);

    bmstu::matrix bad_matrix({1, 2, 3, 4, 5, 6}, 2, 3);
    ASSERT_THROW(bad_matrix.det(), std::logic_error);
}

