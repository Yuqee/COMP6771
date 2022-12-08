#include <iostream>
#include <set>
#include <memory>


class comparator {
public:
    using is_transparent = std::true_type;

    auto operator()(const int& left, const std::unique_ptr<int>& right) const -> bool {
        std::cout << "left INT is: " << left << " left b is: " << *right << '\n';
        return left > *right;
    }

    auto operator()(const std::unique_ptr<int>& left, const int& right) const -> bool {
        std::cout << "left b is: " << *left << " right INT is: " << right << '\n';
        return *left > right;
    }

    auto operator()(const std::unique_ptr<int>& left, const std::unique_ptr<int>& right) const
       -> bool {
        std::cout << "left b is: " << *left << " right b is: " << *right << '\n';
        return *left > *right;
    }
};

auto main() -> int {
    auto nodes = std::set<std::unique_ptr<int>, comparator>{};
    nodes.emplace(std::make_unique<int>(1));
    nodes.emplace(std::make_unique<int>(2));
    std::cout << "Find:\n";
    if (nodes.find(2) != nodes.end()) {
        std::cout << "Found!!!\n";
    }

    for (auto const& n : nodes) {
        std::cout << *n << "  ";
    }
    std::cout << "\n";
}
