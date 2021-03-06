#include <bits/stdc++.h>

using   vi = std::vector<int>;
using  vvi = std::vector<std::vector<int>>;
using vvvi = std::vector<std::vector<std::vector<int>>>;

const int W = 30, H = 30;

struct Vertex {
    int i, j;

    Vertex() : exists(false) {}
    Vertex(int i, int j) : i(i), j(j) {}

    inline explicit operator bool() const { return exists; }

private:
    bool exists = true;    // on the graph.
};
inline bool operator<(const Vertex& lhs, const Vertex& rhs) {
    return lhs.i < rhs.i || (lhs.i == rhs.i && lhs.j < rhs.j);
}
inline bool operator==(const Vertex& lhs, const Vertex& rhs) { return !(lhs<rhs) && !(rhs<lhs); }
inline bool operator!=(const Vertex& lhs, const Vertex& rhs) { return !(lhs==rhs); }
inline bool operator>(const Vertex& lhs, const Vertex& rhs) { return !(lhs<rhs) && lhs!=rhs; }

using Path = std::vector<Vertex>;
inline bool operator<(const Path& lhs, const Path& rhs) {
    for (size_t i = 0; i < lhs.size(); ++i) {
        if (i < rhs.size()) {
            if (lhs[i] < rhs[i]) {
                return true;
            } else if (lhs[i] > rhs[i]) {
                return false;
            }
        } else {
            return true;
        }
    }
    return false;
}

enum Direction {
    Down,
    Right,
};

struct Edge {
    Vertex vertex;
    Direction direction;

    Edge() : exists(false) {}
    Edge(Vertex vertex, Direction direction) : vertex(vertex), direction(direction) {}
    Edge(int i, int j, Direction direction) : vertex(i, j), direction(direction) {}

    inline explicit operator bool() const { return exists; }

private:
    bool exists = true;    // on the graph.
};
inline bool operator<(const Edge& lhs, const Edge& rhs) {
    return lhs.vertex < rhs.vertex || (lhs.vertex == rhs.vertex && lhs.direction < rhs.direction);
}

Edge getEdge(const Vertex& from, const Vertex& to) {
    if ((from.i - to.i) * (to.i - from.i) > 1 || (from.j - to.j) * (to.j - from.j) > 1) {
        return {};
    }
    if (from.i < to.i) {
        return {from, Down};
    } else if (from.i > to.i) {
        return {to, Down};
    } else if (from.j < to.j) {
        return {from, Right};
    } else if (from.j > to.j) {
        return {to, Right};
    }
    return {};
}

struct PossibleLength {
    static const int MEDIUM = 5000;
    static const int DEFAULT_DELTA = 4000;
    static const int MIN = MEDIUM - DEFAULT_DELTA;
    static const int MAX = MEDIUM + DEFAULT_DELTA;
    int shortest, longest;

    PossibleLength() : PossibleLength(MEDIUM, DEFAULT_DELTA) {}
    PossibleLength(int medium) : PossibleLength(medium, DEFAULT_DELTA) {}
    PossibleLength(int medium, int delta) : shortest(medium - delta), longest(medium + delta) {
        this->clamp();
    }

    inline void clamp() {
        if (this->shortest > this->longest) {
            std::swap(this->shortest, this->longest);
        }
        if (this->shortest < MIN) {
            this->longest -= MIN - this->shortest;
            this->shortest = MIN;
        }
        if (this->longest > MAX) {
            this->shortest += this->longest - MAX;
            this->longest = MAX;
        }
        if (this->shortest > MAX) {
            this->shortest = this->longest = MAX;
        }
        if (this->longest < MIN) {
            this->shortest = this->longest = MIN;
        }
    }

    PossibleLength operator=(int medium) {
        int delta = (this->longest - this->shortest) / 2;
        this->shortest = medium - delta;
        this->longest = medium + delta;
        this->clamp();
        return *this;
    }

    inline int getMedium() const { return (shortest + longest)/2; }
    inline operator int() const { return getMedium(); }
};
inline bool operator<(const PossibleLength& lhs, const PossibleLength& rhs) { return lhs < rhs; }

inline std::ostream& operator<<(std::ostream& stream, const Vertex& v) {
    return stream << '(' << v.i << ',' << v.j << ')';
}

std::ostream& operator<<(std::ostream& stream, const Path& p) {
    bool delim = false;
    for (auto&& v : p) {
        stream << (delim ? "-" : "") << v;
        delim |= true;
    }
    return stream;
}

vvi Q(H, vi(W));
std::map<Edge, PossibleLength> distance;

auto dijkstra(const Vertex& s, const Vertex& t) {
    std::vector<std::vector<Vertex>> prevs(H, std::vector<Vertex>(W));

    vvi d(H, vi(W, std::numeric_limits<int>::max()));
    d[s.i][s.j] = 0;

    static const auto compare = [](const Vertex& a, const Vertex& b) { return Q[a.i][a.j] > Q[b.i][b.j]; };
    auto&& pq = std::priority_queue<Vertex, std::vector<Vertex>, decltype(compare)>(compare);

    pq.emplace(s.i, s.j);
    while (!pq.empty()) {
        auto u = pq.top(); pq.pop();
        if (u == t) {
            continue;
        }
        std::set<Vertex> nexts;
        if (u.i > 0) {
            nexts.emplace(u.i - 1, u.j);
        }
        if (u.j > 0) {
            nexts.emplace(u.i, u.j - 1);
        }
        if (u.i < H-1) {
            nexts.emplace(u.i + 1, u.j);
        }
        if (u.j < W-1) {
            nexts.emplace(u.i, u.j + 1);
        }
        for (auto&& v : nexts) {
            int alt = d[u.i][u.j] + distance[getEdge(u, v)];
            if (alt < d[v.i][v.j]) {
                d[v.i][v.j] = Q[v.i][v.j] = alt;
                prevs[v.i][v.j] = u;
                pq.emplace(v.i, v.j);
            }
        }
    }
    return prevs;
}

auto getMovingPath(Vertex t, std::vector<std::vector<Vertex>>& prevs) {
    Path path;
    std::stringstream ss;
    auto&& p = prevs[t.i][t.j];
    while (p) {
        if (p.i < t.i) {
            ss << 'D';
        } else if (p.i > t.i) {
            ss << 'U';
        } else if (p.j < t.j) {
            ss << 'R';
        } else if (p.j > t.j) {
            ss << 'L';
        } else {
            abort();
        }
        t = p;
        path.emplace_back(t);
        p = prevs[t.i][t.j];
    }
    return std::make_pair(path, ss.str());
}

int main() {
    for (int i = 0; i < H-1; ++i) {
        for (int j = 0; j < W-1; ++j) {
            distance.emplace(Edge{i, j, Down}, 5000);
            distance.emplace(Edge{i, j, Right}, 5000);
        }
    }

    std::map<Path, int> pathes;
    std::map<Edge, std::set<std::shared_ptr<Path>>> pathesSelectedEdge;

    for (int i = 0; i < 1000; ++i) {
        int si, sj, ti, tj;
        std::cin >> si >> sj >> ti >> tj;
        auto&& s = Vertex{si, sj};
        auto&& t = Vertex{ti, tj};

        auto&& prevs = dijkstra(s, t);

        auto&& path = [&]{
            auto&& ret = getMovingPath(t, prevs);
            for (auto&& itr = ret.second.rbegin(); itr != ret.second.rend(); ++itr) {
                std::cout << *itr;
            }
            std::cout << std::endl;
            std::cout.flush();
            return ret.first;
        }();

        int length;
        std::cin >> length;

        pathes.emplace(path, length);
        {
            std::vector<std::shared_ptr<Edge>> edgesUsedFirst;
            int unknownLength = length;
            {
                std::unique_ptr<Vertex> prev;
                for (auto&& v : path) {
                    if (prev) {
                        auto&& e = getEdge(*prev, v);
                        if (pathesSelectedEdge[e].empty()) {
                            edgesUsedFirst.emplace_back(std::make_shared<Edge>(e));
                        } else {
                            unknownLength -= distance[e];
                        }
                    }
                    prev = std::make_unique<Vertex>(v);
                }
            }
            {
                std::unique_ptr<Vertex> prev;
                for (auto&& v : path) {
                    if (prev) {
                        auto&& e = getEdge(*prev, v);
                        assert(e);
                        pathesSelectedEdge[e].emplace(std::make_shared<Path>(path));
                    }
                    prev = std::make_unique<Vertex>(v);
                }
            }
            if (!edgesUsedFirst.empty()) {
                if (unknownLength >= 0 || (unknownLength = 0.1 * length + 0.9 * unknownLength) >= 0) {
                    int distancePerEdge = unknownLength / edgesUsedFirst.size();
                    for (auto&& e : edgesUsedFirst) {
                        distance[*e] = distancePerEdge;
                    }
                } else {
                    //std::cerr << "Calculated length is " << (length - unknownLength) / 0.9 << ", but judge said " << length << '\n';
                    int distancePerEdge = length / (path.size() - 1);
                    std::set<Path> affectedPathes;
                    std::unique_ptr<Vertex> prev;
                    for (auto&& v : path) {
                        if (prev) {
                            auto&& e = getEdge(*prev, v);
                            distance[e] = distancePerEdge;
                            for (auto&& p : pathesSelectedEdge[e]) {
                                affectedPathes.insert(*p);
                            }
                        }
                        prev = std::make_unique<Vertex>(v);
                    }
                    // std::cerr << "Affected pathes:\n";
                    // for (auto&& p : affectedPathes) {
                    //     std::cerr << "* " << p << '\n';
                    // }
                }
            } else {
                // std::cerr << "All edges are used.\n";
            }
        }
    }
    return 0;
}
