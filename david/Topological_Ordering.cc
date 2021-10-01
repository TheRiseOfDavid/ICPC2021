#include <iostream>
#include <bits/stdc++.h>
#define LOCAL
#define MAXN 120
using namespace std;
int n, m, a, b;
int cnt[MAXN]; //記錄關係，以此節點為後面，而有多少節點在其前面
vector<int> root[MAXN], ans; 
//root 記錄關係，以此節點為前面，而另一節點就在後面 (vector.push_back)
//ans 答案序列，拓樸排序的序列

void topo(){

    for(int i = 0; i < m; i++){ //不斷輸入 
        cin >> a >> b; //輸入記錄關係，a 是前者 b 是後者
        root[a].push_back(b);  //記錄關係，記錄 a 有多少後面節點，並且記錄。
        cnt[b]++; //記錄有幾個前面節點，如果 b 是後面關係時。
    } 

    deque<int> q; //用來判斷有哪些節點現在已經可以直接被放到答案序列
    for(int i = 1; i <= n; i++){
        if(cnt[i] == 0) q.push_back(i); 
        //在記錄關係中，如果以此節點為後面，沒有節點在前面就加入 q
    }

    int now; //暫存 bfs(q) 當前的節點
    ans.clear(); //答案序列清空
    while(ans.size() != n){ //如果答案序列的長度跟題目給的長度一樣就跳出
        if(q.empty()) break; //如果沒有節點可以直接被放入答案序列就跳出
        now = q.front(); q.pop_front(); //把當前節點給 now
        ans.push_back(now); //將 now 放入答案序列
        for(auto it: root[now]){ //由於 now 節點被放入答案陣列，
        //之前的記錄關係就不須記錄，因為放到答案陣列就剩下的後面節點就必定在後面

            cnt[it]--; //將所有原本在記錄關係中後面的節點 -1，減少了一個記錄關係
            if(cnt[it] == 0) q.push_back(it); //如果都沒有記錄關係就可以放到 q
        }
    }
    if(ans.size() == n){ //如果答案序列跟 n 一樣，表示可以成功排出拓樸排序，就輸出答案
        for(int i = 0; i < ans.size(); i++) cout << ' ' << ans[i];
        cout << '\n';
    }
}