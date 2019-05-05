    #include <bits/stdc++.h>

    using namespace std;

    int main() {
        int H, W, N;
        cin >> H >> W >> N;
        
        int sx, sy;
        cin >> sy >> sx;

        string S, T;
        cin >> S >> T;

        int tu = 0, td = 0, tl = 0, tr = 0, au = 0, ad = 0, al = 0, ar = 0;
        for (int i = 0; i < N; ++i) {
            if (S[i] == 'L') ++tl;
            if (S[i] == 'R') ++tr;
            if (S[i] == 'U') ++tu;
            if (S[i] == 'D') ++td;
            int uy = sy - tu, lx = sx - tl, dy = sy + td, rx = sx + tr;
            if (uy + ad <= 0 || lx + ar <= 0 || H < dy - au || W < rx - al) {
                cout << "NO" << endl;
                return 0;
            }
            if (T[i] == 'L' && 1 < sx + tr - al) ++al;
            if (T[i] == 'R' && sx - tl + ar < W) ++ar;
            if (T[i] == 'U' && 1 < sy + td - au) ++au;
            if (T[i] == 'D' && sy - tu + ad < H) ++ad;
        }

        cout << "YES" << endl;

        return 0;
    }