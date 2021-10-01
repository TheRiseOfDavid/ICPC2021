// Kruskal Algorithm 介紹
//
// 主要是在一張圖中組合成一顆樹，其中每一條邊都有一個成本，且要求這顆樹的總和成本必須要是最小。
// 時間複雜度為 O(ElogE)
// 主要用來找出一張圖中的最小生成樹、最大生成樹

#include <iostream>
#include <bits/stdc++.h>
#define LOCAL
#define MAXN 200020
#define int long long
using namespace std;
int n, m;
int a, b, c;
int p[MAXN];

struct edge{
    int u, v, c; //u,v 分別為邊的節點， c 是成本
    
    edge(): u(0), v(0), c(0) {}
    edge(int u, int v, int c): u(u), v(v), c(c) {}
    bool operator < (const edge& other) const{
        return c < other.c;
    }
};
vector<edge> node;
vector<edge> MST; //最小生成樹

int find_root(int x){
    //cout << "find\_root " << x << "\\n";
    if(p[x] != x) return p[x] = find_root(p[x]);
    return x;
}

void kruskal(){
    node.clear();
    MST.clear();
    for(int i = 0; i < n; i++) p[i] = i; //init disjoint set

    for(int i = 0; i < m; i++){
        cin >> a >> b >> c; //輸入邊、成本
        node.push_back({a,b,c});
    }
    sort(node.begin(), node.end()); //排序，這邊排序方式為遞增

    for(edge it: node){
        //cout << it.u << " " << it.v << " " << it.c << "\\n";
        //cout << p[3] << " " << p[4] << "\\n";
        int pu = find_root(it.u); //判斷邊的節點們是否都在同個 set 
        int pv = find_root(it.v);
        if(pu != pv){ //分析 3-1
                p[pv] = pu;
                MST.push_back(it); //記錄此 edge
        }
    }

    for(edge it: MST){
        cout << it.u << " " << it.v << " " << it.c << "\n"; //輸出所有邊
    }


}