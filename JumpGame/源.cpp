#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

class Solution {
public:
	bool canJump(vector<int>& nums) {
		int n = nums.size();
		int rightmost = 0;
		for (int i = 0; i < n; i++) {
			if (i <= rightmost) {
				rightmost = max(rightmost, i + nums[i]);
				if (rightmost >= n - 1) {
					return true;
				}
			}
		}
		return false;
	}
};

int main() {
	int a[] = { 3,2,1,0,4 };
	vector<int> nums(a, a + 6);
	Solution s;
	cout<<s.canJump(nums);
	return 0;
}