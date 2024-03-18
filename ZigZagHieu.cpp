#include <fstream>
using namespace std;

int main() {
    ifstream in ("ZigZag.inp");
    ofstream out ("ZigZag.out");

    int n, s; in >>n >> s;
    int maTran [n][n];
    int f = s + n*n - 1;
    int i = n - 1, j = 0, d = 1;
    bool bor = false; 

    while (s <= f) {
        maTran [i][j] = s++;
        if ((i == n - 1 || i == 0) && j < n - 1 && !bor) {
            j++;
            d *= -1;
            bor = true;
        }
        else if ((j == 0 || j == n - 1) && !bor) {
            i--;
            d *= -1;
            bor = true;
        }
        else {
            i += d;
            j += d;
            bor = false;
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) out << maTran [i][j] << " ";
        out << endl;
    }

    in.close();
    out.close();
    return 0;
}
