#include <stdio.h>
/* 
    算法一：使用三个for循环 复杂度：n^3 
           两个for循环遍历子序列，一个for循环累加
*/
int MaxSubSequenceSum1(const int A[], int N)
{
    int thisSum = 0;
    int maxSum = 0;

    for (int i = 0; i < N; i++)
    {
        for (int j = i; j < N; j++)
        {
            thisSum = 0;
            for (int k = i; k <= j; k++)
                thisSum += A[k];

            if (thisSum > maxSum)
                maxSum = thisSum;
        }
    }
    return maxSum;
}
/* 
    算法二：使用两个for循环 复杂度：n^2 
           剔除了用于累加的for循环，将thisSum作为前缀和使用
*/
int MaxSubSequenceSum2(const int A[], int N)
{
    int thisSum = 0;
    int maxSum = 0;
    for (int i = 0; i < N; i++)
    {
        thisSum = 0;
        for (int j = i; j < N; j++)
        {
            thisSum += A[j];
            if (thisSum > maxSum)
                maxSum = thisSum;
        }
    }
    return maxSum;
}
/* 
    算法三：递归执行 分治法 复杂度：nlogn
    思路：最大子序列有三种可能
            1.在左半部分
            2.在右半部分
            3.在中间（涵盖边界到最左|右边的情况）
          三种可能对应三种方案
            1.递归，给左侧子序列去做
            2.递归，给右侧子序列去做
            3.从中间向两侧寻找最大的序列
          比较三种结果，得出答案
*/
int max(int a, int b)
{
    return a >= b ? a : b;
}
/* 递归主体 */
static int MaxSubSum(const int A[], int left, int right)
{
    if (left == right) //当只有一个数字时返回
    {
        if (A[left] > 0) //选择该数
            return A[left];
        else
            return 0; //不选该数（考虑全部为负数的情况）
    }

    int center = (left + right) / 2;
    int maxLeftSum = MaxSubSum(A, left, center);
    int maxRightSum = MaxSubSum(A, center + 1, right);

    int maxLeftBorderSum = 0, leftBorderSum = 0;
    for (int i = center; i >= left; i--)
    {
        leftBorderSum += A[i];
        if (leftBorderSum > maxLeftBorderSum)
            maxLeftBorderSum = leftBorderSum;
    }

    int maxRightBorderSum = 0, rightBorderSum = 0;
    for (int i = center + 1; i <= right; i++)
    {
        rightBorderSum += A[i];
        if (rightBorderSum > maxRightBorderSum)
            maxRightBorderSum = rightBorderSum;
    }
    return max(max(maxLeftSum, maxRightSum), maxLeftBorderSum + maxRightBorderSum);
}
int MaxSubSequenceSum3(const int A[], int N)
{
    return MaxSubSum(A, 0, N - 1);
}
/* 
    算法四：贪心算法 复杂度：n
           可以把连续的子序列当作一个数来看待，
                1. 是个正数 ，保留
                2. 是个负数， 剔除
                3. 比max值大，替换
           因为存在负数，如{10,-5,-7,5,4}对序列产生了分割的效果
           仅需要在各个片段中寻找最大子序列即可
*/
int MaxSubSequenceSum4(const int A[], int N)
{
    int thisSum = 0, maxSum = 0;
    for (int j = 0; j < N; j++)
    {
        thisSum += A[j];
        if(thisSum > maxSum )
            maxSum = thisSum;
        else if(thisSum < 0)
            thisSum = 0;
    }
    return maxSum;
}
int main()
{
    int A[] = {-2, 11, -4, 13, -5, -2};
    int N = 6;
    int ans = MaxSubSequenceSum4(A, N);
    printf("%d", ans);
    return 0;
}