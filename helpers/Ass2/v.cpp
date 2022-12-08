// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#include <comp6771/euclidean_vector.hpp>
#include <iterator>
#include <algorithm>

namespace comp6771 {
    // Constructors
    euclidean_vector::euclidean_vector(){
        dimension_ = 1;
        this->magnitude_ = std::make_unique<double[]>(1);
    }
    euclidean_vector::euclidean_vector(int d) : dimension_{d}{
        this->magnitude_ = std::make_unique<double[]>(static_cast<size_t>(d));
    }

    euclidean_vector::euclidean_vector(int d, double num) : dimension_{d}{
        this->magnitude_ = std::make_unique<double[]>(static_cast<size_t>(dimension_));
        std::fill(this->magnitude_.get(), this->magnitude_.get()+dimension_, num);
    }

    euclidean_vector::euclidean_vector(std::vector<double>::const_iterator start,
    std::vector<double>::const_iterator ending)
    : dimension_{static_cast<int>(std::distance(start, ending))} {
        this->magnitude_ = std::make_unique<double[]>(static_cast<size_t>(dimension_));
        std::copy(start, ending, this->magnitude_.get());
    }

    euclidean_vector::euclidean_vector(std::initializer_list<double> list) : dimension_{static_cast<int>(list.size())}{
        this->magnitude_ = std::make_unique<double[]>(static_cast<size_t>(dimension_));
        std::copy(list.begin(), list.end(), this->magnitude_.get());
    }

    euclidean_vector::euclidean_vector(euclidean_vector const& v) : dimension_{v.dimension_}{
        this->magnitude_ = std::make_unique<double[]>(static_cast<size_t>(dimension_));
        std::copy(v.magnitude_.get(), v.magnitude_.get()+v.dimension_, this->magnitude_.get());
    }


    // Destructor
    euclidean_vector::~euclidean_vector() = default;


    // Operations Member
    auto euclidean_vector::operator=(euclidean_vector const& v) -> euclidean_vector& {
        dimension_ = v.dimension_;
        this->magnitude_ = std::make_unique<double[]>(static_cast<size_t>(dimension_));
        std::copy(v.magnitude_.get(), v.magnitude_.get()+v.dimension_, this->magnitude_.get());
        return *this;
    }

    auto euclidean_vector::operator[](int i) -> double&{
        return this->magnitude_[static_cast<size_t>(i)];
    }

    auto euclidean_vector::operator[](int i) const -> double{
        return this->magnitude_[static_cast<size_t>(i)];
    }

    auto euclidean_vector::operator+() const -> euclidean_vector{
        return *this;
    }

    auto euclidean_vector::operator-() -> euclidean_vector{
        std::for_each(this->magnitude_.get(), this->magnitude_.get()+dimension_,
        [](auto& ele) { ele = -ele; });
        return *this;
    }

    auto euclidean_vector::operator+=(euclidean_vector const& v) -> euclidean_vector& {
        std::transform(this->magnitude_.get(), this->magnitude_.get()+dimension_,
        v.magnitude_.get(), this->magnitude_.get(), std::plus<double>());
        return *this;
    }

    auto euclidean_vector::operator-=(euclidean_vector const& v) -> euclidean_vector& {
        std::transform(this->magnitude_.get(), this->magnitude_.get()+dimension_,
        v.magnitude_.get(), this->magnitude_.get(), std::minus<double>());
        return *this;
    }

    auto euclidean_vector::operator*=(double num) -> euclidean_vector& {
        std::transform(this->magnitude_.get(), this->magnitude_.get()+dimension_,
        this->magnitude_.get(), std::bind(std::multiplies<double>(), std::placeholders::_1, num));
        return *this;
    }

    auto euclidean_vector::operator/=(double num) -> euclidean_vector& {
        std::transform(this->magnitude_.get(), this->magnitude_.get()+dimension_,
        this->magnitude_.get(), std::bind(std::divides<double>(), std::placeholders::_1, num));
        return *this;
    }

    euclidean_vector::operator std::vector<double>() const{
        std::vector<double> v;
        v.insert(v.begin(), this->magnitude_.get(), this->magnitude_.get()+dimension_);
        return v;
    }

    euclidean_vector::operator std::list<double>() const{
        std::list<double> li;
        li.insert(li.begin(), this->magnitude_.get(), this->magnitude_.get()+dimension_);
        return li;
    }

    // Member Functions
    auto euclidean_vector::at(int index) const -> double{
        return this->magnitude_[static_cast<size_t>(index)];
    }
    auto euclidean_vector::at(int index) -> double& {
        return this->magnitude_[static_cast<size_t>(index)];
    }
    auto euclidean_vector::dimensions() -> int {
        return dimension_;
    }


    // Operations Friend
} // namespace comp6771
