// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#include <comp6771/euclidean_vector.hpp>

namespace comp6771 {
    // Constructors
    euclidean_vector::euclidean_vector() {
        dimension_ = 1;
        magnitude_ = std::make_unique<double[]>(static_cast<size_t>(dimension_));
    }
    euclidean_vector::euclidean_vector(int dim)
    : dimension_{dim} {
        magnitude_ = std::make_unique<double[]>(static_cast<size_t>(dimension_));
    }

    euclidean_vector::euclidean_vector(int dim, double num)
    : dimension_{dim} {
        magnitude_ = std::make_unique<double[]>(static_cast<size_t>(dimension_));
        std::fill(magnitude_.get(), magnitude_.get() + dimension_, num);
    }

    euclidean_vector::euclidean_vector(std::vector<double>::const_iterator start,
                                       std::vector<double>::const_iterator ending)
    : dimension_{static_cast<int>(std::distance(start, ending))} {
        magnitude_ = std::make_unique<double[]>(static_cast<size_t>(dimension_));
        std::copy(start, ending, magnitude_.get());
    }

    euclidean_vector::euclidean_vector(std::initializer_list<double> lis)
    : dimension_{static_cast<int>(lis.size())} {
        magnitude_ = std::make_unique<double[]>(static_cast<size_t>(dimension_));
        std::copy(lis.begin(), lis.end(), magnitude_.get());
    }

    euclidean_vector::euclidean_vector(euclidean_vector const& vec)
    : dimension_{vec.dimension_} {
        magnitude_ = std::make_unique<double[]>(static_cast<size_t>(dimension_));
        std::copy(vec.magnitude_.get(), vec.magnitude_.get() + vec.dimension_, magnitude_.get());
    }

    // Destructor
    euclidean_vector::~euclidean_vector() = default;

    // Operations Member
    auto euclidean_vector::operator=(euclidean_vector const& vec) -> euclidean_vector& {
        if (this != &vec) {
            dimension_ = vec.dimension_;
            magnitude_ = std::make_unique<double[]>(static_cast<size_t>(dimension_));
            std::copy(vec.magnitude_.get(), vec.magnitude_.get() + vec.dimension_, magnitude_.get());
        }
        return *this;
    }

    auto euclidean_vector::operator[](int index) -> double& {
        return magnitude_[static_cast<size_t>(index)];
    }

    auto euclidean_vector::operator[](int index) const -> double {
        return magnitude_[static_cast<size_t>(index)];
    }

    auto euclidean_vector::operator+() const -> euclidean_vector {
        return *this;
    }

    auto euclidean_vector::operator-() const -> euclidean_vector {
        std::for_each (magnitude_.get(), magnitude_.get() + dimension_, [](auto& ele) { ele = -ele; });
        return *this;
    }

    auto euclidean_vector::operator+=(euclidean_vector const& vec) -> euclidean_vector& {
        std::transform(magnitude_.get(),
                       magnitude_.get() + dimension_,
                       vec.magnitude_.get(),
                       magnitude_.get(),
                       std::plus<double>());
        return *this;
    }

    auto euclidean_vector::operator-=(euclidean_vector const& vec) -> euclidean_vector& {
        std::transform(magnitude_.get(),
                       magnitude_.get() + dimension_,
                       vec.magnitude_.get(),
                       magnitude_.get(),
                       std::minus<double>());
        return *this;
    }

    auto euclidean_vector::operator*=(double num) -> euclidean_vector& {
        std::transform(magnitude_.get(),
                       magnitude_.get() + dimension_,
                       magnitude_.get(),
                       [num](auto&& p_h1) {
                           return std::multiplies<double>()(std::forward<decltype(p_h1)>(p_h1), num);
                       });
        return *this;
    }

    auto euclidean_vector::operator/=(double num) -> euclidean_vector& {
        std::transform(magnitude_.get(),
                       magnitude_.get() + dimension_,
                       magnitude_.get(),
                       [num](auto&& p_h1) {
                           return std::divides<double>()(std::forward<decltype(p_h1)>(p_h1), num);
                       });
        return *this;
    }

    euclidean_vector::operator std::vector<double>() const {
        std::vector<double> vec;
        vec.insert(vec.begin(), magnitude_.get(), magnitude_.get() + dimension_);
        return vec;
    }

    euclidean_vector::operator std::list<double>() const {
        std::list<double> lis;
        lis.insert(lis.begin(), magnitude_.get(), magnitude_.get() + dimension_);
        return lis;
    }

    // Member Functions
    auto euclidean_vector::at(int index) const -> double {
        return magnitude_[static_cast<size_t>(index)];
    }
    auto euclidean_vector::at(int index) -> double& {
        return magnitude_[static_cast<size_t>(index)];
    }
    auto euclidean_vector::dimensions() const -> int {
        return dimension_;
    }

    // Operations Friend
    auto operator==(euclidean_vector const& lhs, euclidean_vector const& rhs) -> bool {
        return (lhs.dimension_ == rhs.dimension_)
               && (std::equal(lhs.magnitude_.get(),
                              lhs.magnitude_.get() + lhs.dimension_,
                              rhs.magnitude_.get()));
    }

    auto operator!=(euclidean_vector const& lhs, euclidean_vector const& rhs) -> bool {
        return !(lhs == rhs);
    }

    auto operator+(euclidean_vector const& lhs, euclidean_vector const& rhs) -> euclidean_vector {
        auto res = euclidean_vector(lhs.dimension_);
        res += lhs;
        res += rhs;
        return res;
    }

    auto operator-(euclidean_vector const& lhs, euclidean_vector const& rhs) -> euclidean_vector {
        auto res = euclidean_vector(lhs.dimension_);
        return (lhs + (-rhs));
    }

    auto operator*(euclidean_vector const& vec, double num) -> euclidean_vector {
        auto res = vec;
        return res *= num;
    }
    auto operator*(double num, euclidean_vector const& vec) -> euclidean_vector {
        auto res = vec;
        return res *= num;
    }

    auto operator/(euclidean_vector const& vec, double num) -> euclidean_vector {
        auto res = vec;
        return res /= num;
    }

    auto operator<<(std::ostream& os, euclidean_vector const& vec) -> std::ostream& {
        os << "[";
        if (vec.dimension_ > 0) {
            std::copy(vec.magnitude_.get(),
                      vec.magnitude_.get() + vec.dimension_ - 1,
                      std::ostream_iterator<double>(os, " "));
            os << vec[vec.dimension_ - 1];
        }
        os << "]";
        return os;
    }

    auto euclidean_norm(euclidean_vector const& vec) -> double {
        if (vec.norm_ == -1) {
            auto square = [](double sum_so_far, double num) { return sum_so_far + pow(num, 2.0); };
            vec.norm_ = sqrt(
               std::accumulate(vec.magnitude_.get(), vec.magnitude_.get() + vec.dimension_, 0.0, square));
        }
        return vec.norm_;
    }

    // auto euclidean_norm(euclidean_vector const& vec) -> double {
    //  auto norm = double{0};
    //  if (vec.dimensions() != 0) {
    //      for (auto i = 0; i < vec.dimensions(); ++i) {
    //          norm += pow(vec[i], 2.0);
    //      }
    //  }
    //  return sqrt(norm);
    // }
    auto unit(euclidean_vector const& vec) -> euclidean_vector {
        return vec / euclidean_norm(vec);
    }

    auto dot(euclidean_vector const& x, euclidean_vector const& y) -> double {
        auto res = double{0};
        for (auto i = 0; i < x.dimensions(); ++i) {
            res += (x[i] * y[i]);
        }
        return res;
    }
} // namespace comp6771
