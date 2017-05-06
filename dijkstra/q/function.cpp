/**
 *
 * @file   function.cpp
 * @brief  迷路及びライフから算出される、最適な道を通った場合に関する結果を表示する
 * @author 
 * @date 
 */

#include <stdlib.h>
#include "main.h"

/**
 * @fn
 * @brief         アイテム番号を取得
 * @param  symbol char時の文字
 * @return        各symbolについて定めた番号
 */
int getItemNumber(char symbol)
{
    switch(symbol)
    {
        case '.':
            return -1;
        case '@':
            return 0;
        case '%':
            return 12;
        case 'F':
            return 10;
        case 'A':
            return 11;
        default:
            return symbol - '0';
    }
}

/**
 * @fn
 * @brief         アイテムを入れ替える
 * @param  base   交換するベースアイテム
 * @param  target 交換対象
 */
void swap(Item* base, Item* target)
{
    Item temp;
    temp    = *base;
    *base   = *target;
    *target = temp;
}

/**
 * @fn
 * @brief         baseとtarget間の距離を取得
 * @param  base   距離を測るベースとなるアイテム
 * @param  target 対象となるアイテム
 * @return        距離
 */
int getDistance(Item base, Item target)
{
    return abs(base.position.x - target.position.x) + abs(base.position.y - target.position.y);
}

/**
 * @fn
 * @brief         最適な道を通ったのか評価
 * @param  status ある道を通ってきた際の評価
 */
void evaluation(Status status)
{
    if(status.goal == 1)
    {
        if(status.amulet >= maxStatus.amulet && status.money >= maxStatus.money)
        {
                maxStatus = status;
        }
    }
}

/**
 * @fn
 * @brief         アイテムを取得した際に発生する評価変更
 * @param  status ある道を通ってきた際の評価
 * @param  item   入手したアイテム
 */
void getItem(Status* status, int item)
{
    switch(item)
    {
        case 10:
            status->life += 5;
            break;
        case 11:
            status->amulet = 1;
            break;
        default:
            status->money += item;
            break;
    }
}
