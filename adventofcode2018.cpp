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

int main()
{
    day7_2();
    return 0;
}
