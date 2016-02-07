/*
Given an integer array nums, find the sum of the elements between indices i and j (i ≤ j), inclusive.

The update(i, val) function modifies nums by updating the element at index i to val.
Example:
Given nums = [1, 3, 5]

sumRange(0, 2) -> 9
update(1, 2)
sumRange(0, 2) -> 8
Note:
The array is only modifiable by the update function.
You may assume the number of calls to update and sumRange function is distributed evenly.
*/
/* Runtime: 1728 ms. Your runtime beats 39.31% of cpp submissions.*/

class NumArray {
public:
    /*implement a Binary-Indexed-Tree (BIT), update and getSum has complexity of o(logn)*/
    
    //the tree is stored in an array
    int size;
    vector<int> bit;
    vector<int> v;
    
    NumArray(vector<int> &nums) {
        size = nums.size();
        v.resize(size, 0); //store value of nums
        bit.resize(size+1, 0);
        
        for (int i=0; i<size; i++){
            update(i, nums[i]);
        }
    }

    void update(int i, int val) {
    	int origV = v[i];
    	v[i] = val;
    	
        int index = i+1;
        
        int val_to_add = val - origV;
        while ( index <= size){
            bit[index] += val_to_add;
            index += (index & -index);
        }
    }
    
    int getSum(int i){
        int index = i+1;
        
        int sum = 0;
        while (index > 0){
            sum += bit[index];
            index -= (index & -index);
        }
        
        return sum;
    }

    int sumRange(int i, int j) {
        
        int sum1 = getSum(j);
        int sum2 = getSum(i-1);
        
        return sum1-sum2;
    }

};


// Your NumArray object will be instantiated and called as such:
// NumArray numArray(nums);
// numArray.sumRange(0, 1);
// numArray.update(1, 10);
// numArray.sumRange(1, 2);
