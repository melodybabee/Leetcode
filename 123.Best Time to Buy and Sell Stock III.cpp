题意：
122 follow up, 只能交易两次，求最大利润。
思路：
1.使用一个通用的方法限制交易的次数，本题把限制的次数更改为2次
2.设置两个数组，分别表示局部最优和全局最优，local[i][j]表示在第i天可以最多进行j次交易，且最后一次交易在最后一天的最大利润
global[i][j]表示到达第i天之后最多可以进行的j次交易的利润。都分别是一个二维数组。
3.local[i][j] = max(global[i - 1][j - 1] + max(diff, 0), local[i - 1][j] + diff)
局部最优表示为前一天少交易一次+本次的利润的和（本次赚钱），与上一天交易规定次数的利润+本次消费额中的较大值。
local[i-1][j]比如包含第i-1天卖出的交易，所以现在变成第i天卖出，并不会增加交易次数，而且这里无论diff是不是大于0都一定要加上，因为否则就不满足local[i][j]必须在最后一天卖出的条件了
4.global[i][j] = max(global[i-1][j],local[i][j]);
当天的全局最优是当次的局部最优和前一天的全局最优之间的较大值。
5.最后返回全局最优中的最后一个元素的值。
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        if(prices.empty()) return 0;
        vector<vector<int>>local(prices.size(),vector<int>(3,0));
        vector<vector<int>>global(prices.size(),vector<int>(3,0));
        for(int i = 1; i < prices.size();++i){
            int diff = prices[i]- prices[i-1];
            for(int j = 1; j <= 2; ++j){
                local[i][j] = max(global[i-1][j-1] + max(diff,0), local[i-1][j]+diff);
                global[i][j] = max(global[i-1][j],local[i][j]);
            }
        }
        return global[prices.size()-1][2];
    }
};

优化：可以优化为一维数组。【待学习】
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        if(prices.empty()) return 0;
        vector<int>local(3,0);
        vector<int>global(3,0);
        for(int i = 0; i < prices.size()-1;++i){
            int diff = prices[i+1]- prices[i];
            for(int j = 2; j >= 1; --j){
                local[j] = max(global[j-1] + max(diff,0), local[j]+diff);
                global[j] = max(global[j],local[j]);
            }
        }
        return global[2];
    }
};

补充：
1.DP汇总
动态规划是利用存储历史信息使得未来需要历史信息时不需要重新计算，从而达到降低时间复杂度， 用空间复杂度换取时间复杂度目的的方法。
1）确定递推量。 明确DP数组或者变量表示的含义。
这一步需要确定递推过程中要保留的历史信息数量和具体含义，同时也会定下动态规划的维度； 
2）推导递推式。 动态转移方程。
根据确定的递推量，得到如何利用存储的历史信息在有效时间（通常是常量或者线性时间）内得到当前的信息结果； 
3）计算初始条件。设置初始值。
有了递推式之后，计算初始条件，就可以根据递推式得到我们想要的结果了。 通常初始条件都是比较简单的情况， 一般来说直接赋值即可； 
4）（可选）考虑存储历史信息的空间维度。这一步是基于对算法优化的考虑， 一般来说几维动态规划我们就用几维的存储空间是肯定可以实现的。 
但是有时我们对于历史信息的要求不高，比如这一步只需要用到上一步的历史信息，而不需要更早的了，那么我们可以只存储每一步的历史信息，每步覆盖上一步的信息，这样便可以少一维的存储空间，从而优化算法的空间复杂度。 
动态规划的时间复杂度是O(（维度）×（每步获取当前值所用的时间复杂度））。基本上按照上面的思路，动态规划的题目都可以解决，不过最难的一般是在确定递推量，一个好的递推量可以使得动态规划的时间复杂度尽量低。 
2.一维动态规划：（递推公式）
确定递归量， 然后按递归式迭代就可以得到。
例题：
070 Climbing Stairs
091 Decode Ways
096 Unique Binary Search Trees
3.一维数组动态规划：（设置变量记录之前的状态，全局最优／局部最优）
这种方法中我们通常维护两个量， 一个是到目前为止最好的结果信息（全局最优）， 另一个必须包含新加进来的元素的最好的结果信息（局部最优）
例题：
053 Maximum Subarray
121 Best Time to Buy and Sell Stock
152 Maximum Product Subarray