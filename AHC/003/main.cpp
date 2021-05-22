#include <bits/stdc++.h>

using   vi = std::vector<int>;
using  vvi = std::vector<std::vector<int>>;
using vvvi = std::vector<std::vector<std::vector<int>>>;

struct Vertex {
    int i, j;

    Vertex() : exists(false) {}
    Vertex(int i, int j) : i(i), j(j) {}

    inline bool operator!=(const Vertex& rhs) const { return i != rhs.i || j != rhs.j; }
    inline explicit operator bool() const { return exists; }

private:
    bool exists = true;    // on the graph.
};

const int W = 30, H = 30;

vvi Q(H, vi(W));
auto compare = [](const Vertex& a, const Vertex& b) {
    return Q[a.i][a.j] > Q[b.i][b.j];
};
auto&& pq = std::priority_queue<Vertex, std::vector<Vertex>, decltype(compare)>(compare);

vvvi distance(H, vvi(W, vi(2, 5000)));

using Path = std::vector<Vertex>;

auto dijkstra(Vertex s, Vertex t) {
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
            int alt = d[u.i][u.j];
            auto&& v = nexts[i];
            if (v.i < u.i) {
                alt += distance[v.i][v.j][0];
            } else if (v.i > u.i) {
                alt += distance[u.i][u.j][0];
            } else if (v.j < u.j) {
                alt += distance[v.i][v.j][1];
            } else {
                alt += distance[u.i][u.j][1];
            }
			if (alt < d[v.i][v.j]) {
				d[v.i][v.j] = alt;
				prevs[v.i][v.j] = u;
                pq.emplace(v.i, v.j);
			}
        }
    }
    return prevs;
}

auto getMovingPath(Vertex t, std::vector<std::vector<Vertex>> prevs) {
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
    for (int i = 0; i < 1000; ++i) {
        int si, sj, ti, tj;
        std::cin >> si >> sj >> ti >> tj;
        auto&& s = Vertex{si, sj}, t = Vertex{ti, tj};

        auto&& prevs = dijkstra(s, t);

        std::vector<Vertex> path;
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

        // TODO: update Distance
    }
    return 0;
}