# Problem 106 Solution Summary

## Problem Description
Split an island network (tree structure) by removing one island U such that each resulting connected component has at most k islands. Output all valid island numbers in descending order.

## Solution Approach

### Algorithm
1. **Build adjacency list** from input edges (O(n))
2. **Root the tree** at node 1 and compute subtree sizes via DFS (O(n))
3. **Check each node** u from 1 to n:
   - For each neighbor v of u:
     - If v is the parent: component size = n - subtree_size[u]
     - If v is a child: component size = subtree_size[v]
   - If all components ≤ k, then u is valid
4. **Sort and output** valid nodes in descending order

### Time Complexity
- **O(n)** - One DFS pass + O(1) check per node
- Previous O(n²) approach with repeated DFS caused TLE

### Space Complexity
- **O(n)** - Adjacency list, subtree sizes, parent array

## Submissions

### Submission 1 (ID: 767145)
- **Score**: 60/100
- **Status**: Time Limit Exceeded on test cases 7-10
- **Issue**: O(n²) algorithm with repeated DFS calls
- **Passed**: Test cases 1-6

### Submission 2 (ID: 767168)
- **Score**: 100/100 ✓
- **Status**: Accepted on all test cases
- **Optimization**: Single DFS pass with O(1) component size lookup
- **Max Time**: 29ms (well within 1000ms limit)
- **Max Memory**: 10.5 MB (well within 64 MB limit)

## Key Insights
- When node u is removed from a tree, it splits into |adj[u]| components
- By rooting the tree, we can precompute all subtree sizes efficiently
- Each component's size can be determined in O(1) using the precomputed values
- No need to repeatedly traverse the tree for each candidate node

## Test Results
All 10 test groups passed with "accepted" status.
