#include "Vector.hpp"
#include "../common.hpp"

void ex1() {
    using namespace std;
    using T = int;
    constexpr size_t d = 10;

    Vector<T> v1(d);
    for (size_t i = 0; i < d; i++)
        v1[i] = T(i);
    cout << "Wektor v1: " << v1 << endl;

    Vector<T> v2 = v1 + v1;
    cout << "Wektor v2: " << v2 << endl;

    cout << "v1 == v1: " << (v1 == v1 ? "TAK" : "NIE") << endl;
    cout << "v1 != v1: " << (v1 != v1 ? "TAK" : "NIE") << endl;
    cout << "v1 == v2: " << (v1 == v2 ? "TAK" : "NIE") << endl;
    cout << "v1 != v2: " << (v1 != v2 ? "TAK" : "NIE") << endl;
    Vector<T> v3(5);
    cout << "Wektor v3: " << v3 << endl;
    cout << "v1 == v3: " << (v1 == v3 ? "TAK" : "NIE") << endl;
    v3 = v1;
    cout << "Wektor v3: " << v3 << endl;
    cout << "v1 == v3: " << (v1 == v3 ? "TAK" : "NIE") << endl;
}

int main() {
    menu m{{{1, ex1}}};
    m.run();
    return 0;
}
