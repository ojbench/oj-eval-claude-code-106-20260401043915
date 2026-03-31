#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <cstring>
using namespace std;

const int MAXN = 100005;
vector<int> adj[MAXN];
int subtree_size[MAXN];
int n, k;
bool visited[MAXN];

// Calculate subtree sizes with node u as root, parent p
void dfs(int u, int parent) {
    subtree_size[u] = 1;
    for (int v : adj[u]) {
        if (v != parent) {
            dfs(v, u);
            subtree_size[u] += subtree_size[v];
        }
    }
}

// Check if removing node u satisfies the condition
bool check(int u) {
    // For each neighbor of u, calculate the size of component when u is removed
    for (int v : adj[u]) {
        int component_size;

        // If v is in the subtree of u (when rooted at 1)
        // We need to check this more carefully
        // Actually, we need to calculate component sizes properly

        // Let's use a different approach: for each neighbor v of u,
        // do a DFS from v without passing through u
        memset(visited, false, sizeof(visited));
        visited[u] = true;

        // Count size of component containing v
        function<int(int)> count_component = [&](int node) -> int {
            visited[node] = true;
            int size = 1;
            for (int next : adj[node]) {
                if (!visited[next]) {
                    size += count_component(next);
                }
            }
            return size;
        };

        component_size = count_component(v);

        if (component_size > k) {
            return false;
        }
    }
    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> k;

    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    vector<int> valid_nodes;

    for (int u = 1; u <= n; u++) {
        if (check(u)) {
            valid_nodes.push_back(u);
        }
    }

    if (valid_nodes.empty()) {
        cout << "None" << endl;
    } else {
        sort(valid_nodes.begin(), valid_nodes.end(), greater<int>());
        for (int i = 0; i < valid_nodes.size(); i++) {
            if (i > 0) cout << " ";
            cout << valid_nodes[i];
        }
        cout << endl;
    }

    return 0;
}
