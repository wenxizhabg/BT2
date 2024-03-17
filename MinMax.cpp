#include <fstream>
using namespace std;
using ull = unsigned long long;
int main() {
    ifstream in ("InpMinMax.txt");
    ofstream out ("OutMinMax.txt");

    ull N, M, K; in >> N >> M >> K;
    ull x, min = ULLONG_MAX, max = 0;
    for (ull i = 0; i < N; i++) {
        for (ull j = 0; j < M; j++) {
            in >> x;
            if (j == K - 1 && x > max) max = x;
            if (i == K - 1 && x < min) min = x;
        }
    } 
    out <<max << " " << min;

    in.close();
    out.close();
    return 0;
}