#include <bits/stdc++.h>
using namespace std;

int main() {
    cout << fixed << setprecision(2);

    int n, x, y, cnt = 0;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> x >> y;
        if (y > x)
            cnt++;
    }

    cout << 100.0 * cnt / n << endl;

    return 0;
}