#include <iostream>
#include<vector>
using namespace std;

class Solution {
public:
	vector<int> twoSum(vector<int>& nums, int target) {
		vector<int> ret(2, 1);
		int high, low, mid, sum;
		high = nums.size();
		low = 0;
		mid = (high + low) / 2;
		for (int i = 0; i < nums.size(); i++)
			for (int j = i + 1; j < nums.size(); j++) {
				if (nums[i] + nums[j] == target) {
					ret[0] = i;
					ret[1] = j;
					return ret;
				}
			}
		return ret;
	}
};

int main()
{
	Solution s;
	int a[] = { 3,2,4 };
	vector<int> nums(a, a+3);
	vector<int> b(2, 1);
	b=s.twoSum(nums, 6);
	cout << "[" << b[0] << "," << b[1] << "]" << endl;
}
