#include <string.h>

#include <iostream>
#include <queue>
#include <vector>

#define MAXN 10010

using namespace std;

vector<int> edges[MAXN];
int import[MAXN];

int shortest_path(int n, int root) {
    bool visit[n + 1];
    int dist[n + 1];
    memset(visit, false, sizeof(visit));
    memset(dist, 0x3f3f3f, sizeof(dist));

    deque<int> q;
    q.push_back(root);
    dist[root] = 0;

    while (!q.empty()) {
        int node = q.front();
        q.pop_front();

        for (auto i : edges[node]) {
            if (dist[i] > dist[node] + 1) {
                dist[i] = dist[node] + 1;
                if (!visit[i]) {
                    visit[i] = true;
                    q.push_back(i);
                }
            }
        }
    }

    // 這邊依照題目決定 code
    int result = 0;
    for (int i = 1; i <= n; i++) {
        if (import[i] > 1) result += dist[i];
    }
    return result;
}

void reset(int n) {
    for (int i = 1; i <= n; i++) {
        edges[i].clear();
    }
    memset(import, 0, sizeof(import));
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n, s;
        cin >> n >> s;

        reset(n);

        while (s--) {
            int prev, cur;
            cin >> prev;
            while (cin >> cur, cur > 0) {
                edges[prev].push_back(cur);
                edges[cur].push_back(prev);
                import[prev]++;
                prev = cur;
            }
            import[prev]++;
        }

        int ans = 0, min_dist = INT32_MAX;

        for (int i = 1; i <= n; i++) {
            if (import[i] > 1) {
                int dist = shortest_path(n, i);

                if (dist < min_dist) {
                    min_dist = dist;
                    ans = i;
                }
            }
        }

        cout << "Krochanska is in: " << ans << endl;
    }

    return 0;
}