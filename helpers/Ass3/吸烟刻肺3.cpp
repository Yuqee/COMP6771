#include <algorithm>
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

    edge(int* const& dis_op, int const& wei)
    : dist{dis_op}
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
        return left < *right;
    }

    auto operator()(const std::unique_ptr<int>& left, const int& right) const -> bool {
        return *left < right;
    }

    auto operator()(const std::unique_ptr<int>& left, const std::unique_ptr<int>& right) const
       -> bool {
        return *left < *right;
    }
};

class src_compare {
public:
    using is_transparent = std::true_type;

    auto operator()(const int& left, const int* right) const -> bool {
        return left < *right;
    }

    auto operator()(const int* left, const int& right) const -> bool {
        return *left < right;
    }

    auto operator()(const int* left, const int* right) const -> bool {
        return *left < *right;
    }

    auto operator()(const int& left, const edge& right) const -> bool {
        return left < *right.dist;
    }

    auto operator()(const edge& left, const int& right) const -> bool {
        return *left.dist < right;
    }

    auto operator()(const edge& left, const edge& right) const -> bool {
        if (*left.dist < *right.dist) {
            return true;
        }
        if (*left.dist == *right.dist) {
            return *left.weight < *right.weight;
        }
        return false;
    }
};

class dst_compare {
public:
    using is_transparent = std::true_type;

    auto operator()(const int& left, const edge& right) const -> bool {
        return left < *right.dist;
    }

    auto operator()(const edge& left, const int& right) const -> bool {
        return *left.dist < right;
    }

    auto operator()(const edge& left, const edge& right) const -> bool {
        if (*left.dist < *right.dist) {
            return true;
        }
        if (*left.dist == *right.dist) {
            return *left.weight < *right.weight;
        }
        return false;
    }
};

auto print(std::map<int*, std::set<edge, dst_compare>, src_compare> const& edges) {
    for (auto const& e : edges) {
        for (auto const& dst_w : e.second) {
            std::cout << *e.first << "->" << *dst_w.dist << " of weight " << *dst_w.weight << '\n';
        }
    }
}
auto main() -> int {
    auto edges = std::map<int*, std::set<edge, dst_compare>, src_compare>{};
    auto nodes = std::set<std::unique_ptr<int>, node_compare>{};

    nodes.emplace(std::make_unique<int>(1));
    nodes.emplace(std::make_unique<int>(2));
    nodes.emplace(std::make_unique<int>(3));

    auto op1 = nodes.find(1)->get();
    auto op2 = nodes.find(2)->get();
    auto op3 = nodes.find(3)->get();

    edges.emplace(op1, std::set<edge, dst_compare>{});
    edges[op1].emplace(edge(op1, 1));
    edges.emplace(op2, std::set<edge, dst_compare>{});
    edges[op2].emplace(edge(op1, 1));
    edges[op2].emplace(edge(op2, 3));
    edges.emplace(op3, std::set<edge, dst_compare>{});
    edges[op3].emplace(edge(op1, 2));
    edges[op3].emplace(edge(op2, 3));
    edges[op3].emplace(edge(op3, 12));
    edges[op3].emplace(edge(op3, 9));
    edges[op3].emplace(edge(op1, 1));
    edges[op2].emplace(edge(op3, 3));
    edges[op1].emplace(edge(op1, 1));
    edges[op1].emplace(edge(op3, 1));
    edges[op1].emplace(edge(op1, 1));
    edges[op1].emplace(edge(op1, 1));

    print(edges);

    std::cout << "Merge replace node 3 with node 1\n";
    // /*For node3 as src, loop through and insert into
    // node1's set and then delete them form edges*/
    for (auto const& e : edges[op3]) {
        edges[op1].emplace(e);
    }
    print(edges);
    /*For node3 as dst, check inside every sets of src*/
    for (auto& e : edges) {
        auto count = e.second.count(*op3);
        while (count != 0) {
            std::cout << "Remain: " << count << '\n';
            auto const& it = e.second.find(*op3);
            auto const wei = *(*it).weight;
            e.second.erase(it);
            e.second.emplace(edge(op1, wei));
            count--;
        }
    }
    edges.erase(op3);
    print(edges);
}
