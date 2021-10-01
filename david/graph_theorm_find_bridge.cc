// 四個陣列，一個 vector edge 紀錄題目的邊
//  depth 記錄當前深度
//  low 紀錄當前節點，能返回的最淺深度是多少
//  visit 紀錄是否有走訪過
//  ancestor 為 disjoint set，將所有橋的節點放在一起

#define MAXN
vector<int> edge[MAXN];
int visit[MAXN], depth[MAXN], low[MAXN];
int ancestor[MAXN];
int cnt = 1

int find_root(int x){ 
    if(ancestor[x] != x) return ancestor[x] = find_root(ancestor[x]);
    return ancestor[x];
}

void find_bridge(int root, int past){ //找到橋點
    visit[root] = 1; //表示走訪過
    depth[root] = low[root] = cnt++; //邏輯證明 2.1
    for(int node: edge[root]){ //不斷遍地
        //因為是無向邊，因此雙向同個 edge 不是 bridge 
        if(node == past) continue; 
        if(visit[node]) low[root] = min(low[root], depth[node]); //邏輯證明 2.2
        else{
            //先進行 DFS，往下找其他的 node 有沒有辦法回到曾經走放過的節點
            find_bridge(node, root); 
            low[root] = min(low[root], low[node]); //邏輯證明 2.3
            if(low[node] > depth[root]){  //邏輯證明 2.4
                int fa_node = find_root(node); //進行 disjoint merge
                int fa_root = find_root(root);
                //cout << "fa " << fa_node << " " << fa_root << "\n";
                ancestor[fa_node] = fa_root;
            }
        }
    }
}