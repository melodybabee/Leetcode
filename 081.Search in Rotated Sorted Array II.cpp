题意：
在一个旋转的有可重复元素的数组中找到目标值。（033变形）
思路：
1.和033相同，因为数组是旋转的，所以需要判断下目标元素在数组的左边还是右边
2.不同之处是因为数字允许重复，因此有可能中间位置的元素与最右侧的元素相等，那么就不知道下一步应该从哪侧判断
那么如果是相等的情况，就把最右侧的元素向左移动一位，再进行比较，如果还相等就继续移动，直到移动到不同值为止
3.因为最快的情况是数组中的所有元素都是相等的，或者只有一个不相等的数字，那么T(n) = O(n)
class Solution {
public:
    bool search(vector<int>& nums, int target) {
        bool ret;
        int l = 0;
        int r = nums.size()-1;
        if(nums.size() == 0) return false;
        while(l <= r){
            int mid = l + (r-l)/2;
            if(nums[mid] == target) return true;
            else if(nums[mid] < nums[r]){
                if(target > nums[mid] && target <= nums[r]){
                    l = mid+1;
                }else r = mid-1;
            }else if(nums[mid] > nums[r]){
                if(target >= nums[l] && target < nums[mid]){
                    r = mid-1;
                }else l = mid+1;
            }else --r;
        }
        return false;
    }
};