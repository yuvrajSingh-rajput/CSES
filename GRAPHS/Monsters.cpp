#include<bits/stdc++.h>
using ll = long long;
const long double pi=3.141592653589793238462;
const long long mod = 1e9+7;
using namespace std;

ll max(ll a, ll b) { return (a > b) ? a : b;}
ll min(ll a, ll b) { return (a < b) ? a : b;}
ll gcd(ll a, ll b) { return b == 0 ? a : gcd(b, a % b);}
ll lcm(ll a, ll b) { return (a * 1LL * b) / gcd(a, b);}

int n, m;
vector<vector<int>> g;  // matrix to store the minimum reaching time of monsters at a particular cell.
vector<pair<int, int>> monsters;
pair<int, int> si, se;
map<pair<int, int>, pair<int, int>> parent;
vector<pair<int,int>> moves = {{-1,0},{1,0},{0,1},{0,-1}}; 

bool isValid(int i, int j, int timer){
    if(i < 0 || i > n - 1 || j < 0 || j > m - 1) return false;

    if(g[i][j] <= timer) return false;

    return true;
}

bool isExcape(int i, int j, int timer){
    if(!isValid(i, j, timer)) return false;

    if(i == 0 || j == 0 || i == n - 1 || j == m - 1) return true;

    return false;
}

void preprocessMonsters(void){
    queue<pair<pair<int, int>, int>> q;
    for(auto it : monsters){
        q.push({it, 0});
    }

    while(!q.empty()){
        int cx = q.front().first.first;
        int cy = q.front().first.second;
        int timer = q.front().second;
        q.pop();
        timer ++;

        for(auto move: moves){
            int tx = cx + move.first;
            int ty = cy + move.second;

            if(isValid(tx, ty, timer)){
                g[tx][ty] = timer;
                q.push({{tx, ty}, timer});
            }
        }
    }
}

bool bfsExcape(void){
    queue<pair<pair<int, int>, int>> q;
    q.push({si, 0});
    parent[si] = {-1, -1};

    while(!q.empty()){
        int cx = q.front().first.first;
        int cy = q.front().first.second;
        int timer = q.front().second;
        q.pop(); timer++;

        for(auto move: moves){
            int tx = cx + move.first;
            int ty = cy + move.second;

            if(isExcape(tx, ty, timer)){
                parent[{tx, ty}] = {cx, cy};
                se = {tx, ty};
                return true;
            }

            if(isValid(tx, ty, timer)){
                parent[{tx, ty}] = {cx, cy};
                g[tx][ty] = timer;  // to get the shortest path only, also to avoid cell revisit.
                q.push({{tx, ty}, timer});
            }
        }
    }
    return false;
}

void solve(void){
    cin >> n >> m;
    g.resize(n);
    for(int i = 0; i < n; i++){
        g[i].resize(m);
    }
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            g[i][j] = INT_MAX;
        }
    }
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            char ch; cin >> ch;
            if(ch == '#'){
                g[i][j] = 0;
            }else if(ch == 'M'){
                g[i][j] = 0;
                monsters.push_back({i, j});
            }else if(ch == 'A'){
                si = {i, j};
                g[i][j] = 0;
            }else{
                g[i][j] = INT_MAX;
            }
        }
    }
    if(si.first == 0 || si.second == 0 || si.first == n - 1 || si.second == m - 1){
        cout << "YES\n";
        cout << "0\n";
        return;
    }

    preprocessMonsters();

    if(!bfsExcape()){
        cout << "NO\n";
        return;
    }
    
    cout << "YES\n";
    pair<int, int> temp = se;
    pair<int, int> temp1 = parent[temp];
    pair<int, int> ed = {-1, -1};
    vector<char> ans;

    while(temp1 != ed){
        if((temp.second - temp1.second) == 1 and (temp.first - temp1.first) == 0){
        ans.push_back('R');
        }
        if((temp.second - temp1.second) == -1 and (temp.first - temp1.first) == 0){
        ans.push_back('L');
        }
        if((temp.second - temp1.second) == 0 and (temp.first - temp1.first) == 1){
        ans.push_back('D');
        }
        if((temp.second - temp1.second) == 0 and (temp.first - temp1.first) == -1){
        ans.push_back('U');
        }

        temp = parent[temp];
        temp1 = parent[temp];
    }

    reverse(ans.begin(), ans.end());
    cout << ans.size() << "\n";
    for(auto it: ans) cout << it;
}

signed main(int argc, char* argv[]){
    ios_base::sync_with_stdio(false);
    #ifndef YUVRAJ_SINGH_RAJPUT_DEBUG
        cin.tie(nullptr);
        auto _clock_start = chrono::high_resolution_clock::now();
    #endif

    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    solve();

    #ifndef YUVRAJ_SINGH_RAJPUT_DEBUG
        auto _clock_end = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::milliseconds>(_clock_end-_clock_start).count();
        cerr << "Execution time: " << duration << " ms." << endl;
    #endif

    return 0;
}
