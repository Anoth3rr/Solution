#include<bits/stdc++.h>
using namespace std;
string s;
int main() {
    getline(cin, s);
    if (s[0] >= '0' && s[0] <= '9') {
        cout << "no\n";
        return 0;
    }
    else
        for (int i = 1; i < s.size(); ++i) {
            if (!(s[i] >= 'a' && s[i] <= 'z' || s[i] >= 'A' && s[i] <= 'Z' || s[i] >= '0' && s[i] <= '9' || s[i] == '_')) {
                cout << "no\n";
                return 0;
            }
        }
    cout << "yes\n";
    return 0;
}