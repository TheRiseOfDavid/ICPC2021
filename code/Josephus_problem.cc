int josephus(int n, int k){
    int s = 0; //一開始的編號
    for(int i = 2; i <= n; i++) s = (s+k) % i; //第 i 輪中，他的位置是第 s 
    return s+1; //如果題目的編號一開始是 1，那我們就加一
}