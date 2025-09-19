#include<bits/stdc++.h>
using namespace std;
int main() {
    string s;
    cin >> s;
    for (int i = 0; i < s.size(); ++i) {
        if (s[i] >= 'a') cout << char((s[i] - 'a' + 4) % 26 + 'a');
        else cout << char((s[i] - 'A' + 4) % 26 + 'A');
    }
    cout << endl;
    return 0;
}