// 給你一字串，請新增字元讓這字串變成迴文，但新增字元數量要最少。
// 迴文：從左邊讀與從右邊讀意思都一樣
// 題目善意提示：這題不要給經驗不足的新手做 ^^

// KMP algorithm 介紹
// 在線性時間內找出段落(Pattern) 在文字(text) 中哪裡出現過。
// 對 Pattern 找出次長相同前綴後綴，在使用 DP 將時間複雜度壓縮

string  strB ;
int b[MAXN] ;
// b[] value 表示 strB當下此字元上次前綴的 index，如果已經沒有前綴則設定 -1

void kmp_process(){
    int n = strB.length() ,i = 0 ,  j = -1 ;
    // j = 前綴的長度
    //strB 是 pattern , j = -1 時代表沒有辦法再回推到前一個次長相同前綴
    b[0] = -1 ;
    // 由於 strB[0] 絕對沒有前綴所以設定 -1 
    while(i < n ){ //對從 Pattern 的第 0 個字元到第 i 字元找出次長相同前綴
        while(j >= 0 && strB[i] != strB[j]) j = b[j] ;
        // j >= 0 代表還可以有機會找出 次長相同前綴
        // strB[i] != strB[j] 則代表他們字元不同，於是在這裡把 j 值設為 b[j]
        // 當 j 只要被設定成 -1 就代表完全沒有次長相同前綴
        i++ ; j++ ;
        b[i] = j ;
        // strB[i] 上次前綴的 index 值或是將 j 設定成 0 而不設定成 -1 是因為
        // 他有可能會是 strB[0] 長度只有 1 的前綴
    }

    //debug 供應測試用
    //    for(int k = 0 ; k <= n ; k++)
    //        cout << b[k] << ' ' ;
    //    cout << '\n' ;
}

string strA ;
//strA 是 text

void kmp_search(){
    int n = strA.length() , m=strB.length() , i=0 , j=0  ;
    while(i < n ){ //對從 text 找出搜尋哪裡符合 Pattern 
        while(j >= 0 && strA[i] != strB[j]) j = b[j] ;
        // j >= 0  代表還可以有機會是 pattern 的前綴
        // strA[i] != strB[j]  則代表他們字元不同，於是在這裡把 j 改為 b[j]
        // b[j] 說明請看 kmp_process 宣告 b[j] 時的解釋
        i++ ; j++ ;
        if (j == m) { // j 已經跟 pattern 的長度相同了
            printf("P is found at index %d in T\n", i - j); 
            // 告訴使用者在哪裡找出
            j = b[j];
            // 將 j 設定成此字元上次前綴的 index
        }
    }
}

