#include <iostream>
#include <map>
#include <memory>
#include <set>

struct edge {
    int* dist;
    std::unique_ptr<int> weight;

    edge() = default;

    edge(std::unique_ptr<int> const& dis_node, int const& wei)
    : dist{dis_node.get()}
    , weight{std::make_unique<int>(wei)} {}

    edge(edge const& other)
    : dist{other.dist}
    , weight{std::make_unique<int>(*(other.weight))} {}

    auto operator<(const edge& rhs) const -> bool {
        if (*dist != *rhs.dist) {
            return *dist < *rhs.dist;
        }
        return *weight < *(rhs.weight);
    }
};

class node_compare {
public:
    using is_transparent = std::true_type;

    auto operator()(const int& left, const std::unique_ptr<int>& right) const -> bool {
        return left > *right;
    }

    auto operator()(const std::unique_ptr<int>& left, const int& right) const -> bool {
        return *left > right;
    }

    auto operator()(const std::unique_ptr<int>& left, const std::unique_ptr<int>& right) const
       -> bool {
        return *left > *right;
    }
};

class src_compare {
public:
    using is_transparent = std::true_type;

    auto operator()(const int& left, const int* right) const -> bool {
        return left > *right;
    }

    auto operator()(const int* left, const int& right) const -> bool {
        return *left > right;
    }

    auto operator()(const int* left, const int* right) const -> bool {
        return *left > *right;
    }
};

class dst_comapre {
public:
    using is_transparent = std::true_type;

    auto operator()(const int& left, const edge& right) const -> bool {
        return left > *right.dist;
    }

    auto operator()(const edge& left, const int& right) const -> bool {
        return *left.dist > right;
    }

    auto operator()(const edge& left, const edge& right) const -> bool {
        return *left.dist > *right.dist;
    }
};

auto main() -> int {
    auto graphs = std::map<int*, std::set<edge, dst_comapre>, src_compare>{};
    auto nodes = std::set<std::unique_ptr<int>, node_compare>{};

    nodes.emplace(std::make_unique<int>(1));
    nodes.emplace(std::make_unique<int>(2));
    if (nodes.find(2) != nodes.end()) {
        std::cout << "FOUND 2 in nodes!!!!\n";
    }

    auto edges = std::set<edge, dst_comapre>{};
    edges.emplace(edge(*nodes.find(1), 2));
    auto op1 = (*nodes.find(2)).get();
    graphs.emplace(op1, edges); /*2->1 of wieght 2*/
    if (graphs.find(2) != graphs.end()) {
        std::cout << "FOUND 2 in src of g!!!!\n";
    }
    if (graphs.find(1) != graphs.end()) {
        std::cout << "FOUND 1 in src of g!!!!\n";
    }

    if (edges.find(1) != edges.end()) {
        std::cout << "FOUND 1 in dist in edges!!!!\n";
    }
}
