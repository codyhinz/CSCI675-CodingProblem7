class Solution {
public:
    int minMoves(vector<int>& nums, int k) {
        // Store the indices of all 1's in the array
        vector<int> arr;
        for (int i = 0; i < nums.size(); ++i) {
            if (nums[i]) {
                arr.push_back(i);
            }
        }
        
        int m = arr.size(); // Number of 1's in the original array
        
        // Create a prefix sum array of the indices of 1's
        // s[i] represents the sum of indices of first i 1's
        long s[m + 1];
        s[0] = 1; // Start with 1 to adjust for 0-based indexing
        for (int i = 0; i < m; ++i) {
            s[i + 1] = s[i] + arr[i];
        }
        
        long ans = 1L << 60; // Initialize answer to a very large number
        
        // Split k into two parts: x (left half) and y (right half)
        int x = (k + 1) / 2;
        int y = k - x;
        
        // Iterate through all possible center positions for the k consecutive 1's
        for (int i = x - 1; i < m - y; ++i) {
            int j = arr[i]; // Current center position
            
            // Calculate sum of indices for left and right parts
            int ls = s[i + 1] - s[i + 1 - x]; // Sum of x indices to the left
            int rs = s[i + 1 + y] - s[i + 1]; // Sum of y indices to the right
            
            // Calculate moves needed for left part
            // Ideal positions: j, j-1, j-2, ..., j-x+1
            // a = ideal sum - actual sum
            long a = (j + j - x + 1L) * x / 2 - ls;
            
            // Calculate moves needed for right part
            // Ideal positions: j+1, j+2, ..., j+y
            // b = actual sum - ideal sum
            long b = rs - (j + 1L + j + y) * y / 2;
            
            // Update the minimum moves needed
            ans = min(ans, a + b);
        }
        
        return ans;
    }
};