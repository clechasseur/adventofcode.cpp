#include "Dijkstra.h"

#include <algorithm>
#include <unordered_set>
#include <limits>

#include <coveo/linq.h>

namespace dij {

// https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm
//
std::tuple<std::unordered_map<node*, int64_t>, std::unordered_map<node*, node*>> get_dijkstra(graph* pg, node* pstart)
{
    using namespace coveo::linq;

    std::unordered_set<node*> Q;
    std::unordered_map<node*, int64_t> dist;
    std::unordered_map<node*, node*> prev;

    auto all_to_check = from(pg->all_passable())
                      | union_with(std::vector<node*>{ pstart });
    for (node* pn : all_to_check) {
        dist[pn] = std::numeric_limits<int64_t>::max();
        prev[pn] = nullptr;
        Q.emplace(pn);
    }
    dist[pstart] = 0;

    while (!Q.empty()) {
        node* pu = nullptr;
        int64_t udist = std::numeric_limits<int64_t>::max();
        for (node* pn : Q) {
            int64_t ndist = dist[pn];
            if (ndist < udist) {
                pu = pn;
                udist = ndist;
            }
        }
        if (pu == nullptr) {
            break;
        }
        Q.erase(pu);

        for (node* pv : pg->neighbours(pu, nullptr)) {
            auto alt = dist[pu] + pg->dist(pu, pv);
            if (alt < dist[pv] || (alt == dist[pv] && pg->is_a_better(pu, prev[pv]))) {
                dist[pv] = alt;
                prev[pv] = pu;
            }
        }
    }

    return std::make_tuple(dist, prev);
}

std::vector<node*> assemble_path(const std::unordered_map<node*, node*>& prev, node* pstart, node* pend)
{
    std::vector<node*> path;
    node* pn = pend;
    for (;;) {
        if (pn != pstart) {
            path.push_back(pn);
        } else {
            break;
        }
        pn = prev.find(pn)->second;
    }
    std::reverse(path.begin(), path.end());
    return path;
}

} // namespace dij
