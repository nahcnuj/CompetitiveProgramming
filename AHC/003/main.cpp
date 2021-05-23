#include <bits/stdc++.h>

using   vi = std::vector<int>;
using  vvi = std::vector<std::vector<int>>;
using vvvi = std::vector<std::vector<std::vector<int>>>;

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

Edge getEdge(Vertex from, Vertex to) {
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

const int W = 30, H = 30;

vvi Q(H, vi(W));
auto compare = [](const Vertex& a, const Vertex& b) { return Q[a.i][a.j] > Q[b.i][b.j]; };
auto&& pq = std::priority_queue<Vertex, std::vector<Vertex>, decltype(compare)>(compare);

std::map<Edge, int> distance;

using Path = std::vector<Vertex>;

auto dijkstra(Vertex s, Vertex t) {
    std::vector<std::vector<Vertex>> prevs(H, std::vector<Vertex>(W));

    vvi d(H, vi(W, std::numeric_limits<int>::max()));
    d[s.i][s.j] = 0;

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
                d[v.i][v.j] = alt;
                prevs[v.i][v.j] = u;
                Q[v.i][v.j] = alt;
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
            distance.emplace(Edge{i, j, Down}, 1000);
            distance.emplace(Edge{i, j, Right}, 1000);
        }
    }

    std::map<Path, int> pathes;
    std::map<Edge, std::set<Path>> pathesSelectedEdge;

    for (int i = 0; i < 1000; ++i) {
        int si, sj, ti, tj;
        std::cin >> si >> sj >> ti >> tj;
        auto&& s = Vertex{si, sj};
        auto&& t = Vertex{ti, tj};

        auto&& prevs = dijkstra(s, t);

        Path path;
        {
            auto&& ret = getMovingPath(t, prevs);
            path = ret.first;
            for (auto&& itr = ret.second.rbegin(); itr != ret.second.rend(); ++itr) {
                std::cout << *itr;
            }
            std::cout << std::endl;
            std::cout.flush();
        }

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
                        auto x = pathesSelectedEdge.find(e);
                        if (x == pathesSelectedEdge.end()) {
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
                        pathesSelectedEdge[e].emplace(path);
                    }
                    prev = std::make_unique<Vertex>(v);
                }
            }
            if (unknownLength >= 0) {
                if (!edgesUsedFirst.empty()) {
                    auto&& length = unknownLength / edgesUsedFirst.size();
                    for (auto&& e : edgesUsedFirst) {
                        const int threshold = 1000;
                        distance[*e] = length;
                    }
                }
            } else {
                int distancePerEdge = length / (path.size()-1);
                std::unique_ptr<Vertex> prev;
                for (auto&& v : path) {
                    if (prev) {
                        auto&& e = getEdge(*prev, v);
                        assert(e);
                        distance[e] = distancePerEdge;
                    }
                    prev = std::make_unique<Vertex>(v);
                }
            }
        }
    }
    return 0;
}
