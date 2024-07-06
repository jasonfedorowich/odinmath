#include <iostream>
#include <vector>
using namespace std;
#define	POLYNOM1(x, a)	((a)[1]*(x)+(a)[0])
#define	POLYNOM2(x, a)	(POLYNOM1((x),(a)+1)*(x)+(a)[0])

static double   p[] = {
        1.0,
        -0.13338350006421960681e+0,
        0.34248878235890589960e-2,
        -0.17861707342254426711e-4
};

int main() {
    int y = ((((p + 1) + 1)[1] * ((2)) + ((p + 1) + 1)[0]) * (2) + (p + 1)[0]);
    int x = POLYNOM2(2, p);
    std::cout << "Hello, World!" << std::endl;
    vector<int>* v = new vector<int>;
    (*v)[0];
    delete v;
    return 0;
}
