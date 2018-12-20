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

#include <coveo/linq.h>

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

void day15_1()
{
    struct point {
        int x, y;
        point(int i = 0, int j = 0) : x(i), y(j) { }
        bool operator<(const point& right) const {
            int cmp = y - right.y;
            if (cmp == 0) {
                cmp = x - right.x;
            }
            return cmp < 0;
        }
    };
    struct tile {
        char ground = 0;
        char mob = 0;
        int hp = 0;
        bool moved = false;
    };
    std::vector<std::vector<tile>> grid;
    grid.resize(32);
    for (auto&& g : grid) {
        g.resize(32);
    }
    for (int y = 0; y < 32; ++y) {
        std::string line;
        std::getline(std::cin, line);
        for (int x = 0; x < 32; ++x) {
            tile t;
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
                    break;
                }
            }
            grid[x][y] = t;
        }
    }


}

int main()
{
    day15_1();
    return 0;
}
