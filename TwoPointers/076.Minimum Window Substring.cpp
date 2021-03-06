题意：
找到string中包含目标子数组的最小字符串。
思路：
1.首先把目标字符串中的字符依次放入hashtable中，再依次遍历长字符串。
2.每次遍历到一个，map的value减一，如果value仍然大于等于0，说明这一位在t中存在，++count；
3.当count的大小等于t的长度的时候，说明已经完全匹配上t,那么计算此时的string长度，取从头部开始string长度的子串
4.开始从左边界向右移动，依次增加map的value，如果value值大于0了，说明已经有字符不与t匹配了，那么count--,向右移动，重新进入循环。
class Solution {
public:
    string minWindow(string s, string t) {
        unordered_map<char,int>map;
        string ret = "";
        for(int i = 0; i < t.size();++i){
            ++map[t[i]];
        }
        int count = 0;
        int left = 0;
        int length = INT_MAX;
        for(int i = 0; i< s.size();++i){
            --map[s[i]];
            if(map[s[i]] >= 0) ++count;
            while(count == t.size()){
                if(length > i - left +1){
                    length = i - left + 1;
                    ret = s.substr(left,length);
                }
                ++map[s[left]];
                if(map[s[left]] > 0) --count;
                ++left;
            }
        }
        return ret;
    }
};

12.10复习：
注意：
1.用一个count计数来求出是否找到了其中一个满足条件的子序列。找到后左指针开始向右移动。
2.在目标字符串中的字符value大于等于1，不存在于目标字符串中的字符个数为0，减1的话会为负，因此大于等于0的就在目标字符串里面。
同理移动左边界的时候如果大于0，那么目标字符串的个数-1。
class Solution {
public:
    string minWindow(string s, string t) {
        unordered_map<char,int>map;
        int count = 0;
        int left = 0;
        int length = INT_MAX;
        string ret = "";
        for(auto c:t) ++map[c];
        for(int i = 0; i < s.size(); ++i){
            --map[s[i]];
            if(map[s[i]] >= 0) ++count;
            while(count == t.size()){
                int len = i - left+1;
                if(len < length){
                    length = len;
                    ret = s.substr(left,len);
                }
                ++map[s[left]];
                if(map[s[left]] > 0){
                    --count;
                }
                ++left;
            }
        }
        return ret;
    }
};
