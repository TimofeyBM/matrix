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



    private:
        std::vector<T> data_;
        std::vector<std::vector<T *>> representation_;

        size_t rows_;
        size_t columns_;
    };
}