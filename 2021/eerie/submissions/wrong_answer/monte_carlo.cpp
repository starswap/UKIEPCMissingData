#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops") 
#pragma GCC target("avx2")

#include <bits/stdc++.h>
using namespace std;

/* Monte Carlo simulation with an average relative error of
 about 4x10^-5 on the samples */

std::random_device rd;
std::mt19937_64 gen(rd());

uint64_t shuffle_table[4] = {gen(), gen(), gen(), gen()};
uint64_t next(void) // XORshift
{
    uint64_t s1 = shuffle_table[0];
    uint64_t s0 = shuffle_table[1];
    uint64_t result = s0 + s1;
    shuffle_table[0] = s0;
    s1 ^= s1 << 23;
    shuffle_table[1] = s1 ^ s0 ^ (s1 >> 18) ^ (s0 >> 5);
    return result;
}

double rand_range(double l, double u) {
    return (double) next() / UINT64_MAX * (u - l) + l;
}

const int TOTAL_POINTS = 120000000;
const int MAX_H = 10000;
bool in_pillar[MAX_H];

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cout << fixed << setprecision(10);

    double W, L; cin >> W >> L;
    int N; cin >> N;
    
    int s, e;
    for (int i = 0, n = 0; n < N; ++n) {
        cin >> s >> e;
        while (i < s) in_pillar[i++] = false;
        while (i < e) in_pillar[i++] = true;
        in_pillar[e] = false;
    }

    // Source: (-L, 0)
    // Middle: (W, 0)
    
    double H = e / L * (L + 2 * W);

    int in_shadow = 0;
    for (int i = 0; i < TOTAL_POINTS; ++i) {
        double h = rand_range(0, H); // h_gen(gen);
        double w = rand_range(0, W); // w_gen(gen);
        bool in = false;
        
        for (int i = 0; i < 2; ++i, w = 2 * W - w) {
            double cross = (h) / (w + L) * L;
            int below = floor(cross);
            if (below < MAX_H) in |= in_pillar[below];
        }
        in_shadow += in;
    }

    double half_area = ((double) in_shadow) / TOTAL_POINTS * W * H;
    cout << 2 * half_area << endl;
    return 0;
}