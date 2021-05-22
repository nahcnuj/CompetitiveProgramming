#include <bits/stdc++.h>

struct Vertex {
    int i, j;

    Vertex(){}
    Vertex(int i, int j) : i(i), j(j) {}

    bool operator!=(const Vertex& rhs) const { return i != rhs.i || j != rhs.j; }
};

const int W = 30, H = 30;

std::vector<std::vector<int>> Q(H, std::vector<int>(W));
auto compare = [](const Vertex& a, const Vertex& b) {
    return Q[a.i][a.j] > Q[b.i][b.j];
};
auto&& pq = std::priority_queue<Vertex, std::vector<Vertex>, decltype(compare)>(compare);

std::vector<std::vector<std::vector<int>>> distance(H, std::vector<std::vector<int>>(W, std::vector<int>(2, 1000)));

auto dijkstra(Vertex s, Vertex t) {
    std::vector<std::vector<std::shared_ptr<Vertex>>> prev(H, std::vector<std::shared_ptr<Vertex>>(W));

    std::vector<std::vector<int>> d(H, std::vector<int>(W, std::numeric_limits<int>::max()));
    d[s.i][s.j] = 0;

    pq.emplace(s.i, s.j);
    while (!pq.empty()) {
        auto u = pq.top(); pq.pop();
        Vertex nexts[4];
        int i = 0;
        //if (u != t) {
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
        //}
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
				prev[v.i][v.j].reset(new Vertex{u.i, u.j});
                pq.emplace(v.i, v.j);
			}
        }
    }
    return std::make_pair(d, prev);
}

auto getMovingPath(Vertex t, std::vector<std::vector<std::shared_ptr<Vertex>>> prevs) {
    std::vector<std::shared_ptr<Vertex>> path;
    std::stringstream ss;
    auto p = std::move(prevs[t.i][t.j]);
    while (p) {
        if (p->i < t.i) {
            ss << 'D';
        } else if (p->i > t.i) {
            ss << 'U';
        } else if (p->j < t.j) {
            ss << 'R';
        } else if (p->j > t.j) {
            ss << 'L';
        } else {
            abort();
        }
        t = *p;
        path.emplace_back(std::move(p));
        p = std::move(prevs[t.i][t.j]);
    }
    return std::make_pair(std::move(path), ss.str());
}

int main() {
    for (int i = 0; i < 1000; ++i) {
        int si, sj, ti, tj;
        std::cin >> si >> sj >> ti >> tj;
        auto s = Vertex{si, sj}, t = Vertex{ti, tj};
        auto ret = dijkstra(s, t);
        auto path = getMovingPath(t, ret.second);
        for (auto&& itr = path.second.rbegin(); itr != path.second.rend(); ++itr) {
            std::cout << *itr;
        }
        std::cout << std::endl;
        std::cout.flush();

        int length;
        std::cin >> length;

        // TODO: update Distance
    }
    return 0;
}