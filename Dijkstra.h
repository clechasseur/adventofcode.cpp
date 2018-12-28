#pragma once

#include <vector>
#include <tuple>
#include <unordered_map>

namespace dij {

struct node {
    virtual ~node() { }
};
struct graph {
    virtual ~graph() { }
    virtual std::vector<node*> all_passable() const = 0;
    virtual std::vector<node*> neighbours(node* pn, node* pinclude) const = 0;
    virtual int64_t dist(node* pn1, node* pn2) const = 0;
    virtual bool is_a_better(node* pa, node* pb) const = 0;
};

std::tuple<std::unordered_map<node*, int64_t>, std::unordered_map<node*, node*>> get_dijkstra(graph* pg, node* pstart);
std::vector<node*> assemble_path(const std::unordered_map<node*, node*>& prev, node* pstart, node* pend);

}
