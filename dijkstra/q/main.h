#ifndef _main_h
#define _main_h

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

extern int getItemNumber(char symbol);
extern void swap(Item* base, Item* target);
extern int getDistance(Item base, Item target);
extern void evaluation(Status status);
extern void getItem(Status* status, int item);
extern void solve(Item* items, int from, int to, int go, int itemLength, Status status);

extern Status maxStatus;

#endif
