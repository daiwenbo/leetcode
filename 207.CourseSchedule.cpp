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


/*a faster solution*/
/* 396 ms, Your runtime beats 11.88% of cpp submissions.*/
class Solution {
public:
    bool canFinish(int numCourses, vector<pair<int, int>>& prerequisites) {
        /*try to perform topology sorting: repeatly find nodes with in degree of 0
        if can not consume all node by this way, means there is a cycle, return false
        */
        unordered_map<int, vector<int> > out;
        unordered_map<int, vector<int> > in;
        
        for(int i=0; i<numCourses; i++){
            vector<int> dummy;
            out[i] = dummy;
            in[i] = dummy;
        }
        
        //initialize the out and in adj list
        for(auto& p : prerequisites){
            // dependency chart: p.first depends on p.second, 
            // so nodes are: p.second->p.first
            out[p.second].push_back(p.first);
            in[p.first].push_back(p.second);
        }
        
        vector<int> nodesToRemove(1, -1); //initialized it with some random value
        while ( !nodesToRemove.empty() && !in.empty()){
            //find all the 0-in nodes
            nodesToRemove.clear();
            for (auto& inNode: in){
               if ( inNode.second.empty() ){
                   //node i has no in-edge
                   nodesToRemove.push_back(inNode.first);
               } 
            }
            
            //remove all the 0-in nodes from "in", 
            //also remove all its outgoing edges, reflect the change in "in"
            for(auto nodeToRemove : nodesToRemove){
                in.erase(nodeToRemove);
                for(auto downStreamNode : out[nodeToRemove]){
                    in[downStreamNode].resize(in[downStreamNode].size()-1);
                    if ( in[downStreamNode].size() == 0){
                        in[downStreamNode].clear();
                    }
                }
            }
        }
        
        return in.empty();
        
    }
};
