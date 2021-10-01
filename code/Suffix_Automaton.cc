// 只要關於這兩個字串問題都可以使用 O(n) 時間複雜度解決：
//  在另一個字串中查詢另一個字串的所有出現位置
//  計算此字串中裡面有多少不同的子字串

// 需要用到 struct，此 struct 需要 len , link , next，這些的意義為：

// len 目前的最長長度
// link 為當前子字串中第一個最長後綴結束位置
// next 連結其他的點的邊，方向是 ->

// 重大的三個特性
// 跟著藍色線走到終點時會是必定是 “aabbabd” 的後綴
// 跟著藍色線走到任意點必定會是此字串的子字串
// 發明這個的演算法大師太強了，跟神一般的存在

#define SAMN N*10 
// N 為字串最長長度
int sz , last ; // 到 SAM 初始化說明

struct state{
    int len , link ; // len = 最長長度 , link = 當前子字串中第一個最長後綴結束位置 

    map<char,int> next ;
}st[SAMN];

void sam_init(){
    sz = 0 ;
    st[0].len = 0 ;
    st[0].link = -1 ;
    st[0].next.clear();
    sz++ ;
    last = 0 ;
}

void sam_extend(char c ){ //char c 要擴增的字元
    int cur = sz++ ; //sz++ 增加 sam array 長度 , cur 為當前的 sam 節點
    st[cur].next.clear() ; //先把當前的 sam 連接點狀態移除
    st[cur].len = st[last].len+1 ; //為前一個 sam 節點 len +1 表示其長度
    int p = last ; // p = 查詢當前字串的「所有子字串」與新增加 c 後的字串是否有共同後綴，
    //將跑到他們有共同後綴的「前一個位置」
    //注意：這裡的共同後綴只要有一個字元是就可以是共同後綴
    //舉例："abca" and "abcab" 中的 'b' 就是共同後綴

    while(p != -1 && !st[p].next.count(c)){ // p = -1 表示已經到起點，
        // !st[p].next.count(c) 則是詢問增加此字元後是否會有共同後綴的情形，
        // 如果有則需要額外處理
        st[p].next[c] = cur ; // 將前面的點與現在的 sam 節點做連結
        p = st[p].link ; // 由於現在的字元並沒有和前面的子字串有共同後綴，
        // 於是他們的 link 就向上追蹤
        // 如果有則 st[p].next.count(c) == TRUE 不符合迴圈要求
    }
    if(p == -1){ 
        // p = -1 表示沒有共同後綴且此字元在當前字串中從沒出現過，
        //才回到了起始點，所以將 link 設置為 0 
        st[cur].link = 0 ; 
    }
    else{
        int q = st[p].next[c] ; // q 為他們共同後綴的位置
        if(st[p].len + 1 == st[q].len){ 
            //如果 st[p].len + 1 == st[q].len 表示「不同位置但相同字元」的共同後綴長度大於一
            //只需要直接將當前的 sam[cur].link 設定成 q 也就是共同後綴的位置 
            st[cur].link = q ;
        }
        else{ // 如果不同位置但相同字元的共同後綴如果等於一，則需要連創建新的 sam 節點，
            // 建立以 c + 字串前一個字元的後綴(前一個並不包括我們現在新增的 c)，
            // 並同時放棄另一個不同位置但也是 c 字元的後綴，但要持續存在以保護先前做好的 sam
            int clone = sz++ ; // 創建新節點
            st[clone].len = st[p].len + 1 ; // 表示從共同後綴的前一個位置 +1，
            //用來建立以 c + 字串前一個字元的後綴
            st[clone].next = st[q].next ; //複製 q 的 next，因為前面已經設定好連接的點，
            //但是因為共同後綴不同，後面還需要一個 while 迴圈進行調整
            st[clone].link = st[q].link ; //將他們 link 先設置相同，
            //之後用 while 迴圈再移動到正確的 link
            while(p != -1 && st[p].next[c] == q){ 
                //p != -1 是不可以讓她更改起始點的位置
                //st[p].next[c] == q 接下來的點是從 clone 繼續擴展而不是原先的 q，
                //所以要將原先連接到 q 的點全部改連接至 clone
                st[p].next[c] = clone ; //更改連接點至 clone
                p = st[p].link ; // 繼續往上層追蹤
            }
            st[q].link = st[cur].link = clone ;
            // 最後則是也要把 q and cur 的 link 改到 clone，
            // 原因則是因為接下來的點是從 clone 繼續擴展而不是原先的 q
        }
    }
    last = cur ; //準備下一次的擴展
}

// QUESTION: 最小循環移位(Lexicographically minimum string rotation) 是甚麼？
// 給你一組字串，找出字典序最小的循環字串，沒錯，就是這題的題目，非常純粹的模板題。

// 要怎麼解開呢？
// 其實容易想到，只需要將原本的字串複製一次給原本的字串，即string += string，透過從起始點一路跟著當下可以走的最小字典序節點走，走到原先字串的長度，在k-string.length()+1，就是最小循環移位了。

// QUESTION A: 為甚麼只要原本的字串複製一次給原本的字串呢？
// 由於第一次的字串長度結束位置 + 字串長度(即第二次循環) < 連續三次循環長度，就算從最後一個字元開始循環也不會大於三次循環，即可證明我們不需要第三次循環，只要循環一次就好。

//st 是 sam、now 是還要再找幾次，一開始為原本字串長度
while(now--){
    for(auto it : st[u].next){ //跟著字典續追蹤
        u = it.second ;
        break ; //找到了就往下個節點移動，類似於 DFS
    }
}
cout << st[u].len - len + 1 << '\n' ; 
//找到當下的節點後，找出它的長度並且扣掉原始長度並加一即是答案
