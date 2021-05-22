#include <bits/stdc++.h>

using   vi = std::vector<int>;
using  vvi = std::vector<std::vector<int>>;
using vvvi = std::vector<std::vector<std::vector<int>>>;

struct Vertex {
    int i, j;

    Vertex() : exists(false) {}
    Vertex(int i, int j) : i(i), j(j) {}

    inline bool operator==(const Vertex& rhs) const { return !(*this != rhs); }
    inline bool operator!=(const Vertex& rhs) const { return i != rhs.i || j != rhs.j; }
    inline bool operator<(const Vertex& rhs) const { return i < rhs.i && j < rhs.j; }

    inline explicit operator bool() const { return exists; }

private:
    bool exists = true;    // on the graph.
};

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

    inline bool operator==(const Edge& rhs) const { return vertex == rhs.vertex && direction == rhs.direction; }
    inline bool operator<(const Edge& rhs) const { return vertex < rhs.vertex && direction < rhs.direction; }

    inline explicit operator bool() const { return exists; }

private:
    bool exists = true;    // on the graph.
};

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
auto compare = [](const Vertex& a, const Vertex& b) {
    return Q[a.i][a.j] > Q[b.i][b.j];
};
auto&& pq = std::priority_queue<Vertex, std::vector<Vertex>, decltype(compare)>(compare);

std::map<Edge, int> distance;

using Path = std::vector<Vertex>;

auto dijkstra(Vertex s, Vertex t) {
    // std::cerr << "dijkstra" << std::endl;
    std::vector<std::vector<Vertex>> prevs(H, std::vector<Vertex>(W));

    vvi d(H, vi(W, std::numeric_limits<int>::max()));
    d[s.i][s.j] = 0;

    pq.emplace(s.i, s.j);
    while (!pq.empty()) {
        auto u = pq.top(); pq.pop();
        Vertex nexts[4];
        int i = 0;
        if (u != t) {
            if (u.i > 0) {
                nexts[i++] = {u.i - 1, u.j};
            }
            if (u.j > 0) {
                nexts[i++] = {u.i, u.j - 1};
            }
            if (u.i < H-1) {
                nexts[i++] = {u.i + 1, u.j};
            }
            if (u.j < W-1) {
                nexts[i++] = {u.i, u.j + 1};
            }
        }
        while (--i >= 0) {
            auto&& v = nexts[i];
            int alt = d[u.i][u.j] + distance[getEdge(u, v)];
			if (alt < d[v.i][v.j]) {
				d[v.i][v.j] = alt;
				prevs[v.i][v.j] = u;
                pq.emplace(v.i, v.j);
			}
        }
    }
    // prevs[s.i][s.j] = Vertex{};
    return prevs;
}

auto getMovingPath(Vertex t, std::vector<std::vector<Vertex>> prevs) {
    // std::cerr << "getMovingPath" << std::endl;
    Path path;
    std::stringstream ss;
    auto&& p = prevs[t.i][t.j];
    while (p) {
        // std::cerr << p.i << p.j << std::endl;
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
    for (int i = 0; i < H; ++i) {
        for (int j = 0; j < W; ++j) {
            distance.emplace(Edge{i, j, Down}, 5000);
            distance.emplace(Edge{i, j, Right}, 5000);
        }
    }

    std::map<Path, int> pathes;
    std::map<Edge, std::set<Path>> pathesSelectedEdge;

    for (int i = 0; i < 1000; ++i) {
        // std::cerr << "Query " << i+1 << std::endl;
        int si, sj, ti, tj;
        std::cin >> si >> sj >> ti >> tj;
        auto&& s = Vertex{si, sj}, t = Vertex{ti, tj};

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
            std::unique_ptr<Vertex> prev;
            for (auto&& v : path) {
                // std::cerr << unknownLength << std::endl;
                if (prev) {
                    auto&& e = getEdge(*prev, v);
                    // std::cerr << '(' << e.vertex.i << ',' << e.vertex.j << ")-" << e.direction << "->\n";
                    // std::cerr << '(' << prev->i << ',' << prev->j << ")-(" << v.i << ',' << v.j << ")?\n";
                    auto x = pathesSelectedEdge.find(e);
                    if (x == pathesSelectedEdge.begin() || x == pathesSelectedEdge.end() || x == --pathesSelectedEdge.end()) {
                        edgesUsedFirst.emplace_back(std::make_shared<Edge>(e));
                    } else {
                        // std::cerr << '(' << x->first.vertex.i << ',' << x->first.vertex.j << ")-" << x->first.direction << "->\n";
                        // for (auto&& p : x->second) {
                        //     for (auto&& v : p) {
                        //         std::cerr << '(' << v.i << ',' << v.j << ")-";
                        //     }
                        //     std::cerr << '\n';
                        // }
                        // std::cerr << distance[e] << std::endl;
                        unknownLength -= distance[e];
                        assert(unknownLength >= 0);
                    }
                }
                prev = std::make_unique<Vertex>(v);
            }
            for (auto&& v : path) {
                if (prev) {
                    // std::cerr << '(' << prev->i << ',' << prev->j << ")-(" << v.i << ',' << v.j << ")!\n";
                    auto&& e = getEdge(*prev, v);
                    assert(e);
                    pathesSelectedEdge[e].emplace(path);
                    // std::cerr << '(' << e.vertex.i << ',' << e.vertex.j << ")-" << e.direction << "->\n";
                    // for (auto&& v : path) {
                    //     std::cerr << '(' << v.i << ',' << v.j << ")-";
                    // }
                    // std::cerr << '\n';
                }
                prev = std::make_unique<Vertex>(v);
            }
            if (!edgesUsedFirst.empty()) {
                auto&& length = unknownLength / edgesUsedFirst.size();
                for (auto&& e : edgesUsedFirst) {
                    //std::cerr << e->vertex.i << ',' << e->vertex.j << ',' << e->direction <<' '<< length << std::endl;
                    distance[*e] = length;
                }
            }
        }
    }
    return 0;
}
