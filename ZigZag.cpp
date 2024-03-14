#include <iostream>
#include <fstream>
using namespace std;

void dichuyen(bool up, int &row, int &col) {
    if (up) {
        row--;
        col--;
    }
    else {
        row++;
        col++;
    }
}

int main () {
    ifstream in ("ZigZag.inp");
    ofstream out ("ZigZag.out");

    int n, s; cin >> n >> s;
    int maTran [n][n];
    bool up;

    int bienTrai = 0, bienPhai = n - 1;
    int bienTren = 0, bienDuoi = n - 1;

    int row = bienDuoi, col = bienTrai;
    maTran [row][col] = s;

    while (true) {
        if (row == bienDuoi) {
            up = true;
            col++;
            if (col > bienPhai) dichuyen(up, row, col);
            maTran [row][col] = ++s;
        } 
        else if (col == bienPhai) {
            up = true;
            row --;
            maTran [row][col] = ++s;
        }

        if (col ==  bienTrai) {
            up = false;
            row --;
            if (row < bienTren) dichuyen(up, row, col);
            maTran [row][col] = ++s;
        }
        else if (row == bienTren) {
            up = false;
            col ++;
            maTran [row][col] = ++s;
        }

        if (row == bienTren && col == bienPhai) break;

        dichuyen(up, row, col);
        maTran [row][col] = ++s;     
    }
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) cout << maTran [i][j] << "  ";
        cout << "\n";
    }
    
    in.close();
    out.close();
    return 0;
}