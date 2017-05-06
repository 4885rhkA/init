/**
 *
 * @file   algorithm.cpp
 * @brief  迷路及びライフから算出される、最適な道を通った場合に関する結果を表示する
 * @author 
 * @date 
 */

#include "main.h"

/**
 * @fn
 * @brief             問題を解く関数
 * @param  items      各問題において登場したアイテム
 * @param  from       配列items内何番目のものかを使うか示すための数値
 * @param  to         配列items内何番目のものかを使うか示すための数値
 * @param  go         0: 再帰なし 1:再帰あり
 * @param  itemLength 配列itemsの要素数
 * @param  status     ステータス
 */
void solve(Item* items, int from, int to, int go, int itemLength, Status status)
{
    if(to >= itemLength)
    {
        if(status.position.x == items[itemLength - 1].position.x && status.position.y == items[itemLength - 1].position.y)
        {
            status.goal = 1;
            evaluation(status);
        }
        return;
    }
    else if(go == 1)
    {        
        status.life -= getDistance(items[from], items[to]);
        if(items[to].item != 0 && items[to].item != 12)
        {
            getItem(&status, items[to].item);
        }
        status.position = items[to].position;
    }

    if(status.life >= 0)
    {
        solve(items, to, to + 1, 0, itemLength, status);
        solve(items, to, to + 1, 1, itemLength, status);
    }
}
