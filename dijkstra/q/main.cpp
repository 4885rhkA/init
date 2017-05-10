/**
 *
 * @file   main.cpp
 * @brief  迷路及びライフから算出される、最適な道を通った場合に関する結果を表示する
 * @author
 * @date
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc/malloc.h>

#define QUESTION 2
#define ITEMMAXLENGTH 8

typedef struct
{
    int x;
    int y;
} Position;

typedef struct
{
    Position position;
    int      item;       /* -1;地面 0;プレイヤー 1-9;財宝 10;食べ物  11;魔除け  12;ゴール  */
} Item;

typedef struct
{
    int life;
    int goal;
    int money;
    int amulet;
    Position position;
} Status;

typedef struct
{
    int point[ITEMMAXLENGTH];
} Visited;

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


void swap(Item* itemA, Item* itemB)
{
    Item temp;
    temp   = *itemA;
    *itemA = *itemB;
    *itemB = temp;
}


int getDistance(Item itemA, Item itemB)
{
    return abs(itemA.position.x - itemB.position.x) + abs(itemA.position.y - itemB.position.y);
}


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


Status getItem(Status status, int item)
{
    switch(item)
    {
        case 10:
            status.life += 5;
            break;
        case 11:
            status.amulet = 1;
            break;
        default:
            status.money += item;
            break;
    }
    return status;
}


void solve(Item* items, int from, int to, int go, int itemLength, Status status, Visited visited)
{
    if(go == 1)
    {
        status.life -= getDistance(items[from], items[to]);
        if(items[to].item != 0 && items[to].item != 12)
        {
            status = getItem(status, items[to].item);
        }
        status.position = items[to].position;
    }
    visited.point[to] = 1;
    
    if(status.life < 0)
    {
        return;
    }
    
    if(to == itemLength - 1)
    {
        if(status.position.x == items[itemLength - 1].position.x && status.position.y == items[itemLength - 1].position.y)
        {
            status.goal = 1;
        }
        evaluation(status);
    }
    
    for(int i = 0; i < itemLength; i++)
    {
        if(visited.point[i] == 0)
        {
            if(go == 1)
            {
                solve(items, to, i, 0, itemLength, status, visited);
                solve(items, to, i, 1, itemLength, status, visited);
            }
            if(go == 0)
            {
                solve(items, from, i, 0, itemLength, status, visited);
                solve(items, from, i, 1, itemLength, status, visited);
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
        
        Visited visited;
        for(int i = 0; i < ITEMMAXLENGTH; i++)
        {
            visited.point[i] = 0;
        }
        
        /* 最適解を求める */
        solve(items, 0, 0, 0, itemLength, status, visited);
        printf("%d %d %d\n", maxStatus.position.x, maxStatus.position.y, maxStatus.money);
        
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
