/*
There are a total of n courses you have to take, labeled from 0 to n - 1.
Some courses may have prerequisites, for example to take course 0 you have to 
first take course 1, which is expressed as a pair: [0,1]

Given the total number of courses and a list of prerequisite pairs, 
return the ordering of courses you should take to finish all courses.

There may be multiple correct orders, you just need to return one of them. 
If it is impossible to finish all courses, return an empty array.

For example:
2, [[1,0]]
There are a total of 2 courses to take. To take course 1 you should have finished course 0. So the correct course order is [0,1]

4, [[1,0],[2,0],[3,1],[3,2]]
There are a total of 4 courses to take. To take course 3 you should have finished both courses 1 and 2. 
Both courses 1 and 2 should be taken after you finished course 0. So one correct course order is [0,1,2,3]. 
Another correct ordering is[0,2,1,3].
*/

/*
Runtime: 636 ms
Your runtime beats 5.53% of cpp submissions.
*/

class Solution {
public:
    vector<int> findOrder(int numCourses, vector<pair<int, int>>& prerequisites) {
        /*try to perform topology sorting: repeatly find nodes with in degree of 0
        if can not consume all node by this way, means there is a cycle, return false
        */
        vector<int> res;
        
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
                res.push_back(nodeToRemove);
                in.erase(nodeToRemove);
                for(auto downStreamNode : out[nodeToRemove]){
                    in[downStreamNode].resize(in[downStreamNode].size()-1);
                    if ( in[downStreamNode].size() == 0){
                        in[downStreamNode].clear();
                    }
                }
            }
        }
        
        if (in.empty()){
            //all nodes have been sorted
            return res;
        }else{
            vector<int> dummy;
            return dummy;
        }
    }
};
