/*
1. 两数之和

给定一个整数数组 nums 和一个整数目标值 target，请你在该数组中找出和为目标值 target 的那两个整数，并返回它们的数组下标。

你可以假设每种输入只会对应一个答案。但是，数组中同一个元素在答案里不能重复出现。

你可以按任意顺序返回答案。

示例 1：

输入：nums = [2,7,11,15], target = 9
输出：[0,1]
解释：因为 nums[0] + nums[1] == 9 ，返回 [0, 1] 。
示例 2：

输入：nums = [3,2,4], target = 6
输出：[1,2]
示例 3：

输入：nums = [3,3], target = 6
输出：[0,1]
*/

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

// 解题思路一：判断数组中第i个元素之后的元素与i的和是否为target，这种思路需要使用两个嵌套for循环，方法复杂度较高为O(N²)。

#include <stdio.h>

int *twoSum(int *nums, int numsSize, int target, int *returnSize)
{
    for (int i=0; i<numsSize; i++)
    {
        for (int j=i+1; j<numsSize; j++)
        {
            if (nums[i]+nums[j]==target)
            {
                int *ret = malloc(sizeof(int)*2);
                ret[0]=i;
                ret[1]=j;
                *returnSize = 2;
                return ret;
            }
        }
    }
    *returnSize = 0;
    return NULL;
}

// 解题思路二，使用哈希表，通过对第i个元素进行哈希表查询，是否存在一个target-i，然后将i插入哈希表，同时保证i不会与自己匹配。同时复杂度为O(N)

#include <uthash.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
typedef struct hashTable
{
    int key;
    int val;
    UT_hash_handle hh;
};

struct hashTable *hash_t;

struct hashTable *find(int ikey)
{
    struct hashTable *tmp;
    HASH_FIND_INT(hash_t, &ikey, tmp);
    return tmp;
}

void insert(int ikey, int ival)
{
    struct hashTable *it = find(ikey);
    if (it==NULL)
    {
        struct hashTable *tmp = malloc(sizeof(struct hashTable));
        tmp->key = ikey, tmp->val = ival;
        HASH_ADD_INT(hash_t, key, tmp);
    }else
    {
        it->val = ival;
    }
}

int *twoSum(int *nums, int numsSize, int target, int *returnSize)
{
    hash_t = NULL;
    for (int i=0; i<numsSize; i++)
    {
        struct hashTable *it = find(target-nums[i]);
        if (it != NULL)
        {
            int *ret = malloc(sizeof(int)*2);
            ret[0] = it->val, ret[1] = i;
            *returnSize = 2;
            return ret; 
        }else
        {
            insert(nums[i], i);
        }
    }
    *returnSize = 0;
    return NULL;
}

