/*
A robot is located at the top-left corner of a m x n grid (marked 'Start' in the diagram below).

The robot can only move either down or right at any point in time. The robot is trying to reach 
the bottom-right corner of the grid (marked 'Finish' in the diagram below).

How many possible unique paths are there?
*/

/*Your runtime beats 5.51% of cpp submissions.*/

class Solution {
public:
    int uniquePaths(int m, int n) {
        /*DP: array p[m, n], p[i, j] represents the num of unique paths from start to [i, j]
         p[0, n] = 1, p[n, 0] = 1;
         optimal structure: p[i, j] = p[i-1, j] + p[i, j-1]
         return p[m-1, n-1]
        */
        if (m==0 || n==0){
            return 0;
        }
        
        vector< vector<int> > p;
        p.resize(m);
        for (int i=0; i<m; i++){
            p[i].resize(n, 1);
        }
        
        for (int i=1; i<m; i++){
            for (int j=1; j<n; j++){
                p[i][j] = p[i-1][j] + p[i][j-1];
            }
        }
        
        return p[m-1][n-1];
    }
};
