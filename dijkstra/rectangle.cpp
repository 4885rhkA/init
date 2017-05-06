/**
 *
 * @file   main.cpp
 * @brief  ２つの入力された長方形に関するデータから、重なっている長方形に関する情報を表示する
 * @author 
 * @date 
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/**
 * 2次元座標
 */
typedef struct
{
    float x;
    float y;
} Position;

/**
 * 長方形の辺の長さ
 */
typedef struct
{
    float width;
    float height;
} Length;

/**
 * 長方形
 */
typedef struct
{
    Position center;
    Length   length;
    Position leftBottom;
} Rectangle;

/**
 * @fn
 * @brief         ２つの長方形が交わっているか否かを判定
 * @param  base   比較するベース
 * @param  target 比較対象
 * @return        0: 交差なし / 1:交差あり
 */
 int cross(Rectangle base, Rectangle target)
{
    if(fabs(base.center.x - target.center.x) < (base.length.width + target.length.width)/2)
    {
        if(fabs(base.center.y - target.center.y) < (base.length.height + target.length.height)/2)
        {
            return 1;
        }
    }
    return 0;
}

/**
 * @fn
 * @brief             重なっている長方形に対するRectangleを取得
 * @param  rectangles 2つの入力された長方形のRectangleを含んだ配列のポインタ
 * @return            重なっている長方形に対するRectangle
 */
Rectangle getCrossedRectangle(Rectangle* rectangles)
{
    float sx = 0.0f;
    float sy = 0.0f;
    float ex = 0.0f;
    float ey = 0.0f;
    
    for(int i = 0; i < 2; i++)
    {
        if(i == 0)
        {
            sx = rectangles[i].leftBottom.x;
            sy = rectangles[i].leftBottom.y;
            ex = rectangles[i].leftBottom.x + rectangles[i].length.width;
            ey = rectangles[i].leftBottom.y + rectangles[i].length.height;
        }
        else{
            sx = fmax(rectangles[i].leftBottom.x, sx);
            sy = fmax(rectangles[i].leftBottom.y, sy);
            ex = fmin(rectangles[i].leftBottom.x + rectangles[i].length.width,  ex);
            ey = fmin(rectangles[i].leftBottom.y + rectangles[i].length.height, ey);
        }
    }
    
    Rectangle rec;
    rec.center.x      = sx + (ex - sx) / 2;
    rec.center.y      = sy + (ey - sy) / 2;
    rec.length.width  = ex - sx;
    rec.length.height = ey - sy;
    rec.leftBottom.x  = sx;
    rec.leftBottom.y  = sy;
    
    return rec;
}

/**
 * @fn
 * @brief    メイン関数
 * @return 0
 */
int main()
{
    float centerPositionX = 0;
    float centerPositionY = 0;
    float width           = 0;
    float height = 0;

    Rectangle rectangles[2];

    for(int i = 0; i < 2; i++)
    {
        printf("%dつめの長方形について\n", i + 1);
        printf("長方形の中心X座標は？\n");
        scanf("%f", &centerPositionX);
        printf("長方形の中心Y座標は？\n");
        scanf("%f", &centerPositionY);
        printf("縦の長さは？\n");
        scanf("%f", &width);
        printf("横の長さは？\n");
        scanf("%f", &height);
        printf("\n");

        rectangles[i].center.x      = centerPositionX;
        rectangles[i].center.y      = centerPositionY;
        rectangles[i].length.width  = width;
        rectangles[i].length.height = height;
        rectangles[i].leftBottom.x  = rectangles[i].center.x - rectangles[i].length.width/2;
        rectangles[i].leftBottom.y  = rectangles[i].center.y - rectangles[i].length.height/2;
    }
    
    if(cross(rectangles[0], rectangles[1]))
    {
        printf("Crossed!\n");
        Rectangle rec = getCrossedRectangle(rectangles);
        printf("width: %.2f height: %.2f\n", rec.length.width, rec.length.height);
    }
    else
    {
        printf("Not crossed!\n");
    }

    return 0;
}
