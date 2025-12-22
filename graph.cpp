#include<bits/stdc++.h>
#define ll long long
#define ALL(x) (x).begin(), (x).end()
#define R_ALL(x) (x).rbegin(), (x).rend()
using namespace std;

const ll MOD = 1e9 + 7;


//ALL GRAPH METHODS
vector<vector<int>> dir = {{0,1},{0,-1},{1,0},{-1,0}};
string d = "RLDU";

void dfs_grid(int r,int c,vector<string>& a, vector<vector<int>>& v, int& n, int& m){
    v[r][c] = 1;
    for(int i=0; i<4; i++){
        int row = r + dir[i][0];
        int col = c + dir[i][1];
        if( row < 0 || col < 0 || row == n || col == m || a[row][col] == '#' || v[row][col] ) continue;
        dfs_grid(row, col, a, v, n, m);
    }
}

void dfs_graph(int u, vector<int>& vis, vector<vector<int>>& graph){
    vis[u] = 1;
    for(auto& v : graph[u]){
        if(!vis[v]){
            dfs_graph(v, vis, graph);
        }
    }
}

class DisjointSet{
    vector<int> size, parent;
    public:
    DisjointSet(int n){
        size.resize(n + 1, 1);
        parent.resize(n + 1);
        for (int i = 0; i <= n; i++) parent[i] = i;
    }

    int getSize(int node){
        return size[represent(node)];
    }

    int represent(int node){ 
        return (parent[node] == node) ? node : parent[node] = represent(parent[node]); 
    }
    
    bool unite(int u, int v){
        int utp_u = represent(u);
        int utp_v = represent(v);
        if (utp_u == utp_v) return false;
        if (size[utp_u] < size[utp_v]){
            parent[utp_u] = utp_v;
            size[utp_v] += size[utp_u];
        }else{
            parent[utp_v] = utp_u;
            size[utp_u] += size[utp_v];
        }
        return true;
    }
};

    vector<int> buildBipartite(int n, vector<vector<int>>& graph){
        vector<int> color(n, -1);
        queue<int> q;
        color[0] = 0;
        q.push(0);
        while(!q.empty()){
            int u = q.front();
            q.pop();
            for(auto& v : graph[u]){
                if(color[v] == -1){
                    color[v] = !color[u];
                    q.push(v);
                }
            }
        }
        return color;
    }


///////////////////////////////////////////////BINARY LIFTING//////////////////////////////////////////////////////////

class BinaryLifting{
    vector<vector<int>> adj;
    vector<vector<int>> parent;
    vector<int> height;
    //will be deleted
    vector<int> count;

    void setHeight(int node, int par, int h){
        height[node] = h;
        for(auto& v : adj[node]){
            if(v == par) continue;
            parent[v][0] = node;
            setHeight(v, node, 1 + h);
        }
    }

    public:
    //Modify the constructor based on the type of input
    BinaryLifting(int n, vector<vector<int>>& edges){
        //initialize the vectors;
        adj.resize(n + 1);
        parent.resize(n + 1, vector<int>(20, -1));
        height.resize(n + 1);
        count.resize(n + 1, 0);

        //making adjecency list
        for(auto& e : edges){
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }
        //calling the preprocessing funcions
        setHeight(1, -1, 0); //calculating height
        //preprocessing parent
        //binary lifting
        for(int i = 1; i < 20; i++){  //it may be 20 or 30 depending open the constraints
            for(int node = 1; node <= n; node++){
                int par = parent[node][i - 1];
                if(par == -1) continue;
                parent[node][i] = parent[par][i - 1];
            }
        }
    }

    int getParent(int node, int k){
        for(int bit = 0; bit < 20; bit++){
            if(k & (1 << bit)){
                node = parent[node][bit];
                if(node == -1) return -1;
            }
        }
        return node;
    }

    int getLCA(int u, int v){
        if(height[u] < height[v]) swap(u, v);
        //making the two nodes to same level
        int d = height[u] - height[v];
        u = getParent(u, d);
        if(u == v) return u;

        for(int bit = 19; bit >= 0; bit--){
            if(parent[u][bit] == parent[v][bit]) continue;
            u = parent[u][bit];
            v = parent[v][bit];
        }
        return parent[u][0];
    }

    // utilities functions
    int getDistance(int u, int v){
        int lca = getLCA(u, v);
        int distance =  height[u] + height[v] - 2 * height[lca];
        return distance;
    }

    void process(int u, int v){
        count[u]++;
        count[v]++;
        int lca = getLCA(u, v);
        count[lca]--;
        if(lca != 1) count[parent[lca][0]]--;
    }

    void counting(int u, int par){
        int value = 0;
        for(auto& v : adj[u]){
            if(v == par) continue;
            counting(v, u);
            value += count[v];
        }
        count[u] += value;
    }

    void printCount(int n){
        for(int i = 1; i <= n; i++) cout<<count[i]<<" ";
    }
};


inline void solve(){
    // GRAPH INPUT
    // for(int i=0; i<m; i++){
    //     int u,v,w;
    //     cin>>u>>v>>w;
    //     graph[u].push_back({v, w});
    //     graph[v].push_back({u, w});
    // }
};
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1;
    // cin>>t;
    while(t--) solve();
    return 0;
}