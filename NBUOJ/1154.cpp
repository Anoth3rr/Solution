#include<bits/stdc++.h>
using namespace std;
int main() {
    int a[13], target, t = -1;
    for (int i = 1; i <= 5; ++i)
        cin >> a[i];
    cin >> target;
    for (int i = 1; i <= 5; ++i)
        if (a[i] == target) {
            t = i;
            break;
        }
    if (t == -1)
        cout << "not found\n";
    else
        for (int i = 1; i <= 5; ++i)
            if (t != i)
                cout << a[i] << " ";
    return 0;
}