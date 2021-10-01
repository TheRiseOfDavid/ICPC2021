// 對某一字串的所有後綴進行字典排序，常用於全文索引、數據壓縮算法與生物資訊學。
// 這裡介紹的演算法寫法時間複雜度為 O(nlogn)

// QUESTION 1: sa (suffix array) 用途是甚麼呢？
// sa[i] 表示此字串所有後綴排序後第 i 大的 index。

// QUESTION 2: rk (rank array) 用途是甚麼呢？
// rk[i] 表示此字串所有後綴排序後，字串中 index 後綴的排名。

int sa[N] , rk[N<<1] , oldrk[N<<1] , id[N] , cnt[N] ;
// id = 舊的 sa 排名 , cnt 在 radix sort 時幫助
int n , m , maxn , lenA , lenB , flag =0 ;
// n 字串長度 , m 文字的最大長度
string strA ;
// 要進行 suffix array 的字串，請記住這裡的字串第一個 index 為 1

void build_sa(){  //build suffix array
    int i , m , p , w ; 
    // 在這邊把常在迴圈使用的變數名稱拉出來宣告，以避免不斷宣告造成的效率浪費
    n = strA.length()-1 ; //減去 string[0] 的空格
    m = max(n , 300 ); // 由於 ascii 上限是 255，我們這邊直接開 300
    // 也省去把字元 hash 的麻煩
    memset(cnt,0,sizeof(cnt)); //重設 cnt 陣列以免多次使用時與上次使用的值混亂在其中
    memset(rk,0,sizeof(rk)); //重設 rk 陣列以免多次使用時與上次使用的值混亂在其中

    // **** radix sort 排序開始 ****
    for(i = 1 ; i <= n ; i++) ++cnt[rk[i] = (int)strA[i]] ;
    // rk[i] = (int) strA[i] 每一個字元在字串中排名
    //++cnt[rk[i] = (int)strA[i]] radix sort 分類
    for(i = 1 ; i <= m ; i++) cnt[i] += cnt[i-1] ; 
    //將 cnt 遞增排序方便之後找出數值排在第幾位
    for(i = n ; i >= 1 ; i--) sa[cnt[rk[i]]--] = i ;
    // cnt[rk[i]] 先找出字元在字串中排名再透過 cnt 找出他應該排在第幾位
    // 隨後進行 cnt[rk[i]]--，方便下一個值得排序位置。
    // **** radix sort 排序結束 ****

    for(w = 1 ; w < n ; w <<= 1){ // 倍增思想開始
        memset(cnt,0,sizeof(cnt)); //第一次 radix sort 開始，排序關鍵為後者
        // 最好範例：倍增排序圖中黑色粗線類似於勾勾的斜線，下方解釋 A 圖中
        for(i = 1 ; i <= n ; i++) id[i] = sa[i] ;
        // id 用來記錄現在排序的順序，配合這次的 radix sort 再進行更動
        for(i = 1 ; i <= n ; i++) ++cnt[rk[id[i]+w]] ;
        for(i = 1 ; i <= m ; i++) cnt[i] += cnt[i-1] ;
        for(i = n ; i >= 1 ; i--) sa[cnt[rk[id[i]+w]]--] = id[i] ;
        // radix sort 與一開始相同，只是多增加 w，因為排序關鍵為後者
        // 第一次 radix sort 結束

        // 第二次 radix sort 開始，排序關鍵為前者
        memset(cnt, 0 , sizeof(cnt));
        for(i = 1 ; i <= n ; i++) id[i] = sa[i] ;
        for(i = 1 ; i <= n ; i++) ++cnt[rk[id[i]]] ;
        for(i = 1 ; i <= m ; i++) cnt[i] += cnt[i-1] ;
        for(i = n ; i >= 1 ; i--) sa[cnt[rk[id[i]]]--] = id[i] ;
        // 第二次 radix sort 結束

        // 根據 radix sort 在排列一次 rank 
        memcpy(oldrk , rk , sizeof(rk)); //複製 rank 來幫助 rank 間的交換
        for(p = 0 , i = 1 ; i <= n ; i++){ // p 為 rank 的等級，i 則是資料
            if(oldrk[sa[i]] == oldrk[sa[i-1]] && 
               oldrk[sa[i] + w] == oldrk[sa[i-1] + w])
               //如果與前一個 rank 值是相同則理應現在應該也要相同
               //最好範例：倍增排序圖示說明第一次排序的 rank[4 \~ 7], index 從 1 開始，
               //下方解釋 B 圖中
                rk[sa[i]] = p ; //rank 字典排序不變
            else
                rk[sa[i]] = ++p ; //rank 字典排序增加
        }
    }

    // debug 輸出測試，以驗證是否正確
    //    cout << "Suffix Array is:\\n" ;
    //    for(int i = 1 ; i <= n ; i++)
    //        cout << i << ' ' << strA.substr(sa[i]) << ' ' <<sa[i] << '\\n' ;
    //  
}

// 最長共同前綴 Longest Common Prefix Array (LCP)
// 定義 height = Longest Common Prefix Array
// 道理其實相當簡單，我們的 Suffix Array 是字典排序，於是我們可以推出一公式 height[i]=lcp(sa[i],sa[i−1]，也就是讓第 i 名的後綴去跟前一名後綴算出最長共同前綴。

// height[1]=0，由於我們的 string index 是從 1 開始，所以 1 只能夠跟 0 比無意義因而設成 0。

// 因為 height 他每個 index 都是獨立並沒有相關性，我們的比較方式是根據字串中的每個後綴由字串 index 順序，去找出他的 sa -1 位置去找出 lcp 長度，下一次則是找 index +1 的後綴與他的 sa-1 位置去找出 lcp 長度，由於比較的字串只是刪除上一個前綴的第一個字元，於是 lcp 長度最差則是 lcp -1(前提為 lcp > 0)，所以可以直接從 index + lcp 的長度直接比較，可以減少重複比較，以達到降低時間複雜度。

// 時間複雜度是 O(n)。

// 如果還是聽不太懂，感覺有點紙上談兵，就讓我用程式碼來解釋吧！

void build_lcp(){
    int lcp[N] = {} ;
    int max_lcp = 0 ; // max\_lcp 最大長度
    //k 為現在 i 名的後綴與前一名後綴長度算出的最長共同前綴
    for(int i = 1 , k = 0 ; i <= n ; i++){
        if(k) k-- ; 
        // 由於我們下次是把字串 index 在往後一個 index，所以 lcp 最差的情況則會是 x-1
        // 因為其實要比較的字串只是刪除上一個後綴的第一個字元
        
        while(strA[i+k] == strA[sa[rk[i]-1]+k]) ++k ;
        //比較順序較為特殊，因為他每個陣列都可以分開進行討論，
        //於是我們比較字串的 index 開始的後綴與他的 sa 前一項找出 lcp
        // strA[i] = 字串的 index 開始的後綴
        // strA[sa[rk[i]-1]] = 字串的 index 開始的後綴的 sa 前一項
        // while 裡面的 +k 則是減少重複比較，如果上次的 lcp 已經找出長度為 x 的 lcp

        lcp[rk[i]] = k ;
    }

    for(int i = 1 ; i <= n ; i++){
        if((sa[i] < lenA && sa[i-1] < n+1 && sa[i-1] > lenA ) ||
            (sa[i] > lenA && sa[i-1] < n+1 && sa[i-1] < lenA))
            max_lcp = max(max_lcp , lcp[i]);
    }
}