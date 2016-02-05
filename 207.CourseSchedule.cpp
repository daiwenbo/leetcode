class Solution {
public:
    bool canFinish(int numCourses, vector<pair<int, int>>& prerequisites) {
        /*build a adj list representation of the graph, and then 
        look for a back edge (an edge connecting to a grey node)*/
        
        //build the adj list
        unordered_map< int, vector<int> > adj;
        unordered_map<int, int> nodeColor;
        
        int num_edges = prerequisites.size();
        for(int i=0; i<num_edges; i++){
            adj[prerequisites[i].first].push_back(prerequisites[i].second);
            nodeColor[prerequisites[i].first] = 0;
            nodeColor[prerequisites[i].second] = 0;
        }
        
        stack<int> s;
        for (
        unordered_map<int, int>::iterator nodeIdx = nodeColor.begin(); 
        nodeIdx != nodeColor.end();
        nodeIdx ++ ){
            if (nodeIdx->second == 0){
                //if this node is white, use it as a root
                s.push(nodeIdx->first);
                
                while( !s.empty() ){
                    int u = s.top(); s.pop();
                    nodeColor[u] = 1; //grey
                    //push all u's neighbors into stack (check for back edges first)
                    vector<int> uAdj = adj[u];
                    int num_adj = uAdj.size();
                    for(int i=0; i<num_adj; i++){
                        if (nodeColor[uAdj[i]] == 0){
                            s.push(uAdj[i]);
                        }else if (nodeColor[uAdj[i]] == 1){
                            //is gray, then edge u->uAdj[i] is a back edge, there is a cycle
                            return false; 
                        }
                    }
                    nodeColor[u] = 2; //pain it black
                }//end of while loop
            }
        }//end of for loop
        
        return true;
    }
};
