/*
For a undirected graph with tree characteristics, we can choose any node as the root. 
The result graph is then a rooted tree. Among all possible rooted trees, those with minimum height 
are called minimum height trees (MHTs). Given such a graph, write a function to find all the MHTs 
and return a list of their root labels. 

Format
 The graph contains n nodes which are labeled from 0 to n - 1. You will be given the number n 
 and a list of undirected edges (each edge is a pair of labels). 

You can assume that no duplicate edges will appear in edges. Since all edges are undirected, 
[0, 1] is the same as [1, 0] and thus will not appear together in edges. 

Example 1: 
Given n = 4, edges = [[1, 0], [1, 2], [1, 3]] 
        0
        |
        1
       / \
      2   3
return  [1] 

Example 2: 
Given n = 6, edges = [[0, 3], [1, 3], [2, 3], [4, 3], [5, 4]] 
     0  1  2
      \ | /
        3
        |
        4
        |
        5
return  [3, 4] 
*/

/*Runtime: 1684 ms. Your runtime beats 1.86% of cpp submissions*/

class Solution {
public:
    vector<int> findMinHeightTrees(int n, vector<pair<int, int>>& edges) {
        /*idea: peel the onion. repeatly remove nodes with degree of 1, and their edges, 
        until there is only 1 or 2 nodes left*/
        vector<int> res;
        if (n<=2){
            for (int i=0; i<n; i++){
                res.push_back(i);
            }
            return res;
        }
        
        map<int, vector<int> > adj;
        map<int, int> degreeCount;
        
        for (int i=0; i<n; i++){
            vector<int> dummy;
            adj[i] = dummy;
            degreeCount[i] = 0;
        }
        
        //initialize the adj matrix
        for (auto& edge: edges){
            int u = edge.first;
            int v = edge.second;
            adj[u].push_back(v);
            adj[v].push_back(u);
            degreeCount[u]++;
            degreeCount[v]++;
        }
        
        //repeatly remove nodes with degree of 1
        vector<int> nodes1degree;
        while (degreeCount.size() > 2){
           nodes1degree.clear();
           for (map<int, int>::iterator it=degreeCount.begin();
            it != degreeCount.end();
            it++){
                if (it->second==1){
                    nodes1degree.push_back(it->first);
                }
            }
           
           for (auto node2remove : nodes1degree){
               //for all the adj node of node2remove, reduce their degree by 1
               for (auto adjNode : adj[node2remove]){
                   if (degreeCount.find(adjNode) != degreeCount.end()){
                       degreeCount[adjNode]--;
                   }
               }
               //remove node2remove from degreeCount
               degreeCount.erase(node2remove);
               
           }
        }
        
        
        for (map<int, int>::iterator it = degreeCount.begin();
            it != degreeCount.end();
            it++){
            res.push_back(it->first);
        }
        
        return res;
    }
};
