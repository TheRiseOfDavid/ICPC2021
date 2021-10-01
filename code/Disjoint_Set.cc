#define MAXN 2000
void init(){
    for(int i = 0; i < MAXN; i++){
        tree[i] = i;
        cnt[i] = 1; //cnt 為數量，也就是每一個集合的數量，一開始都是 1，因為只有自己。
    }
}

int find_root(int i){
    if(tree[i] != i) //如果 tree[i] 本身並不是集合中的代表元素，
    //表示這個集合中有其他元素，並且其他元素才是代表元素
        return tree[i] = find_root(tree[i]); //遞迴，將 tree[i] 的元素在進行查詢，
        //並將代表元素設為現在的 tree[i]
    return tree[i]; //回傳代表元素
}

void merge(int a, int b){
    rx = find_root(tree[a]); //找出 find\_root(tree[a]) 的代表元素
    ry = find_root(tree[b]); //找出 find\_root(tree[b]) 的代表元素
    if(rx != ry) //如果不一樣就合併
        tree[ry] = rx; //要合併的是代表元素，不是 tree[b]
        cnt[rx] += cnt[ry]; //將原本另一集合的數量加到這集合，因為他們合併了
        cnt[ry] = 0;  //由於合併，因此將原本獨立的集合數量歸 0
}