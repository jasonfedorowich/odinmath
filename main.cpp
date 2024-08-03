#include <iostream>
#include <vector>
using namespace std;

int main() {
    std::cout << "Hello, World!" << std::endl;
    vector<int>* v = new vector<int>;
    (*v)[0];
    delete v;
    return 0;
}
