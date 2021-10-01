#include <iostream>
#include <bits/stdc++.h>
#define MAXN 5020
#define LOCAL
using namespace std;

int a[MAXN];
int T, n, len = 0, cur;

int lis(){
    deque<int> b; //用來產生 LIS 長度
    b.push_back(a[0]); //先放入一個數值，以避免 b.back() 找不到值
    int temp; //紀錄二分搜尋後找到的位置
    for(int i = 1; i < n; i++){
        if(a[i] > b.back()){ //如果現在這個數字大於此數列中最大的數字
            b.push_back(a[i]); //LIS push back
        }
        else{
            temp = upper_bound(b.begin(), b.end(), a[i]) - b.begin(); 
            //二分搜尋，找到他適合的位置，前面數字比她小或相等，後面數字大
            temp = lower_bound(b.begin(), b.end(), a[i]) - b.begin(); 
            //大部分使用 upper\_bound，少用 lower\_bound
            b.insert(b.begin()+temp , a[i]); //插入數值在此位置
        }
    }
    return b.size(); //輸出最長 LIS 長度
}