// 在介紹最大二分匹配時，必須先介紹二分圖。
// 二分圖是一種圖的特例，二分圖的結構為，X 群體的每一個點都有連結到至少一個以上 Y 群體的點、T 群體的每一個點都有連結到至少一個以上 X 群體的點，且 X、Y 群體各自沒有邊互相連接。
// 二分匹配就是，每一個 x 節點只能連到一個 y 個節點、每一個 y 節點只能連到一個 x 個節點，舊式二分匹配，類似於一夫一妻制。
// 我們使用 Augmenting Path Algorithm 實作，時間複雜度為 O(VE)，V 是頂點、e 是邊

//二分匹配變化，如果遇到棋盤，其中以座標 (x,y) 為例，則 x,y 軸只能有此點，那也是二分圖，這邊則是將 x 軸與 y 軸配對。



vector<int> edge[MAXN];
int mx[MAXN], my[MAXN], vy[MAXN]; //matchX, matchY, visitY

bool dfs(int x){
    for(auto y: edge[x]){ //對 x 可以碰到的邊進行檢查
        if(vy[y] == 1) continue; //避免遞迴 error
        vy[y] = 1;
        if(my[y] == -1 || dfs(my[y])){ //分析 3
            mx[x] = y;
            my[y] = x;
            return true;
        }
    }
    return false; //分析 4
}

int bipartite_matching(){
    memset(mx, -1, sizeof(mx)); //分析 1,2
    memset(my, -1, sizeof(my));
    int ans = 0;

    for(int i = 1; i <= cnt; i++){  //對每一個 x 節點進行 DFS(最大匹配)
        memset(vy, 0, sizeof(vy));
        if(dfs(i)) ans++;

    }
    return ans;
}