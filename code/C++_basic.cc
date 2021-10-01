// * define int long long 避免溢位問題
// * cin、cout 在測資過多時最好加速
// * define debug 用來測試

#include <bits/stdc++.h>
#define int long long
#define debug

using namespace std;

main()
{
    #ifdef debug
    freopen("in1.txt", "r", stdin);
    freopen("out1.txt", "w", stdout);
    #endif // debug
    // 讀寫加速
    // 關閉 iostream 物件和 cstdio 流同步以提高輸入輸出的效率
    ios::sync_with_stdio(false);
    // 可以通過 tie(0)（0表示 NULL）來解除 cin 與 cout 的繫結，進一步加快執行效率
    cin.tie(0);
}