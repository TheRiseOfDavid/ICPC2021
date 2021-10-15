// 能夠針對有、無權重的有向圖做出全點全源最短路徑演算法。
// 全點全源：任意點到任意點的最短距離

// 時間複雜度為 $O(n^3)$，n 為頂點

#include <iostream>
#include <bits/stdc++.h>
#define LOCAL
#define MAXN 120
#define int long long
#define INF 0x3f3f3f
using namespace std;
int t, n, r;
int u, v, c;
int start, destination, kase = 1;
int dist[MAXN][MAXN];

void floyd(){
    for(int k = 0; k < n; k++){ //以 k 為中繼點
        for(int i = 0; i < n; i++){ //從 i 出發
            for(int j = 0; j < n; j++){ //抵達 j 
                //如果 i to j，經過 k 會比較快就替換答案
                if(dist[i][k] + dist[k][j] < dist[i][j]) 
                    dist[i][j] = dist[i][k] + dist[k][j];
            }
        }
    }

}

void print(){ //印出最短距離圖
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            printf("%10d ", dist[i][j]);
        }
        printf("\n");
    }
}

int32_t main()
{
#ifdef LOCAL
    freopen("in1.txt", "r", stdin);
#endif // LOCAL
    cin >> t;
    while(t--){
        cin >> n >> r;
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                dist[i][j] = INF; //一開始 i 都無法抵達 j 節點
            }
            dist[i][i] = 0; //但是自己可以抵達自己
        }
        for(int i = 0; i < r; i++){
            cin >> u >> v;
            dist[u][v] = 1; //加入邊
            dist[v][u] = 1; //考慮雙向邊
        }

        floyd();
        int ans = 0;
        cin >> start >> destination; 
        cout << dist[start][destination] << "\n" //輸出起點到終點的最短距離
        //print();

    }
    return 0;
}