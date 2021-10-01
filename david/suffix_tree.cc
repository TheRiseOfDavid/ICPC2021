// 以下是 Suffix Tree 能解決的問題：

// 尋找 A 字串是否在字串 B 中
// 找出 B 在 A 字串重複的次數
// 最長共同子字串

// 時間複雜度 O(n)

// remaining 隱藏在 Suffix Tree 中的後綴節點
// root = Suffix Tree 的最主要根節點
// active_node 活動節點，主要是用來生長葉節點 (leaf)
// active_e 隱藏節點的第一個字元
// active_len 隱藏在 Suffix Tree 中節點的長度
// node 一個 struct 用來存入 Suffix Tree 節點
//     start 此節點開始的位置(index)
//     end 此節點結束的位置(end)
//     舉例： node.start = 3 and node.end = 5，則 string 的長度是 string.substr(3,2)，用數學表示則是 (start,end]
//     next 用來指出下一個節點的位置，個人習慣用 map
//     slink 指出此節點的最長後綴節點，EX: XYZ 則指出 YZ。
//     edge_length() 公式為 min(end,pos+1)−start
//     用來找出此節點的字串長度

struct node{
    int start , end ,slink ; 
    map<char,int> next ;

    int edge_length(){
        return min(end , pos+1) - start ;
    }

    void init(int st , int ed = oo){
        start = st ;
        end = ed ;
        slink = 0 ;
        next.clear() ;
    }
}tree[2*N];

void st_init(){
    //tree root is 1 not zero
    needSL = remainder_ = 0 ;
    active_node = active_e = active_len = 0 ;
    pos = -1 ;

    cnt = root = 1 ;
    active_node = 1 ;
    tree[cnt++].init(-1,-1);
    return ;
}

char active_edge(){ //隱藏字元的第一個
    return text[active_e] ;
}

void add_SL(int node){ // slink 指回上一個隱藏節點的位置，如果上一個後綴節點的葉節點需要被更改時，
// 這裡的下方葉節點也能被迅速被更改，達到 O(1) 效果
    if(needSL > 0 ) tree[needSL].slink = node ;
    needSL = node ;
}

bool walkdown(int node){ //即 原理說明 - "xyzxyaxyz$" 的 step 1， xyz 但 xy 是一個節點，
// 需要在往下一個子節點前進
    if(active_len >= tree[node].edge_length()){
        active_e += tree[node].edge_length() ; //找到此長度後的第一個隱藏字元 
        active_len -= tree[node].edge_length() ; //減少長度
        active_node = node ; //往後方前進
        return true ;
    }
    return false ;
}

void st_extend(char c){ //擴增 suffix tree 
    pos++; // 往下個字串前進
    needSL = 0 ; // 紀錄上一個切割點的位置，用來 slink 的前一個點
    remainder_++ ; // 先 +1，如果這個點有被增加之後做 -1 的動作
    while(remainder_ > 0){
        if(active_len == 0 ) active_e = pos ; 
        // 如果 active len 等於 0，就表示沒有隱藏長度，所以我們要判斷的就是當前字元
        // 是否存在此 active_node 節點中
        if(tree[active_node].next[active_edge()] == 0){ 
            // active_node 沒有此字元的節點，新增節點
            int leaf = cnt ;
            tree[cnt++].init(pos) ;
            tree[active_node].next[active_edge()] = leaf ;
            add_SL(active_node) ;　// 紀錄 slink 的位置，以防下次用到
        }
        else{ // active_node 有此字元的節點
            int nxt = tree[active_node].next[active_edge()] ;
            if(walkdown(nxt)) continue ; // 如果還需要在往下一個節點走，就減少隱藏長度，
            //然後回去重新查詢
            if(text[tree[nxt].start + active_len] == c){ 
                // 如果此節點有包含到此字元，代表隱藏長度可以+1，因為後綴還是在節點長裡面
                active_len++ ; // 隱藏長度可以 +1
                add_SL(active_node) ; // 紀錄 slink 的位置，以防下次用到
                break ; //由於隱藏節點是 +1，所以我們沒必要減
            }
            // 需要做切割點
            int split = cnt ; 
            tree[cnt++].init(tree[nxt].start , tree[nxt].start + active_len) ;
            //製作切割點中...，結束位置就是當前節點的 start + 隱藏長度
            tree[active_node].next[active_edge()] = split ;
            // 需要將 active_node 指向我們的切割點，而不是原來的點
            int leaf = cnt ; // 需要葉節點
            tree[cnt++].init(pos) ;
            // 製作葉節點
            tree[split].next[c] = leaf ; // 把葉節點指向我們的切割點
            tree[nxt].start += active_len ; //原本的節點 start 往後到切割點的 end
            tree[split].next[text[tree[nxt].start]] = nxt ; //將原本節點指向我們的切割點
            add_SL(split) ; // 紀錄 slink 的位置，以防下次用到
        }
        remainder_-- ; // 由於有增加節點，所以 -1
        if(active_node == root && active_len > 0 ){ 
            //active_len > 0 表示我們現在做的是把隱藏節點新增，所以要減掉
            //active_node == root 確保有回到根節點才做隱藏節點減掉，否則 
            //text[node.start + active_len ] 就會亂掉
            active_len-- ;
            //由於我們減少了一個隱藏長度，所以 -1 
            active_e = pos - remainder_ + 1 ;
            //找到減少後隱藏長度的第一個隱藏字元，此時如果 active_len == 0，
            // 則下次迴圈則在 active_e 會被重新定義成 pos
        }
        else{
            // 跟著 slink 走去改動其他的後綴在 tree[active_node].slink > 0 時，
            // 否則則回到 root，繼續建立後綴樹
            active_node = tree[active_node].slink > 0 ? tree[active_node].slink : root ;
        }
    }
    return ;
}