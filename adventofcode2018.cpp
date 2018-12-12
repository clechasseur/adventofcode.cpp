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

int main()
{
    day4_1();
    return 0;
}
