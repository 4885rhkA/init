/**
 *
 * @file   main.cpp
 * @brief  入力された金額から、100円 50円 10円で支払えるパターンがいくつあるか示す
 * @author 
 * @date 
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int count = 0;

/**
 * @fn
 * @brief         ２つの引数の大小を比較
 * @param  base   比較するベース
 * @param  target 比較対象
 * @return        target == base: 0  base > target: 正の整数 target > base: 負の整数
 */
int compareInteger(const void *base, const void *target)
{
    return *(int*)target - *(int*)base;
}

/**
 * @fn
 * @brief        入力された金額から、100円 50円 10円で支払えるパターンが何パターンあるのか数える
 * @param  coins 円の種類を格納した配列のポインタ
 * @param  total 何パターンあるか数える金額
 * @param  now   coinsに格納してある配列の場所
 * @return       パターン数
 */
void countPattern(int* coins, int total, int now)
{

    if(total == 0)
    {
        count++;
    }
    else if(total > 0)
    {
        if(now <= sizeof(coins) / sizeof(coins[0]))
        {
            for(int i = 0; i <= total / coins[now]; i++)
            {
                countPattern(coins, total - coins[now] * i, now + 1);
            }
        }
    }
    
}

/**
 * @fn
 * @brief    メイン関数
 * @return 0
 */
 int main()
{
    int coins[] = {100, 50, 10};
    int money = 0;
    
    qsort(coins, sizeof(coins)/sizeof(coins[0]), sizeof(int), compareInteger);
    
    scanf("%d", &money);
    
    countPattern(coins, money, 0);
    
    printf("%d\n", count);
    
    return 0;
}