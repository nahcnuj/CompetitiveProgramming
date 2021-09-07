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

    // cost of n-th machine
    inline constexpr long long operator[](size_t n) const {
        assert(1 <= n && n <= N);
        return costs[n];
    }
};
const Costs<MAX_N*MAX_N> machine_costs;

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

    inline static Action purchase(int r, int c) {
        return Action({r, c});
    }

    inline static Action move(int r1, int c1, int r2, int c2) {
        return Action({r1, c1, r2, c2});
    }

    inline bool is_pass()     const { return vs.size() == 1; }
    inline bool is_purchase() const { return vs.size() == 2; }
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
    int N, M, T;
    int day;
    int num_machine;
    int money;
    std::vector<bool> has_machine;
    std::vector<int> vege_values;

    Game() : day(0), num_machine(0), money(1) {}

    Game(int N_, int M_, int T_) : Game() {
        N = N_;
        M = M_;
        T = T_;

        has_machine.resize(N*N);
        vege_values.resize(N*N);
    }

    Game(const Game& game) : Game(game.N, game.M, game.T) {
        day         = game.day;
        num_machine = game.num_machine;
        money       = game.money;
        has_machine = game.has_machine;

        veges_start = game.veges_start;
        veges_end   = game.veges_end;
        vege_values = game.vege_values;

        machines    = game.machines;
        num_waiting = game.num_waiting;

        sum_future_veges = game.sum_future_veges;
    }

    void init(const std::vector<std::vector<Vegetable>>& veges_start, const std::vector<std::vector<Vegetable>>& veges_end) {
        this->veges_start = veges_start;
        this->veges_end   = veges_end;

        appear_veges();
    }

    inline bool is_over() const { return day >= T; }

    inline int get_next_machine_price() const { return machine_costs[num_machine+1]; }

    inline bool can_buy_machine() const { return money >= get_next_machine_price(); }

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

        machines.emplace_back(r, c);
        num_waiting = num_machine;
    }

    void move(int r1, int c1, int r2, int c2) {
        assert(has_machine[r1 * N + c1] && !has_machine[r2 * N + c2]);
        std::swap(has_machine[r1 * N + c1], has_machine[r2 * N + c2]);

        auto itr = std::find(machines.begin(), machines.end(), std::make_pair(r1, c1));
        itr->first = r2;
        itr->second = c2;
        num_waiting--;
        if (num_waiting < 0) {
            num_waiting = num_machine;
        }
    }

    void apply(const Action& action) {
        if (action.is_purchase()) {
            purchase(action.vs[0], action.vs[1]);
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
        static auto comp = [this](const Action& lhs, const Action& rhs) {
            return lhs.is_pass() || !rhs.is_pass() || evaluate_action(lhs) < evaluate_action(rhs);
        };
        std::priority_queue<Action, std::vector<Action>, decltype(comp)> candidates(comp, generate_candidates());
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
    static std::vector<std::vector<Vegetable>> veges_start; // veges_start[i] : vegetables appear on day i
    static std::vector<std::vector<Vegetable>> veges_end;   // veges_end[i] : vegetables disappear on day i
    
    std::vector<std::pair<int,int>> machines;
    int num_waiting;

    std::vector<std::vector<int>> sum_future_veges;
    std::map<unsigned, int> evaluation_cache;

    int evaluate_action(const Action& action) {
        auto hash = static_cast<unsigned>(action) | (static_cast<unsigned>(day) << 16);
        if (auto itr = evaluation_cache.find(hash); itr != evaluation_cache.end()) {
            return itr->second;
        }

        auto evaluation = evaluate_action_without_cache(action);
        evaluation_cache.insert(std::make_pair(hash, evaluation));
        return evaluation;
    }

    int evaluate_action_without_cache(const Action& action) {
        int actual_score_diff = simulate(action) - money;

        int expected_score = 0;

        return actual_score_diff + std::max(expected_score, actual_score_diff);
    }

    std::vector<Action> generate_candidates() const {
        std::vector<Action> candidates;
        candidates.emplace_back(Action::pass());
        return candidates;
    }

    bool alive_vegetable_tomorrow(int r, int c) const {
        if (vege_values[r * N + c] == 0) {
            return false;
        }
        auto&& dead_veges = veges_end[day+1];
        auto itr = std::find_if(dead_veges.begin(), dead_veges.end(), [r,c](const Vegetable& vege) {
            return vege.r == r && vege.c == c;
        });
        return itr != dead_veges.end();
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
std::vector<std::vector<Vegetable>> Game::veges_start;
std::vector<std::vector<Vegetable>> Game::veges_end;

int main() {
    int N, M, T;
    std::cin >> N >> M >> T;
    Game game(N, M, T);

    std::vector<std::vector<Vegetable>> veges_start(T);
    std::vector<std::vector<Vegetable>> veges_end(T);
    for (int i = 0; i < M; i++) {
        int r, c, s, e, v;
        std::cin >> r >> c >> s >> e >> v;
        Vegetable vege(r, c, s, e, v);
        veges_start[s].push_back(vege);
        veges_end[e].push_back(vege);
    }

    game.init(veges_start, veges_end);

    while (!game.is_over()) {
#ifndef ONLINE_JUDGE
        std::cerr << "Day: " << game.day << " Money: " << game.money << " Harvester: " << game.num_machine << " ===============================\n";
#endif
        Action action = game.select_next_action();
        game.proceed(action);
        std::cout << action << "\n";
    }
}
