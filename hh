#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    if(!(cin>>T))return 0;
    while(T--){
        int n; cin>>n;
        vector<int>a(n+1), b(n+1);
        for(int i=1;i<=n;i++) cin>>a[i];
        for(int i=1;i<=n;i++) cin>>b[i];

        int mV = n;
        vector<int> c(mV+1,0);
        for(int i=1;i<=n;i++){ c[a[i]]++; c[b[i]]++; }
        bool ok=true;
        for(int v=1;v<=mV;v++) if(c[v]%2){ ok=false; break; }
        if(!ok){ cout<<-1<<"\n"; continue; }

        struct E{int to,id;};
        vector<vector<E>> g(mV+1);
        vector<int> eu, ev, pos;
        eu.reserve(n); ev.reserve(n); pos.reserve(n);
        int m=0;
        for(int i=1;i<=n;i++){
            if(a[i]!=b[i]){
                eu.push_back(a[i]);
                ev.push_back(b[i]);
                pos.push_back(i);
                g[a[i]].push_back({b[i], m});
                g[b[i]].push_back({a[i], m});
                ++m;
            }
        }

        if(m==0){ cout<<0<<" "<<0<<"\n"; continue; }

        for(int v=1;v<=mV;v++) if(g[v].size()%2) ok=false;
        if(!ok){ cout<<-1<<"\n"; continue; }

        vector<char> used(m,0);
        vector<int> p(mV+1,0);
        vector<pair<int,int>> op;
        op.reserve(3*n);
        ll tc=0;

        for(int s=1;s<=mV;s++){
            if(g[s].empty()) continue;
            while(p[s] < (int)g[s].size() && used[g[s][p[s]].id]) ++p[s];
            if(p[s] >= (int)g[s].size()) continue;
            vector<pair<int,int>> st;
            vector<int> circ;
            st.emplace_back(s,-1);
            while(!st.empty()){
                int v=st.back().first;
                while(p[v] < (int)g[v].size() && used[g[v][p[v]].id]) ++p[v];
                if(p[v] == (int)g[v].size()){
                    int eid = st.back().second;
                    st.pop_back();
                    if(eid != -1) circ.push_back(eid);
                } else {
                    E e = g[v][p[v]++];
                    if(used[e.id]) continue;
                    used[e.id]=1;
                    st.emplace_back(e.to, e.id);
                }
            }
            if(circ.empty()) continue;
            reverse(circ.begin(), circ.end());
            int L = circ.size();
            vector<int> verts; verts.reserve(L+1);
            int cur = s;
            verts.push_back(cur);
            for(int eid : circ){
                int u = eu[eid], vtx = ev[eid];
                int nx = (cur==u? vtx : u);
                verts.push_back(nx);
                cur = nx;
            }
            vector<int> last(mV+1, -1);
            for(int i=0;i<=(int)L;i++){
                int vr = verts[i];
                if(last[vr] != -1){
                    int prev = last[vr];
                    int stidx = prev;
                    int edidx = i-1;
                    vector<int> cyc;
                    for(int t=stidx;t<=edidx;t++) cyc.push_back(circ[t]);
                    int k = cyc.size();
                    if(k>0){
                        vector<int> pls(k);
                        for(int t=0;t<k;t++) pls[t]=pos[cyc[t]];
                        vector<int> srt=pls;
                        sort(srt.begin(), srt.end());
                        int med = srt[k/2];
                        int idx=0;
                        while(idx<k && pls[idx]!=med) ++idx;
                        if(idx==k) idx=0;
                        int hub = pls[idx];
                        for(int step=1;step<k;step++){
                            int j=(idx+step)%k;
                            int oth=pls[j];
                            op.emplace_back(hub,oth);
                            tc += ll(abs(hub-oth));
                        }
                    }
                    for(int t=prev+1;t<i;t++) last[verts[t]] = -1;
                    last[vr]=i;
                } else last[vr]=i;
            }
        }
        cout<<tc<<" "<<op.size()<<"\n";
        for(auto &pr:op) cout<<pr.first<<" "<<pr.second<<"\n";
    }
    return 0;
}
