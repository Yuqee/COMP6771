friend auto operator<<(std::ostream& os, graph const& g) -> std::ostream& {
         for (auto const& src : g.nodes_) {
             os << *src << " (\n";
             auto str = std::ostringstream{};
             str << *src;
             auto const space = static_cast<int>(str.str().length()) + 1;
             auto const src_it = g.edges_.find(*src);
             if (src_it != g.edges_.end()) {
                 auto leng = std::set<int>{};
                 for (auto const& ed : (*src_it).second) {
                     str = std::ostringstream{};
                     str << *(ed.dist);
                     leng.emplace(static_cast<int>(str.str().length()));
                 }
                 auto const w_space = *leng.rbegin();
                 for (auto const& ed : (*src_it).second) {
                     os << std::setw(space) << "" << *(ed.dist);
                     str = std::ostringstream{};
                     str << *(ed.dist);
                     auto space2 = w_space - static_cast<int>(str.str().length()) + 1;
                     os << std::setw(space2) << ""
                        << "| " << *(ed.weight) << '\n';
                 }
             }
             os << ")\n";
         }
         return os;
        }