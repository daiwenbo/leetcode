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

