/*
There are a total of n courses you have to take, labeled from 0 to n - 1.

Some courses may have prerequisites, for example to take course 0 you have to first take course 1, 
which is expressed as a pair: [0,1]

Given the total number of courses and a list of prerequisite pairs, is it possible for you to finish all courses?

For example:
2, [[1,0]]
There are a total of 2 courses to take. To take course 1 you should have finished course 0. So it is possible.

2, [[1,0],[0,1]]
There are a total of 2 courses to take. To take course 1 you should have finished course 0, 
and to take course 0 you should also have finished course 1. So it is impossible.
*/

/* 608ms. Your runtime beats 2.63% of cpp submissions */

class Solution {
public:
    unordered_map< int, vector<int> > adj;
    unordered_map<int, int> nodeColor;
    
    bool canFinish(int numCourses, vector<pair<int, int>>& prerequisites) {
        if (numCourses==0 || numCourses==1){
            return true;
        }
        /*build a adj list representation of the graph, and then 
        look for a back edge (an edge connecting to a grey node)*/
        
        //build the adj list
        int num_edges = prerequisites.size();
        for(int i=0; i<num_edges; i++){
            adj[prerequisites[i].first].push_back(prerequisites[i].second);
            nodeColor[prerequisites[i].first] = 0;
            nodeColor[prerequisites[i].second] = 0;
        }
        
        bool res = true;
        for (
        unordered_map<int, int>::iterator nodeIdx = nodeColor.begin(); 
        nodeIdx != nodeColor.end();
        nodeIdx ++ ){
            if (nodeIdx->second == 0){
                //if this node is white, use it as a root
                res &= dfs_visit(nodeIdx->first);
            }
        }//end of for loop
        
        return res;
    }
    
    bool dfs_visit(int u){
        bool res = true;
        
        nodeColor[u] = 1; //paint it grey
        vector<int> uAdj = adj[u];
        int num_adj = uAdj.size();
        for(int i=0; i<num_adj; i++){
            int v = uAdj[i];
            cout<<"Adj["<<u<<"]: "<<v<<" , color: "<<nodeColor[v]<<endl;
            if (nodeColor[v] == 0){
                res &= dfs_visit(v);
            }else if (nodeColor[v] == 1){
                //is grey, then edge u->uAdj[i] is a back edge, there is a cycle
                res = false; 
            }
        }
        nodeColor[u] = 2; //pain it black
        return res;
    }
};
