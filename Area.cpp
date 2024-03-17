#include <fstream>
using namespace std;
using ull = unsigned long long;

int main() {
    ifstream in ("AreaInp.txt");
    ofstream out ("AreaOut.txt");

    while (in.eof() == false) {
        int x; in >> x;

        if (x == 0) {
            ull a; in >> a;
            out << a * a << endl; 
        }
        
        if (x == 1) {
            ull a, b, h; in >> a >> b >> h;
            out << (a + b) * h / 2 << endl;    
        }

    }

    in.close();
    out.close();
    return 0;
}