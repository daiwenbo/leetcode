/*
Given a 2D matrix matrix, find the sum of the elements inside the rectangle defined by 
its upper left corner (row1, col1) and lower right corner (row2, col2).

Range Sum Query 2D
The above rectangle (with the red border) is defined by (row1, col1) = (2, 1) 
and (row2, col2) = (4, 3), which contains sum = 8. 

Example:
Given matrix = [
  [3, 0, 1, 4, 2],
  [5, 6, 3, 2, 1],
  [1, 2, 0, 1, 5],
  [4, 1, 0, 1, 7],
  [1, 0, 3, 0, 5]
]
sumRegion(2, 1, 4, 3) -> 8
sumRegion(1, 1, 2, 2) -> 11
sumRegion(1, 2, 2, 4) -> 12

Note:
1.You may assume that the matrix does not change.
2.There are many calls to sumRegion function.
3.You may assume that row1 ≤ row2 and col1 ≤ col2.
*/

/*Runtime: 280ms. Your runtime beats 19.85% of cpp submissions*/

class NumMatrix {
public:
    int row;
    int col;
    vector<int> sum;
    
    NumMatrix(vector<vector<int>> &matrix) {
        row = matrix.size();
        if (row > 0) col = matrix[0].size();
        
        sum.resize(row*col+1, 0);
        
        for (int i=0; i<row; i++){
            for (int j=0; j<col; j++){
                int id = cordinate2id(i, j)+1;
                
                sum[id] = sum[id-1]+matrix[i][j]; //sum[i] is sum of matrix[0][0] - matrix[i-1]
            }
        }
    }

    int sumRegion(int row1, int col1, int row2, int col2) {
        int res = 0;
        for (int row=row1; row<=row2; row++){
            res += sum[cordinate2id(row, col2)+1] - sum[cordinate2id(row, col1)];
        }
        
        return res;
    }
    
    int cordinate2id(int i, int j){
        return i*col+j;
    }
};


// Your NumMatrix object will be instantiated and called as such:
// NumMatrix numMatrix(matrix);
// numMatrix.sumRegion(0, 1, 2, 3);
// numMatrix.sumRegion(1, 2, 3, 4);
