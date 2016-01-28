/*
Clone an undirected graph. Each node in the graph contains a label and a list of its neighbors.


OJ's undirected graph serialization:
Nodes are labeled uniquely.

We use # as a separator for each node, and , as a separator for node label and each neighbor of the node.
As an example, consider the serialized graph {0,1,2#1,2#2,2}.

The graph has a total of three nodes, and therefore contains three parts as separated by #.

First node is labeled as 0. Connect node 0 to both nodes 1 and 2.
Second node is labeled as 1. Connect node 1 to node 2.
Third node is labeled as 2. Connect node 2 to node 2 (itself), thus forming a self-cycle.
Visually, the graph looks like the following:

       1
      / \
     /   \
    0 --- 2
         / \
         \_/
*/

/**
 * Definition for undirected graph.
 * struct UndirectedGraphNode {
 *     int label;
 *     vector<UndirectedGraphNode *> neighbors;
 *     UndirectedGraphNode(int x) : label(x) {};
 * };
 */
class Solution {
public:
    UndirectedGraphNode *cloneGraph(UndirectedGraphNode *node) {
        if (!node){
            return NULL;
        }
        
        //do a bfs on the original graph, copy the nodes during that bfs
        //need a map to record the mapping between original nodes and copied nodes
        map<UndirectedGraphNode*, UndirectedGraphNode*> mapOrigCopied;
        
        queue<UndirectedGraphNode*> bfsQ; //need this for bfs
        //start from the given node
        bfsQ.push(node);
        
        while(!bfsQ.empty()){
            UndirectedGraphNode* u = bfsQ.front();
            bfsQ.pop();
            
            //copy this node, if it does not exist in the map yet
            if (mapOrigCopied.find(u) == mapOrigCopied.end()){
                UndirectedGraphNode* copyNode = new UndirectedGraphNode(u->label);
                mapOrigCopied[u] = copyNode;
            }
            
            //handle all the neighbors of u
            int numNeighbors = u->neighbors.size();
            for(int i=0; i<numNeighbors; i++){
                
                UndirectedGraphNode* v = u->neighbors[i];

                //make a copy of this v, add the copy into u'copy's neighbor list
                if (mapOrigCopied.find(v)==mapOrigCopied.end()){
                    UndirectedGraphNode* copyNode = new UndirectedGraphNode(v->label);
                    mapOrigCopied[v] = copyNode;
                    bfsQ.push(v); //means this v has not been visited before, so add it into the queue
                }
                
                mapOrigCopied[u]->neighbors.push_back(mapOrigCopied[v]);
            }
        }
        
        return mapOrigCopied[node];
    }
};
