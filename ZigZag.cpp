#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

int main () {
    int n, s; cin >> n >> s;
    int maTran [n][n];
    int x, y;
    ofstream out ("ZigZag.out");

    for (int duongCheo = - (n-1); duongCheo <= (n-1); duongCheo++) {
        int doLonDuongCheo = (duongCheo > 0) ? duongCheo : -duongCheo;
        int huong ;
        if ( (duongCheo + n - 1) % 2 == 0) { //di xuoong
            x = doLonDuongCheo;
            y = 0;
            huong = 1;
        }
        else {
            x = n - 1;
            y = x - doLonDuongCheo;
            huong = -1;
        }
        
        for (int i = 0; i < n - doLonDuongCheo; i++) {
            if (duongCheo < 0) maTran [x + i * huong][y + i * huong] = s++;
            else maTran [y + i * huong][x + i * huong] = s++;
        }
    }
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) out << setw(3) << maTran[i][j] << " ";
        out << endl;
    }
    
    return 0;
}