// \#\# Tarjan's Algorithm 無向圖實作與原理
// \#\#\# 原理
// /* 使用 DFS 實作
// /* 使用堆疊紀錄每一個經過的點
// /* 找出每一個點最高能回到哪一個點
// /* 如果這個點最高能回朔的點還是自己，則表示這個點往下的所有點都會回朔到他，形成一個 SCC，因此將堆疊裡的點刪除，直到 stack.top() 最高能回朔的點還是自己。



#include <iostream>
#include <bits/stdc++.h>
#define LOCAL
#define int long long
#define MAXN 10020
using namespace std;
int cnt;
vector<int> edge[MAXN]; //圖
int stk[MAXN], in_stk[MAXN]; //stk 是堆疊, in-stk 確認此點是否已在堆疊上
int visit[MAXN]; //是否有走訪過
int lead[MAXN], low[MAXN]; //lead 表示此點為哪一個 SCC、low 表示此點最高能回到哪一個點
int stk_index; //堆疊的 size


void scc(int root){
    if(visit[root]) return;

    visit[root] = low[root] = cnt++; //因為是第一次接觸，先認定 root 只能回到 root
    stk[++stk_index] = root; // root 加入 stack， stk-index+1
    in_stk[root] = 1; //此點加入 stack

    for(auto it: edge[root]){ //DFS
        scc(it);
        //如果 scc 完成以後，因為 root -> it 是一條邊，如果 it 可以返回到的點比 root 小，
        //那就改變 low[root]
        if(in_stk[it]) low[root] = min(low[it], low[root]); 
    }

    //如果 low[root] 同時也是 root，表示這個點是 SCC 起點，把這個點以下的 stack，都設定為同組的 SCC
    if(visit[root] == low[root]){ 
        int it;
        do{
            it = stk[stk_index--]; //找出 stack.top()
            in_stk[it] = 0; //stack.pop()
            lead[it] = root; //it 的 SCC 是 root 組
        }while(it != root); //只要 it != root，表示還沒有找玩
    }
}

void tarjan(){
    memset(visit, 0, sizeof(visit));
    for(int i = 1; i <= n; i++){
        if(visit[i]) continue;
        stk_index = -1; cnt = 1;
        scc(i);
    }
}