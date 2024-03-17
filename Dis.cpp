#include <fstream>
#define bp(x) x * x
using namespace std;
using ull = unsigned long long;

struct vec {
    int x, y, z;
};

ull dis (vec a, vec b) {
    return bp(a.x - b.x) + bp(a.y - b.y) + bp(a.z - b.z);
}

int main () {
    ifstream in ("InpDis.txt");
    ofstream out ("OutDis.txt");

    vec listVec[1000]; ull min = ULLONG_MAX;
    ull count = 0; ull id1, id2;
    while (in.eof() == false) {
        in >> listVec[count].x >> listVec[count].y >> listVec[count].z;
        count++;

        for (ull i = 0; i < count; i++) if (dis(listVec[i], listVec[count]) < min) {
            min = dis(listVec[i], listVec[count]);
            id1 = i; id2 = count;
        }
    }

    out << "(" << listVec[id1].x << "," << listVec[id1].y << "," << listVec[id1].z << ") ";
    out << "(" << listVec[id2].x << "," << listVec[id2].y << "," << listVec[id2].z << ")";
    in.close();
    out.close();
}
