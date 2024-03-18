#include <fstream>
using namespace std;

struct vecto {
    int x, y, huong;
};

int main () {
    ifstream in ("ZigZag.inp");
    ofstream out ("ZigZag.out");

    int n, s; in >> n >> s;
    int maTran [n][n];
    vecto vec;

    for (int duongCheo = - (n-1); duongCheo <= (n-1); duongCheo++) {
        int doLonDuongCheo = (duongCheo > 0) ? duongCheo : -duongCheo;

        if ((duongCheo + n - 1) % 2 == 0) vec = {doLonDuongCheo, 0, 1};
        else vec = {n - 1, n - 1 - doLonDuongCheo, -1};
        
        for (int i = 0; i < n - doLonDuongCheo; i++)
            if (duongCheo < 0) maTran [vec.x + i * vec.huong][vec.y + i * vec.huong] = s++;
            else maTran [vec.y + i * vec.huong][vec.x + i * vec.huong] = s++;
    }
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) out << maTran[i][j] << " ";
        out << endl;
    }
    
    in.close();
    out.close();
    return 0;
}
