/*
Given an integer matrix, find the length of the longest increasing path.
From each cell, you can either move to four directions: left, right, up or down. 
You may NOT move diagonally or move outside of the boundary (i.e. wrap-around is not allowed).

Example 1:
nums = [
  [9,9,4],
  [6,6,8],
  [2,1,1]
]

Return 4
The longest increasing path is [1, 2, 6, 9].

Example 2:
nums = [
  [3,4,5],
  [3,2,6],
  [2,2,1]
]

Return 4
The longest increasing path is [3, 4, 5, 6]. Moving diagonally is not allowed.
*/

/*Runtime: 836 ms
Your runtime beats 2.01% of cpp submissions.
*/

class Solution {
public:
    int num_row;
    int num_col;
    int longestIncreasingPath(vector<vector<int>>& matrix) {
        /*generate a graph based on the number values, and then do topology sorting */
        //matrix size?
        num_row = matrix.size();
        if (num_row>0){
            num_col = matrix[0].size();
        }
        
        if (num_row == 0 || num_col == 0){
            return 0;
        }
        
        //generate graph, adjIn/adjOut list representation
        unordered_map< int, vector<int> > adjOut;
        unordered_map< int, vector<int> > adjIn;
        
        //initialize, to make sure each node has an entry in the adj list
        for (int i=0; i<num_row*num_col; i++){
            vector<int> dummy;
            adjOut[i] = dummy;
            adjIn[i] = dummy;
        }
        
        for (int i=0; i<num_row; i++){
            for (int j=0; j<num_col; j++){
                //for node[i, j], check all its neighors if exist
                int nodeId = locationToId(i, j);
                int node = matrix[i][j];
                //left
                if (j-1>=0){
                    if (matrix[i][j-1] > node){
                        int neighborId = locationToId(i, j-1); 
                        //node point to neighbor
                        adjOut[nodeId].push_back(neighborId);
                        adjIn[neighborId].push_back(nodeId);
                    }
                }
                //right
                if (j+1<num_col){
                    if (matrix[i][j+1] > node){
                        int neighborId = locationToId(i, j+1); 
                        //node point to neighbor
                        adjOut[nodeId].push_back(neighborId);
                        adjIn[neighborId].push_back(nodeId);
                    }
                }
                //up
                if (i-1>=0){
                    if (matrix[i-1][j] > node){
                        int neighborId = locationToId(i-1, j); 
                        //node point to neighbor
                        adjOut[nodeId].push_back(neighborId);
                        adjIn[neighborId].push_back(nodeId);
                    }
                }
                //down
                if (i+1<num_row){
                    if (matrix[i+1][j] > node){
                        int neighborId = locationToId(i+1, j); 
                        //node point to neighbor
                        adjOut[nodeId].push_back(neighborId);
                        adjIn[neighborId].push_back(nodeId);
                    }
                }
            }// end of for all cols
        }//end of for all rows
        
        //now the adjOut and adjIn has been built up, do topology sorting
        
        int round = 0;
        vector<int> nodesToRemove(1, -1);
        while ( !nodesToRemove.empty() && !adjIn.empty() ){
            nodesToRemove.clear();
            //find which nodes has 0 in-degree
            for (auto& inNode: adjIn){
                if (inNode.second.empty()){
                    nodesToRemove.push_back( inNode.first );
                }
            }
            
            if (!nodesToRemove.empty()){
                round++;
            }
            for (auto nodeToRemove: nodesToRemove){
                //for nodeToRemove, remove it from "inAdj", and also all its outgoing edges
                adjIn.erase(nodeToRemove);
                
                for (auto downStreamNode : adjOut[nodeToRemove]){
                    adjIn[downStreamNode].pop_back();
                }
            }
        }//end of while loop
        
        return round;
    }
    
    int locationToId(int row, int col){
        assert(row < num_row && col < num_col);
        return row*num_col + col; 
    }
};
