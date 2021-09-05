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

    explicit operator unsigned() const {
        if (vs.size() == 1) {
            return -1;
        }
        unsigned hash = 0;
        for (size_t i = 0; i < vs.size(); i++) {
            hash |= (vs[i] & 0xF) << (i*4);
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

std::vector<std::vector<Vegetable>> veges_start; // veges_start[i] : vegetables appear on day i
std::vector<std::vector<Vegetable>> veges_end;   // veges_end[i] : vegetables disappear on day i

struct Game {
    static int N, M, T;
    int day;
    int num_machine;
    int money;
    std::vector<bool> has_machine;
    std::vector<int> vege_values;

    Game() :
        day(0),
        num_machine(0),
        money(1),
        has_machine(N*N),
        vege_values(N*N)
    {
        appear_veges();
    }

    Game(const Game& game) :
        day(game.day),
        num_machine(game.num_machine),
        money(game.money),
        has_machine(game.has_machine),
        vege_values(game.vege_values)
    {
    }

    inline int get_next_machine_price() const {
        return machine_costs[num_machine+1];
    }

    inline bool can_buy_machine() const {
        return money >= get_next_machine_price();
    }

    void appear_veges() {
        for (const Vegetable& vege : veges_start[day]) {
            vege_values[vege.r * N + vege.c] = vege.v;
        }
    }

    void disappear_veges() {
        for (const Vegetable& vege : veges_end[day]) {
            vege_values[vege.r * N + vege.c] = 0;
        }
    }

    void purchase(int r, int c) {
        assert(!has_machine[r * N + c]);
        assert(can_buy_machine());
        has_machine[r * N + c] = true;
        money -= get_next_machine_price();
        num_machine++;
    }

    void move(int r1, int c1, int r2, int c2) {
        assert(has_machine[r1 * N + c1] && !has_machine[r2 * N + c2]);
        std::swap(has_machine[r1 * N + c1], has_machine[r2 * N + c2]);
    }

    void apply(const Action& action) {
        if (action.vs.size() == 2) {
            purchase(action.vs[0], action.vs[1]);
        } else if (action.vs.size() == 4) {
            move(action.vs[0], action.vs[1], action.vs[2], action.vs[3]);
        }
    }

    void harvest() {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (has_machine[i * N + j] && vege_values[i * N + j] > 0) {
                    money += vege_values[i * N + j] * count_connected_machines(i, j);
                    vege_values[i * N + j] = 0;
                }
            }
        }
    }

    void proceed(const Action& action) {
        apply(action);
        harvest();
        disappear_veges();
        if (++day < T) {
            appear_veges();
        }
        evaluation_cache.clear();
    }

    int simulate(const Action& action) const {
        auto copied_game = *this;
        copied_game.proceed(action);
        return copied_game.money;
    }

    int count_connected_machines(int r, int c) const {
        std::vector<std::pair<int, int>> connected_machines = {{r, c}};
        std::vector<bool> visited(N*N);
        visited[r * N + c] = true;
        size_t count = 0;
        while (count < connected_machines.size()) {
            int cr = connected_machines[count].first;
            int cc = connected_machines[count].second;
            for (int dir = 0; dir < 4; dir++) {
                int nr = cr + DR[dir];
                int nc = cc + DC[dir];
                if (0 <= nr && nr < N && 0 <= nc && nc < N && has_machine[nr * N + nc] && !visited[nr * N + nc]) {
                    visited[nr * N + nc] = true;
                    connected_machines.emplace_back(nr, nc);
                }
            }
            count++;
        }
        return count;
    }

    Action select_next_action() {
        sum_future_veges.assign(N, std::vector<int>(N, 0));

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
                if (has_machine[r * N + c]) {
                    machines.emplace_back(r, c);
                } else {
                    if (vege_values[r * N + c] > 0) {
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
    std::map<unsigned, int> evaluation_cache;

    int evaluate_action(const Action& action) {
        auto hash = static_cast<unsigned>(action) | (static_cast<unsigned>(day) << 16);
        if (auto itr = evaluation_cache.find(hash); itr != evaluation_cache.end()) {
            return itr->second;
        }
        auto evaluation = [this](auto&& action) -> int {
            int score = simulate(action);

            auto&& vs = action.vs;
            if (vs.size() == 2) {
                score += sum_future_veges[vs[0]][vs[1]] * count_connected_machines(vs[0], vs[1]);
            } else if (vs.size() == 4) {
                score += sum_future_veges[vs[2]][vs[3]] * count_connected_machines(vs[2], vs[3]) - sum_future_veges[vs[0]][vs[1]] * (count_connected_machines(vs[0], vs[1]) - 1);
            }

            return score;
        }(action);
        evaluation_cache.insert(std::make_pair(hash, evaluation));
        return evaluation;
    }
};
int Game::N, Game::M, Game::T;

int main() {
    std::cin >> Game::N >> Game::M >> Game::T;
    veges_start.resize(Game::T);
    veges_end.resize(Game::T);
    for (int i = 0; i < Game::M; i++) {
        int r, c, s, e, v;
        std::cin >> r >> c >> s >> e >> v;
        Vegetable vege(r, c, s, e, v);
        veges_start[s].push_back(vege);
        veges_end[e].push_back(vege);
    }

    Game game;
    for (int day = 0; day < Game::T; day++) {
#ifndef ONLINE_JUDGE
        std::cerr << "Day: " << day << " ===============================\n";
#endif
        Action action = game.select_next_action();
        game.proceed(action);
        std::cout << action << "\n";
    }
}
