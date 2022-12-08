#ifndef GDWG_GRAPH_HPP
#define GDWG_GRAPH_HPP

#include <algorithm>
#include <iostream>
#include <iterator>
#include <map>
#include <memory>
#include <set>
#include <stdexcept>
#include <vector>

// This will not compile straight away
namespace gdwg {
    template<typename N, typename E>
    class graph {
    public:
        struct value_type {
            N from;
            N to;
            E weight;
        };

    private:
        struct edge {
            N* dist;
            std::unique_ptr<E> weight;

            edge() = default;

            edge(std::unique_ptr<N> const& dis_node, E const& wei)
            : dist{dis_node.get()}
            , weight{std::make_unique<E>(wei)} {}

            edge(N* const& dis_op, E const& wei)
            : dist{dis_op}
            , weight{std::make_unique<E>(wei)} {}

            edge(edge const& other)
            : dist{other.dist}
            , weight{std::make_unique<E>(*(other.weight))} {}

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

            auto operator()(const N& left, const std::unique_ptr<N>& right) const -> bool {
                return left < *right;
            }

            auto operator()(const std::unique_ptr<N>& left, const N& right) const -> bool {
                return *left < right;
            }

            auto operator()(const std::unique_ptr<N>& left, const std::unique_ptr<N>& right) const
               -> bool {
                return *left < *right;
            }
        };

        class src_compare {
        public:
            using is_transparent = std::true_type;

            auto operator()(const N& left, const N* right) const -> bool {
                return left < *right;
            }

            auto operator()(const N* left, const N& right) const -> bool {
                return *left < right;
            }

            auto operator()(const N* left, const N* right) const -> bool {
                return *left < *right;
            }
        };

        class dst_compare {
        public:
            using is_transparent = std::true_type;

            auto operator()(const N& left, const edge& right) const -> bool {
                return left < *right.dist;
            }

            auto operator()(const edge& left, const N& right) const -> bool {
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

        // Add node_compare so that the log complexcity of std::set::find is reserved.
        std::set<std::unique_ptr<N>, node_compare> nodes_;
        /*1 src nodes can have more than 1 edges, hence
           Key: src node,
           Value: sets of edges:
              dist node, weight*/
        std::map<N*, std::set<edge, dst_compare>, src_compare> edges_;

        auto swap(graph& other) -> void {
            std::swap(nodes_, other.nodes_);
            std::swap(edges_, other.edges_);
        }
        class iterator {
            using map_it =
               typename std::map<N*, std::set<edge, dst_compare>, src_compare>::const_iterator;
            using set_it = typename std::set<edge, dst_compare>::const_iterator;

        public:
            using value_type = graph<N, E>::value_type;
            using reference = value_type;
            using pointer = void;
            using difference_type = std::ptrdiff_t;
            using iterator_category = std::bidirectional_iterator_tag;

            // Iterator constructor
            iterator() = default;

            // Iterator source
            auto operator*() const -> reference {
                return value_type{*(src_it_->first), *(dstw_it_->dist), *(dstw_it_->weight)};
            }
            // auto operator->() -> pointer not required

            // Iterator traversal
            auto operator++() -> iterator& {
                if (dstw_it_ != (*src_it_).second.end()) {
                    dstw_it_++;
                }
                if (dstw_it_ == (*src_it_).second.end()) {
                    src_it_++;
                    if (src_it_ != edge_end_) {
                        dstw_it_ = (*src_it_).second.begin();
                    }
                    if (src_it_ == edge_end_) {
                        dstw_it_ = (*src_it_).second.end();
                    }
                }
                return *this;
            }
            auto operator++(int) -> iterator {
                auto temp = *this;
                ++*this;
                return temp;
            }
            auto operator--() -> iterator& {
                if (src_it_ == edge_end_ || dstw_it_ == (*src_it_).second.begin()) {
                    src_it_--;
                    dstw_it_ = (*src_it_).second.end();
                }
                dstw_it_--;
                return *this;
            }
            auto operator--(int) -> iterator {
                auto temp = *this;
                --*this;
                return temp;
            }

            // Iterator comparison
            auto operator==(iterator const& other) const -> bool {
                if (edge_end_ == other.edge_end_ && edge_begin_ == other.edge_begin_) {
                    return src_it_ == other.src_it_ && dstw_it_ == other.dstw_it_;
                }
                return false;
            }

        private:
            explicit iterator(map_it const& startpoint,
                              map_it const& src,
                              set_it const& dstw,
                              map_it const& endpoint)
            : edge_begin_{startpoint}
            , src_it_{src}
            , dstw_it_{dstw}
            , edge_end_{endpoint} {};
            map_it edge_begin_;
            map_it src_it_;
            set_it dstw_it_;
            map_it edge_end_;

            friend class graph<N, E>;
        };

    public:
        [[nodiscard]] auto begin() const -> iterator {
            if (edges_.size() == 0) {
                return end();
            }
            return iterator(edges_.begin(), edges_.begin(), edges_.begin()->second.begin(), edges_.end());
        }

        [[nodiscard]] auto end() const -> iterator {
            return iterator(edges_.begin(), edges_.end(), edges_.end()->second.end(), edges_.end());
        }

        graph()
        : nodes_{std::set<std::unique_ptr<N>, node_compare>{}}
        , edges_{std::map<N*, std::set<edge, dst_compare>, src_compare>{}} {}

        graph(std::initializer_list<N> il)
        : edges_{std::map<N*, std::set<edge, dst_compare>, src_compare>{}} {
            nodes_ = std::set<std::unique_ptr<N>, node_compare>{};
            for (const auto& node : il) {
                nodes_.emplace(std::make_unique<N>(node));
            }
        }

        template<typename InputIt>
        graph(InputIt first, InputIt last)
        : edges_(std::map<N*, std::set<edge, dst_compare>, src_compare>{}) {
            nodes_ = std::set<std::unique_ptr<N>, node_compare>{};
            for (auto it = first; it != last; ++it) {
                nodes_.emplace(std::make_unique<N>(*it));
            }
        }

        graph(graph&& other) noexcept
        : nodes_{std::exchange(other.nodes_, std::set<std::unique_ptr<N>, node_compare>{})}
        , edges_{std::exchange(other.edges_, std::map<N*, std::set<edge, dst_compare>, src_compare>{})} {
        }

        auto operator=(graph&& other) noexcept -> graph& {
            std::swap(nodes_, other.nodes_);
            std::swap(edges_, other.edges_);
            other.nodes_ = std::set<std::unique_ptr<N>, node_compare>{};
            other.edges_ = std::map<N*, std::set<edge, dst_compare>, src_compare>{};
            return *this;
        }

        graph(graph const& other)
        : nodes_{std::set<std::unique_ptr<N>, node_compare>{}}
        , edges_(std::map<N*, std::set<edge, dst_compare>, src_compare>{}) {
            for (auto const& n : other.nodes_) {
                nodes_.emplace(std::make_unique<N>(*n));
                auto const src_it = other.edges_.find(*n);
                if (src_it != other.edges_.end()) {
                    edges_.emplace(n.get(), std::set<edge, dst_compare>{});
                    for (auto& e : (*src_it).second) {
                        edges_[n.get()].emplace(edge(e.dist, *e.weight));
                    }
                }
            }
        }

        auto operator=(graph const& other) -> graph& {
            if (this != std::addressof(other)) {
                clear();
                nodes_ = std::set<std::unique_ptr<N>, node_compare>{};
                edges_ = std::map<N*, std::set<edge, dst_compare>, src_compare>{};
                for (auto const& n : other.nodes_) {
                    nodes_.emplace(std::make_unique<N>(*n));
                    auto const src_it = other.edges_.find(*n);
                    if (src_it != other.edges_.end()) {
                        edges_.emplace(n.get(), std::set<edge, dst_compare>{});
                        for (auto& e : (*src_it).second) {
                            edges_[n.get()].emplace(edge(e.dist, *e.weight));
                        }
                    }
                }
            }
            return *this;
        }

        auto insert_node(N const& value) -> bool {
            if (is_node(value)) {
                return false;
            }
            nodes_.emplace(std::make_unique<N>(value));
            return true;
        }

        auto insert_edge(N const& src, N const& dst, E const& weight) -> bool {
            if (!is_node(src) || !is_node(dst)) {
                throw std::runtime_error("Cannot call gdwg::graph<N, E>::insert_edge when either src "
                                         "or dst node does not exist");
            }

            // valid nodes, check if there are edges with the src:
            auto src_iter = nodes_.find(src);
            auto dist_iter = nodes_.find(dst);
            auto src_key_iter = edges_.find(src);
            if (src_key_iter == edges_.end()) {
                /*New edge, new src*/
                edges_.emplace((*src_iter).get(), std::set<edge, dst_compare>{});
                edges_[(*src_iter).get()].emplace(edge(*dist_iter, weight));
                return true;
            }
            /*Custom Compare in std::set<edge>
            Check if (src, dst, weight) exists*/
            if (edges_[(*src_iter).get()].find(dst) == edges_[(*src_iter).get()].end()) {
                /*New edge, old src*/
                edges_[(*src_iter).get()].emplace(edge(*dist_iter, weight));
                return true;
            }

            auto range = edges_[(*src_iter).get()].equal_range(*(*dist_iter));
            for (auto& it = range.first; it != range.second; ++it) {
                if (*(*it).weight == weight) {
                    // src, dst, weight already exists
                    return false;
                }
            }
            // Old src, old dst, new weight
            edges_[(*src_iter).get()].emplace(edge(*dist_iter, weight));
            return true;
        }

        auto replace_node(N const& old_data, N const& new_data) -> bool {
            if (!is_node(old_data)) {
                throw std::runtime_error("Cannot call gdwg::graph<N, E>::replace_node on a node that "
                                         "doesn't exist");
            }
            if (is_node(new_data)) {
                return false;
            }

            nodes_.emplace(std::make_unique<N>(new_data));
            edges_.emplace((*nodes_.find(new_data)).get(), std::set<edge, dst_compare>{});
            auto new_it = nodes_.find(new_data);
            auto old_it = nodes_.find(old_data);
            /*Case1 old_data as src*/
            auto old_key_it = edges_.find(old_data);
            auto new_key_it = edges_.find(new_data);
            if (old_key_it != edges_.end()) {
                for (auto const& e : (*old_key_it).second) {
                    (*new_key_it).second.emplace(e);
                }
                edges_.erase(old_key_it);
            }
            /*Case2 old_data as dst*/
            for (auto& e : edges_) {
                auto count = e.second.count(old_data);
                while (count != 0) {
                    auto const it = e.second.find(old_data);
                    auto const wei = *(*it).weight;
                    e.second.emplace(edge(*new_it, wei));
                    e.second.erase(it);
                    --count;
                }
            }
            nodes_.erase(old_it);
            return true;
        }

        auto merge_replace_node(N const& old_data, N const& new_data) -> void {
            if (!is_node(old_data) || !is_node(new_data)) {
                throw std::runtime_error("Cannot call gdwg::graph<N, E>::merge_replace_node on old or "
                                         "new data if they don't exist in the graph");
            }
            /*Case1: when new_data appears in src:
               old_data->data of weight w
               to
               new_data->data of weight w */
            auto new_it = nodes_.find(new_data);
            auto old_it = nodes_.find(old_data);
            auto old_key_it = edges_.find(old_data);
            auto new_key_it = edges_.find(new_data);
            if (new_key_it == edges_.end()) {
                edges_.emplace((*new_it).get(), std::set<edge, dst_compare>{});
                new_key_it = edges_.find(new_data);
            }
            if (old_key_it != edges_.end()) {
                for (auto const& e : (*old_key_it).second) {
                    (*new_key_it).second.emplace(e);
                }
                edges_.erase(old_key_it);
            }
            /*Case2: when new_data appears in dst:
               data->old_data of weight w
               to
               data->new_data  of weight w */
            for (auto& e : edges_) {
                auto count = e.second.count(old_data);
                while (count != 0) {
                    auto const it = e.second.find(old_data);
                    auto const wei = *(*it).weight;
                    e.second.emplace(edge(*new_it, wei));
                    e.second.erase(it);
                    --count;
                }
            }
            // Remove node old_data
            nodes_.erase(old_it);
        }

        auto erase_node(N const& value) -> bool {
            if (!is_node(value)) {
                return false;
            }
            /*Case1: node of val is a src*/
            auto val_it = edges_.find(value);
            if (val_it != edges_.end()) {
                edges_.erase(val_it);
                /*Case2: node of val is a dst*/
                for (auto& e : edges_) {
                    auto count = e.second.count(value);
                    while (count != 0) {
                        e.second.erase(e.second.find(value));
                        --count;
                    }
                }
                nodes_.erase(nodes_.find(value));
                return true;
            }
            for (auto& e : edges_) {
                auto count = e.second.count(value);
                while (count != 0) {
                    e.second.erase(e.second.find(value));
                    --count;
                }
            }
            nodes_.erase(nodes_.find(value));
            return true;
        }

        auto erase_edge(N const& src, N const& dst, E const& weight) -> bool {
            if (!is_node(src) || !is_node(dst)) {
                throw std::runtime_error("Cannot call gdwg::graph<N, E>::erase_edge on src or dst if "
                                         "they don't exist in the graph");
            }
            auto src_key_it = edges_.find(src);
            if (src_key_it == edges_.end()) {
                return false;
            }
            auto dst_it = (*src_key_it).second.find(dst);
            if (dst_it == (*src_key_it).second.end()) {
                return false;
            }
            auto range = (*src_key_it).second.equal_range(dst);
            for (auto& it = range.first; it != range.second; ++it) {
                if (*(*it).weight == weight) {
                    (*src_key_it).second.erase(it);
                    if ((*src_key_it).second.size() == 0) {
                        edges_.erase(src_key_it);
                    }
                    return true;
                }
            }
            return false;
        }

        auto erase_edge(iterator i) -> iterator {
            if (i == end()) {
                return i;
            }

            auto holder = i++;
            edges_[(*holder.src_it_).first].erase(holder.dstw_it_);
            if (edges_[(*holder.src_it_).first].size() == 0) {
                edges_.erase(holder.src_it_);
            }
            if (edges_.size() == 0) {
                return end();
            }
            return i;
        }

        auto erase_edge(iterator i, iterator s) -> iterator {
            if (i == end()) {
                return end();
            }
            while (i != s) {
                if (i == end()) {
                    return end();
                }
                i = erase_edge(i);
            }
            return s;
        }

        auto clear() noexcept -> void {
            edges_.clear();
            nodes_.clear();
        }

        [[nodiscard]] auto is_node(N const& value) const -> bool {
            return nodes_.find(value) != nodes_.end();
        }

        [[nodiscard]] auto empty() const -> bool {
            return nodes_.size() == 0;
        }

        [[nodiscard]] auto is_connected(N const& src, N const& dst) const -> bool {
            if (!is_node(src) || !is_node(dst)) {
                throw std::runtime_error("Cannot call gdwg::graph<N, E>::is_connected if src or dst "
                                         "node don't exist in the graph");
            }
            auto src_it = edges_.find(src);
            if (src_it == edges_.end()) {
                return false;
            }
            return (*src_it).second.find(dst) != (*src_it).second.end();
        }

        [[nodiscard]] auto nodes() const -> std::vector<N> {
            auto vec = std::vector<N>{};
            vec.reserve(nodes_.size());
            for (auto const& n : nodes_) {
                vec.emplace(vec.end(), *n);
            }
            return vec;
        }

        [[nodiscard]] auto weights(N const& src, N const& dst) const -> std::vector<E> {
            if (!is_node(src) || !is_node(dst)) {
                throw std::runtime_error("Cannot call gdwg::graph<N, E>::weights if src or dst node "
                                         "don't exist in the graph");
            }

            auto src_it = edges_.find(src);
            if (src_it == edges_.end()) {
                return std::vector<E>{};
            }

            auto dst_it = (*src_it).second.find(dst);
            if (dst_it == (*src_it).second.end()) {
                return std::vector<E>{};
            }

            auto weis = std::vector<E>{};
            auto range = (*src_it).second.equal_range(*(*dst_it).dist);
            for (auto it = range.first; it != range.second; ++it) {
                weis.emplace(weis.end(), (*(*it).weight));
            }
            return weis;
        }

        [[nodiscard]] auto find(N const& src, N const& dst, E const& weight) const -> iterator {
            if (!is_node(src) || !is_node(dst)) {
                return end();
            }
            auto src_it = edges_.find(src);
            if (src_it == edges_.end()) {
                return end();
            }
            auto range = (*src_it).second.equal_range(dst);
            for (auto it = range.first; it != range.second; ++it) {
                if (*(*it).weight == weight) {
                    return iterator(edges_.begin(), src_it, it, edges_.end());
                }
            }
            return end();
        }

        [[nodiscard]] auto connections(N const& src) const -> std::vector<N> {
            if (!is_node(src)) {
                throw std::runtime_error("Cannot call gdwg::graph<N, E>::connections if src doesn't "
                                         "exist in the graph");
            }
            auto src_it = edges_.find(src);
            if (src_it == edges_.end()) {
                return std::vector<N>{};
            }

            auto connects = std::vector<N>{};
            for (auto const& dst : (*src_it).second) {
                if (std::find(connects.begin(), connects.end(), *(dst.dist)) == connects.end()) {
                    connects.emplace(connects.end(), *(dst.dist));
                }
            }
            return connects;
        }

        [[nodiscard]] auto operator==(graph const& other) const -> bool {
            if (nodes_.size() != other.nodes_.size() || edges_.size() != other.edges_.size()) {
                return false;
            }

            auto node_equal = std::equal(nodes_.begin(),
                                         nodes_.end(),
                                         other.nodes_.begin(),
                                         other.nodes_.end(),
                                         [](auto const& lhs, auto const& rhs) { return *lhs == *rhs; });
            if (!node_equal) {
                return false;
            }
            if (node_equal) {
                auto other_e = other.edges_.begin();
                for (auto const& ed : edges_) {
                    if (!std::equal(ed.second.begin(),
                                    ed.second.end(),
                                    (*other_e).second.begin(),
                                    (*other_e).second.end(),
                                    [](auto const& lhs, auto const& rhs) {
                                        return *lhs.dist == *rhs.dist && *lhs.weight == *rhs.weight;
                                    }))
                    {
                        return false;
                    }
                    other_e++;
                }
            }
            return true;
        }

        friend auto operator<<(std::ostream& os, graph const& g) -> std::ostream& {
            for (auto const& src : g.nodes_) {
                os << *src << " (\n";
                auto const src_it = g.edges_.find(*src);
                if (src_it != g.edges_.end()) {
                    for (auto const& ed : (*src_it).second) {
                        os << "  " << *(ed.dist) << " | " << *(ed.weight) << '\n';
                    }
                }
                os << ")\n";
            }
            return os;
        }
    };

} // namespace gdwg

#endif // GDWG_GRAPH_HPP
