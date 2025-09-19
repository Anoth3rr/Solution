#include<bits/stdc++.h>
using namespace std;
int main() {
    string s;
    int h[11] = {0};
    getline(cin, s);
    for (int i = 0; i < s.size(); ++i)
        if ('0' <= s[i] && s[i] <= '9')
            h[s[i] - '0']++;
    for (int i = 0; i < 10; ++i)
        if (h[i])
            cout << i << ":" << h[i] << endl;
    return 0;
}