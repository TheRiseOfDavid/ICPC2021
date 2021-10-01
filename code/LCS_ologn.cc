#include <iostream>
#include <bits/stdc++.h>
#define LOCAL
#define N 120
using namespace std;
int n ;
string strA , strB ;
int t[N*N] , d[N*N] , num[N*N] ; //t and d 是 LIS 要用到 
// d 用來記住 LIS 中此數字的前一個數字
// t 當前 LIS 的數列位置
// num 則是我們根據 strB 的字元生成數列，用來找出最長 LIS 長度 
map<char,vector<int>> dict ; //記住每個字串出現的 index 位置

int bs(int l , int r , int v ){ //binary search 
    int m ;
    while(r>l){
        m = (l+r) /2 ;
        if(num[v] > num[t[m]]) l = m+1 ;
        else if (num[v] < num[t[m]]) r = m ;
        else return m ;
    }
    return r ;
}

int lcs(){
    dict.clear() ; //先將 dict 先清空
    for(int i = strA.length()-1 ; i > 0 ; i--) dict[strA[i]].push_back(i) ;
    // 將每個字串的位置紀錄並放入 vector 中，請記住 i = strA.length() -1 才可以達到逆續效果

    int k = 0 ; //紀錄生成數列的長度的最長長度
    for(int i = 1 ; i < strB.length() ; i++){ // 依據 strB 的每個字元來生成數列
        for(int j = 0 ; j < dict[strB[i]].size() ; j++) 
        //將此字元在 strA 出現的位置放入數列
            num[++k] = dict[strB[i]][j] ;
    }
    if(k==0) return 0 ; //如果 k = 0 就表示他們沒有共同字元都沒有於是就直接輸出 0

    d[1] = -1 , t[1] = 1 ; //LIS init
    int len = 1, cur ; // len 由於前面已經把 LCS = 0 的機會排除，於是這裡則從 1 開始

    // 標準的 LIS 作法，不斷嘗試將 LCS 生長
    for(int i = 1 ; i <= k ; i++ ){
        if(num[i] > num[t[len]]) t[++len] = i , d[i] = t[len-1] ;
        else{
            cur = bs(1,len,i);
            t[cur] = i ;
            d[i] = t[cur-1];
        }

        //debug
//        for(int i = 1 ; i <= k ; i++)
//            cout << num[t[i]] << ' ' ;
//        cout << '\\n' ;
    }
    return len ;

}