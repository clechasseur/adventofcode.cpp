// adventofcode2018.cpp

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <set>
#include <map>
#include <utility>
#include <memory>
#include <algorithm>
#include <iterator>
#include <cctype>
#include <future>
#include <thread>
#include <forward_list>
#include <functional>
#include <queue>
#include <stack>
#include <limits>
#include <unordered_set>
#include <unordered_map>

#include <coveo/linq.h>

#include "Dijkstra.h"

using namespace coveo::linq;

void day1_1()
{
    int freq = 0;
    for (;;) {
        std::string line;
        std::getline(std::cin, line);
        if (line == "0") {
            break;
        }
        bool plus = (line[0] == '+');
        line = line.substr(1);
        std::istringstream iss(line);
        int mod = 0;
        iss >> mod;
        if (!plus) {
            mod = -mod;
        }
        freq += mod;
    }
    std::cout << freq << std::endl;
}

void day1_2()
{
    std::vector<int> input;
    for (;;) {
        std::string line;
        std::getline(std::cin, line);
        if (line == "0") {
            break;
        }
        bool plus = (line[0] == '+');
        line = line.substr(1);
        std::istringstream iss(line);
        int mod = 0;
        iss >> mod;
        if (!plus) {
            mod = -mod;
        }
        input.push_back(mod);
    }

    int freq = 0;
    std::set<int> seen;
    bool go = true;
    while (go) {
        for (auto it = input.begin(); go && it != input.end(); ++it) {
            freq += *it;
            if (!seen.emplace(freq).second) {
                go = false;
            }
        }
    }
    std::cout << freq << std::endl;
}

void day2_1()
{
    int two = 0, three = 0;
    for (;;) {
        std::string word;
        std::getline(std::cin, word);
        if (word == "out") {
            break;
        }
        std::map<char, int> m;
        for (auto it = word.begin(); it != word.end(); ++it) {
            ++m[*it];
        }
        bool has_two = false, has_three = false;
        for (auto it = m.begin(); it != m.end(); ++it) {
            if (it->second == 2) {
                has_two = true;
            } else if (it->second == 3) {
                has_three = true;
            }
            if (has_two && has_three) {
                break;
            }
        }
        if (has_two) {
            ++two;
        }
        if (has_three) {
            ++three;
        }
    }
    int checksum = two * three;
    std::cout << checksum << std::endl;
}

void day2_2()
{
    std::vector<std::string> input;
    for (;;) {
        std::string word;
        std::getline(std::cin, word);
        if (word == "out") {
            break;
        }
        input.push_back(word);
    }

    bool go = true;
    for (auto it1 = input.begin(); go && it1 != input.end(); ++it1) {
        for (auto it2 = input.begin(); go && it2 != input.end(); ++it2) {
            if (it1 != it2) {
                int sim = 0;
                std::string common;
                for (auto wit1 = it1->begin(), wit2 = it2->begin(); wit1 != it1->end() && wit2 != it2->end(); ++wit1, ++wit2) {
                    if (*wit1 == *wit2) {
                        ++sim;
                        common.push_back(*wit1);
                    }
                }
                if (sim == it1->size() - 1) {
                    std::cout << common << std::endl;
                    go = false;
                }
            }
        }
    }
}

void day3_1()
{
    struct piece {
        int id = 0, x = 0, y = 0, width = 0, height = 0;
    };
    std::vector<piece> pieces;
    for (;;) {
        std::string line;
        std::getline(std::cin, line);
        if (line == "out") {
            break;
        }
        line = line.substr(1); // drop the #
        std::istringstream iss(line);
        char c = 0;
        piece p;
        iss >> p.id >> c;       // c reads the @
        iss >> p.x >> c;        // c reads the ,
        iss >> p.y >> c;        // c reads the :
        iss >> p.width >> c;    // c reads the x
        iss >> p.height;
        pieces.push_back(p);
    }

    std::vector<std::vector<int>> fabric;
    fabric.resize(1000);
    for (auto&& f : fabric) {
        f.resize(1000);
    }
    for (auto&& p : pieces) {
        for (int x = p.x; x < p.x + p.width; ++x) {
            for (int y = p.y; y < p.y + p.height; ++y) {
                ++fabric[x][y];
            }
        }
    }

    int overlaps = 0;
    for (int i = 0; i < 1000; ++i) {
        for (int j = 0; j < 1000; ++j) {
            if (fabric[i][j] > 1) {
                ++overlaps;
            }
        }
    }
    std::cout << overlaps << std::endl;
}

void day3_2()
{
    struct piece {
        int id = 0, x = 0, y = 0, width = 0, height = 0;
    };
    std::vector<piece> pieces;
    for (;;) {
        std::string line;
        std::getline(std::cin, line);
        if (line == "out") {
            break;
        }
        line = line.substr(1); // drop the #
        std::istringstream iss(line);
        char c = 0;
        piece p;
        iss >> p.id >> c;       // c reads the @
        iss >> p.x >> c;        // c reads the ,
        iss >> p.y >> c;        // c reads the :
        iss >> p.width >> c;    // c reads the x
        iss >> p.height;
        pieces.push_back(p);
    }

    std::vector<std::vector<int>> fabric;
    fabric.resize(1000);
    for (auto&& f : fabric) {
        f.resize(1000);
    }
    for (auto&& p : pieces) {
        for (int x = p.x; x < p.x + p.width; ++x) {
            for (int y = p.y; y < p.y + p.height; ++y) {
                ++fabric[x][y];
            }
        }
    }

    piece lone;
    for (auto&& p : pieces) {
        bool good = true;
        for (int x = p.x; good && x < p.x + p.width; ++x) {
            for (int y = p.y; good && y < p.y + p.height; ++y) {
                good = fabric[x][y] == 1;
            }
        }
        if (good) {
            lone = p;
            break;
        }
    }
    std::cout << lone.id << std::endl;
}

void day4_1()
{
    struct datentime {
        int y = 0, m = 0, d = 0, h = 0, min = 0;
        bool operator<(const datentime& right) const {
            int cmp = y - right.y;
            if (cmp == 0) {
                cmp = m - right.m;
                if (cmp == 0) {
                    cmp = d - right.d;
                    if (cmp == 0) {
                        cmp = h - right.h;
                        if (cmp == 0) {
                            cmp = min - right.min;
                        }
                    }
                }
            }
            return cmp < 0;
        }
    };
    std::map<datentime, std::string> entries;
    for (;;) {
        std::string line;
        std::getline(std::cin, line);
        if (line == "out") {
            break;
        }
        std::istringstream iss(line);
        datentime date;
        std::string entry;
        char c = 0;
        iss >> c >> date.y
            >> c >> date.m
            >> c >> date.d
                 >> date.h
            >> c >> date.min
            >> c;
        std::getline(iss, entry);
        while (entry.front() == ' ') {
            entry = entry.substr(1);
        }
        entries.emplace(date, entry);
    }

    struct timeperiod {
        datentime start, end;
    };
    std::map<int, std::vector<timeperiod>> guards;
    std::vector<timeperiod>* pcurperiods = nullptr;
    for (auto&& e : entries) {
        if (e.second.front() == 'G') {
            std::istringstream iss(e.second);
            std::string foo;
            char c = 0;
            int id = 0;
            iss >> foo >> c >> id;
            pcurperiods = &guards[id];
        } else if (e.second.front() == 'f') {
            pcurperiods->push_back({e.first, {}});
        } else {
            pcurperiods->back().end = e.first;
        }
    }

    struct guardinfo {
        int asleep_mins;
        int mins[60];
        guardinfo() : asleep_mins(0), mins() { }
    };
    std::map<int, guardinfo> guardinfos;
    for (auto&& g : guards) {
        auto& gi = guardinfos[g.first];
        for (auto&& tp : g.second) {
            gi.asleep_mins += (tp.end.min - tp.start.min);
            for (int i = tp.start.min; i < tp.end.min; ++i) {
                ++gi.mins[i];
            }
        }
    }

    auto winner = std::max_element(guardinfos.begin(), guardinfos.end(),
                                   [](auto&& left, auto&& right) {
                                       return left.second.asleep_mins < right.second.asleep_mins;
                                   });
    int max_min = 0;
    int max_value = 0;
    for (int i = 0; i < 60; ++i) {
        if (winner->second.mins[i] > max_value) {
            max_min = i;
            max_value = winner->second.mins[i];
        }
    }
    std::cout << winner->first * max_min << std::endl;
}

void day4_2()
{
    struct datentime {
        int y = 0, m = 0, d = 0, h = 0, min = 0;
        bool operator<(const datentime& right) const {
            int cmp = y - right.y;
            if (cmp == 0) {
                cmp = m - right.m;
                if (cmp == 0) {
                    cmp = d - right.d;
                    if (cmp == 0) {
                        cmp = h - right.h;
                        if (cmp == 0) {
                            cmp = min - right.min;
                        }
                    }
                }
            }
            return cmp < 0;
        }
    };
    std::map<datentime, std::string> entries;
    for (;;) {
        std::string line;
        std::getline(std::cin, line);
        if (line == "out") {
            break;
        }
        std::istringstream iss(line);
        datentime date;
        std::string entry;
        char c = 0;
        iss >> c >> date.y
            >> c >> date.m
            >> c >> date.d
                 >> date.h
            >> c >> date.min
            >> c;
        std::getline(iss, entry);
        while (entry.front() == ' ') {
            entry = entry.substr(1);
        }
        entries.emplace(date, entry);
    }

    struct timeperiod {
        datentime start, end;
    };
    std::map<int, std::vector<timeperiod>> guards;
    std::vector<timeperiod>* pcurperiods = nullptr;
    for (auto&& e : entries) {
        if (e.second.front() == 'G') {
            std::istringstream iss(e.second);
            std::string foo;
            char c = 0;
            int id = 0;
            iss >> foo >> c >> id;
            pcurperiods = &guards[id];
        } else if (e.second.front() == 'f') {
            pcurperiods->push_back({e.first, {}});
        } else {
            pcurperiods->back().end = e.first;
        }
    }

    std::vector<std::map<int, int>> minutes;
    minutes.resize(60);
    for (auto&& g : guards) {
        for (auto&& tp : g.second) {
            for (int i = tp.start.min; i < tp.end.min; ++i) {
                ++minutes[i][g.first];
            }
        }
    }

    int minute = 0;
    int num_sleeps = 0;
    int guard_id = 0;
    for (int i = 0; i < 60; ++i) {
        for (auto&& gi : minutes[i]) {
            if (gi.second > num_sleeps) {
                minute = i;
                num_sleeps = gi.second;
                guard_id = gi.first;
            }
        }
    }
    std::cout << guard_id * minute << std::endl;
}

void day5_1()
{
    std::list<char> chain;
    for (;;) {
        std::string line;
        std::getline(std::cin, line);
        if (line == "out") {
            break;
        }
        chain.push_back(line[0]);
    }

    int removals;
    do {
        removals = 0;
        auto it = chain.begin();
        while (it != chain.end()) {
            auto itnext = std::next(it);
            if (itnext == chain.end()) {
                break;
            }
            if (std::tolower(*it) == std::tolower(*itnext) && *it != *itnext) {
                it = chain.erase(it, std::next(itnext));
                ++removals;
            } else {
                ++it;
            }
        }
        std::cout << removals << std::endl;
    } while (removals > 0);
    std::cout << chain.size() << std::endl;
}

void day5_2()
{
    std::list<char> chain;
    for (;;) {
        std::string line;
        std::getline(std::cin, line);
        if (line == "out") {
            break;
        }
        chain.push_back(line[0]);
    }

    auto compute = [&](char c) -> int {
        std::list<char> newchain(chain);
        {
            auto it = newchain.begin();
            while (it != newchain.end()) {
                if (std::tolower(*it) == c) {
                    it = newchain.erase(it);
                } else {
                    ++it;
                }
            }
        }

        int removals;
        do {
            removals = 0;
            auto it = newchain.begin();
            while (it != newchain.end()) {
                auto itnext = std::next(it);
                if (itnext == newchain.end()) {
                    break;
                }
                if (std::tolower(*it) == std::tolower(*itnext) && *it != *itnext) {
                    it = newchain.erase(it, std::next(itnext));
                    ++removals;
                } else {
                    ++it;
                }
            }
        } while (removals > 0);
        return static_cast<int>(newchain.size());
    };
    std::vector<std::future<int>> futures;
    for (char c = 'a'; c <= 'z'; ++c) {
        futures.emplace_back(std::async(std::launch::async, compute, c));
    }
    int shortest_len = from(futures)
                     | min([](auto&& f) { return f.get(); });
    std::cout << shortest_len << std::endl;
}

void day6_1()
{
    struct coord {
        int x, y;
        coord(int i = 0, int j = 0) : x(i), y(j) { }
    };
    std::vector<coord> coords;
    int highx = 0, highy = 0;
    for (;;) {
        std::string line;
        std::getline(std::cin, line);
        if (line == "out") {
            break;
        }
        std::istringstream iss(line);
        coord p;
        char c = 0;
        iss >> p.x >> c >> p.y;
        coords.push_back(p);
        highx = std::max(highx, p.x);
        highy = std::max(highy, p.y);
    }
    ++highx, ++highy;

    auto manhattan = [](coord a, coord b) {
        return std::abs(a.x - b.x) + std::abs(a.y - b.y);
    };

    std::vector<std::vector<std::map<int, int>>> space;
    space.resize(highx);
    for (auto&& d : space) {
        d.resize(highy);
    }
    for (int i = 0; i < highx; ++i) {
        for (int j = 0; j < highy; ++j) {
            auto&& m = space[i][j];
            for (int k = 0; k < coords.size(); ++k) {
                m[k] = manhattan(coords[k], { i, j });
            }
        }
    }

    struct coverinfo {
        int num = 0;
        bool valid = true;
    };
    std::map<int, coverinfo> cover;
    for (int i = 0; i < highx; ++i) {
        for (int j = 0; j < highy; ++j) {
            auto&& m = space[i][j];
            auto seq = from(m)
                     | order_by([](auto&& p) { return p.second; });
            int closest_id = std::begin(seq)->first;
            int closest_dist = std::begin(seq)->second;
            if (std::next(std::begin(seq))->second > closest_dist) {
                ++cover[closest_id].num;
                if (i == 0 || i == (highx - 1) || j == 0 || j == (highy - 1)) {
                    cover[closest_id].valid = false;
                }
            }
        }
    }

    int largesize = from(cover)
                  | where([](auto&& p) { return p.second.valid; })
                  | order_by_descending([](auto&& p) { return p.second.num; })
                  | select([](auto&& p) { return p.second.num; })
                  | first();
    std::cout << largesize << std::endl;
}

void day6_2()
{
    struct coord {
        int x, y;
        coord(int i = 0, int j = 0) : x(i), y(j) { }
    };
    std::vector<coord> coords;
    int highx = 0, highy = 0;
    for (;;) {
        std::string line;
        std::getline(std::cin, line);
        if (line == "out") {
            break;
        }
        std::istringstream iss(line);
        coord p;
        char c = 0;
        iss >> p.x >> c >> p.y;
        coords.push_back(p);
        highx = std::max(highx, p.x);
        highy = std::max(highy, p.y);
    }
    ++highx, ++highy;

    auto manhattan = [](coord a, coord b) {
        return std::abs(a.x - b.x) + std::abs(a.y - b.y);
    };

    int region_size = 0;
    for (int i = 0; i < highx; ++i) {
        for (int j = 0; j < highy; ++j) {
            int tot_dist = 0;
            for (auto&& c : coords) {
                tot_dist += manhattan(c, { i, j });
            }
            if (tot_dist < 10000) {
                ++region_size;
            }
        }
    }
    std::cout << region_size << std::endl;
}

void day7_1()
{
    std::map<char, std::set<char>> prereqs;
    for (char c = 'A'; c <= 'Z'; ++c) {
        prereqs.emplace(std::piecewise_construct,
                        std::make_tuple(c),
                        std::make_tuple());
    }
    for (;;) {
        std::string line;
        std::getline(std::cin, line);
        if (line == "out") {
            break;
        }
        std::istringstream iss(line);
        std::string word;
        char before = 0, after = 0;
        iss >> word >> before
            >> word >> word >> word >> word
            >> word >> after;
        prereqs[after].emplace(before);
    }

    std::string path;
    while (!prereqs.empty()) {
        for (auto&& p : prereqs) {
            if (p.second.empty()) {
                path.push_back(p.first);
                for (auto&& p2 : prereqs) {
                    p2.second.erase(path.back());
                }
                prereqs.erase(path.back());
                break;
            }
        }
    }
    std::cout << path << std::endl;
}

void day7_2()
{
    std::map<char, std::set<char>> prereqs;
    for (char c = 'A'; c <= 'Z'; ++c) {
        prereqs.emplace(std::piecewise_construct,
                        std::make_tuple(c),
                        std::make_tuple());
    }
    for (;;) {
        std::string line;
        std::getline(std::cin, line);
        if (line == "out") {
            break;
        }
        std::istringstream iss(line);
        std::string word;
        char before = 0, after = 0;
        iss >> word >> before
            >> word >> word >> word >> word
            >> word >> after;
        prereqs[after].emplace(before);
    }

    std::map<char, int> work;
    int sec = 0;
    for (;;) {
        for (auto it = work.begin(); it != work.end(); ) {
            if (--it->second == 0) {
                for (auto&& p : prereqs) {
                    p.second.erase(it->first);
                }
                prereqs.erase(it->first);
                it = work.erase(it);
            } else {
                ++it;
            }
        }
        if (prereqs.empty()) {
            break;
        }
        for (auto it = prereqs.begin(); it != prereqs.end() && work.size() < 5; ++it) {
            if (it->second.empty()) {
                work.emplace(std::piecewise_construct,
                             std::make_tuple(it->first),
                             std::make_tuple(60 + static_cast<int>(it->first - 'A' + 1)));
            }
        }
        ++sec;
    }
    std::cout << sec << std::endl;
}

void day8_1()
{
    struct node {
        std::vector<node> children;
        std::vector<int> meta;
        
        void load() {
            int nchildren = 0, nmeta = 0;
            std::cin >> nchildren >> nmeta;
            while (nchildren-- > 0) {
                children.emplace_back().load();
            }
            while (nmeta-- > 0) {
                std::cin >> meta.emplace_back();
            }
        }

        coveo::enumerable<const node> get_enum() const {
            coveo::enumerable<const node> e = from(coveo::enumerate_one_ref(*this));
            for (const node& c : children) {
                e = from(std::move(e))
                  | concat(c.get_enum());
            }
            return e;
        }
    };
    node root;
    root.load();
    int tot_meta = from(root.get_enum())
                 | select_many([](const node& n) { return n.meta; })
                 | sum([](int i) { return i; });
    std::cout << tot_meta << std::endl;
}

void day8_2()
{
    struct node {
        std::vector<node> children;
        std::vector<int> meta;
        
        void load() {
            int nchildren = 0, nmeta = 0;
            std::cin >> nchildren >> nmeta;
            while (nchildren-- > 0) {
                children.emplace_back().load();
            }
            while (nmeta-- > 0) {
                std::cin >> meta.emplace_back();
            }
        }

        int val() const {
            if (children.empty()) {
                return from(meta)
                     | sum([](int i) { return i; });
            } else {
                int v = 0;
                for (int m : meta) {
                    if (m >= 1 && m <= children.size()) {
                        v += children[m - 1].val();
                    }
                }
                return v;
            }
        }
    };
    node root;
    root.load();
    std::cout << root.val() << std::endl;
}

void day9_1()
{
    const int NUM_PLAYERS = 476;
    const int LAST_MARBLE = 71657;

    struct circle {
        std::list<int> stor;
        decltype(stor)::iterator it = stor.end();
        void insert(int marble) {
            it = stor.insert(it, marble);
        }
        int remove() {
            int marble = *it;
            it = stor.erase(it);
            if (it == stor.end()) {
                it = stor.begin();
            }
            return marble;
        }
        void move_clockwise(int move) {
            while (move-- > 0) {
                ++it;
                if (it == stor.end()) {
                    it = stor.begin();
                }
            }
        }
        void move_counterclockwise(int move) {
            while (move-- > 0) {
                if (it == stor.begin()) {
                    it = stor.end();
                }
                --it;
            }
        }
    };

    std::vector<int> score;
    score.resize(NUM_PLAYERS);
    int cur_player = 0;
    circle board;
    board.insert(0);
    for (int marble = 1; marble <= LAST_MARBLE; ++marble) {
        if (marble % 23 == 0) {
            score[cur_player] += marble;
            board.move_counterclockwise(7);
            score[cur_player] += board.remove();
        } else {
            board.move_clockwise(2);
            board.insert(marble);
        }
        if (++cur_player == NUM_PLAYERS) {
            cur_player = 0;
        }
    }

    int highscore = from(score)
                  | order_by_descending([](int s) { return s; })
                  | first();
    std::cout << highscore << std::endl;
}

void day9_2()
{
    const int64_t NUM_PLAYERS = 476;
    const int64_t LAST_MARBLE = 7165700;

    struct circle {
        std::list<int64_t> stor;
        decltype(stor)::iterator it = stor.end();
        void insert(int64_t marble) {
            it = stor.insert(it, marble);
        }
        int64_t remove() {
            int64_t marble = *it;
            it = stor.erase(it);
            if (it == stor.end()) {
                it = stor.begin();
            }
            return marble;
        }
        void move_clockwise(int move) {
            while (move-- > 0) {
                ++it;
                if (it == stor.end()) {
                    it = stor.begin();
                }
            }
        }
        void move_counterclockwise(int move) {
            while (move-- > 0) {
                if (it == stor.begin()) {
                    it = stor.end();
                }
                --it;
            }
        }
    };

    std::vector<int64_t> score;
    score.resize(NUM_PLAYERS);
    int cur_player = 0;
    circle board;
    board.insert(0);
    for (int64_t marble = 1; marble <= LAST_MARBLE; ++marble) {
        if (marble % 23 == 0) {
            score[cur_player] += marble;
            board.move_counterclockwise(7);
            score[cur_player] += board.remove();
        } else {
            board.move_clockwise(2);
            board.insert(marble);
        }
        if (++cur_player == NUM_PLAYERS) {
            cur_player = 0;
        }
    }

    int64_t highscore = from(score)
                      | order_by_descending([](int64_t s) { return s; })
                      | first();
    std::cout << highscore << std::endl;
}

void day10_1and2()
{
    struct light {
        int x = 0, y = 0, vx = 0, vy = 0;
        void move(int pow = 1) {
            x += (vx * pow);
            y += (vy * pow);
        }
    };
    std::vector<light> lights;
    for (;;) {
        std::string line;
        std::getline(std::cin, line);
        if (line == "out") {
            break;
        }
        std::istringstream iss(line);
        light l;
        char c = 0;
        iss >> c >> c >> c >> c >> c >> c >> c >> c >> c >> c
            >> l.x >> c >> l.y >> c
            >> c >> c >> c >> c >> c >> c >> c >> c >> c >> c
            >> l.vx >> c >> l.vy;
        lights.push_back(l);
    }

    const int MAX_TIME_S = 100000;
    const int SKIP_S = 10490;
    const int CLOSENESS = 25;
    for (auto&& l : lights) {
        l.move(SKIP_S);
    }
    for (int sec = SKIP_S; sec < MAX_TIME_S; ++sec) {
        int close = 0;
        for (auto it1 = lights.begin(); close < CLOSENESS && it1 != lights.end(); ++it1) {
            for (auto it2 = std::next(it1); close < CLOSENESS && it2 != lights.end(); ++it2) {
                if ((std::abs(it1->x - it2->x) + std::abs(it1->y - it2->y)) == 1) {
                    ++close;
                }
            }
        }
        if (close >= CLOSENESS) {
            std::cout << sec << std::endl;
            int minx = from(lights)
                     | min([](auto&& l) { return l.x; });
            int maxx = from(lights)
                     | max([](auto&& l) { return l.x; });
            int miny = from(lights)
                     | min([](auto&& l) { return l.y; });
            int maxy = from(lights)
                     | max([](auto&& l) { return l.y; });
            for (int x = minx; x <= maxx; ++x) {
                for (int y = miny; y <= maxy; ++y) {
                    if (std::any_of(lights.begin(), lights.end(), [=](auto&& l) { return l.x == x && l.y == y; })) {
                        std::cout << '#';
                    } else {
                        std::cout << '.';
                    }
                }
                std::cout << std::endl;
            }
        } else if (sec % 1000 == 0) {
            std::cout << sec << std::endl;
        }
        for (auto&& l : lights) {
            l.move();
        }
    }
}

void day11_1()
{
    const int SERIAL = 2568;

    std::vector<std::vector<int>> grid;
    grid.resize(300);
    for (auto&& v : grid) {
        v.resize(300);
    }
    for (int x = 1; x <= 300; ++x) {
        for (int y = 1; y <= 300; ++y) {
            int& cell = grid[x - 1][y - 1];
            int rackid = x + 10;
            cell = rackid;
            cell *= y;
            cell += SERIAL;
            cell *= rackid;
            cell /= 100;
            cell %= 10;
            cell -= 5;
        }
    }

    int highx = 0, highy = 0, highpow = -1000;
    for (int x = 0; x < 298; ++x) {
        for (int y = 0; y < 298; ++y) {
            int pow = grid[x][y] +
                      grid[x + 1][y] +
                      grid[x + 2][y] +
                      grid[x][y + 1] +
                      grid[x + 1][y + 1] +
                      grid[x + 2][y + 1] +
                      grid[x][y + 2] +
                      grid[x + 1][y + 2] +
                      grid[x + 2][y + 2];
            if (pow > highpow) {
                highx = x + 1;
                highy = y + 1;
                highpow = pow;
            }
        }
    }
    std::cout << highx << "," << highy << " : " << highpow << std::endl;
}

void day11_2()
{
    const int SERIAL = 2568;

    std::vector<std::vector<int>> grid;
    grid.resize(300);
    for (auto&& v : grid) {
        v.resize(300);
    }
    for (int x = 1; x <= 300; ++x) {
        for (int y = 1; y <= 300; ++y) {
            int& cell = grid[x - 1][y - 1];
            int rackid = x + 10;
            cell = rackid;
            cell *= y;
            cell += SERIAL;
            cell *= rackid;
            cell /= 100;
            cell %= 10;
            cell -= 5;
        }
    }

    struct answer {
        int x = 0, y = 0, size = 0, pow = -1000;
    };
    auto find_answer = [&](int size) -> answer {
        answer a;
        a.size = size;
        for (int x = 0; x < (300 - size + 1); ++x) {
            for (int y = 0; y < (300 - size + 1); ++y) {
                int pow = 0;
                for (int i = x; i < x + size; ++i) {
                    for (int j = y; j < y + size; ++j) {
                        pow += grid[i][j];
                    }
                }
                if (pow > a.pow) {
                    a.x = x + 1;
                    a.y = y + 1;
                    a.pow = pow;
                }
            }
        }
        return a;
    };
    std::vector<std::future<answer>> futures;
    for (int i = 1; i <= 300; ++i) {
        futures.emplace_back(std::async(std::launch::async, find_answer, i));
    }
    answer higha = from(futures)
                 | select([](auto&& f) { return f.get(); })
                 | order_by_descending([](auto&& a) { return a.pow; })
                 | first();
    std::cout << higha.x << "," << higha.y << "," << higha.size << " : " << higha.pow << std::endl;
}

void day12_1()
{
    std::map<int, int> gen;
    for (int i = -52; i <= 202; ++i) {
        gen.emplace(i, 0);
    }
    {
        std::string line;
        std::getline(std::cin, line);
        std::istringstream iss(line);
        std::string s;
        iss >> s >> s;
        for (int i = 0; !iss.eof(); ++i) {
            char c = 0;
            iss >> c;
            gen[i] = c == '#' ? 1 : 0;
        }

        std::getline(std::cin, line);
    }

    struct note {
        int minus2 = 0, minus1 = 0, nexus = 0, plus1 = 0, plus2 = 0;
        bool operator<(const note& right) const {
            int cmp = minus2 - right.minus2;
            if (cmp == 0) {
                cmp = minus1 - right.minus1;
                if (cmp == 0) {
                    cmp = nexus - right.nexus;
                    if (cmp == 0) {
                        cmp = plus1 - right.plus1;
                        if (cmp == 0) {
                            cmp = plus2 - right.plus2;
                        }
                    }
                }
            }
            return cmp < 0;
        }
    };
    std::set<note> notes;
    for (;;) {
        std::string line;
        std::getline(std::cin, line);
        if (line == "out") {
            break;
        }
        std::istringstream iss(line);
        note n;
        char c = 0;
        std::string s;
        int* pval[5] = { &n.minus2, &n.minus1, &n.nexus, &n.plus1, &n.plus2 };
        for (int i = 0; i < 5; ++i) {
            iss >> c;
            *pval[i] = c == '#' ? 1 : 0;
        }
        iss >> s >> c;
        if (c == '#') {
            notes.emplace(n);
        }
    }

    for (int g = 0; g < 20; ++g) {
        auto nextgen = gen;
        for (int i = -50; i <= 200; ++i) {
            note n;
            n.minus2 = gen[i - 2];
            n.minus1 = gen[i - 1];
            n.nexus = gen[i];
            n.plus1 = gen[i + 1];
            n.plus2 = gen[i + 2];
            nextgen[i] = (notes.find(n) != notes.end()) ? 1 : 0;
        }
        gen = nextgen;
    }

    int sum_pots = from(gen)
                 | where([](auto&& p) { return p.second == 1; })
                 | select([](auto&& p) { return p.first; })
                 | sum([](int i) { return i; });
    std::cout << sum_pots << std::endl;
}

void day12_2()
{
    std::map<int64_t, int> gen;
    for (int64_t i = -1002; i <= 1002; ++i) {
        gen.emplace(i, 0);
    }
    {
        std::string line;
        std::getline(std::cin, line);
        std::istringstream iss(line);
        std::string s;
        iss >> s >> s;
        for (int i = 0; !iss.eof(); ++i) {
            char c = 0;
            iss >> c;
            gen[i] = c == '#' ? 1 : 0;
        }

        std::getline(std::cin, line);
    }

    struct note {
        int minus2 = 0, minus1 = 0, nexus = 0, plus1 = 0, plus2 = 0;
        bool operator<(const note& right) const {
            int cmp = minus2 - right.minus2;
            if (cmp == 0) {
                cmp = minus1 - right.minus1;
                if (cmp == 0) {
                    cmp = nexus - right.nexus;
                    if (cmp == 0) {
                        cmp = plus1 - right.plus1;
                        if (cmp == 0) {
                            cmp = plus2 - right.plus2;
                        }
                    }
                }
            }
            return cmp < 0;
        }
    };
    std::set<note> notes;
    for (;;) {
        std::string line;
        std::getline(std::cin, line);
        if (line == "out") {
            break;
        }
        std::istringstream iss(line);
        note n;
        char c = 0;
        std::string s;
        int* pval[5] = { &n.minus2, &n.minus1, &n.nexus, &n.plus1, &n.plus2 };
        for (int i = 0; i < 5; ++i) {
            iss >> c;
            *pval[i] = c == '#' ? 1 : 0;
        }
        iss >> s >> c;
        if (c == '#') {
            notes.emplace(n);
        }
    }

    for (int64_t g = 0; g < 100; ++g) {
        auto nextgen = gen;
        for (int64_t i = -1000; i <= 1000; ++i) {
            note n;
            n.minus2 = gen[i - 2];
            n.minus1 = gen[i - 1];
            n.nexus = gen[i];
            n.plus1 = gen[i + 1];
            n.plus2 = gen[i + 2];
            nextgen[i] = (notes.find(n) != notes.end()) ? 1 : 0;
        }
        gen = nextgen;
        //int64_t sum_pots = from(gen)
        //                 | where([](auto&& p) { return p.second == 1; })
        //                 | select([](auto&& p) { return p.first; })
        //                 | sum([](int64_t i) { return i; });
        //for (int64_t i = -200; i <= 200; ++i) {
        //    std::cout << (gen[i] == 1 ? '#' : '.');
        //}
        //std::cout << " -> " << g << " (" << sum_pots << ")" << std::endl;
    }

    int64_t sum_pots = from(gen)
                     | where([](auto&& p) { return p.second == 1; })
                     | select([](auto&& p) { return p.first; })
                     | sum([](int64_t i) { return i; });
    sum_pots += (50000000000 - 100) * 38;
    std::cout << sum_pots << std::endl;
}

void day13_1()
{
    enum class nextturn { left, straight, right, none };
    struct point {
        char track = ' ';
        char cart = 0;
        nextturn next = nextturn::none;
        bool moved = false;
    };
    std::vector<std::vector<point>> grid;
    grid.resize(150);
    for (auto&& g : grid) {
        g.resize(150);
    }
    for (int y = 0; y < 150; ++y) {
        std::string line;
        std::getline(std::cin, line);
        for (int x = 0; x < 150; ++x) {
            point p;
            char c = line[x];
            switch (c) {
                case ' ':
                case '-':
                case '|':
                case '/':
                case '\\':
                case '+': {
                    p.track = c;
                    break;
                }
                case 'v':
                case '^': {
                    p.track = '|';
                    p.cart = c;
                    p.next = nextturn::left;
                    break;
                }
                case '<':
                case '>': {
                    p.track = '-';
                    p.cart = c;
                    p.next = nextturn::left;
                    break;
                }
            }
            grid[x][y] = p;
        }
    }

    bool crashed = false;
    int crashx = 0, crashy = 0;
    for (int t = 0; !crashed; ++t) {
        for (auto&& g : grid) {
            for (auto&& p : g) {
                p.moved = false;
            }
        }
        for (int y = 0; !crashed && y < 150; ++y) {
            for (int x = 0; !crashed && x < 150; ++x) {
                point& rp = grid[x][y];
                if (rp.cart != 0 && !rp.moved) {
                    int destx = 0, desty = 0;
                    switch (rp.cart) {
                        case 'v': {
                            destx = x;
                            desty = y + 1;
                            break;
                        }
                        case '^': {
                            destx = x;
                            desty = y - 1;
                            break;
                        }
                        case '<': {
                            destx = x - 1;
                            desty = y;
                            break;
                        }
                        case '>': {
                            destx = x + 1;
                            desty = y;
                            break;
                        }
                    }
                    point* pdest = &grid[destx][desty];
                    if (pdest->cart != 0) {
                        crashed = true;
                        crashx = destx;
                        crashy = desty;
                        rp.cart = 0;
                        rp.next = nextturn::none;
                        pdest->track = 'X';
                    } else {
                        pdest->cart = rp.cart;
                        pdest->next = rp.next;
                        pdest->moved = true;
                        rp.cart = 0;
                        rp.next = nextturn::none;
                        switch (pdest->track) {
                            case '/': {
                                switch (pdest->cart) {
                                    case '^': {
                                        pdest->cart = '>';
                                        break;
                                    }
                                    case '>': {
                                        pdest->cart = '^';
                                        break;
                                    }
                                    case 'v': {
                                        pdest->cart = '<';
                                        break;
                                    }
                                    case '<': {
                                        pdest->cart = 'v';
                                        break;
                                    }
                                }
                                break;
                            }
                            case '\\': {
                                switch (pdest->cart) {
                                    case '^': {
                                        pdest->cart = '<';
                                        break;
                                    }
                                    case '<': {
                                        pdest->cart = '^';
                                        break;
                                    }
                                    case 'v': {
                                        pdest->cart = '>';
                                        break;
                                    }
                                    case '>': {
                                        pdest->cart = 'v';
                                        break;
                                    }
                                }
                                break;
                            }
                            case '+': {
                                switch (pdest->next) {
                                    case nextturn::left: {
                                        switch (pdest->cart) {
                                            case '<': {
                                                pdest->cart = 'v';
                                                break;
                                            }
                                            case 'v': {
                                                pdest->cart = '>';
                                                break;
                                            }
                                            case '>': {
                                                pdest->cart = '^';
                                                break;
                                            }
                                            case '^': {
                                                pdest->cart = '<';
                                                break;
                                            }
                                        }
                                        pdest->next = nextturn::straight;
                                        break;
                                    }
                                    case nextturn::straight: {
                                        pdest->next = nextturn::right;
                                        break;
                                    }
                                    case nextturn::right: {
                                        switch (pdest->cart) {
                                            case '<': {
                                                pdest->cart = '^';
                                                break;
                                            }
                                            case '^': {
                                                pdest->cart = '>';
                                                break;
                                            }
                                            case '>': {
                                                pdest->cart = 'v';
                                                break;
                                            }
                                            case 'v': {
                                                pdest->cart = '<';
                                                break;
                                            }
                                        }
                                        pdest->next = nextturn::left;
                                        break;
                                    }
                                }
                                break;
                            }
                        }
                    }
                }
            }
        }
    }
    std::cout << crashx << ',' << crashy << std::endl;
}

void day13_2()
{
    enum class nextturn { left, straight, right, none };
    struct point {
        char track = ' ';
        char cart = 0;
        nextturn next = nextturn::none;
        bool moved = false;
    };
    std::vector<std::vector<point>> grid;
    grid.resize(150);
    for (auto&& g : grid) {
        g.resize(150);
    }
    for (int y = 0; y < 150; ++y) {
        std::string line;
        std::getline(std::cin, line);
        for (int x = 0; x < 150; ++x) {
            point p;
            char c = line[x];
            switch (c) {
                case ' ':
                case '-':
                case '|':
                case '/':
                case '\\':
                case '+': {
                    p.track = c;
                    break;
                }
                case 'v':
                case '^': {
                    p.track = '|';
                    p.cart = c;
                    p.next = nextturn::left;
                    break;
                }
                case '<':
                case '>': {
                    p.track = '-';
                    p.cart = c;
                    p.next = nextturn::left;
                    break;
                }
            }
            grid[x][y] = p;
        }
    }

    bool found_last = false;
    int lastx = 0, lasty = 0;
    for (int t = 0; !found_last; ++t) {
        int carts_left = 0;
        int potentiallastx = 0, potentiallasty = 0;
        for (auto&& g : grid) {
            for (auto&& p : g) {
                p.moved = false;
            }
        }
        for (int y = 0; !found_last && y < 150; ++y) {
            for (int x = 0; !found_last && x < 150; ++x) {
                point& rp = grid[x][y];
                if (rp.cart != 0 && !rp.moved) {
                    int destx = 0, desty = 0;
                    switch (rp.cart) {
                        case 'v': {
                            destx = x;
                            desty = y + 1;
                            break;
                        }
                        case '^': {
                            destx = x;
                            desty = y - 1;
                            break;
                        }
                        case '<': {
                            destx = x - 1;
                            desty = y;
                            break;
                        }
                        case '>': {
                            destx = x + 1;
                            desty = y;
                            break;
                        }
                    }
                    point* pdest = &grid[destx][desty];
                    if (pdest->cart != 0) {
                        rp.cart = 0;
                        rp.next = nextturn::none;
                        rp.moved = false;
                        pdest->cart = 0;
                        pdest->next = nextturn::none;
                        pdest->moved = false;
                    } else {
                        pdest->cart = rp.cart;
                        pdest->next = rp.next;
                        pdest->moved = true;
                        rp.cart = 0;
                        rp.next = nextturn::none;
                        ++carts_left;
                        potentiallastx = destx;
                        potentiallasty = desty;
                        switch (pdest->track) {
                            case '/': {
                                switch (pdest->cart) {
                                    case '^': {
                                        pdest->cart = '>';
                                        break;
                                    }
                                    case '>': {
                                        pdest->cart = '^';
                                        break;
                                    }
                                    case 'v': {
                                        pdest->cart = '<';
                                        break;
                                    }
                                    case '<': {
                                        pdest->cart = 'v';
                                        break;
                                    }
                                }
                                break;
                            }
                            case '\\': {
                                switch (pdest->cart) {
                                    case '^': {
                                        pdest->cart = '<';
                                        break;
                                    }
                                    case '<': {
                                        pdest->cart = '^';
                                        break;
                                    }
                                    case 'v': {
                                        pdest->cart = '>';
                                        break;
                                    }
                                    case '>': {
                                        pdest->cart = 'v';
                                        break;
                                    }
                                }
                                break;
                            }
                            case '+': {
                                switch (pdest->next) {
                                    case nextturn::left: {
                                        switch (pdest->cart) {
                                            case '<': {
                                                pdest->cart = 'v';
                                                break;
                                            }
                                            case 'v': {
                                                pdest->cart = '>';
                                                break;
                                            }
                                            case '>': {
                                                pdest->cart = '^';
                                                break;
                                            }
                                            case '^': {
                                                pdest->cart = '<';
                                                break;
                                            }
                                        }
                                        pdest->next = nextturn::straight;
                                        break;
                                    }
                                    case nextturn::straight: {
                                        pdest->next = nextturn::right;
                                        break;
                                    }
                                    case nextturn::right: {
                                        switch (pdest->cart) {
                                            case '<': {
                                                pdest->cart = '^';
                                                break;
                                            }
                                            case '^': {
                                                pdest->cart = '>';
                                                break;
                                            }
                                            case '>': {
                                                pdest->cart = 'v';
                                                break;
                                            }
                                            case 'v': {
                                                pdest->cart = '<';
                                                break;
                                            }
                                        }
                                        pdest->next = nextturn::left;
                                        break;
                                    }
                                }
                                break;
                            }
                        }
                    }
                }
            }
        }
        if (carts_left == 1) {
            found_last = true;
            lastx = potentiallastx;
            lasty = potentiallasty;
        }
    }
    std::cout << lastx << ',' << lasty << std::endl;
}

void day14_1()
{
    const int NUM_RECIPES = 327901;

    std::list<int> board;
    board.push_back(3);
    board.push_back(7);
    auto cur1 = board.begin();
    auto cur2 = std::next(cur1);
    auto move = [&](std::list<int>::iterator& it, int move) {
        while (move-- > 0) {
            ++it;
            if (it == board.end()) {
                it = board.begin();
            }
        }
    };
    auto split = [](int i) {
        std::vector<int> digits;
        for (;;) {
            digits.push_back(i % 10);
            if (i == (i % 10)) {
                break;
            }
            i /= 10;
        }
        return from(std::move(digits))
             | reverse();
    };

    while (board.size() < NUM_RECIPES + 10) {
        int combined = *cur1 + *cur2;
        for (int i : split(combined)) {
            board.push_back(i);
        }
        move(cur1, 1 + *cur1);
        move(cur2, 1 + *cur2);
    }
    auto next_10 = from(board)
                 | skip(NUM_RECIPES)
                 | take(10);
    for (int i : next_10) {
        std::cout << i;
    }
    std::cout << std::endl;
}

void day14_2()
{
    const int NUM_RECIPES = 327901;

    std::list<int> board;
    board.push_back(3);
    board.push_back(7);
    auto cur1 = board.begin();
    auto cur2 = std::next(cur1);
    auto move = [&](std::list<int>::iterator& it, int move) {
        while (move-- > 0) {
            ++it;
            if (it == board.end()) {
                it = board.begin();
            }
        }
    };
    auto split = [](int i) {
        std::vector<int> digits;
        for (;;) {
            digits.push_back(i % 10);
            if (i == (i % 10)) {
                break;
            }
            i /= 10;
        }
        return from(std::move(digits))
             | reverse()
             | to_vector();
    };

    auto target = split(NUM_RECIPES);
    bool found = false;
    bool one_too_many = false;
    while (!found) {
        int combined = *cur1 + *cur2;
        for (int i : split(combined)) {
            board.push_back(i);
        }
        move(cur1, 1 + *cur1);
        move(cur2, 1 + *cur2);
        if (board.size() >= (target.size() + 1)) {
            found = std::equal(std::prev(board.end(), static_cast<int>(target.size() + 1)), std::prev(board.end()),
                               target.begin(), target.end());
            if (found) {
                one_too_many = true;
            }
        }
        if (!found && board.size() >= target.size()) {
            found = std::equal(std::prev(board.end(), static_cast<int>(target.size())), board.end(),
                               target.begin(), target.end());
        }
    }
    std::cout << (board.size() - target.size() - (one_too_many ? 1 : 0)) << std::endl;
}

void day15_1and2()
{
    struct tile : dij::node {
        int x = 0, y = 0;
        char ground = 0;
        char mob = 0;
        int hp = 0, atk = 0;
        bool moved = false;
    };
    struct graph : dij::graph {
        std::vector<std::vector<std::shared_ptr<tile>>> stor;
        graph() : stor() {
            stor.resize(32);
            for (auto&& s : stor) {
                s.resize(32);
            }
        }
        graph(const graph& g) : stor() {
            stor.resize(32);
            for (auto&& s : stor) {
                s.resize(32);
            }
            for (int x = 0; x < 32; ++x) {
                for (int y = 0; y < 32; ++y) {
                    add(*g.get(x, y));
                }
            }
        }
        graph(graph&&) = default;
        graph& operator=(const graph&) = delete;
        void add(tile t) {
            stor[t.x][t.y] = std::make_shared<tile>(t);
        }
        tile* get(int x, int y) const {
            return stor[x][y].get();
        }
        std::vector<tile*> all_tiles() const {
            return from(stor)
                 | select_many([](auto&& s) { return s; })
                 | select([](auto&& spt) -> tile* { return spt.get(); })
                 | to_vector();
        }
        std::vector<tile*> all_neighbours(tile* pt) const {
            std::vector<tile*> neighbourhood;
            for (int ymod : { -1, 0, 1 }) {
                for (int xmod : { -1, 0, 1 }) {
                    if (xmod == 0 || ymod == 0) {
                        int x = pt->x + xmod;
                        int y = pt->y + ymod;
                        if (x >= 0 && x < 32 && y >= 0 && y < 32) {
                            neighbourhood.push_back(stor[x][y].get());
                        }
                    }
                }
            }
            return neighbourhood;
        }
        virtual std::vector<dij::node*> all_passable() const override {
            return from(stor)
                 | select_many([](auto&& s) { return s; })
                 | where([](auto&& spt) { return spt->ground == '.' && spt->mob == 0; })
                 | select([](auto&& spt) -> dij::node* { return spt.get(); })
                 | to_vector();
        }
        virtual std::vector<dij::node*> neighbours(dij::node* pn, dij::node* pinclude) const override {
            tile* pt = dynamic_cast<tile*>(pn);
            tile* ptinclude = dynamic_cast<tile*>(pinclude);
            auto tile_valid = [&](tile* pv) {
                return (pv->ground == '.' && pv->mob == 0) || pv == ptinclude;
            };
            return from(all_neighbours(pt))
                 | where([&](tile* ptt) { return tile_valid(ptt); })
                 | select([](tile* ptt) -> dij::node* { return ptt; })
                 | to_vector();
        }
        virtual int64_t dist(dij::node*, dij::node*) const override {
            return 1;
        }
        virtual bool is_a_better(dij::node* pa, dij::node* pb) const override {
            tile* pta = dynamic_cast<tile*>(pa);
            tile* ptb = dynamic_cast<tile*>(pb);
            return pta->y < ptb->y || (pta->y == ptb->y && pta->x < ptb->x);
        }
    } orig_grid;
    for (int y = 0; y < 32; ++y) {
        std::string line;
        std::getline(std::cin, line);
        for (int x = 0; x < 32; ++x) {
            tile t;
            t.x = x;
            t.y = y;
            switch (line[x]) {
                case '#':
                case '.': {
                    t.ground = line[x];
                    break;
                }
                case 'G':
                case 'E': {
                    t.ground = '.';
                    t.mob = line[x];
                    t.hp = 200;
                    t.atk = 3;
                    break;
                }
            }
            orig_grid.add(t);
        }
    }

    auto dump_grid = [](const graph& g) {
        for (int y = 0; y < 32; ++y) {
            std::vector<tile*> mobs;
            for (int x = 0; x < 32; ++x) {
                tile* pt = g.get(x, y);
                if (pt->mob != 0) {
                    std::cout << pt->mob;
                    mobs.push_back(pt);
                } else {
                    std::cout << pt->ground;
                }
            }
            for (tile* pm : mobs) {
                std::cout << " (" << pm->x << "," << pm->y << ")_" << pm->hp;
            }
            std::cout << std::endl;
        }
    };
    auto has_enemies = [](const graph& g, tile* pt) {
        const char tolookfor = pt->mob == 'G' ? 'E' : 'G';
        return from(g.all_tiles())
             | where([=](tile* ptt) { return ptt->mob == tolookfor; })
             | any();
    };
    auto get_enemies_neighbours = [](const graph& g, tile* pt) {
        const char tolookfor = pt->mob == 'G' ? 'E' : 'G';
        return from(g.all_tiles())
             | where([=](tile* ptt) { return ptt->mob == tolookfor; })
             | select_many([&](tile* ptt) { return g.neighbours(ptt, pt); })
             | select([](dij::node* pn) { return dynamic_cast<tile*>(pn); })
             | order_by([](tile* ptt) { return ptt->y; })
             | then_by([](tile* ptt) { return ptt->x; })
             | to_vector();
    };
    auto get_attack_target = [](const graph& g, tile* pt) {
        char tolookfor = pt->mob == 'G' ? 'E' : 'G';
        return from(g.all_neighbours(pt))
             | where([=](tile* ptt) { return ptt->mob == tolookfor; })
             | order_by([](tile* ptt) { return ptt->hp; })
             | then_by([](tile* ptt) { return ptt->y; })
             | then_by([](tile* ptt) { return ptt->x; })
             | first_or_default();
    };
    
    auto run_combat = [&](int elf_atk) -> std::tuple<graph, int, int, std::map<char, int>> {
        graph grid(orig_grid);
        for (tile* pt : grid.all_tiles()) {
            if (pt->mob == 'E') {
                pt->atk = elf_atk;
            }
        }

        int turn = 0;
        bool done = false;
        std::map<char, int> casualties;
        while (!done) {
            for (tile* pt : grid.all_tiles()) {
                pt->moved = false;
            }
            for (int y = 0; !done && y < 32; ++y) {
                for (int x = 0; !done && x < 32; ++x) {
                    tile* pt = grid.get(x, y);
                    if (pt->mob != 0 && !pt->moved) {
                        // move
                        if (!has_enemies(grid, pt)) {
                            done = true;
                            break;
                        }
                        auto target_tiles = get_enemies_neighbours(grid, pt);
                        std::unordered_map<tile*, std::tuple<tile*, int64_t>> moves;
                        if (!target_tiles.empty()) {
                            std::unordered_map<dij::node*, int64_t> dij_dist;
                            std::unordered_map<dij::node*, dij::node*> dij_prev;
                            std::tie(dij_dist, dij_prev) = dij::get_dijkstra(&grid, pt);
                            for (tile* pe : target_tiles) {
                                auto distit = dij_dist.find(pe);
                                if (distit != dij_dist.end() && distit->second != std::numeric_limits<int64_t>::max()) {
                                    auto path = dij::assemble_path(dij_prev, pt, pe);
                                    tile* pnext = !path.empty() ? dynamic_cast<tile*>(path.front()) : nullptr;
                                    moves[pe] = std::make_tuple(pnext, distit->second);
                                }
                            }
                        }
                        auto closest = from(moves)
                                     | order_by([](auto&& r) { return std::get<1>(r.second); })
                                     | then_by([](auto&& r) { return r.first->y; })
                                     | then_by([](auto&& r) { return r.first->x; })
                                     | then_by([](auto&& r) { return std::get<0>(r.second)->y; })
                                     | then_by([](auto&& r) { return std::get<0>(r.second)->x; })
                                     | first_or_default();
                        int64_t closest_dist = std::get<1>(closest.second);
                        if (closest.first != nullptr && closest_dist > 0) {
                            tile* pnext = std::get<0>(closest.second);
                            pnext->mob = pt->mob;
                            pnext->hp = pt->hp;
                            pnext->atk = pt->atk;
                            pnext->moved = true;
                            pt->mob = 0;
                            pt->hp = 0;
                            pt->atk = 0;
                            pt->moved = false;
                            pt = pnext;
                        } else {
                            pt->moved = true;
                        }

                        // attack
                        tile* ptarget = get_attack_target(grid, pt);
                        if (ptarget != nullptr) {
                            ptarget->hp -= pt->atk;
                            if (ptarget->hp <= 0) {
                                ++casualties[ptarget->mob];
                                ptarget->mob = 0;
                                ptarget->hp = 0;
                                ptarget->atk = 0;
                                ptarget->moved = false;
                            }
                        }
                    }
                }
            }
            if (!done) {
                ++turn;
                //if (turn >= 18) {
                //    std::cout << "After turn " << turn << ":" << std::endl;
                //    dump_grid();
                //    std::string line;
                //    std::getline(std::cin, line);
                //}
            }
        }

        int remain_hp = from(grid.all_tiles())
                      | where([](tile* pt) { return pt->mob != 0; })
                      | default_if_empty()
                      | sum([](tile* pt) { return pt != nullptr ? pt->hp : 0; });
        return std::make_tuple(std::move(grid), turn, remain_hp, std::move(casualties));
    };

    std::cout << "First puzzle" << std::endl;
    auto first_outcome = run_combat(3);
    std::cout << "End of combat - " << std::get<1>(first_outcome) << " full rounds." << std::endl;
    dump_grid(std::get<0>(first_outcome));
    std::cout << "Combat outcome: " << std::get<1>(first_outcome) * std::get<2>(first_outcome) << std::endl << std::endl;

    std::cout << "Second puzzle" << std::endl;
    for (int elf_atk = 4; ; ++elf_atk) {
        auto outcome = run_combat(elf_atk);
        std::cout << "End of combat with elf attack power " << elf_atk << " - " << std::get<1>(outcome) << " full rounds." << std::endl;
        if (std::get<3>(outcome)['E'] == 0) {
            std::cout << "No elf casualties!" << std::endl;
            dump_grid(std::get<0>(outcome));
            std::cout << "Combat outcome: " << std::get<1>(outcome) * std::get<2>(outcome) << std::endl << std::endl;
            break;
        } else {
            std::cout << "Elf casualties: " << std::get<3>(outcome)['E'] << " - not good." << std::endl;
        }
    }
}

void day16_1()
{
    struct registers {
        int r[4] = { 0 };
        bool operator==(const registers& right) const {
            return std::equal(std::begin(r), std::end(r), std::begin(right.r), std::end(right.r));
        }
    };
    struct opcode {
        std::string name;
        std::function<void(registers&, int, int, int)> impl;
    };
    std::vector<opcode> opcodes = {
        {
            "addr",
            [](registers& regs, int a, int b, int c) {
                regs.r[c] = regs.r[a] + regs.r[b];
            }
        },
        {
            "addi",
            [](registers& regs, int a, int b, int c) {
                regs.r[c] = regs.r[a] + b;
            }
        },
        {
            "mulr",
            [](registers& regs, int a, int b, int c) {
                regs.r[c] = regs.r[a] * regs.r[b];
            }
        },
        {
            "muli",
            [](registers& regs, int a, int b, int c) {
                regs.r[c] = regs.r[a] * b;
            }
        },
        {
            "banr",
            [](registers& regs, int a, int b, int c) {
                regs.r[c] = regs.r[a] & regs.r[b];
            }
        },
        {
            "bani",
            [](registers& regs, int a, int b, int c) {
                regs.r[c] = regs.r[a] & b;
            }
        },
        {
            "borr",
            [](registers& regs, int a, int b, int c) {
                regs.r[c] = regs.r[a] | regs.r[b];
            }
        },
        {
            "bori",
            [](registers& regs, int a, int b, int c) {
                regs.r[c] = regs.r[a] | b;
            }
        },
        {
            "setr",
            [](registers& regs, int a, int b, int c) {
                regs.r[c] = regs.r[a];
            }
        },
        {
            "seti",
            [](registers& regs, int a, int b, int c) {
                regs.r[c] = a;
            }
        },
        {
            "gtir",
            [](registers& regs, int a, int b, int c) {
                regs.r[c] = (a > regs.r[b] ? 1 : 0);
            }
        },
        {
            "gtri",
            [](registers& regs, int a, int b, int c) {
                regs.r[c] = (regs.r[a] > b ? 1 : 0);
            }
        },
        {
            "gtrr",
            [](registers& regs, int a, int b, int c) {
                regs.r[c] = (regs.r[a] > regs.r[b] ? 1 : 0);
            }
        },
        {
            "eqir",
            [](registers& regs, int a, int b, int c) {
                regs.r[c] = (a == regs.r[b] ? 1 : 0);
            }
        },
        {
            "eqri",
            [](registers& regs, int a, int b, int c) {
                regs.r[c] = (regs.r[a] == b ? 1 : 0);
            }
        },
        {
            "eqrr",
            [](registers& regs, int a, int b, int c) {
                regs.r[c] = (regs.r[a] == regs.r[b] ? 1 : 0);
            }
        },
    };

    int morethan3 = 0;
    for (;;) {
        std::string line;
        std::getline(std::cin, line);
        if (line == "out") {
            break;
        }
        std::istringstream issb(line);
        registers before;
        std::string word;
        char ch = 0;
        issb >> word >> ch
             >> before.r[0] >> ch
             >> before.r[1] >> ch
             >> before.r[2] >> ch
             >> before.r[3];

        std::getline(std::cin, line);
        std::istringstream isso(line);
        int op = 0, a = 0, b = 0, c = 0;
        isso >> op >> a >> b >> c;

        std::getline(std::cin, line);
        std::istringstream issa(line);
        registers after;
        issa >> word >> ch
             >> after.r[0] >> ch
             >> after.r[1] >> ch
             >> after.r[2] >> ch
             >> after.r[3];

        std::getline(std::cin, line);

        std::set<std::string> newguesses;
        for (auto&& guess : opcodes) {
            registers during(before);
            guess.impl(during, a, b, c);
            if (during == after) {
                newguesses.insert(guess.name);
            }
        }
        if (newguesses.size() >= 3) {
            ++morethan3;
        }
    }
    std::cout << morethan3 << std::endl;
}

void day16_2()
{
    struct registers {
        int r[4] = { 0 };
        bool operator==(const registers& right) const {
            return std::equal(std::begin(r), std::end(r), std::begin(right.r), std::end(right.r));
        }
    };
    struct opcode {
        std::string name;
        std::function<void(registers&, int, int, int)> impl;
    };
    std::vector<opcode> opcodes = {
        {
            "addr",
            [](registers& regs, int a, int b, int c) {
                regs.r[c] = regs.r[a] + regs.r[b];
            }
        },
        {
            "addi",
            [](registers& regs, int a, int b, int c) {
                regs.r[c] = regs.r[a] + b;
            }
        },
        {
            "mulr",
            [](registers& regs, int a, int b, int c) {
                regs.r[c] = regs.r[a] * regs.r[b];
            }
        },
        {
            "muli",
            [](registers& regs, int a, int b, int c) {
                regs.r[c] = regs.r[a] * b;
            }
        },
        {
            "banr",
            [](registers& regs, int a, int b, int c) {
                regs.r[c] = regs.r[a] & regs.r[b];
            }
        },
        {
            "bani",
            [](registers& regs, int a, int b, int c) {
                regs.r[c] = regs.r[a] & b;
            }
        },
        {
            "borr",
            [](registers& regs, int a, int b, int c) {
                regs.r[c] = regs.r[a] | regs.r[b];
            }
        },
        {
            "bori",
            [](registers& regs, int a, int b, int c) {
                regs.r[c] = regs.r[a] | b;
            }
        },
        {
            "setr",
            [](registers& regs, int a, int b, int c) {
                regs.r[c] = regs.r[a];
            }
        },
        {
            "seti",
            [](registers& regs, int a, int b, int c) {
                regs.r[c] = a;
            }
        },
        {
            "gtir",
            [](registers& regs, int a, int b, int c) {
                regs.r[c] = (a > regs.r[b] ? 1 : 0);
            }
        },
        {
            "gtri",
            [](registers& regs, int a, int b, int c) {
                regs.r[c] = (regs.r[a] > b ? 1 : 0);
            }
        },
        {
            "gtrr",
            [](registers& regs, int a, int b, int c) {
                regs.r[c] = (regs.r[a] > regs.r[b] ? 1 : 0);
            }
        },
        {
            "eqir",
            [](registers& regs, int a, int b, int c) {
                regs.r[c] = (a == regs.r[b] ? 1 : 0);
            }
        },
        {
            "eqri",
            [](registers& regs, int a, int b, int c) {
                regs.r[c] = (regs.r[a] == b ? 1 : 0);
            }
        },
        {
            "eqrr",
            [](registers& regs, int a, int b, int c) {
                regs.r[c] = (regs.r[a] == regs.r[b] ? 1 : 0);
            }
        },
    };

    std::map<int, std::set<std::string>> guesses;
    for (;;) {
        std::string line;
        std::getline(std::cin, line);
        if (line.empty()) {
            break;
        }
        std::istringstream issb(line);
        registers before;
        std::string word;
        char ch = 0;
        issb >> word >> ch
             >> before.r[0] >> ch
             >> before.r[1] >> ch
             >> before.r[2] >> ch
             >> before.r[3];

        std::getline(std::cin, line);
        std::istringstream isso(line);
        int op = 0, a = 0, b = 0, c = 0;
        isso >> op >> a >> b >> c;

        std::getline(std::cin, line);
        std::istringstream issa(line);
        registers after;
        issa >> word >> ch
             >> after.r[0] >> ch
             >> after.r[1] >> ch
             >> after.r[2] >> ch
             >> after.r[3];

        std::getline(std::cin, line);

        std::set<std::string> newguesses;
        for (auto&& guess : opcodes) {
            registers during(before);
            guess.impl(during, a, b, c);
            if (during == after) {
                newguesses.insert(guess.name);
            }
        }
        auto it = guesses.find(op);
        if (it == guesses.end()) {
            guesses[op] = newguesses;
        } else {
            it->second = from(it->second)
                       | intersect(newguesses)
                       | to<std::set<std::string>>();
        }
    }

    std::map<int, opcode*> instructions_map;
    while (!guesses.empty()) {
        std::set<std::string> toremove;
        for (auto it = guesses.begin(); it != guesses.end(); ) {
            if (it->second.size() == 1) {
                opcode& rop = from(opcodes)
                            | single([&](auto&& o) { return o.name == *it->second.begin(); });
                instructions_map[it->first] = &rop;
                toremove.insert(*it->second.begin());
                it = guesses.erase(it);
            } else {
                ++it;
            }
        }
        for (auto&& g : guesses) {
            g.second = from(g.second)
                     | except(toremove)
                     | to<std::set<std::string>>();
        }
    }

    std::string emptyline;
    std::getline(std::cin, emptyline);
    registers cpu;
    for (;;) {
        std::string line;
        std::getline(std::cin, line);
        if (line.empty()) {
            break;
        }
        std::istringstream iss(line);
        int op = 0, a = 0, b = 0, c = 0;
        iss >> op >> a >> b >> c;
        instructions_map[op]->impl(cpu, a, b, c);
    }
    for (int i = 0; i < 4; ++i) {
        if (i != 0) {
            std::cout << ", ";
        }
        std::cout << "R" << i << " = " << cpu.r[i];
    }
    std::cout << std::endl;
}

void day17_1and2()
{
    struct spot {
        int x = 0, y = 0;
        bool operator<(const spot& right) const {
            int cmp = x - right.x;
            if (cmp == 0) {
                cmp = y - right.y;
            }
            return cmp < 0;
        }
    };
    std::vector<spot> spots;
    for (;;) {
        std::string line;
        std::getline(std::cin, line);
        if (line == "out") {
            break;
        }
        std::istringstream iss(line);
        char coord = 0, c = 0;
        int singleval = 0, rbeg = 0, rend = 0;
        iss >> coord >> c >> singleval >> c
            >> c >> c >> rbeg >> c >> c >> rend;
        if (coord == 'x') {
            for (int i = rbeg; i <= rend; ++i) {
                spots.push_back({ singleval, i });
            }
        } else {
            for (int i = rbeg; i <= rend; ++i) {
                spots.push_back({ i, singleval });
            }
        }
    }
    auto xs = from(spots)
            | select([](auto&& s) { return s.x; })
            | order_by([](int i) { return i; });
    int maxx = from(xs)
             | last();
    auto ys = from(spots)
            | select([](auto&& s) { return s.y; })
            | order_by([](int i) { return i; });
    int miny = from(ys)
             | first();
    int maxy = from(ys)
             | last();

    std::vector<std::vector<char>> terrain;
    terrain.resize(maxx + 2);
    for (auto&& ty : terrain) {
        ty.resize(maxy + 2);
        for (char& c : ty) {
            c = '.';
        }
    }
    for (auto&& s : spots) {
        terrain[s.x][s.y] = '#';
    }
    terrain[500][0] = '+';
    auto dump_terrain = [&]() {
        std::cout << "maxx = " << maxx << ", miny = " << miny << ", maxy = " << maxy << std::endl
                  << std::endl;
        for (int y = 0; y <= maxy; ++y) {
            for (int x = 0; x <= maxx; ++x) {
                std::cout << terrain[x][y];
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    };

    //dump_terrain();

    std::queue<spot> startingpoints;
    startingpoints.push({ 500, 0 });
    std::set<spot> seenpoints;
    auto passable = [&](int x, int y) {
        return terrain[x][y] == '.' || terrain[x][y] == '|';
    };
    auto blocked = [&](int x, int y) {
        return terrain[x][y] != '.' && terrain[x][y] != '|';
    };
    while (!startingpoints.empty()) {
        spot curstart = startingpoints.front();
        int x = curstart.x, y = curstart.y;
        if (terrain[x][y] == '~') {
            startingpoints.push({ x, y - 1 });
            startingpoints.pop();
            continue;
        }
        while (y <= maxy && passable(x, y + 1)) {
            if (terrain[x][y] == '.') {
                terrain[x][y] = '|';
            }
            ++y;
        }
        if (y > maxy) {
            startingpoints.pop();
            continue;
        }
        int leftx = x, rightx = x;
        while (blocked(leftx, y + 1) && passable(leftx - 1, y)) {
            if (terrain[leftx][y] == '.') {
                terrain[leftx][y] = '|';
            }
            --leftx;
            if (terrain[leftx][y] == '.') {
                terrain[leftx][y] = '|';
            }
        }
        while (blocked(rightx, y + 1) && passable(rightx + 1, y)) {
            if (terrain[rightx][y] == '.') {
                terrain[rightx][y] = '|';
            }
            ++rightx;
            if (terrain[rightx][y] == '.') {
                terrain[rightx][y] = '|';
            }
        }
        if (passable(leftx, y + 1)) {
            spot toadd{ leftx, y };
            if (seenpoints.insert(toadd).second) {
                startingpoints.push(toadd);
            }
        }
        if (passable(rightx, y + 1)) {
            spot toadd{ rightx, y };
            if (seenpoints.insert(toadd).second) {
                startingpoints.push(toadd);
            }
        }
        if (blocked(leftx, y + 1) && blocked(rightx, y + 1)) {
            if ((x - leftx) < (rightx - x)) {
                x = rightx;
            } else {
                x = leftx;
            }
            terrain[x][y] = '~';
        } else {
            startingpoints.pop();
        }
    }
    int reachable = 0, water = 0;
    for (int x = 0; x <= maxx; ++x) {
        for (int y = miny; y <= maxy; ++y) {
            if (terrain[x][y] == '~' || terrain[x][y] == '|') {
                ++reachable;
            }
            if (terrain[x][y] == '~') {
                ++water;
            }
        }
    }
    std::cout << "Reachable: " << reachable << std::endl
              << "Water: " << water << std::endl
              << std::endl;

    //dump_terrain();
}

void day18_1()
{
    std::vector<std::vector<char>> terrain;
    terrain.resize(50);
    for (auto&& t : terrain) {
        t.resize(50);
    }
    for (int y = 0; y < 50; ++y) {
        std::string line;
        std::getline(std::cin, line);
        for (int x = 0; x < 50; ++x) {
            terrain[x][y] = line[x];
        }
    }

    auto dump_terrain = [&]() {
        for (int y = 0; y < 50; ++y) {
            for (int x = 0; x < 50; ++x) {
                std::cout << terrain[x][y];
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    };

    auto adjescent = [&](int x, int y) -> coveo::enumerable<const char> {
        std::vector<char> v;
        if (y > 0) {
            if (x > 0) {
                v.push_back(terrain[x - 1][y - 1]);
            }
            v.push_back(terrain[x][y - 1]);
            if (x < 49) {
                v.push_back(terrain[x + 1][y - 1]);
            }
        }
        if (x > 0) {
            v.push_back(terrain[x - 1][y]);
        }
        if (x < 49) {
            v.push_back(terrain[x + 1][y]);
        }
        if (y < 49) {
            if (x > 0) {
                v.push_back(terrain[x - 1][y + 1]);
            }
            v.push_back(terrain[x][y + 1]);
            if (x < 49) {
                v.push_back(terrain[x + 1][y + 1]);
            }
        }
        return coveo::enumerate_container(std::move(v));
    };
    std::map<char, std::function<char(int, int)>> next_turn = {
        {
            '.',
            [&](int x, int y) {
                auto num_trees = from(adjescent(x, y))
                               | count([](char c) { return c == '|'; });
                return num_trees >= 3 ? '|' : '.';
            }
        },
        {
            '|',
            [&](int x, int y) {
                auto num_ly = from(adjescent(x, y))
                            | count([](char c) { return c == '#'; });
                return num_ly >= 3 ? '#' : '|';
            }
        },
        {
            '#',
            [&](int x, int y) {
                auto adj = adjescent(x, y);
                auto num_ly = from(adj)
                            | count([](char c) { return c == '#'; });
                auto num_trees = from(adj)
                               | count([](char c) { return c == '|'; });
                return (num_ly >= 1 && num_trees >= 1) ? '#' : '.';
            }
        },
    };

    for (uint64_t minute = 0; minute < 10; ++minute) {
        auto newterrain(terrain);
        for (int y = 0; y < 50; ++y) {
            for (int x = 0; x < 50; ++x) {
                newterrain[x][y] = next_turn[terrain[x][y]](x, y);
            }
        }
        terrain = newterrain;
        //dump_terrain();
    }
    auto acres = from(terrain)
               | select_many([](auto&& t) { return t; });
    auto num_trees = from(acres)
                   | count([](char c) { return c == '|'; });
    auto num_ly = from(acres)
                | count([](char c) { return c == '#'; });
    std::cout << num_trees * num_ly << std::endl;
}

void day18_2()
{
    std::vector<std::vector<char>> terrain;
    terrain.resize(50);
    for (auto&& t : terrain) {
        t.resize(50);
    }
    for (int y = 0; y < 50; ++y) {
        std::string line;
        std::getline(std::cin, line);
        for (int x = 0; x < 50; ++x) {
            terrain[x][y] = line[x];
        }
    }

    auto dump_terrain = [&]() {
        for (int y = 0; y < 50; ++y) {
            for (int x = 0; x < 50; ++x) {
                std::cout << terrain[x][y];
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    };

    auto adjescent = [&](int x, int y) -> coveo::enumerable<const char> {
        std::vector<char> v;
        if (y > 0) {
            if (x > 0) {
                v.push_back(terrain[x - 1][y - 1]);
            }
            v.push_back(terrain[x][y - 1]);
            if (x < 49) {
                v.push_back(terrain[x + 1][y - 1]);
            }
        }
        if (x > 0) {
            v.push_back(terrain[x - 1][y]);
        }
        if (x < 49) {
            v.push_back(terrain[x + 1][y]);
        }
        if (y < 49) {
            if (x > 0) {
                v.push_back(terrain[x - 1][y + 1]);
            }
            v.push_back(terrain[x][y + 1]);
            if (x < 49) {
                v.push_back(terrain[x + 1][y + 1]);
            }
        }
        return coveo::enumerate_container(std::move(v));
    };
    std::map<char, std::function<char(int, int)>> next_turn = {
        {
            '.',
            [&](int x, int y) {
                auto num_trees = from(adjescent(x, y))
                               | count([](char c) { return c == '|'; });
                return num_trees >= 3 ? '|' : '.';
            }
        },
        {
            '|',
            [&](int x, int y) {
                auto num_ly = from(adjescent(x, y))
                            | count([](char c) { return c == '#'; });
                return num_ly >= 3 ? '#' : '|';
            }
        },
        {
            '#',
            [&](int x, int y) {
                auto adj = adjescent(x, y);
                auto num_ly = from(adj)
                            | count([](char c) { return c == '#'; });
                auto num_trees = from(adj)
                               | count([](char c) { return c == '|'; });
                return (num_ly >= 1 && num_trees >= 1) ? '#' : '.';
            }
        },
    };

    std::map<std::vector<std::vector<char>>, uint64_t> seen;
    uint64_t loopbeg = 0, loopdur = 0;
    for (uint64_t minute = 0; minute < 1000000000; ++minute) {
        auto newterrain(terrain);
        for (int y = 0; y < 50; ++y) {
            for (int x = 0; x < 50; ++x) {
                newterrain[x][y] = next_turn[terrain[x][y]](x, y);
            }
        }
        terrain = newterrain;
        auto it = seen.find(terrain);
        if (it == seen.end()) {
            seen[terrain] = minute;
        } else {
            std::cout << "Minute " << minute << " is like minute " << it->second << std::endl;
            loopbeg = it->second;
            loopdur = minute - loopbeg;
            break;
        }
    }
    uint64_t posinloop = ((1000000000 - 1) - loopbeg) % loopdur;
    std::cout << "Position in loop: " << posinloop << std::endl;
    auto finalterrain = from(seen)
                      | where([&](auto&& p) { return p.second == loopbeg + posinloop; })
                      | select([](auto&& p) { return p.first; })
                      | single();
    auto acres = from(finalterrain)
               | select_many([](auto&& t) { return t; });
    auto num_trees = from(acres)
                   | count([](char c) { return c == '|'; });
    auto num_ly = from(acres)
                | count([](char c) { return c == '#'; });
    std::cout << num_trees * num_ly << std::endl;
}

void day19_1and2()
{
    struct registers {
        int r[6] = { 0 };
        std::string dump() const {
            std::ostringstream oss;
            oss << "[";
            for (int i = 0; i < 6; ++i) {
                if (i != 0) {
                    oss << ", ";
                }
                oss << r[i];
            }
            oss << "]";
            return oss.str();
        }
    };
    using opcode_impl = std::function<void(registers&, int, int, int)>;
    std::map<std::string, opcode_impl> opcodes = {
        {
            "addr",
            [](registers& regs, int a, int b, int c) {
                regs.r[c] = regs.r[a] + regs.r[b];
            }
        },
        {
            "addi",
            [](registers& regs, int a, int b, int c) {
                regs.r[c] = regs.r[a] + b;
            }
        },
        {
            "mulr",
            [](registers& regs, int a, int b, int c) {
                regs.r[c] = regs.r[a] * regs.r[b];
            }
        },
        {
            "muli",
            [](registers& regs, int a, int b, int c) {
                regs.r[c] = regs.r[a] * b;
            }
        },
        {
            "banr",
            [](registers& regs, int a, int b, int c) {
                regs.r[c] = regs.r[a] & regs.r[b];
            }
        },
        {
            "bani",
            [](registers& regs, int a, int b, int c) {
                regs.r[c] = regs.r[a] & b;
            }
        },
        {
            "borr",
            [](registers& regs, int a, int b, int c) {
                regs.r[c] = regs.r[a] | regs.r[b];
            }
        },
        {
            "bori",
            [](registers& regs, int a, int b, int c) {
                regs.r[c] = regs.r[a] | b;
            }
        },
        {
            "setr",
            [](registers& regs, int a, int b, int c) {
                regs.r[c] = regs.r[a];
            }
        },
        {
            "seti",
            [](registers& regs, int a, int b, int c) {
                regs.r[c] = a;
            }
        },
        {
            "gtir",
            [](registers& regs, int a, int b, int c) {
                regs.r[c] = (a > regs.r[b] ? 1 : 0);
            }
        },
        {
            "gtri",
            [](registers& regs, int a, int b, int c) {
                regs.r[c] = (regs.r[a] > b ? 1 : 0);
            }
        },
        {
            "gtrr",
            [](registers& regs, int a, int b, int c) {
                regs.r[c] = (regs.r[a] > regs.r[b] ? 1 : 0);
            }
        },
        {
            "eqir",
            [](registers& regs, int a, int b, int c) {
                regs.r[c] = (a == regs.r[b] ? 1 : 0);
            }
        },
        {
            "eqri",
            [](registers& regs, int a, int b, int c) {
                regs.r[c] = (regs.r[a] == b ? 1 : 0);
            }
        },
        {
            "eqrr",
            [](registers& regs, int a, int b, int c) {
                regs.r[c] = (regs.r[a] == regs.r[b] ? 1 : 0);
            }
        },
    };
    struct instruction {
        std::string opname;
        const opcode_impl* op = nullptr;
        int a = 0, b = 0, c = 0;
    };

    registers cpu;
    int* ip = nullptr;
    std::vector<instruction> program;
    {
        std::string line;
        std::getline(std::cin, line);
        std::istringstream iss(line);
        int n = 0;
        char c = 0;
        iss >> c >> c >> c >> n;
        ip = &cpu.r[n];
    }
    for (;;) {
        std::string line;
        std::getline(std::cin, line);
        if (line == "out") {
            break;
        }
        std::istringstream iss(line);
        instruction inst;
        iss >> inst.opname >> inst.a >> inst.b >> inst.c;
        inst.op = &opcodes[inst.opname];
        program.emplace_back(inst);
    }

    while (*ip >= 0 && *ip < program.size()) {
        const instruction& inst = program[*ip];
        (*inst.op)(cpu, inst.a, inst.b, inst.c);
        ++*ip;
    }
    std::cout << "Program #1, R0 = " << cpu.r[0] << std::endl;

    // If we had forever:
    //for (int& r : cpu.r) {
    //    r = 0;
    //}
    //cpu.r[0] = 1;
    //*ip = 0;
    //while (*ip >= 0 && *ip < program.size()) {
    //    const instruction& inst = program[*ip];
    //    std::cout << "(" << *ip << ") " << cpu.dump() << " "
    //                << inst.opname << " " << inst.a << " " << inst.b << " " << inst.c << " ";
    //    (*inst.op)(cpu, inst.a, inst.b, inst.c);
    //    std::cout << cpu.dump() << std::endl;
    //    ++*ip;
    //}
    //std::cout << "Program #2, R0 = " << cpu.r[0] << std::endl;

    // If we cheat:
    const int NUMBER = 10551370;
    int total = 0;
    for (int i = 1; i <= NUMBER; ++i) {
        if (NUMBER % i == 0) {
            total += i;
        }
    }
    std::cout << "Program #2, R0 = " << total << std::endl;
}

void day20_1()
{
    const std::string INPUT = "^ESWSSSSSWSWWNNNENNWWNWWSWNNNESEENEESE(NENWNEENNWNEEESESWSESENEENNNNWWW(NNWSSWNWSWNWWSESSS(E|WWNENWWSWWWNWNWSSESESS(WWN(WN(WSWNWWWWWNNWSSWNNNWSSSWWSESWSSSENNESESWSSSWWNWWSWSEE(SSSSWNWNN(ESNW|)WNNNNNEEE(NNWSWNNEENWNENNWWNWSWWSWNWWWSSSESENN(NWSNES|)EEENEE(E|SWS(WSESWWSWWN(ENENWESWSW|)WSSEEEE(NEWS|)SWWWSEEESSSSESSWSSWSWNWNEENWWNWWSSWNWSSWSEEEE(ESWSWSEENESSESENNWNN(ESEEENENWWW(SEWN|)(NNE(N|SEEN(W|EENEESENNESSSSESSSWSEENNENWNENWWNEENESSENENNESSEESESEEEEESSENEENENWWSWNWWWWNNWNNWNNWSSW(WWNWSWNNNENNWWNENNWWWSWNW(SSESEE(SWSESWSEE(NNNEWSSS|)SS(EESNWW|)WSWNN(E|WWWNN(EE(SWEN|)NNWSWNNE(WSSENEWSWNNE|)|WWWSSES(WSNE|)E(NNWESS|)E))|N(NEWS|)W)|NEN(WWS(WNSE|)S|ESENESE(N|ESESS(WNSE|)SENNN(NWES|)EESWSESSS(EEESWSESSE(EESWWSEEENEN(W|EN(W|NNENESSWSSSWS(W|EENESENNESSSENEEEEESESENNENEENNESESENESSSSWWWNN(ESENSWNW|)(WWSWSSSWWN(WWN(NWSSSESSEEESWWWWNWWNNWWSESSSWNNWNNWNW(SSESSSSE(NN|SWSSSESESESWWNWSSSESENN(W|ESESEENEENNWNENNEESSSSEENWNNNENNWWS(WWWWSESWSSS(E|W(NW(S|NENWWNWNENW(WSNE|)NEEN(NE(NWES|)SEESWS(W(SSWNNSSENN|)N|EEENNEES(ENENESENESESEENWNEEEEESENNNNEEESWSEEEEESSEEESEEESEESEEESSSWNWWN(WWSSE(SEE(NWES|)ESESSSWWSSSENNEENNNNN(W|NNNNNWWWNNNWSSWNNNENWNNWWWSEESWWSS(WNNNWWS(ESSWNSENNW|)WNWWW(SEEWWN|)NENNESENNESESE(NNWNNEENNNNWSSWS(WWNNE(ENNNNNWWWSWSSENENESSWS(E|WWSESWSSWSEE(EENWWN|SWWSWNWWWNEENNWNNNNNNESSSSEE(NNNW(NNWWNNWWNNWWNEENWNWWS(SWNWSSWNWNNE(S|NENNESS(SWEN|)ENENWNWWNWSSSWSWWWNWSWNNNWSWWNWSSWWW(SSSSESWSSWW(NEWS|)WSWSWSW(NNEN(WWNE(E|NNN)|E)|S(W(N|S)|EENESSWSSS(SWNSEN|)EENN(WSNE|)ENENENNWN(WWS(SS(S|EN(N|E))|W)|ENESSSENESSWSSWW(NENSWS|)WSWSEEESWWS(WNSE|)EEEENWNEESS(ENNNWNW(SWWWEEEN|)NENNNESSENESENNENNEEEN(WWWWNWSSESWSWNNWSWNWW(SEWN|)NNNENNESESSE(SWWN(WSNE|)N|NNEES(ENE(NWWWWWNNWSW(N|WSSW(SSSWENNN|)NW(NEWS|)S)|SS(E|W))|W))|EESSENESE(SSESWWWWSESWSEENNEESE(SSWSES(E|WWNWSSEESWSSEES(WWWNWWW(WSSSWS(E(ENENE(NWWSNEES|)SES(EENNW(W|S)|WW)|S)|WWWWW(S(E|WWW(SS|WW))|NEEENE(NE(NWWSWW(S(WWWWNSEEEE|)E|NEN(W|N))|S)|S)))|NEEENWWWNNNN(ESSSENNNEEN(E|N)|WWWNNNNW(NEESESSE(SWWNNSSEEN|)NNNN(ESEENW|N(WS(WWNEWSEE|)S|N))|SSWS(E|WSSWNNNEN(WWSNEE|)E))))|ENE(NWWWEEES|)E(SWEN|)E))|NNNNNWS(NESSSSNNNNWS|))|NNWWNW))|S))))|WWWNNWWWSWNNWWNWWSESS(ENESNWSW|)WSSWNWSW(SEWN|)NNENE(S|NWWSWWSES(WWWWNWNNWWSWSEE(SSSES(EENNW(WNSE|)S|WWWNNE(S|NWWNWWWWS(EEES(ESSNNW|)W|WSW(SESWENWN|)NWW(SEWN|)NEENE(ENNWNWWWWNNWWNNNWNENWNEEESSW(SSENESS(ENNNWNNENNWNNWWSSE(S(WWWWSWWSSWNNNWSWNNEENNESENENNWNEENNWWWS(EE|WNWNNWWWSWWSWWNWNWNEENNNEEESESWWW(NEWS|)SS(EEN(EEENESEEEESES(WWNWWSE(WNEESEWNWWSE|)|EESWSESWSS(W(N|SSE(N|SWW(WSWNSENE|)N))|ENESENNWNENWNENENWNNWSWWNWNWSS(ESESENES(NWSWNWESENES|)|WWNENWNNESEENEENEEESENNESSSEENWNNENWNWSWNNEEESENESSENESSSWNWSW(W|NN|SSENESESSESEENWNEENNNNWSSWNNNNW(SSSS(W|S(EE|S))|NEENWNNNN(WSWNWWSESWWSWS(EEEN(W|ENESSWSW(ENENNWESSWSW|))|WWNENWNN(ESE(ENWESW|)S|WSWWWN(WWWWWSWNWWWWWWWSEEESWWSEEESWSEEEENESSSEESWWWNNWSSS(WWWWSESS(WNWWNENNENN(NWSWS(E|SWNNWWWSEESSE(SSWWWSWNWNWNENWWNWSSWNNNWNENWNWSSWNNW(SSSEESSE(SSSEEN(W|E(SSSEN(ESSSWWSWSSWSESSESSEENNNW(NENESEN(NWN(NNEEN(WW|N)|WSW(N|WS(SS|E)))|ESESEEN(EESENN(WW|NESSESESE(N|S(E|WWWWN(E(E|N)|WSSSE(EN(ESNW|)W|SWWNWNWSSWWNWSWWWSSWNWWNEEN(WNNWNWN(E|NNWSSWW(NENNEEENNEN(EE|NNWWWWNENNWW(NNESNWSS|)S(SSSESEE(SWS(E|WNW(SSS|N))|N(ESNW|)W)|E))|SEESSE(S(ENSW|)WSSE(SESSEEN(WNSE|)EESWSWWSSEESSWSEEESEEEESSESEENENEENESEESENNWNEESSSSES(WWS(EE|WNWWWS(SWWSEESWSWNWWWSWWSWWNENEENNNEEN(WWNWNWN(WWSSSWWNNE(NNWSWNWSSSE(SWSSENESESWSEE(SSWWWWSWNNWSWWSESSEN(ESESWWSWSWSW(SEESSESWWNNWSSSSSESSW(N|SESESESWWNW(N|SSSESENN(ESEEENNENESESSSSWWWN(ENNESS|WSWNWSSWWW(N(N|EE)|SESWSEEEENN(WWSEWNEE|)NEESSENNEEENENNNESEEENENNNWNENN(EEE(SWSW(SEE(N|SESESWSESESWWWN(E|WNNN(ESSNNW|)NWSSSWSESWWNWSSSEEN(ESEN(ESESSSWSEENNENNW(S|N(W|EENNESENEEENWNWSWNWWS(E|WNNN(NW(S|W)|ESEEEENNW(NEEESWSSSESSENENWNEESEENWNE(NNWSWNNNENWN(EESSESWW(EENWNNSSESWW|)|N|WSSSSSS(E|W(WSNE|)NNN(W|NNN)))|ESSENEN(ESSWSSWNWWSSSSEESSENNNN(WSWNNSSENE|)ENNESSEENNENWW(WNNNWNENEENN(WWSEWNEE|)EN(W|ESSWSEEEESENEE(SEESENEN(W|E(SSSSE(NN|SSSSSWWSSWWWSEEESESE(NNWNEN(E|W)|SESWSWSEEESSWSSENESSSWWN(E|WWWWNENENE(SSWENN|)N(E|WWNNWSSWSWWNNWNNNWNNWWSWNNWSSWNNWNWWNN(ESENENEN(NESESWSWSES(WWNSEE|)EENWNEENESEEES(ENNEENWNWWS(SWNNWWNNNN(N|WSWNWNWSSESWW(SEESES(E(NNNWS|EES)|S)|NNNWSWW(NEWS|)SSEENW)|ESE(N|ESES(WWNWSNESEE|)E(ESNW|)NN(N|W)))|E)|WWWSESW(SSENESESES(WSSW(S|NNW(NEWS|)S)|EN(NWNW|ES))|W(WW|NN)))|W)|WSSSEESSWNWWWWSWSSESSWWWSSWWNNNWWSWSESWWSSSSSENNNNEE(NNN|ESSENNEEENN(WSNE|)EESENNESSSESSSSWSWWNNNEE(SWSNEN|)NWNWW(S(E|WWWSEEESWWWSSENESE(N|SWSESSENNNEESENEEENESSWWSESEESESSSWWSESWWS(EEEENEENEENESSEENWNNWNWSWWNNNENEESWS(WSNE|)EESESEENWNWNNEENWNNWNWWWNNNWWSSE(SSSWNWN(WWNWWWWW(SS(W|ENEEESESSW(N|S(EENE(NWNSES|)S(SSW(NWES|)SSSE(SWWSNEEN|)(NN|EE)|ENEENEN(ESS(ENSW|)(SS|W)|W))|W)))|NNEES(W|ENENNWWWNWS(SEEEWWWN|)WNNENNN(WWNWWS(W|SE(S(EENW|WS)|N))|E(NN|EESSSW(NNWSSNNESS|)SEEEENE(SESS(WNWWSSS(W|EE(NWN|SW))|EEE(ENEWSW|)SSSEEEES(ESWSESSENNNNESSESWSSESENN(ESEENESEENEENNNWNWSWWNENWNNNESEEESS(ENNENESENEENNWNNWWSSS(E(E|NN)|WWNENNWSWNWWNNESEEEENWWN(NESEESEEEENWWWNEEENENESENENWWNNWSSWWWWWSS(W(SEWN|)NWSWNWNENENWNEESS(SWEN|)EENN(W(NWWWEEES|)S|EESWSEENNNEN(ESS(W|EESENESSW(WWNSEE|)SEESWWSESENENNNESSEENENWNNWN(NNWWSSSW(NNNWW(NN|SESWWW)|S(EE(ESSNNW|)NNN|S))|EEESEESSE(SSSWSSWWWNWN(WWSESESWWWWWWWSEESSEEENEESSW(WSWWN(E|WSWNNWSWNN(NNNEN(WWSSW(SWWW(WW|SES(ESSW(N|SEENNNE(SSSSWSWSEEEN(NEEN(WWNEWSEE|)EEEESWSSEEEENENESENNWWWSWNW(SS(W|E)|NEEEENESENNNNENEE(SWSSW(SESSESEEESWWSWWN(NWN(WSSESWWWSW(SSEEENN(WSWENE|)EEEESWSESSENESSSSWWWSSEEN(W|ESE(NNNNNNNWNW(S|NEN(W|E(NNNNW(NENWESWS|)WW(WNNN|SEE)|SS)))|SWWSES(ENSW|)WWWWNWNE(ESENSWNW|)NWWNWSWNNWSSWSWSES(WWNNWNENWNWWWWWWSWNNNWWSESWSWSWNNWSWWSSSES(WWWWWNWSWWWNNNNENWWSSWNWWN(WSSWW(SWNW(SSEEES(WWWWWWWW(NEWS|)WW|ENN(ENESESS(ENN|WWNE)|W))|W)|NENN(NWS(WNWESE|)S|E))|EENEEEEESSW(SS(EEN(W|NNNNEENEEESS(WW(NEWS|)S(SWSSE(SWWNNNNNES(NWSSSSNNNNES|)|N)|EE)|EENWNEE(NEES(ENNNN(EENEEE(NW(NEWS|)WW|SESWSESESWSES(ESES(S|ENNNENWN(EEESSS(ES(W|ESENNNE(EESWWEENWW|)NWN(E|NW(NEWS|)SWSSE(S|N)))|W(W|NN))|WSS(WNNNNW(NEESSENN(SSWNNWESSENN|)|S)|S)))|WWWNWSWNW(S|NENENN(NESSSS(E(N|S)|W)|WSW(N|S)))))|WSWWN(E|WSS(WNNWNWN(WSSW(W|SESS(WNSE|)ENN(ESSEEWWNNW|)N)|EESEENN(E|W(S|W)))|EEE)))|W)|SSS)))|W(SEWN|)N)|N))|EENEEN(NE(EEEEEEN(WWW|ESSWSEESWWWWWNEENWWWWSW(N|S(EENSWW|)WW))|N)|WWW(WNEWSE|)S))|ENNESEE(NWES|)S(E|WW))))|N)|N)|E)|N)|EENWNWWS(E|WW(NENSWS|)SWSWNWSW(WWWWWSE(WNEEEEWWWWSE|)|SES(SWN|ENES)|N))))|W)|N(WW|N)))|W))|NN)|N|ESEEE(N|E))|EE))|N)|ENEE(SSWNSENN|)ENWWNENWWN(SEESWSNENWWN|))|N(EE|N))))|W))|ENESENE(WSWNWSNESENE|))|W(S|WWW(SWSESWWWN(ENSW|)WWSSSSW(WNENNW(S|N(EN|WSW))|SSSSENESESE(SSES(E(S|EN(ESNW|)W)|WW(S|NNWSSWNNWNEE(WWSESSNNWNEE|)))|NNNNNWNN(EEESS(WNWESE|)ESEE(NNW(NWSNES|)S|E)|W(SSSWSEE(N|S)|N))))|NNNN))))|WWN(W|E))|W)|W))|NNWWN(ENSW|)WSSE(SWEN|)E)))))|E)|N)|WNNWNWWNWSWNNWWSSSWNNWWSWSEE(N|SWS(EEEEN(N(NN|EEEESESWWWN(WSNE|)E)|WW)|WNWWNNWNEE(ENWNENWWSSWWSWWSEESESWS(WNWN(E|WSWWNENWNNWWWWNEENNENWWNNWWWSWWWNWWNNEEES(SENENENWNNNENNNWWSS(ENSW|)WWSSSWWWWNNNEEE(NWNNWSSWWNWWWWWNWNNW(NEEEESWS(WNSE|)SENEENWNEN(WNNSSE|)EESWSES(WS(ESNW|)WW|EENWNNESESSENEENNWW(SEWN|)NE(EESESWSEESWWS(WNWSSSWNNWS(NESSENSWNNWS|)|EESSESWSESWWSEESEENESESENESSE(SSENESSS(ENENWNEESE(EESSWW(W(NEEWWS|)W|SSSENNEE(N|S(WSNE|)EEEES(W|EES(EE(EENWNWSWNWWNN(WSWNNSSENE|)E(SEWN|)N|S(W|S))|W))))|NNWN(E|WW(NNES|SE)))|SWNNWSWWNNWSSW(SEESENES(SWWS(S|WNNWWN)|EE)|NNWNEEE(ESSNNW|)NWWNWWWS(E(SS|E)|W(NN|W))))|NNNNNWSWNWNEEENNE(SS|ENENESEES(SS|ENE(SEWN|)NWWNEENENN(ESNW|)WWS(E|SWNWWSS(E(N|S)|WNNWWSSS(ENNSSW|)WWWNENNNW(SSWSSSEE(SWS(WNWWNWS(WNN(EEESNWWW|)NNNENWW(W|SS)|SSESWS(EE(ESEE|NNNW)|S))|E)|EE)|NENEEEN(W|EEESES(ENE(NNNWSSWN(SENNESNWSSWN|)|S)|SWWN(E|NWSSWWN(WSSSSNNNNE|)E))))))))))|NWW(WS(ES|WWNE)|NENNESS(NNWSSWENNESS|))))|SSSSE(N|SSESWSW(SESESWW(N|SESSENEENW(W|NNESEESWSESENNEE(SWSESSENNE(NWES|)SSESWSSSWNNNWWSESSWNWSSEEEESENNNEN(ESENE(SEEEESSWWN(E|WWWSWSW(NNEWSS|)S(WWWWWN(EE|WSWNWSWNWWWNW(SSEEEWWWNN|)NNESESEENNENWWW(SESNWN|)NWW(SEWN|)NEN(WNNSSE|)ESENEE(NWWEES|)EEESWSSW(SSWSEWNENN|)NWW(NEEWWS|)W)|EENENESS(ENEES(EEEE|W)|W)))|NWNWW(SEWN|)NN(WSNE|)EES(W|EE(NWNE|ESWW)))|W)|NNN(WWNWNWNWW(NN(WSNE|)ESEE(NWES|)SE(S|N)|SESES(WWNWSNESEE|)ES(ESENSWNW|)W)|EEEEE(S|NWNNES)))))|NNN)))|SWWSEE)|WW))|EEE)|SS))))))|N)))))))|N))|NWWWWWN(SEEEEEWWWWWN|)))|SS)|W))|S)))))|N)|W)))|N)|E)|WNENWWNENNNWSWWWNEENENWWNNENNWNN(WSSS(E|WSSSS(SSWNNWSSWNWWSSSW(NNNWNN(W|NESEENWN(W|EEENNWW(SEWN|)N(NESENEESSW(N|SSSSWNWSSWWW(EEENNEWSSWWW|))|W)))|SESEEEESWSSES(WWWWS(E|SW(SEWN|)NNNW(NNW(SS|NNE(NWWSNEES|)SESEEESSWNW(W|S))|S))|ENEENNNE(ESS(E|SW(SWSS(ESENN(ESNW|)(W|N)|WN(N|W(SSSS|W)))|NN))|NWWSW(NWWWNN(W(SS|N)|ESENESEEEN(WW|E))|SS(ENSW|)W))))|E(NNN|E)))|ESESESSENNNEEESWWSESSESESS(ENNN(EEESWSESW(SEE|WNN)|WNENW(WSNE|)NNNNW(SWNWSWNW(NEWS|)W(SESNWN|)W|N))|WNWWSW(NNW(N(EE(SEWN|)N|W(NN|W))|S)|SE(SSWNSENN|)E(N|E)))))))|W)))|NNEN(NNW(NNNNNEES(SWNSEN|)ENNE(SEESW(SEEEWWWN|)W|NWNNE(S|NNWSWNWNNNW(NENESESSE(SWWNNSSEEN|)NN(NNW(WWW(S|NEENWWNNNNE(NWNENW|SSES(ESSEWNNW|)W))|S)|E(SS|E))|SSSSESSW(N|SSEEN(W|NN)))))|SS)|E))|N)|ENWNN(EEN(WN(E|N)|ESSW(SEWN|)W)|W))|N)|S)|E)|EES(ENN(NEES(W|E(EE|N))|W)|WSWS(WNSE|)E))|EE))|ENNNW(S|NNN(WWNWNWNN(WWWWNEENWWNWN(E|WSSWNWWWWW(WNEEEEEEN(SWWWWWEEEEEN|)|SEEEESESENE(SSSSWSSW(SES(S|ENEENWWNENNNEESWSSESEE(N(E|NW(S|NN|W))|S)|W)|NWSWNNWWS(SENSWN|)WWNENEENNE(NWWWSESWW(N|WW|S)|ESWSESENNES(NWSSWNSENNES|)))|N)))|EE(NWNEWSES|)S(ES(W|S)|W))|ESSESS(EENN(WS|ESE)|SS))))|N)|N)))|EEENNNNEESSE(S(WWNNSSEE|)S|NESEE(N(N|W)|S))))))))|W))|SS)|N)|N))|N)|NENWNEESENESS(WW|ES(SEESENNNEESENESSWS(EEEN(WNENWNNWSWWN(WSWWSW(SEWN|)NWNEEE|E)|EE)|WW(SWW(WNWSNESE|)SEESESE(S(WWNSEE|)E|N)|N(N|E)))|W)))|E))|EEESWS(WNSE|)E)|S(S|EENNN(ESSSS|WSS)))|EEE(EENEENNNEE(SWSESW|NNE(S|NWWSSWNNWSSWSS(SENNSSWN|)WWNENNNW(S(S|WNWSWW(SEWN|)NN(WS|ES))|NEE(E|SS))))|S))|EE)))|EEESEESSSEEESWSWSWSWW(NNW(WSEWNE|)NEE(E(SWSNEN|)E|NNWN(WW(NE|SESE)|E))|SESWSESWSWSSSEEEESWWWSSWNNWWWNWWNE(EESENSWNWW|)NWWWSSSSWWWSWW(SEEESENESSWWSSEEEN(WW|ENNNW(SS|N(WWW|NN(NN|EESWSESEENWNEESSEESESSESSSENNNNNESSESWSEEEESESWWWWW(NEEEWWWS|)SEESWWSESEEESSESEENESSEENWNENNWNENWWNNESEESSESWSSENEESWSWWSESEEN(EESES(WSSWWNWSWNN(WWN(WSWNWWN(E|WWNWNNWWWWN(NWNNE(NWWSSSSSSWNNWSWSESSS(SSESENNWNEEE(SWEN|)EENWWNN(ESENESS(S|E)|W(NN|SSWNWS))|WNNWNWNWWNENWNNENENWNW(NENESENNN(WSWNSENE|)ESSEN(N|ESSWWSEEE(N|SWWSESWWW(NN(ES|NW)|SW(W|N|SEE(NEESWENWWS|)SW(W|S)))))|WSWWWWW(NNE(SEEEWWWN|)NWNW(NEESNWWS|)SS|SS(W|EESENEN(WWW|E(ENSW|)SSSSSWSSSSW(SES(W|EENWNEE(EN(ESNW|)WN(NWWSESW(ENWNEEWWSESW|)|E)|S))|NWNNE(S|NNN(E(N|S)|WSSWW(SS(WWNE|EN)|NENNWS)))))))))|S)|E))|E)|EEE(S|N))|EE(NESENNNESSENESSESE(NNEEEENNNEENNESSSSSSSSW(NNNW(NNESNWSS|)S(S|WW)|SEEENESSSENNENNNWNEESSSEESWSEENNNNNEENNWNNWSWSS(W(SSSENN|WWWNNESENNE(SS|ENWNENWWWNNEEENNWWNNENENENWWNNEES(ESENEEEENNENNNESSESENE(NNWNENNWWS(WS(ESSEWNNW|)WWNWSWWWNNWWWNEEEESSENNNENNWWWSE(SWWNWSWNWNEEENENWWSWNWWNWWWWWWSWNWNWWNENESENEEEN(ESSEES(EENNW(WWNEEEESSENEEN(WW|EESENESSESWWWWS(WWWW(NEEEN(W|E(N|EE))|W)|SSENEN(EEESENNEE(NWNWW(WNEEEES(NWWWWSNEEEES|)|S(S|E))|SSSSWN(NN|WSWSWW(NN(W|E(NWES|)(E|S))|SESS(WNWSNESE|)(S|ENNESEENNW(W|S)))))|W)))|S)|WWWNWWS(W|E))|WWWWWWSWWWWN(EEE|WSSWSSWWNWWWSWSWSESSWNWWSSE(ESENESSSWWWWWNN(ESE(EE|N)|NWNNE(S|NWWSWNWNNESEEEENE(SSWENN|)ENWNNWSWWSS(ENEWSW|)WNNWSWNWSWNNN(WSWWN(WWWWW(SSSENNEESS(WNSE|)SESESSSSWSESSEENESSESWSSSEESEESENNNENESSWSSSSWWWN(WWSESSSSS(WWW(NWNWNWNW(SSEWNN|)WNNNNW(NEESSENNNESESWSSS(WNWSNESE|)SEENE(SSE(SW(SE|WNW)|N)|NWN(WSSNNE|)N(NNWNWWNEEE(S|NWWWNWSSSWNNNWSWW(SEES(SEEWWN|)WWWWNEN(SWSEEEWWWNEN|)|NENNN(WSSNNE|)EN(W|NENE(SS(ENNSSW|)WSESS(WNWSNESE|)E|N))))|EES(W|EE)))|WSESWW(WNENWESWSE|)SS)|SESSWNWWSES(WW(NN|W)|SSE(NESE(NNWWEESS|)E|S)))|ESEESSESSENNNENWNNWWW(SEESSNNWWN|)WNNESEEENN(WSWNWW|ESENNENNNESEEESSENEESSW(SEENESSESSWWN(NWWSESWSWSESWWSEESWSWS(EENENNEENWWNEN(ESESSEESENNEENEESWS(EESWSEE(SWWSSEE(NWES|)SWWSEES(WWS|ES)|ENWNE(ES(ENSW|)S|NWWNNESENNNNNE(SSSEEWWNNN|)NWNEE(NWWNEENWWWNWNENNWWS(E|WNNNEES(W|ENESESENEEN(WWWNWNWSWNWSWWSWNWWNWWSSSWNNNNWNWWNEENEENESSSW(NWSNES|)SEEENNESSS(W|EENENWW(NN(WNWNW(WWWWN(WSS(EE|SWNWWWSSESSE(NNNWESSS|)EESSE(N|SSSESWSEEEESSWNWWWSEESWSES(WWNNWWNW(NENWNEE(SSS|NNWWNWWNW(NNN(WNNNE(NEWS|)SS|ESSEEES(SEWN|)WW)|SSEES(WWSSS(WWWSSSWW(SEWN|)NNE(S|NNNNN(WSWNWSSWNWSW(WSEESEN(SWNWWNSEESEN|)|NNNWNNWNNNE(NWWSW(NNNWNN(ESE(N|SSEENW)|W(N|S))|SESSW(S|N))|ESS(WNSE|)ENESSESWS(E|SWNNWNE(WSESSEWNNWNE|))))|EESSS(WNN|ENNN)))|SEENNW(NEWS|)S)|EE)))|S)|ESESSW(NWNSES|)SESWS(W|EEE(ENNNWNNW(NNENEESSESEE(NWNN(ESNW|)NW(WWWNEEENWWNNNWWNWW(N|SSE(N|S(WWNSEE|)EE(NWES|)SWSSSWWSES(NWNEENSWWSES|)))|SS)|SSWWSES(ENSW|)WSWNNNN(EE|NW(N(W|N)|S)))|SSSESW)|SWWWSE)))))|NESEENW(ESWWNWESEENW|))|SS(E|SS))|EENEEESE(SSS(WNWN(NWS(SSEWNN|)WW|E)|E(NNNEWSSS|)ESSWNW)|N))|S))|EESWSSSS(WNNW(NEWS|)WWW(N|SSEEN(ESNW|)W)|ESENNESENNN(EESSW(SSWWEENN|)N|WWWS(S|EE))))))|E|S)))|WWSSWWSWNNWWWSESWWS(EES(WSNE|)EEENWWNN(SSEESWENWWNN|)|W))|W)|WNWWSESS(ENSW|)W(NW(S|NWNENENENE(NNE(S|NWNNNEE(NWWNWN(E|WSSESSSSSSWNNNWN(ENWNSESW|)WWSSE(N|ESSS(E|W(WSS(ENEWSW|)SSS(W|E)|NN))))|SS(WNSE|)S))|SS(W|E)))|S))|E)|N)))|EE)|WW)|E)|ESENEEES(WW|ENEEESENEEEEEESWS(S|WNWSWW(NEWS|)W(S|W))))))|N)))|E)|E)|SSSWNWW(SESESWWNW(NN|WWSWSESEEN(WNEWSE|)EEESSSSWSSENE(NNNNNNN|SSWWSSESSWSWNWSWNWWNWS(WNNWWNNN(NESSEENWNEESSENESSENE(NWNWNNWWN(WWSWNW(N(WSWENE|)EN(NESE(NNEWSS|)S(E|W)|W)|SSEEE(EESNWW|)N)|EEESE(NE(NWES|)S|S(S|W)))|SSWWW(SEEEEWWWWN|)NWSWNWW(EESENEWSWNWW|))|WWW)|SSSENNESESSW(SEEENNW(NEEENE(NNNNWESSSS|)SSSWSW(NNEWSS|)SWSSENENE(SSWSSE(SWSWSEE(N|SWSSWSEE(NN|SSWWWN(WWSSSSWSESWW(SSW(NWES|)SSEEENESENNNENWW(SSWW(SW|NE)|NEEENE(NWWSWNN(W(SS|N)|EEE)|SSWSSSE(NN|SWW(SWWSESEEE(NNWSWENESS|)SSWSS(ENSW|)WNNN(E|W)|NN))))|NNNENNW(S|WWNNNENNWSWWNNWWNNESEENWNEN(NNNEEE(NNWSWWNE(WSEENEWSWWNE|)|SWWSSSSSES(WWSNEE|)EEEESWWSESEE(N(ENWNNNWSWNWNWNN(WSSSESE(WNWNNNSSSESE|)|ESEE(ES(E(N|S)|WW)|NNW(WNEEWWSE|)S))|W)|SWWWW(N(E|NN)|S(WNSE|)E)))|WWWWN(N|WSSE(SWSESWWSS(WNNWWNNESENN(ESSNNW|)WWNENWW(WW|S)|EE(SWSNEN|)N(EESWENWW|)W)|EE)))))|EE)))|N)|N)|S)|N))))|N))|W)))|E(E|N)))|SWSWNNWNWSSE(WNNESEWNWSSE|))|S))|W)))))|NEN(W|EENWNEE(SS|NNWN(WSWNNWS(WNNWSWWSE(S|E)|SSE(EE|SS))|EESEENW(ESWWNWESEENW|))))))))))))|W)|W|S))|E)|N)|WW)|N)|S))))|N)|S)|E)))|E)|SS)|SW(W|S(E|SS)))))|S)|E)|SWW(N|WW))|ENESSWW(EENNWSNESSWW|)))|N)|EE)|W))|WW))|S))|E)))|NNESE(EEES(E(NNW|SSE)|WWW)|N))|E)|E)|N))))|NNNNN(W(WW|N)|E))|WN(N|WWSS(E(SENSWN|)N|W))))))|SEES(SESNWN|)WW)))|W)|W)|N(NN|WW))|E))|S(WWS|EES))|N)|E)|E)|ENNEESES(ENSW|)WW(N|S)))|SEESWSE(WNENWWEESWSE|))|S(WWNSEE|)SSSSWS)$";
}

void day21_1and2()
{
    struct registers {
        int64_t r[6] = { 0 };
        std::string dump() const {
            std::ostringstream oss;
            oss << std::hex << "[";
            for (int i = 0; i < 6; ++i) {
                if (i != 0) {
                    oss << ", ";
                }
                oss << r[i];
            }
            oss << "]";
            return oss.str();
        }
    };
    using opcode_impl = std::function<void(registers&, int64_t, int64_t, int64_t)>;
    std::map<std::string, opcode_impl> opcodes = {
        {
            "addr",
            [](registers& regs, int64_t a, int64_t b, int64_t c) {
                regs.r[c] = regs.r[a] + regs.r[b];
            }
        },
        {
            "addi",
            [](registers& regs, int64_t a, int64_t b, int64_t c) {
                regs.r[c] = regs.r[a] + b;
            }
        },
        {
            "mulr",
            [](registers& regs, int64_t a, int64_t b, int64_t c) {
                regs.r[c] = regs.r[a] * regs.r[b];
            }
        },
        {
            "muli",
            [](registers& regs, int64_t a, int64_t b, int64_t c) {
                regs.r[c] = regs.r[a] * b;
            }
        },
        {
            "banr",
            [](registers& regs, int64_t a, int64_t b, int64_t c) {
                regs.r[c] = regs.r[a] & regs.r[b];
            }
        },
        {
            "bani",
            [](registers& regs, int64_t a, int64_t b, int64_t c) {
                regs.r[c] = regs.r[a] & b;
            }
        },
        {
            "borr",
            [](registers& regs, int64_t a, int64_t b, int64_t c) {
                regs.r[c] = regs.r[a] | regs.r[b];
            }
        },
        {
            "bori",
            [](registers& regs, int64_t a, int64_t b, int64_t c) {
                regs.r[c] = regs.r[a] | b;
            }
        },
        {
            "setr",
            [](registers& regs, int64_t a, int64_t b, int64_t c) {
                regs.r[c] = regs.r[a];
            }
        },
        {
            "seti",
            [](registers& regs, int64_t a, int64_t b, int64_t c) {
                regs.r[c] = a;
            }
        },
        {
            "gtir",
            [](registers& regs, int64_t a, int64_t b, int64_t c) {
                regs.r[c] = (a > regs.r[b] ? 1 : 0);
            }
        },
        {
            "gtri",
            [](registers& regs, int64_t a, int64_t b, int64_t c) {
                regs.r[c] = (regs.r[a] > b ? 1 : 0);
            }
        },
        {
            "gtrr",
            [](registers& regs, int64_t a, int64_t b, int64_t c) {
                regs.r[c] = (regs.r[a] > regs.r[b] ? 1 : 0);
            }
        },
        {
            "eqir",
            [](registers& regs, int64_t a, int64_t b, int64_t c) {
                regs.r[c] = (a == regs.r[b] ? 1 : 0);
            }
        },
        {
            "eqri",
            [](registers& regs, int64_t a, int64_t b, int64_t c) {
                regs.r[c] = (regs.r[a] == b ? 1 : 0);
            }
        },
        {
            "eqrr",
            [](registers& regs, int64_t a, int64_t b, int64_t c) {
                regs.r[c] = (regs.r[a] == regs.r[b] ? 1 : 0);
            }
        },
    };
    struct instruction {
        std::string opname;
        const opcode_impl* op = nullptr;
        int64_t a = 0, b = 0, c = 0;
    };

    registers cpu;
    int64_t* ip = nullptr;
    std::vector<instruction> program;
    {   
        std::string line;
        std::getline(std::cin, line);
        std::istringstream iss(line);
        int n = 0;
        char c = 0;
        iss >> c >> c >> c >> n;
        ip = &cpu.r[n];
    }
    for (;;) {
        std::string line;
        std::getline(std::cin, line);
        if (line == "out") {
            break;
        }
        std::istringstream iss(line);
        instruction inst;
        iss >> inst.opname >> inst.a >> inst.b >> inst.c;
        inst.op = &opcodes[inst.opname];
        program.emplace_back(inst);
    }

    cpu = { { 0, 0, 0, 0, 0, 0 } };
    int64_t first = -1, last = -1;
    std::unordered_set<int64_t> seen;
    while (*ip >= 0 && *ip < static_cast<int64_t>(program.size())) {
        const instruction& inst = program[*ip];
        (*inst.op)(cpu, inst.a, inst.b, inst.c);
        ++*ip;
        if (*ip == 28) {
            if (!seen.emplace(cpu.r[4]).second) {
                break;
            }
            if (first == -1) {
                first = cpu.r[4];
            }
            last = cpu.r[4];
        }
    }
    std::cout << "Day 1: " << first << std::endl
              << "Day 2: " << last << std::endl;
}

void day22_1and2()
{
    const int64_t DEPTH = 5913;
    const int64_t TARGET_X = 8;
    const int64_t TARGET_Y = 701;
    const int64_t CAVE_SIZE_X = TARGET_X + 100;
    const int64_t CAVE_SIZE_Y = TARGET_Y + 100;

    struct region {
        int64_t x = 0, y = 0;
        int64_t geo_index = 0;
        int64_t erosion_lvl = 0;
        char type = 0;
        int64_t risk = 0;
    };
    std::vector<std::vector<region>> cave;
    auto get_geo_index = [&](int64_t x, int64_t y) -> int64_t {
        if (x == 0 && y == 0) {
            return 0;
        } else if (x == TARGET_X && y == TARGET_Y) {
            return 0;
        } else if (y == 0) {
            return x * 16807;
        } else if (x == 0) {
            return y * 48271;
        }
        return cave[x - 1][y].erosion_lvl * cave[x][y - 1].erosion_lvl;
    };
    auto get_erosion_lvl = [&](int64_t geo_index) -> int64_t {
        return (geo_index + DEPTH) % 20183;
    };
    const std::unordered_map<int64_t, char> TYPES_PER_MOD = {
        { 0, '.' },
        { 1, '=' },
        { 2, '|' },
    };
    auto get_type = [&](int64_t erosion_lvl) -> char {
        return TYPES_PER_MOD.find(erosion_lvl % 3)->second;
    };
    auto get_risk = [&](int64_t erosion_lvl) -> int64_t {
        return erosion_lvl % 3;
    };

    cave.resize(CAVE_SIZE_X);
    for (auto&& c : cave) {
        c.resize(CAVE_SIZE_Y);
    }
    for (int64_t x = 0; x < CAVE_SIZE_X; ++x) {
        for (int64_t y = 0; y < CAVE_SIZE_Y; ++y) {
            cave[x][y].x = x;
            cave[x][y].y = y;
            cave[x][y].geo_index = get_geo_index(x, y);
            cave[x][y].erosion_lvl = get_erosion_lvl(cave[x][y].geo_index);
            cave[x][y].type = get_type(cave[x][y].erosion_lvl);
            cave[x][y].risk = get_risk(cave[x][y].erosion_lvl);
        }
    }
    cave[0][0].type = 'M';
    cave[TARGET_X][TARGET_Y].type = 'T';

    int64_t total_risk = 0;
    for (int64_t x = 0; x <= TARGET_X; ++x) {
        for (int64_t y = 0; y <= TARGET_Y; ++y) {
            total_risk += cave[x][y].risk;
        }
    }
    std::cout << "Risk: " << total_risk << std::endl
              << std::endl;

    for (int64_t y = 0; y < CAVE_SIZE_Y; ++y) {
        for (int64_t x = 0; x < CAVE_SIZE_X; ++x) {
            std::cout << cave[x][y].type;
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

    //
}

void day23_1and2()
{
    struct bot {
        int64_t x = 0, y = 0, z = 0;
        int64_t rad = 0;
        bool operator<(const bot& right) const {
            return rad < right.rad;
        }
    };
    auto manhattan = [](const bot& a, const bot& b) {
        return std::abs(a.x - b.x) + std::abs(a.y - b.y) + std::abs(a.z - b.z);
    };

    std::vector<bot> bots;
    for (;;) {
        std::string line;
        std::getline(std::cin, line);
        if (line == "out") {
            break;
        }
        std::istringstream iss(line);
        bot b;
        char c = 0;
        iss >> c >> c >> c >> c >> c >> b.x
            >> c >> b.y
            >> c >> b.z
            >> c >> c >> c >> c >> b.rad;
        bots.push_back(b);
    }

    auto& raddest_bot = from(bots)
                      | max();
    auto bots_in_range = from(bots)
                       | where([&](auto&& b) { return manhattan(b, raddest_bot) <= raddest_bot.rad; })
                       | count();
    std::cout << "Bots in range of raddest bot: " << bots_in_range << std::endl;

    auto smallest_x = from(bots)
                    | min([](auto&& b) { return b.x; });
    auto largest_x = from(bots)
                   | max([](auto&& b) { return b.x; });
    auto smallest_y = from(bots)
                    | min([](auto&& b) { return b.y; });
    auto largest_y = from(bots)
                   | max([](auto&& b) { return b.y; });
    auto smallest_z = from(bots)
                    | min([](auto&& b) { return b.z; });
    auto largest_z = from(bots)
                   | max([](auto&& b) { return b.z; });
    std::cout << "Space:" << std::endl
              << "X = " << smallest_x << ".." << largest_x << " (" << (largest_x - smallest_x) << ")" << std::endl
              << "Y = " << smallest_y << ".." << largest_y << " (" << (largest_y - smallest_y) << ")" << std::endl
              << "Z = " << smallest_z << ".." << largest_z << " (" << (largest_z - smallest_z) << ")" << std::endl;

    //
}

int main()
{
    day15_1and2();
    return 0;
}
