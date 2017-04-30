#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc/malloc.h>

#define ITEMMAXLENGTH 100

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
    int money;
    int amulet;
} Status;

Status maxStatus;

int getItemNumber(char symbol)
{
    switch(symbol)
    {
        case '*':
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

/* 動的計画法による解き方 */
void solve(Item* items, int from, int to, int itemLength, Status status)
{
    /* ゴールしたら評価開始 */
    if(to > itemLength)
    {
        /* 評価 */
        if(status.amulet >= maxStatus.amulet && status.money >= maxStatus.money)
        {
            maxStatus = status;
        }
    }
    /* items個分探索していないがライフが０になった場合 */
    else if(status.life < 0)
    {
        /* 評価 */
        if(status.amulet >= maxStatus.amulet && status.money >= maxStatus.money)
        {
            maxStatus = status;
        }
    }
    /* items個分探索していないし、ライフも０でない場合 */
    else
    {
        /* from to を書かれたとおりに実行しないか */
        solve(items, from, to+1, itemLength, status);

        /* from to を書かれたとおりに実行するか */
        status.life -= getDistance(items[from], items[to]);

        if(status.life > 0)
        {
            /* 移動した場合に特典 */
            switch(items[to].item)
            {
                case 0:             
                case 12:            
                    break;
                case 10:            
                    status.life  += 5;
                    break;;
                case 11:            
                    status.amulet = 1;
                    break;
                default:            
                    status.money += items[to].item;
                    break;
            }
        }
        solve(items, to, to+1, itemLength, status);
    }
}

int main()
{
    Status status;
    status.life   = 0;
    status.money  = maxStatus.money  = 0;
    status.amulet = maxStatus.amulet = 0;

    /* データ読み込み */
    /* ファイル開く */
    FILE *fp;
    char filename[] = "input0.txt";
    if ((fp = fopen(filename, "r")) == NULL) {
        fprintf(stderr, "%sのオープンに失敗しました.\n", filename);
        exit(EXIT_FAILURE);
    }

    /* itemを追加 */
    int   column     = 0;
    int   row        = 0;
    Item* items      = (Item*)malloc(sizeof(Item) * ITEMMAXLENGTH);
    int   itemLength = 0;
    char  life[3];   /* ライフは３桁まで対応 */
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

    /* 最適解を求める */
    solve(items, 0, 1, itemLength, status);
    printf("Ans:%d %d\n", maxStatus.amulet, maxStatus.money);

    return 0;
}