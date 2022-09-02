// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#include <comp6771/euclidean_vector.hpp>
#include <utility>

namespace comp6771 {
	// Constructors
	euclidean_vector::euclidean_vector() {
		dimension_ = 1;
		magnitude_ = std::make_unique<double[]>(static_cast<size_t>(dimension_));
	}
	euclidean_vector::euclidean_vector(int dim)
	: magnitude_{std::make_unique<double[]>(static_cast<size_t>(dim))}
	, dimension_{dim} {}

	euclidean_vector::euclidean_vector(int dim, double num)
	: magnitude_{std::make_unique<double[]>(static_cast<size_t>(dim))}
	, dimension_{dim} {
		std::fill(magnitude_.get(), magnitude_.get() + dimension_, num);
	}

	euclidean_vector::euclidean_vector(std::vector<double>::const_iterator start,
	                                   std::vector<double>::const_iterator ending)
	: magnitude_{std::make_unique<double[]>(
	   static_cast<size_t>(static_cast<int>(std::distance(start, ending))))}
	, dimension_{static_cast<int>(std::distance(start, ending))} {
		std::copy(start, ending, magnitude_.get());
	}

	euclidean_vector::euclidean_vector(std::initializer_list<double> lis)
	: magnitude_{std::make_unique<double[]>(lis.size())}
	, dimension_{static_cast<int>(lis.size())} {
		std::copy(lis.begin(), lis.end(), magnitude_.get());
	}

	euclidean_vector::euclidean_vector(euclidean_vector const& vec)
	: magnitude_{std::make_unique<double[]>(static_cast<size_t>(vec.dimension_))}
	, dimension_{vec.dimension_} {
		std::copy(vec.magnitude_.get(), vec.magnitude_.get() + vec.dimension_, magnitude_.get());
	}

	euclidean_vector::euclidean_vector(euclidean_vector&& vec) noexcept
	: magnitude_{std::exchange(vec.magnitude_, nullptr)}
	, dimension_{std::exchange(vec.dimension_, 0)}
	, norm_{std::exchange(vec.norm_, -1)} {}

	// Destructor
	euclidean_vector::~euclidean_vector() = default;

	// Operations Member
	auto euclidean_vector::operator=(euclidean_vector const& vec) -> euclidean_vector& {
		if (this != std::addressof(vec)) {
			euclidean_vector(vec).swap(*this);
		}
		return *this;
	}

	auto euclidean_vector::operator=(euclidean_vector&& vec) noexcept -> euclidean_vector& {
		swap(vec);
		vec.magnitude_.reset();
		vec.dimension_ = 0;
		vec.norm_ = -1;
		return *this;
	}

	auto euclidean_vector::operator[](int index) -> double& {
		reset_norm();
		return magnitude_[static_cast<size_t>(index)];
	}

	auto euclidean_vector::operator[](int index) const -> double {
		return magnitude_[static_cast<size_t>(index)];
	}

	auto euclidean_vector::operator+() const -> euclidean_vector {
		return *this;
	}

	auto euclidean_vector::operator-() const -> euclidean_vector {
		auto res = euclidean_vector(*this);
		std::for_each (res.magnitude_.get(), res.magnitude_.get() + res.dimension_, [](auto& ele) {
			ele = -ele;
		});
		return res;
	}

	auto euclidean_vector::operator+=(euclidean_vector const& vec) -> euclidean_vector& {
		if (dimension_ != vec.dimension_) {
			throw comp6771::euclidean_vector_error("Dimensions of LHS(" + std::to_string(dimension_)
			                                       + ") and RHS(" + std::to_string(vec.dimension_)
			                                       + ") do not match");
		}
		if (std::all_of(vec.magnitude_.get(), vec.magnitude_.get() + vec.dimension_, [](double& ele) {
			    return ele == 0;
		    }))
		{
			return *this;
		}
		reset_norm();
		std::transform(magnitude_.get(),
		               magnitude_.get() + dimension_,
		               vec.magnitude_.get(),
		               magnitude_.get(),
		               std::plus<double>());
		return *this;
	}

	auto euclidean_vector::operator-=(euclidean_vector const& vec) -> euclidean_vector& {
		if (dimension_ != vec.dimension_) {
			throw comp6771::euclidean_vector_error("Dimensions of LHS(" + std::to_string(dimension_)
			                                       + ") and RHS(" + std::to_string(vec.dimension_)
			                                       + ") do not match");
		}

		if (std::all_of(vec.magnitude_.get(), vec.magnitude_.get() + vec.dimension_, [](double& ele) {
			    return ele == 0;
		    }))
		{
			return *this;
		}
		reset_norm();
		std::transform(magnitude_.get(),
		               magnitude_.get() + dimension_,
		               vec.magnitude_.get(),
		               magnitude_.get(),
		               std::minus<double>());
		return *this;
	}

	auto euclidean_vector::operator*=(double num) -> euclidean_vector& {
		if (num == 1) {
			return *this;
		}
		reset_norm();
		std::transform(magnitude_.get(),
		               magnitude_.get() + dimension_,
		               magnitude_.get(),
		               [num](auto&& p_h1) {
			               return std::multiplies<double>()(std::forward<decltype(p_h1)>(p_h1), num);
		               });
		return *this;
	}

	auto euclidean_vector::operator/=(double num) -> euclidean_vector& {
		if (num == 0) {
			throw comp6771::euclidean_vector_error("Invalid vector division by 0");
		}
		if (num == 1) {
			return *this;
		}

		reset_norm();
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
		if (index < 0 or index >= dimension_) {
			throw comp6771::euclidean_vector_error("Index " + std::to_string(index)
			                                       + " is not valid for this euclidean_vector object");
		}
		return magnitude_[static_cast<size_t>(index)];
	}
	auto euclidean_vector::at(int index) -> double& {
		if (index < 0 or index >= dimension_) {
			throw comp6771::euclidean_vector_error("Index " + std::to_string(index)
			                                       + " is not valid for this euclidean_vector object");
		}
		reset_norm();
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
		if (lhs.dimension_ != rhs.dimension_) {
			throw comp6771::euclidean_vector_error("Dimensions of LHS("
			                                       + std::to_string(lhs.dimension_) + ") and RHS("
			                                       + std::to_string(rhs.dimension_) + ") do not match");
		}
		auto res = euclidean_vector(lhs.dimension_);
		res += lhs;
		res += rhs;
		return res;
	}

	auto operator-(euclidean_vector const& lhs, euclidean_vector const& rhs) -> euclidean_vector {
		if (lhs.dimension_ != rhs.dimension_) {
			throw comp6771::euclidean_vector_error("Dimensions of LHS("
			                                       + std::to_string(lhs.dimension_) + ") and RHS("
			                                       + std::to_string(rhs.dimension_) + ") do not match");
		}
		auto res = euclidean_vector(lhs.dimension_);
		res += lhs;
		res -= rhs;
		return res;
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
		if (num == 0) {
			throw comp6771::euclidean_vector_error("Invalid vector division by 0");
		}
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

	auto euclidean_vector::reset_norm() const -> void {
		norm_ = -1;
	}

	auto euclidean_vector::swap(euclidean_vector& vec) -> void {
		std::swap(magnitude_, vec.magnitude_);
		std::swap(dimension_, vec.dimension_);
		std::swap(norm_, vec.norm_);
	}

	auto euclidean_norm(euclidean_vector const& vec) -> double {
		if (vec.dimension_ == 0) {
			vec.norm_ = 0;
			return vec.norm_;
		}

		if (vec.norm_ == -1) {
			auto square = [](double sum_so_far, double num) { return sum_so_far + pow(num, 2.0); };
			vec.norm_ = sqrt(
			   std::accumulate(vec.magnitude_.get(), vec.magnitude_.get() + vec.dimension_, 0.0, square));
		}
		return vec.norm_;
	}

	auto unit(euclidean_vector const& vec) -> euclidean_vector {
		if (vec.dimensions() == 0) {
			throw comp6771::euclidean_vector_error("euclidean_vector with no dimensions does not have "
			                                       "a unit vector");
		}
		auto norm = euclidean_norm(vec);
		if (norm == 0) {
			throw comp6771::euclidean_vector_error("euclidean_vector with zero euclidean normal does "
			                                       "not have a unit vector");
		}
		return vec / norm;
	}

	auto dot(euclidean_vector const& x, euclidean_vector const& y) -> double {
		if (x.dimension_ != y.dimension_) {
			throw euclidean_vector_error("Dimensions of LHS(" + std::to_string(x.dimension_) + ") and RHS("
			                             + std::to_string(y.dimension_) + ") do not match");
		}
		return std::inner_product(x.magnitude_.get(),
		                          x.magnitude_.get() + x.dimension_,
		                          y.magnitude_.get(),
		                          0.0);
	}
} // namespace comp6771
