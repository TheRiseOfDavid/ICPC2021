#include <algorithm>
#include <iostream>
#include <vector>

#define MAXN 200020

using namespace std;

int p[MAXN];

class Edge {
   private:
   public:
    int start, to, cost;

    Edge() : start(0), to(0), cost(0) {}
    Edge(int start, int to, int cost) : start(start), to(to), cost(cost) {}

    bool operator<(const Edge& other) const {
        return cost < other.cost;
    }
};

int find_root(int x) {
    if (p[x] != x) return p[x] = find_root(p[x]);
    return x;
}

int main() {
    int n, m;
    while (cin >> n >> m, n != 0) {
        vector<Edge> edges;
        for (int i = 0; i < n; i++) p[i] = i;

        for (int i = 0; i < m; i++) {
            int start, to, cost;
            cin >> start >> to >> cost;
            edges.push_back(Edge(start, to, cost));
        }

        sort(edges.begin(), edges.end());

        int save = 0;

        for (auto i : edges) {
            int start_root = find_root(i.start);
            int to_root = find_root(i.to);
            if (start_root != to_root) {
                p[to_root] = start_root;
            } else {
                save += i.cost;
            }
        }

        cout << save << endl;
    }

    return 0;
}