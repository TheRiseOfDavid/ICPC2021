// \# Kosaraju’s Algorithm 介紹
// Kosaraju’s Algorithm 可以找出有向圖的 SCC

// Sridge-connected Component(強連通分量)
// Bridge-connected Component 所有兩點之間雙向皆有路可以抵達

// \#\# Kosaraju's Algorithm 原理
// \#\#\# 證明
// /* 如果是 A、B、C 三個點都為 SCC，那我從 A 反方向走或正方向走都能走到 A
// /* 其中圖中有一條邊為 A -> D
//     - 如果有一個邊是 D -> A，那我們就可以表示 A、B、C、D 都是 SCC
// /* 因此我們準備一張反向圖，一樣從 A 出發
//     - 題目給的圖如果是 A -> B，則反向圖為 B -> A
// /* 走訪 A、B、C
//     - 同理，如果我能夠滿足此上述條件就表示 A、B、C 為 SCC
// /* 無法走訪 A、D
// /* 不可以的話，他們就不是同一組 SCC


#include <iostream>
#include <bits/stdc++.h>
#define LOCAL
#define MAXN 1020
#define int long long
using namespace std;
vector<int> edge[MAXN]; //題目圖
vector<int> rev_edge[MAXN]; //反向圖
vector<int> path; //紀錄離開 DFS 的節點順序
int visit[MAXN]; 
int group[MAXN]; //判斷此節點在哪一個組
int cnt, a, b, q;

void dfs1(int root){
    if(visit[root]) return;
    visit[root] = 1;

    for(auto it: edge[root]){
        dfs1(it);
    }
    path.push_back(root); //紀錄 DFS 離開的節點
}

void dfs2(int root, int ancestor){
    if(visit[root]) return ;

    visit[root] = 1;
    group[root] = ancestor; //root 跟 ancestor 在同一個 SCC
    for(auto it: rev_edge[root]){
       dfs2(it, ancestor);
    }
}

void kosoraju(){
    for(int i = 0; i < q; i++){ //q 為邊的長度 
        cin >> a >> b;
        edge[a].push_back(b); //題目圖
        rev_edge[b].push_back(a); //反向圖
    }

    memset(visit, 0, sizeof(visit));
    path.clear();
    for(int i = 1; i < cnt; i++){ //第一次 DFS
        if(!visit[i]) dfs1(i);
    }

    memset(visit, 0, sizeof(visit));
    memset(group, 0, sizeof(group));
    for(int i = path.size()-1; i >= 0; i--){ //尋找以 path[i] 為主的 SCC 有哪些節點
        if(!visit[path[i]]){
            dfs2(path[i], path[i]);
        }
    }

}