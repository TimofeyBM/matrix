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

