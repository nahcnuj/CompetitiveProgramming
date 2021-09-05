#include <bits/stdc++.h>

const int MAX_N = 16;

const int DR[4] = {1, 0, -1, 0};
const int DC[4] = {0, 1, 0, -1};

template<int N> class Costs {
    long long costs[N+1];

public:
    constexpr Costs() : costs() {
        for (int n = 1; n <= N; n++) {
            costs[n] = (long long)n*n*n;
        }
    }

    // cost of n-th machine
    constexpr long long operator[](size_t n) const {
        assert(1 <= n && n <= N);
        return costs[n];
    }
};
const Costs<MAX_N*MAX_N> machine_costs;

struct Vegetable {
    int r, c, s, e, v;
    Vegetable(int r_, int c_, int s_, int e_, int v_)
     : r(r_), c(c_), s(s_), e(e_), v(v_) {
    }
};

struct Action {
    std::vector<int> vs;

private:
    explicit Action(const std::vector<int>& vs_) : vs(vs_) {}

public:
    static Action pass() {
        return Action({-1});
    }

    static Action purchase(int r, int c) {
        return Action({r, c});
    }

    static Action move(int r1, int c1, int r2, int c2) {
        return Action({r1, c1, r2, c2});
    }

    explicit operator unsigned int() const {
        if (vs.size() == 1) {
            return -1;
        }
        unsigned int hash = 0;
        for (size_t i = 0; i < vs.size(); i++) {
            hash |= (vs[i] & 0xFF) << (i*8);
        }
        return hash;
    }
    friend std::ostream& operator<<(std::ostream& os, const Action& action);
};

std::ostream& operator<<(std::ostream& os, const Action& action) {
    std::copy(action.vs.cbegin(), std::prev(action.vs.cend()), std::ostream_iterator<int>(os, " "));
    os << *action.vs.rbegin();
    return os;
}

int N, M, T;
std::vector<std::vector<Vegetable>> veges_start; // veges_start[i] : vegetables appear on day i
std::vector<std::vector<Vegetable>> veges_end;   // veges_end[i] : vegetables disappear on day i

struct Game {
    std::vector<std::vector<int>> has_machine;
    std::vector<std::vector<int>> vege_values;
    int day;
    int num_machine;
    int money;

    Game() : day(0), num_machine(0), money(1) {
        has_machine.assign(N, std::vector<int>(N, 0));
        vege_values.assign(N, std::vector<int>(N, 0));
        appear_veges();
    }

    Game(const Game& game) : day(game.day), num_machine(game.num_machine), money(game.money) {
        std::copy(game.has_machine.begin(), game.has_machine.end(), std::back_inserter(has_machine));
        std::copy(game.vege_values.begin(), game.vege_values.end(), std::back_inserter(vege_values));
    }

    inline int get_next_machine_price() const {
        return machine_costs[num_machine+1];
    }

    inline bool can_buy_machine() const {
        return money >= get_next_machine_price();
    }

    void appear_veges() {
        for (const Vegetable& vege : veges_start[day]) {
            vege_values[vege.r][vege.c] = vege.v;
        }
    }

    void disappear_veges() {
        for (const Vegetable& vege : veges_end[day]) {
            vege_values[vege.r][vege.c] = 0;
        }
    }

    void purchase(int r, int c) {
        assert(!has_machine[r][c]);
        assert(can_buy_machine());
        has_machine[r][c] = 1;
        money -= get_next_machine_price();
        num_machine++;
    }

    void move(int r1, int c1, int r2, int c2) {
        assert(has_machine[r1][c1] && !has_machine[r2][c2]);
        has_machine[r1][c1] = 0;
        has_machine[r2][c2] = 1;
    }

    void proceed(const Action& action) {
        // apply
        if (action.vs.size() == 2) {
            purchase(action.vs[0], action.vs[1]);
        } else if (action.vs.size() == 4) {
            move(action.vs[0], action.vs[1], action.vs[2], action.vs[3]);
        }
        // harvest
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (has_machine[i][j] && vege_values[i][j] > 0) {
                    money += vege_values[i][j] * count_connected_machines(i, j);
                    vege_values[i][j] = 0;
                }
            }
        }

        disappear_veges();

        day++;
        if (day < T) {
            appear_veges();
        }
    }

    int simulate(const Action& action) const {
        auto copied_game = *this;
        copied_game.proceed(action);
        return copied_game.money;
    }

    int count_connected_machines(int r, int c) const {
        std::vector<std::pair<int, int>> connected_machines = {{r, c}};
        std::vector<std::vector<int>> visited(N, std::vector<int>(N, 0));
        visited[r][c] = 1;
        size_t i = 0;
        while (i < connected_machines.size()) {
            int cr = connected_machines[i].first;
            int cc = connected_machines[i].second;
            for (int dir = 0; dir < 4; dir++) {
                int nr = cr + DR[dir];
                int nc = cc + DC[dir];
                if (0 <= nr && nr < N && 0 <= nc && nc < N && has_machine[nr][nc] && !visited[nr][nc]) {
                    visited[nr][nc] = 1;
                    connected_machines.emplace_back(nr, nc);
                }
            }
            i++;
        }
        return i;
    }

    Action select_next_action() {
        sum_future_veges.assign(N, std::vector<int>(N, 0));
        evaluation_cache.clear();

        // search best place for a new machine
        for (int i = day; i < T; i++) {
            for (const Vegetable& vege : veges_start[i]) {
                sum_future_veges[vege.r][vege.c] += vege.v;
            }
        }

        static auto comp = [this](const Action& lhs, const Action& rhs) { return evaluate_action(lhs) < evaluate_action(rhs); };
        std::priority_queue<Action, std::vector<Action>, decltype(comp)> candidates(comp);
        candidates.emplace(Action::pass());

        std::vector<std::pair<int, int>> machines;
        std::vector<std::pair<int, int>> movable;
        for (int r = 0; r < N; r++) {
            for (int c = 0; c < N; c++) {
                if (has_machine[r][c]) {
                    machines.emplace_back(r, c);
                } else {
                    if (vege_values[r][c] > 0) {
                        movable.emplace_back(r, c);
                    }
                }
            }
        }

        if (can_buy_machine()) {
            for (auto&& to : movable) {
                candidates.emplace(Action::purchase(to.first, to.second));
            }
        }

        for (auto&& m : machines) {
            for (auto&& to : movable) {
                candidates.emplace(Action::move(m.first, m.second, to.first, to.second));
            }
        }

        auto action = candidates.top();

#ifndef ONLINE_JUDGE
        int i = 0;
        while (!candidates.empty()) {
            auto cand = candidates.top();
            candidates.pop();

            std::cerr << cand << ' ' << evaluate_action(cand) << "\n";
            if (++i >= 5) {
                break;
            }
        }
#endif

        return action;
    }

private:
    std::vector<std::vector<int>> sum_future_veges;
    std::map<unsigned int, int> evaluation_cache;

    int evaluate_action(const Action& action) {
        auto hash = static_cast<unsigned int>(action);
        if (auto itr = evaluation_cache.find(hash); itr != evaluation_cache.end()) {
            return itr->second;
        }
        auto evaluation = [this](auto&& vs) -> int {
            auto&& last_chances = veges_end[day];
            switch (vs.size()) {
                case 1:
                    return 1;
                case 2:
                    if (auto itr = std::find_if(last_chances.begin(), last_chances.end(), [&vs](auto vege) {
                        return vege.r == vs[0] && vege.c == vs[1];
                    }); itr == last_chances.end()) {
                        return 0;
                    };
                    return sum_future_veges[vs[0]][vs[1]] * count_connected_machines(vs[0], vs[1]);
                case 4:
                    if (auto itr = std::find_if(last_chances.begin(), last_chances.end(), [&vs](auto vege) {
                        return vege.r == vs[2] && vege.c == vs[3];
                    }); itr == last_chances.end()) {
                        return 0;
                    };
                    return sum_future_veges[vs[2]][vs[3]] * count_connected_machines(vs[2], vs[3]) - sum_future_veges[vs[0]][vs[1]] * count_connected_machines(vs[0], vs[1]);
                default: abort();
            }
        }(action.vs);
        evaluation_cache.insert(std::make_pair(hash, evaluation));
        return evaluation;
    }
};

int main() {
    std::cin >> N >> M >> T;
    veges_start.resize(T);
    veges_end.resize(T);
    for (int i = 0; i < M; i++) {
        int r, c, s, e, v;
        std::cin >> r >> c >> s >> e >> v;
        Vegetable vege(r, c, s, e, v);
        veges_start[s].push_back(vege);
        veges_end[e].push_back(vege);
    }

    Game game;
    for (int day = 0; day < T; day++) {
#ifndef ONLINE_JUDGE
        std::cerr << "Day: " << day << " ===============================\n";
#endif
        Action action = game.select_next_action();
        game.proceed(action);
        std::cout << action << "\n";
    }
}
