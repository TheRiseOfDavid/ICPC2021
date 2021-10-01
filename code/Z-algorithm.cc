// 專門解決在線性時間中在一段文字 (text) 中找到我們所需要的段落 (pattern)
// 與此類似的演算法: KMP algorithm
// 由於此題是 Z-algorithm 的模板題，只要能夠了解 Z-algorithm 就能解決此問題。
// 這題為教學題，但此問題還有一點點的小設計，需要稍加解釋才能完全理解。

// x and y
//     在實現 Z-algorithm 還需要用到兩變數 x,y。

//     x = 目前共同前綴的第一個字元
//     y = 目前共同前綴的最後一字元在字串中的 index

// Z-algorithm 再除了此題目以外的應用
//     通常是應用在尋找段落 (pattern)，將文本字串 (text) 與段落連接起來，視段落為「P」、文字為「T」，並加上一個沒有在 P and T 出現過的字元，假設為「$」，產生出「P$T」，最後產生 Z array，如果 Z array 中的某個值等於 P 的長度，則段落出現在此處。

//     因為從未出現過的字元使得「最長共同前綴總和 (Longest Common Prefix)」最大只能到 P，從未出現的字元阻斷了增加的可能性，才能應用在此。

string s ;
int z[s.length()] = {} ;

for(int i = 1 ; i < s.length() ; i++ ){ 
    z[i] = max(0,min(z[i-x] , y - i + 1));
    // z[i-x] 直接詢問 z[i-x] 共同前綴嘗是多少，
    // 如果當前是在目前的共同前綴中，那理所當然現在的 i 必會等於最初的共同前綴 i-x 值，
    // 如果不是，那必定會是 0。
    // y-i+1  此共同前綴理應只會有 y-i+1 個
    //如果 z[i-x] 比較小，代表沒有從 i 位置開始的前綴字串，否則 z[i-x] 應該要更大，所以
    //也就表示 z[i] == z[k]。
    // 如果 y-i+1 比較小，代表這次的共同前綴比較小，因為 z[i-x] 更大，也就代表應該有從這
    //裡開始的共同前綴
    while(i + z[i] < s.length() && s[z[i]] == s[i+z[i]] ){
        x = i ;
        y = i + z[i] ;
        z[i]++ ;
        //進行比對，查看 s[z[i]] 的位置是否等於 s[i+z[i]] 的位置是的話就比對下一個
    }
}

for(int i = 0 ; i < s.length() ; i++)
    if(z[i] == s.length() - i && maxn >= s.length()-i ){
    // z[i] == s.length() - i -> 如果 z[i] 等於字串剩下的長度那保證會有
    //後綴，通常 i 都會接近 s.length() 時才會符合
    // maxn >= s.length()-i -> 再從 0 to s.length() 時勢必會找到並經過
    //「最長共同前綴總和 (Longest Common Prefix)」，只要他比後綴還要長或相等 
    //(還需要先滿足第一個條件，才能判斷到此條件)，就肯定代表中間已經也有經
    //過「最長共同前綴總和 (Longest Common Prefix)」，尾巴這個並不會是第一次經過，
    //如果尾巴是那就代表他只有兩次的共同前綴。
        cout << s.substr(0,z[i]); // 輸出答案
        return 0 ;
    }
    maxn = max(maxn , z[i]);
    //經過時更新 「最長共同前綴總和 (Longest Common Prefix)」
}
