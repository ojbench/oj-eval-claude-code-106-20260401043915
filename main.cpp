#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 100005;
vector<int> adj[MAXN];
int subtree_size[MAXN];
int parent[MAXN];
int n, k;

// Calculate subtree sizes with node u as root, parent p
void dfs(int u, int p) {
    parent[u] = p;
    subtree_size[u] = 1;
    for (int v : adj[u]) {
        if (v != p) {
            dfs(v, u);
            subtree_size[u] += subtree_size[v];
        }
    }
}

// Check if removing node u satisfies the condition
bool check(int u) {
    // For node u, we need to check all components when u is removed
    // Components are:
    // 1. Each child subtree (when tree is rooted at 1)
    // 2. The "parent" component (rest of the tree)

    for (int v : adj[u]) {
        int component_size;

        if (v == parent[u]) {
            // This is the parent direction - component size is n - subtree_size[u]
            component_size = n - subtree_size[u];
        } else {
            // This is a child - component size is subtree_size[v]
            component_size = subtree_size[v];
        }

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

    // Root the tree at node 1 and calculate subtree sizes
    dfs(1, -1);

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
        for (size_t i = 0; i < valid_nodes.size(); i++) {
            if (i > 0) cout << " ";
            cout << valid_nodes[i];
        }
        cout << endl;
    }

    return 0;
}
