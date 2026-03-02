#include <bits/stdc++.h>
using namespace std;
int main() {
    int v;
    cin >> v;
    for (int i = 0, x; i < 10; ++i) {
        cin >> x;
        if (v - x >= 0)
            v -= x;
    }
    cout << ((v == 0) ? "YES" : "NO") << endl;
}