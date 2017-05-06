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
#include "main.h"

#define QUESTION 10
#define ITEMMAXLENGTH 100

Status maxStatus;

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

        /* 初期化 */
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

        /* 最適解を求める */
        solve(items, 0, 1, 0, itemLength, status);
        solve(items, 0, 1, 1, itemLength, status);

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
