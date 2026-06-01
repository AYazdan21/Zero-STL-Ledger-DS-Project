#include <iostream>
#include <iomanip>
using namespace std;

static const int MAXN = 1000000;

struct Node {
    long long bal, ctal, cbed;
    int child[27], child2[27];
};

Node nd[MAXN];
int nodeCount;
int rishe;
long long hp[2][300010];
string sst[2][300010];
int cnt[2];

int newNode(){
    nodeCount++;
    nd[nodeCount].bal = 0;
    nd[nodeCount].ctal = 0;
    nd[nodeCount].cbed = 0;
    for(int i=0; i<27; i++){
        nd[nodeCount].child[i] = 0;
        nd[nodeCount].child2[i] = 0;
    }
    return nodeCount;
}

int sakht_asli(const string &s){
    int cur = rishe;
    for(int i=0; i<(int)s.size(); i++){
        int c = s[i] - 'a';
        if(!nd[cur].child[c]){
            nd[cur].child[c] = newNode();
        }
        cur = nd[cur].child[c];
    }
    return cur;
}

int sakht_faree(int idx, const string &s, long long a){
    int cur = idx;
    for(int i=0; i<(int)s.size(); i++){
        int c = s[i] - 'a';
        if(!nd[cur].child2[c]){
            nd[cur].child2[c] = newNode();
        }
        cur = nd[cur].child2[c];
    }
    if(nd[cur].bal > 0) nd[idx].cbed--;
    if(nd[cur].bal < 0) nd[idx].ctal--;
    nd[cur].bal += a;
    if(nd[cur].bal > 0) nd[idx].cbed++;
    if(nd[cur].bal < 0) nd[idx].ctal++;
    nd[idx].bal += a;
    return cur;
}

bool cmp_str(const string &a, const string &b){
    int m = (a.size() < b.size() ? a.size() : b.size());
    for(int i=0; i<m; i++){
        if(a[i]<b[i]) return true;
        if(a[i]>b[i]) return false;
    }
    return a.size()<b.size();
}

void swapLL(long long &x, long long &y){
    long long t = x; x = y; y = t;
}

void swapS(string &x, string &y){
    string t = x; x = y; y = t;
}

bool compare(int z, int i, int j){
    if(hp[z][i] < hp[z][j]) return (1 - z);
    if(hp[z][i] > hp[z][j]) return z;
    return cmp_str(sst[z][i], sst[z][j]);
}

void heapify(int z, int idx){
    while(true){
        int l = idx*2, r = l+1, best = idx;
        if(l <= cnt[z] && compare(z, l, best)) best = l;
        if(r <= cnt[z] && compare(z, r, best)) best = r;
        if(best == idx) break;
        swapLL(hp[z][idx], hp[z][best]);
        swapS(sst[z][idx], sst[z][best]);
        idx = best;
    }
}

void add(int z, long long val, const string &s){
    cnt[z]++;
    hp[z][cnt[z]] = val;
    sst[z][cnt[z]] = s;
    int idx = cnt[z];
    while(idx>1 && compare(z, idx, idx/2)){
        swapLL(hp[z][idx], hp[z][idx/2]);
        swapS(sst[z][idx], sst[z][idx/2]);
        idx /= 2;
    }
}

long long getTop(int z){
    while(cnt[z]>0){
        int topIdx = sakht_asli(sst[z][1]);
        if(nd[topIdx].bal == hp[z][1]) break;
        swapLL(hp[z][1], hp[z][cnt[z]]);
        swapS(sst[z][1], sst[z][cnt[z]]);
        hp[z][cnt[z]] = 0;
        sst[z][cnt[z]] = "";
        cnt[z]--;
        heapify(z,1);
    }
    if(cnt[z] == 0) return 0;
    return hp[z][1];
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    nodeCount = 0;
    rishe = newNode();
    int q; cin >> q;
    while(q--){
        int t; cin >> t;
        if(t==1){
            string A,B,C; cin >> A >> B >> C;
            long long val=0;
            for(int i=0;i<(int)C.size();i++){
                if(C[i]=='.') continue;
                val=val*10+(C[i]-'0');
            }
            int idxA=sakht_asli(A);
            int idxB=sakht_asli(B);
            sakht_faree(idxA,B,-val);
            sakht_faree(idxB,A,val);
            add(0,nd[idxA].bal,A);
            add(1,nd[idxA].bal,A);
            add(0,nd[idxB].bal,B);
            add(1,nd[idxB].bal,B);
        }
        if(t==2){
            long long x=getTop(1);
            if(x==0) cout<<"-1\n"; 
            else cout<<sst[1][1]<<'\n';
        }
        if(t==3){
            long long x=getTop(0);
            if(x==0) cout<<"-1\n";
            else cout<<sst[0][1]<<'\n';
        }
        if(t==4){
            string s; cin>>s;
            cout<<nd[sakht_asli(s)].cbed<<"\n";
        }
        if(t==5){
            string s; cin>>s;
            cout<<nd[sakht_asli(s)].ctal<<"\n";
        }
        if(t==6){
            string a,b; cin>>a>>b;
            int idxA=sakht_asli(a);
            int idxC=sakht_faree(idxA,b,0);
            cout<<fixed<<setprecision(2)<<(long double)nd[idxC].bal/100.0<<"\n";
        }
    }
}
