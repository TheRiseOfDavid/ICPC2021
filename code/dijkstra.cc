// \# Dijkstra’a Algorithm 介紹
// 能夠針對有權重的有向圖做出單點全源最短路徑演算法。
// 時間複雜度為 O((E+V)logV)，E 為邊、V 為頂點
// * Dijkstra 變化題，可以擴增 dist
// 如，dist[node][第n短路徑]、dist[node][奇偶數路徑]、可以走重複路徑時，則使用 visit[i]，來避免 deque 裡面有相同節點

#include <iostream>
#include <bits/stdc++.h>
#define LOCAL
#define int long long
#define MAXN 10020
#define INF 2100000000
using namespace std;
struct Edge{ // 我們使用 Edge struct 實做 (root, cost)
    int v, c;
    Edge(): v(0), c(0) {}
    Edge(int _v, int _c): v(_v), c(_c) {}

    bool operator < (const Edge& other) const{ 
        return c < other.c; //遞減排序，決定 priority\_queue 的方式
        //return c > other.c; //遞增排序
    }
};

int c, v;
int a, b, cost;
vector<Edge> edge[MAXN]; //放入題目的邊
int dist[MAXN]; //從 root 出發到 x 邊的最短距離

void dijkstra(int root){
    deque<Edge> q;
    q.push_back({root,0}); //初始放入開始點
    dist[root] = 0; //自己到自己成本為零

    int cost;
    while(!q.empty()){
        Edge node = q.front(); q.pop_front(); 
        //cout << node.v << " " << node.c << "\\n";
        for(auto it: edge[node.v]){
            cost = dist[node.v] + it.c; //分析 3
            if(cost < odd_dist[it.v]){ 
                q.push_back({it.v, cost});
                odd_dist[it.v] = cost;
            }
        }
    }
}


int32_t main()
{
#ifdef LOCAL
    freopen("in1.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif // LOCAL
    while(cin >> c >> v){
        for(int i = 1; i <= c; i++){ //清除邊、重置距離
            edge[i].clear();
            dist[i] = INF;
        }
        for(int i = 0; i < v; i++){ //加入邊
            cin >> a >> b >> cost;
            edge[a].push_back({b,cost}); //單向時使用
            edge[b].push_back({a,cost}); //雙向時使用
        }
        dijkstra(root); //root 為任移值，為開始的點
        if(dist[x] == INF) cout << "-1\n"; // root -> x 最短距離為多少，無法抵達輸出 -1
        else cout << dist[x] << "\n"; //可以抵達則輸出。
    }
    return 0;
}