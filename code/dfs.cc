// 我們的機器人會根據路面上的指示進行移動，請告訴我們當她從座標 0,c 進去後幾步會出來地圖外。
// 如果產生迴圈的狀態，請告訴我們這個迴圈有幾步

#include <iostream>
#include <bits/stdc++.h>
#define LOCAL
#define int long long
#define MAXN
using namespace std;
string maze[20];
int visit[20][20];
int r, c, go;

int dfs(int x, int y, int step){
    //cout << x << " " << y << "\\n";
    if(x < 0 || x >= r || y < 0 || y >= c){ //判斷是否離開地圖
        cout << step << " step(s) to exit\n";
        return 0;
    }
    if(visit[x][y] != -1){ //又重新回到 loop
        //visit[x][y] 由於回到迴圈，因此碰到迴圈的那個點之前的步數都是正常
        //step - visit[x][y] 總步數 - 不是迴圈的步數 = 迴圈步數
        cout << visit[x][y] << " step(s) before a loop of " << step - visit[x][y] << " step(s)\n";
        return 0;
    }


    visit[x][y] = step; //這是第幾步

    //判斷下一個位置要怎麼走
    if(maze[x][y] == 'N') dfs(x-1, y, step+1);
    else if(maze[x][y] == 'S') dfs(x+1, y, step+1);
    else if(maze[x][y] == 'W') dfs(x, y-1, step+1);
    else if(maze[x][y] == 'E') dfs(x, y+1, step+1);
    return 0;
}

int32_t main()
{
#ifdef LOCAL
    freopen("in1.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif // LOCAL
    while(cin >> r >> c >> go && (r + c + go) != 0){ //注意，我的 index 從 0 開始
        for(int i = 0; i < r; i++) cin >> maze[i];
        for(int i = 0; i <= r; i++){
            for(int j = 0; j <= c; j++) visit[i][j] = -1;
        }
        dfs(0,go-1,0);
    }
    return 0;
}