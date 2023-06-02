#pragma once

#include <iostream>
#include <sstream>
#include <vector>

namespace bmstu {
    template<typename T>
    class matrix {
    public:
        matrix() : data_(1), rows_(1), columns_(1) {
            representation_ = {{&data_[0]}};
        }

        matrix(size_t rows, size_t columns) : data_(rows * columns), rows_(rows), columns_(columns) {
            for (size_t i = 0; i < rows_; ++i) {
                std::vector<T *> current_row(columns_);
                for (size_t j = 0; j < columns_; ++j) {
                    current_row[j] = &(data_[i * columns_ + j]);
                }
                representation_.push_back(std::move(current_row));
            }
        }

        matrix(std::initializer_list<T> i_list, size_t rows, size_t columns) : rows_(rows), columns_(columns) {
            if (i_list.size() == rows_ * columns_) {
                data_.resize(rows_ * columns_);
                std::move(i_list.begin(), i_list.end(), data_.data());
                for (size_t i = 0; i < rows_; ++i) {
                    std::vector<T *> current_row(columns_);
                    for (size_t j = 0; j < columns_; ++j) {
                        current_row[j] = &(data_[i * columns_ + j]);
                    }
                    representation_.push_back(std::move(current_row));
                }
            } else {
                throw std::out_of_range(
                        "Current matrix pos wrong (" + std::to_string(rows) + ", " + std::to_string(columns) +
                        ") != " + std::to_string(i_list.size()));
            }
        }

        T &operator()(size_t rows, size_t columns) {
            return *representation_[rows][columns];
        }

        T operator()(size_t rows, size_t columns) const {
            T copy = *representation_[rows][columns];
            return copy;
        }


        template<class S>
        friend S &operator<<(S &ovs, const bmstu::matrix<T> &obj) {
            for (size_t i = 0; i < obj.rows_; ++i) {
                for (size_t j = 0; j < obj.columns_; ++j) {
                    ovs << obj(i, j) << " ";
                }
                ovs << "\r\n";
            }
            return ovs;
        }

        std::vector<T *> operator[](size_t i) {
            return representation_[i];
        }

        std::vector<T> operator[](size_t i) const {
            std::vector<T> result;
            result.resize(columns_);
            for (size_t j = 0; j < columns_; ++j) {
                result[j] = *representation_[i][j];
            }
            return result;
        }

        T det() {
            if (columns_ != rows_) {
                throw std::logic_error("Matrix have determinant if (rows == colimns)!");
            } else {
                T result = T();
                std::vector<size_t> indexes(columns_);
                int sign = 1;
                for (size_t i = 0; i < columns_; ++i) {
                    indexes[i] = i;
                }
                permute(indexes, indexes.size(), result, sign);
                return result;
            }
        }

    private:
        void permute(std::vector<size_t> &a, size_t pos, T &value, int &sign) {
            if (pos == 1) {
                T mrow = T(1);
                for (size_t i = 0; i < columns_; ++i) {
                    mrow *= *this->representation_[i][a[i]];
                }
                value += (mrow * sign);
            } else {
                for (size_t i = 0; i < pos; ++i) {
                    permute(a, pos - 1, value, sign);
                    if (pos % 2) {
                        std::swap(a[0], a[pos - 1]);
                    } else {
                        std::swap(a[i], a[pos - 1]);
                        sign *= (-1);
                    }
                }
            }
        }

        std::vector<T> data_;
        std::vector<std::vector<T *>> representation_;

        size_t rows_;
        size_t columns_;
    };
}