#include <bits/stdc++.h>

const int MAX_T = 1000;
const int MAX_N = 16;

const int DR[4] = {1, 0, -1, 0};
const int DC[4] = {0, 1, 0, -1};

template<int N> class Costs {
    long long costs[N+1];

public:
    constexpr Costs() : costs() {
        for (int n = 1; n <= N; n++) {
            costs[n] = 1ll * n*n*n;
        }
    }

    // cost of n-th harvester
    inline constexpr long long operator[](size_t n) const {
        assert(1 <= n && n <= N);
        return costs[n];
    }
};
const Costs<MAX_N*MAX_N> harvester_costs;

template<int T> class ExpectedValues {
    int values[T];

public:
    constexpr ExpectedValues() : values() {
        for (int t = 0; t < T; t++) {
            values[t] = static_cast<int>(std::pow(2.0, 1.0 + t / 100.0) / 2);
        }
    }

    inline constexpr int operator[](size_t t) const {
        assert(0 <= t && t < T);
        return values[t];
    }
};
const ExpectedValues<MAX_T> expected_values;

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
    inline static Action pass() {
        return Action({-1});
    }

    inline static Action buy(int r, int c) {
        return Action({r, c});
    }

    inline static Action move(int r1, int c1, int r2, int c2) {
        return Action({r1, c1, r2, c2});
    }

    inline bool is_pass()     const { return vs.size() == 1; }
    inline bool is_buy()      const { return vs.size() == 2; }
    inline bool is_move()     const { return vs.size() == 4; }

    explicit operator unsigned() const {
        if (is_pass()) {
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

struct Game {
    static int N, M, T;
    static std::vector<std::vector<int>> veges_diff;    // veges_diff[day][r * N + c]

    int day = 0;
    int money = 1;
    std::vector<std::pair<int,int>> harvesters;
    std::vector<bool> has_harvester;
    std::vector<int> vege_values;

private:
    std::vector<std::vector<int>> sum_future_veges;
    std::map<unsigned, int> evaluation_cache;

public:
    Game() {
#ifndef ONLINE_JUDGE
        assert(N > 0 && M > 0 && T > 0);
        assert(veges_diff.size() == static_cast<size_t>(T));
        for (auto&& diff : veges_diff) assert(diff.size() == static_cast<size_t>(N*N));
#endif

        has_harvester.resize(N*N);
        vege_values.resize(N*N);

        appear_veges();
    }

    inline bool is_over() const { return day >= T; }

    inline int num_harvester() const { return harvesters.size(); }

    void proceed(const Action& action) {
        apply(action);
        harvest();
        disappear_veges();
        if (++day < T) {
            appear_veges();
        }
        evaluation_cache.clear();
    }

    Game simulate(const Action& action) const {
        auto copied_game = *this;
        copied_game.proceed(action);
        return copied_game;
    }

    Action select_next_action() {
        static auto comp = [this](const Action& lhs, const Action& rhs) {
            return evaluate_action(lhs) < evaluate_action(rhs);
        };
        std::priority_queue<Action, std::vector<Action>, decltype(comp)> candidates(comp);

        if (num_harvester() == 0) {
            generate_buy_actions(candidates);
        } else {
            generate_move_actions(candidates);
        }

        if (candidates.empty()) {
            return Action::pass();
        }

        auto action = candidates.top();

#ifndef ONLINE_JUDGE
        int i = 0;
        while (!candidates.empty()) {
            auto cand = candidates.top();
            candidates.pop();

            std::cerr << cand << ' ' << evaluate_action(cand) << "\n";
            if (++i >= 10) {
                break;
            }
        }
        std::cerr << candidates.size() << " candidates\n";
        std::cerr << "SELECTED " << action << ' ' << evaluate_action(action) << '\n';
#endif

        return action;
    }

private:
    inline int get_next_harvester_cost() const { return harvester_costs[num_harvester()+1]; }
    inline bool can_buy_harvester() const { return money >= get_next_harvester_cost(); }

    void appear_veges() {
        auto&& diff = veges_diff[day];
        for (int i = 0; i < N*N; i++) {
            if (vege_values[i] <= 0) {
                vege_values[i] += std::max(diff[i], 0);
            }
        }
    }

    void disappear_veges() {
        auto&& diff = veges_diff[day];
        for (int i = 0; i < N*N; i++) {
            if (vege_values[i] > 0) {
                vege_values[i] += std::min(diff[i], 0);
            }
        }
    }

    void buy(int r, int c) {
#ifndef ONLINE_JUDGE
        assert(can_buy_harvester());
        assert(!has_harvester[r * N + c]);
#endif

        money -= get_next_harvester_cost();

        has_harvester[r * N + c] = true;
        harvesters.emplace_back(r, c);
    }

    void move(int r1, int c1, int r2, int c2) {
#ifndef ONLINE_JUDGE
        assert(has_harvester[r1 * N + c1] && !has_harvester[r2 * N + c2]);
#endif

        std::swap(has_harvester[r1 * N + c1], has_harvester[r2 * N + c2]);

        auto itr = std::find(harvesters.begin(), harvesters.end(), std::make_pair(r1, c1));
        itr->first = r2;
        itr->second = c2;
    }

    void apply(const Action& action) {
        if (action.is_buy()) {
            buy(action.vs[0], action.vs[1]);
            return;
        }
        if (action.is_move()) {
            move(action.vs[0], action.vs[1], action.vs[2], action.vs[3]);
            return;
        }
    }

    void harvest() {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (has_harvester[i * N + j] && vege_values[i * N + j] > 0) {
                    money += vege_values[i * N + j] * count_connected_harvesters(i, j);
                    vege_values[i * N + j] = 0;
                }
            }
        }
    }

    int count_connected_harvesters(int r, int c) const {
        std::vector<std::pair<int, int>> connected_harvesters = {{r, c}};
        std::vector<bool> visited(N*N);
        visited[r * N + c] = true;
        size_t count = 0;
        while (count < connected_harvesters.size()) {
            int cr = connected_harvesters[count].first;
            int cc = connected_harvesters[count].second;
            for (int dir = 0; dir < 4; dir++) {
                int nr = cr + DR[dir];
                int nc = cc + DC[dir];
                if (0 <= nr && nr < N && 0 <= nc && nc < N && has_harvester[nr * N + nc] && !visited[nr * N + nc]) {
                    visited[nr * N + nc] = true;
                    connected_harvesters.emplace_back(nr, nc);
                }
            }
            count++;
        }
        return count;
    }

    int evaluate_action(const Action& action) {
        auto hash = static_cast<unsigned>(action) | (static_cast<unsigned>(day) << 16);
        if (auto itr = evaluation_cache.find(hash); itr != evaluation_cache.end()) {
            return itr->second;
        }

        auto evaluation = evaluate_action_without_cache(action);
        evaluation_cache.insert(std::make_pair(hash, evaluation));
        return evaluation;
    }

    int evaluate_action_without_cache(const Action& action) const {
        int actual_score_diff = simulate(action).money - money;

        int expected_score = 0;

        return actual_score_diff + expected_score;
    }

    template<typename value_t, typename container_t, typename comparator_t>
    void generate_move_actions(std::priority_queue<value_t, container_t, comparator_t>& queue) const {
        std::vector<Action> actions;
        actions.reserve(N*N*N);
        for (int r = 0; r < N; r++) {
            for (int c = 0; c < N; c++) {
                if (has_harvester[r * N + c]) {
                    continue;
                }
                for (auto&& harvester : harvesters) {
                    queue.emplace(Action::move(harvester.first, harvester.second, r, c));
                }
            }
        }
    }

    template<typename value_t, typename container_t, typename comparator_t>
    void generate_buy_actions(std::priority_queue<value_t, container_t, comparator_t>& queue) const {
#ifndef ONLINE_JUDGE
        assert(can_buy_harvester());
#endif

        std::vector<Action> actions;
        actions.reserve(N*N);
        for (int r = 0; r < N; r++) {
            for (int c = 0; c < N; c++) {
                if (has_harvester[r * N + c]) {
                    continue;
                }
                queue.emplace(Action::buy(r, c));
            }
        }
    }

    inline int future_window() const {
#ifdef FUTURE_WINDOW
        return static_cast<int>(FUTURE_WINDOW);
#else
        return static_cast<int>(std::sqrt(day));
#endif
    }

    inline int candidates_cutoff_rank(size_t size) const {
#ifdef CUTOFF_RANK
        return std::min(size, static_cast<size_t>(CUTOFF_RANK));
#else
        return size;
#endif
    }

    inline int single_harvester_term() const {
#ifdef SINGLE_HARVESTER_TERM
        return static_cast<int>(SINGLE_HARVESTER_TERM);
#else
        return 1;
#endif
    }

    inline int ending_term() const {
#ifdef ENDING_TERM
        return static_cast<int>(ENDING_TERM);
#else
        return 1000;
#endif
    }
};
int Game::N, Game::M, Game::T;
std::vector<std::vector<int>> Game::veges_diff;

int main() {
    std::cin >> Game::N >> Game::M >> Game::T;

    Game::veges_diff = std::vector<std::vector<int>>(Game::T, std::vector<int>(Game::N * Game::N));
    for (int i = 0; i < Game::M; i++) {
        int r, c, s, e, v;
        std::cin >> r >> c >> s >> e >> v;
        Vegetable vege(r, c, s, e, v);
        Game::veges_diff[s][r * Game::N + c] = +v;
        Game::veges_diff[e][r * Game::N + c] = -v;
    }

    Game game;

    while (!game.is_over()) {
#ifndef ONLINE_JUDGE
        std::cerr << "Day: " << game.day << " Money: " << game.money << " Harvester: " << game.num_harvester() << " ===============================\n";
#endif
        Action action = game.select_next_action();
        game.proceed(action);
        std::cout << action << "\n";
    }
}
