#include <iostream>
#include <fstream>
using namespace std;

int main() {
    ifstream in ("inpFibo.txt");
    ofstream out ("outFibo.txt");

    int n; in >> n;
    int danhSach[1000];
    
    for (int i = 0; i < n; i++) {
        int x, y; in >> x >> y;
        int soLuong = 0;
        int soDau = 1, soSau = 1, soFibo = soDau + soSau;
        
        while (soFibo < y) {
            soDau = soSau;
            soSau = soFibo;
            soFibo = soDau + soSau;
            if (x < soFibo && soFibo < y ) {
                soLuong ++;
                danhSach[soLuong] = soFibo;
            }
        }
        
        if (soLuong > 0) {
            out << "Có " << soLuong << " số thuộc dãy Fibonaci trong (" << x << ", " << y <<") là ";
            for (int j = 1; j <= soLuong; j++) out << danhSach[j] << " ";
            out << endl;
        } 
        else out << "0" << endl;
    }

    in.close();
    out.close();
    return 0;
}
