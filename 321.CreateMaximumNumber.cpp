/*
Given two arrays of length m and n with digits 0-9 representing two numbers. 
Create the maximum number of length k <= m + n from digits of the two. 
The relative order of the digits from the same array must be preserved. 
Return an array of the k digits. You should try to optimize your time and space complexity.

Example 1:
nums1 = [3, 4, 6, 5]
nums2 = [9, 1, 2, 5, 8, 3]
k = 5
return [9, 8, 6, 5, 3]

Example 2:
nums1 = [6, 7]
nums2 = [6, 0, 4]
k = 5
return [6, 7, 6, 0, 4]

Example 3:
nums1 = [3, 9]
nums2 = [8, 9]
k = 3
return [9, 8, 9]
*/

/*Runtime: 24 ms
Your runtime beats 98.76% of cpp submissions.
*/
class Solution {
public:
    // Get the max number from an array. 
    void getMax(int* num, // array. Should have capacity >= len 
        int len, // array length 
        int* result, // buffer for getting back the result. Should have capacity >= t 
        int t) // number of digit of the max number. t <= len. 
        { 
        int n; int top = 0; // Take the result as a stack and this is the top index of the stack.
        // Fill the first element
        result[0] = num[0];
    
        for(int i = 1; i < len; ++i)
        {
            n = num[i];
            // If top >= 0 AND result[top] is smaller than n AND there is enough remaining numbers to fill the result
            while(top >= 0 && result[top] < n && (t - top) <= (len - i) )
            {
                // Pop the top element.
                top--;
            }
    
            // Move to the new top
            top++;
            if(top < t)
                result[top] = n;
            else
               top = t - 1;  // stay at the last element.
        }
    }
    
    // Merge two numbers so they generate the max number.  This merge runs in linear time O(m + n)
    void merge(int* num1,    // num1 with length of len1
               int len1, 
               int* num2,    // num2 with length of len2
               int len2, 
               int* result)  // result with length of (len1 + len2)
    {
        int i;
        int j, k;
        int t = len1 + len2;
        for(i = 0, j = 0, k = 0; i < t; ++i)
        {
            if(j < len1 && k < len2)
            {
                // Pick the larger number
                if(num1[j] > num2[k])
                    result[i] = num1[j++];
                else if(num1[j] < num2[k])
                    result[i] = num2[k++];
                else // if equal
                {
                    int remaining1 = len1 - j;
                    int remaining2 = len2 - k;
                    if(remaining1 > remaining2)
                    {
                        // Compare remaining part.  Pick the larger one.
                        if(memcmp(num1 + j, num2 + k, sizeof(int) * remaining2) >= 0)
                            result[i] = num1[j++];
                        else
                            result[i] = num2[k++];
                    }
                    else
                    {
                        if(memcmp(num2 + k, num1 + j, sizeof(int) * remaining1) >= 0)
                            result[i] = num2[k++];
                        else
                            result[i] = num1[j++];
                    }
                }
            }
            else if(j < len1 && k >= len2)
            {
                // Keep adding the remaining numbers
                result[i] = num1[j++];
            }
            else // if(j >= len1 && k < len2)
            {
                // Keep adding the remaining numbers
                result[i] = num2[k++];
            }
        }
    }
    
    vector<int> maxNumber(vector<int>& nums1, vector<int>& nums2, int k) {
    
        // Allocate memory
        int* num = new int[k * 4];
        int* buf1 = num + k;
        int* buf2 = num + k * 2;
        int* temp = num + k * 3;
        int memSize = sizeof(int) * k;
        memset(num, 0, memSize);
    
        int i;
        int t1, t2;
        int len1 = nums1.size();
        int len2 = nums2.size();
        if(len1 == 0 && len2 > 0)
        {
            getMax(&nums2[0], len2, num, k);
        }
        else if(len1 > 0 && len2 == 0)
        {
            getMax(&nums1[0], len1, num, k);
        }
        else if(len1 > 0 && len2 > 0)
        {
            if(len1 <= len2)
            {
                int smaller = len1 < k ? len1 : k;
                for(i = k - len2; i <= smaller; ++i)
                {
                    // Tranverse the numbers with all possible combinations
                    t1 = i;
                    t2 = k - i;
                    getMax(&nums1[0], len1, buf1, t1);
                    getMax(&nums2[0], len2, buf2, t2);
                    merge(buf1, t1, buf2, t2, temp);
                    if(memcmp(num, temp, memSize) < 0)
                        memcpy(num, temp, memSize);
                }
            }
            else
            {
                int smaller = len2 < k ? len2 : k;
                for(i = k - len1; i <= smaller; ++i)
                {
                    // Tranverse the numbers with all possible combinations
                    t2 = i;
                    t1 = k - i;
                    getMax(&nums1[0], len1, buf1, t1);
                    getMax(&nums2[0], len2, buf2, t2);
                    merge(buf1, t1, buf2, t2, temp);
                    if(memcmp(num, temp, memSize) < 0)
                        memcpy(num, temp, memSize);
                }
            }
        }
    
        vector<int> rev(num, num + k);
        delete [] num;
    
        return rev;
    
    }
};


/*my owen solution, same idea, but use vector instead of pointer-based array. it's slower
Runtime: 212 ms. Your runtime beats 33.53% of cpp submissions. */
/*test cast: 
[2,1,7,8,0,1,7,3,5,8,9,0,0,7,0,2,2,7,3,5,5]
[2,6,2,0,1,0,5,4,5,5,3,3,3,4]
35
*/

class Solution {
public:
    bool greater(vector<int>& a, vector<int>& b) const{
        vector<int>::iterator ia = a.begin();
        vector<int>::iterator ib = b.begin();
        
        while (*ia == *ib && ia != a.end() && ib != b.end() ){
            ia++;
            ib++;
        }
        
        return *ia > *ib;
    }

    vector<int> maxNumber(vector<int>& nums1, vector<int>& nums2, int k) {
        vector<int> res(k, 0);
        
        int m = nums1.size();
        int n = nums2.size();
        
        for (int i=0; i<=m; i++){
            
            int j = k-i;
            if (j<0 || j>n){
                continue;
            }
            
            //cout<<i<<" "<<j<<endl;
            
            vector<int> from1 = maxNumberFromOneArray(nums1, i);
            vector<int> from2 = maxNumberFromOneArray(nums2, j);
            
            /*
            cout<<"from1 and from2:"<<endl;
            for (auto a: from1){
                cout<<a<<" ";
            }
            cout<<endl;
            for (auto a: from2){
                cout<<a<<" ";
            }
            cout<<endl;
            */
            
            vector<int> merged;
            merged.clear();
            //merge these two
            {
                vector<int>::iterator it1 = from1.begin();
                vector<int>::iterator it2 = from2.begin();
                
                while ( it1 != from1.end() || it2 != from2.end() ){
                    if ( it1 != from1.end() && it2 != from2.end() ){
                        if (*it1==*it2){
                           //this is tricky, consider: 
                           //s1: from1: 5 5 6 2, from2: 5 5 8 1 => wrong: 55655821, correct: 55855621
                           //s2: from1:  1, from2: 1 1 0
                           //s2: from1: 1 1, from2: 1 1 3 4
                           int remining1 = from1.end()-it1;
                           int remining2 = from2.end()-it2;
                           
                           //cout<<"R1 and R2: "<<remining1<<" "<<remining2<<endl;
                           
                           vector<int>::iterator it1Later = it1;
                           vector<int>::iterator it2Later = it2;
                           
                           if (remining1 > remining2){
                               //the remining from2 is shorter
                               int step = remining2-1;
                               while (step > 0 && *it1Later == *it2Later){
                                   it1Later++;
                                   it2Later++;
                                   step--;
                               }
                               
                               if (*it1Later >= *it2Later){
                                   //use from1
                                   merged.push_back(*it1);
                                   it1++;
                               }else{
                                   merged.push_back(*it2);
                                   it2++;
                               }
                           }else{
                               //the remining from1 is shorter
                               int step = remining1-1;
                               while (step > 0 && *it1Later == *it2Later){
                                   it1Later++;
                                   it2Later++;
                                   step--;
                               }
                               
                               if (*it2Later >= *it1Later){
                                   //use from1
                                   merged.push_back(*it2);
                                   it2++;
                               }else{
                                   merged.push_back(*it1);
                                   it1++;
                               }
                           }
                           
                        }else if (*it1>*it2){
                           merged.push_back(*it1);
                           it1++;
                        }
                        else{
                            merged.push_back(*it2);
                            it2++;
                        }
                    }else if (it1!= from1.end()){
                        //only it1 is valid
                        merged.push_back(*it1);
                        it1++;
                    }else if (it2!= from2.end()){
                        //only it2 is valid
                        merged.push_back(*it2);
                        it2++;
                    }
                }
            }
            
            if ( greater(merged, res) ){
                res = merged;
            }
        }
        
        return res;
    }
    
    vector<int> maxNumberFromOneArray(vector<int>& nums, int k){
		vector<int> res;
		if (k==0){
		    return res;
		}
		
		res.push_back(nums[0]);
		
		int size = nums.size();
		for (int i=1; i<size; i++){
			// x = k-res.size(): the res still need x numbers
			// y = size-i-1: the array has y elements left, excluding item i;
			while (!res.empty() && nums[i] > res.back() && k-res.size() <= size-i-1){
				res.pop_back();
			}
			
			if (res.size() < k){
				res.push_back(nums[i]);
			}
			
		}
		
		return res;
	}
};

