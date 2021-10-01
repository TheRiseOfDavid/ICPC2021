// Minimum Edit Distance 介紹
//     可以透過刪除、插入、替換字元來達到將 A 字串轉換到 B 字串，並且是最少編輯次數。
//     此演算法的時間複雜度 O(n2)

// 最短修改距離 Minimum Edit Distance 應用
//     DNA 分析
//     拼寫檢查
//     語音辨識
//     抄襲偵測

int dis[MAXN][MAXN]; 
//dis[A][B] 指在 strA 長度 0 to A 與 strB 長度 0 to B 的最短修改距離為多少
//這裡假設由 A 轉換 B
string strA , strB ;
int n , m ;
n=strA.length() ;
m=strB.length() ;

int med(){ //Minimum Edit Distance
    for(int i = 0 ; i <= n ; i++) dis[i][0] = i ;
    // 由於 B 是 0 ，所以 A 轉換成 B 時每個字元都要被進行刪除的動作
    for(int j = 0 ; j <= m ; j++) dis[0][j] = j ;
    // 由於 A 是 0 ，所以 A 轉換成 B 時每個字元都需要進行插入的動作
    for(int i = 1 ; i <= n ; i++){ // 對 strA 每個字元掃描
        for(int j = 1 ; j <= m ; j++){ // 對 strB 每個字元進行掃描
            if(strA[i-1] == strB[j-1]) dis[i][j] = dis[i-1][j-1] ;
            // 如果他們字元相同則代表不需要修改，因此修改距離直接延續先前
            else dis[i][j] = min(dis[i-1][j-1], min(dis[i-1][j] , dis[i][j-1]))+1;
            // 因為她們字元不相同，所以要詢問 replace , delete , insert 哪一個編輯距離
            // 最小，就選擇他 +1 來成為目前的最少編輯距離
        }
    }
}

return dis[n][m] ; // 這就是最少編輯距離的答案

// QUESTION: 現在的我們知道最少編輯距離的答案，那我們可以回推有哪些字元被編輯嗎？
// 那當然是可以的阿XD，只是寫起來比較麻煩。通常這種答案會有很多種，依照題目的要求通常只需要你輸出一種方式即可。除非是毒瘤

// 實現方式如下：
// 由於這回推其實也就只是一個簡單的遞迴你能夠推得出 DP 就可以知道要怎麼回推哪些字元被編輯，於是我就在程式碼上旁寫下說明來幫助讀者閱讀。希望能夠幫助到
