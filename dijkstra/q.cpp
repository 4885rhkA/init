/**
 *
 * @file   hard.cpp
 * @brief  迷路及びライフから算出される、最適な道を通った場合に関する結果を表示する
 * @author 
 * @date 
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc/malloc.h>

#define QUESTION 10
#define ITEMMAXLENGTH 100

/**
 * 2次元座標
 */
typedef struct
{
    int x;
    int y;
} Position;

/**
 * アイテム
 */
typedef struct
{
    Position position;
    /* -1;地面 0;プレイヤー 1-9;財宝 10;食べ物  11;魔除け  12;ゴール  */
    int      item;
} Item;

/**
 * ステータス
 */
typedef struct
{
    int      life;
    int      goal;
    int      money;
    int      amulet;
    Position position;
} Status;

Status maxStatus;

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

/**
 * @fn
 * @brief    メイン関数
 * @return 0
 */
int main()
{
    for(int now = 0; now < QUESTION; now++)
    {
        Status status;
        status.position.x = status.position.y = maxStatus.position.x = maxStatus.position.y = 0;
        status.life       = maxStatus.life    = 0;
        status.goal       = maxStatus.goal    = 0;
        status.money      = maxStatus.money   = 0;
        status.amulet     = maxStatus.amulet  = 0;

        /* データ読み込み */
        /* ファイル開く */
        FILE *fp;
        char *filename = (char*)malloc(sizeof(128));
        sprintf(filename, "input%d.txt", now);
        if ((fp = fopen(filename, "r")) == NULL) {
            fprintf(stderr, "%sのオープンに失敗しました.\n", filename);
            exit(EXIT_FAILURE);
        }

        /* itemを追加 */
        int   column     = 0;
        int   row        = 0;
        Item* items      = (Item*)malloc(sizeof(Item) * ITEMMAXLENGTH);
        int   itemLength = 0;
        char* life       = (char*)malloc(4);   /* ライフは３桁まで対応 */
        char  mapResult;
        while ((mapResult = fgetc(fp)) != EOF) {
            if (mapResult == '\n') {
                row++;
                column = 0;
            }
            else if(mapResult != '\0')
            {
                if(row == 0)
                {
                    life[column] = mapResult;
                    column++;
                }
                else
                {
                    if(getItemNumber(mapResult) > -1)
                    {
                        items[itemLength].position.x = column;
                        items[itemLength].position.y = row-1;
                        items[itemLength].item       = getItemNumber(mapResult);
                        itemLength++;
                    }
                    column++;
                }
            }
        }

        status.life = atoi(life);
        printf("%d\n", status.life);

        /* ファイルのクローズ */
        fclose(fp);

        /* アイテムの並び替え */
        for (int i = 0; i < itemLength; i++)
        {
            if(items[i].item == 0)
            {
                swap(&items[0], &items[i]);
            }
            if(items[i].item == 12)
            {
                swap(&items[itemLength - 1], &items[i]);
            }
        }

        maxStatus.position = items[0].position;

        /* 最適解を求める */
        solve(items, 0, 1, 0, itemLength, status);
        solve(items, 0, 1, 1, itemLength, status);
        printf("Ans:%d %d %d %d\n", maxStatus.position.x, maxStatus.position.y, maxStatus.amulet, maxStatus.money);

        /* 後処理 */
        free(filename);
        free(life);
        free(items);
        filename = NULL;
        life     = NULL;
        items    = NULL;
    }

    return 0;
}
