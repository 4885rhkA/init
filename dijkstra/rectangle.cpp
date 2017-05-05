#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* 中心座標 */
typedef struct
{
    float x;
    float y;
} Position;

/* 長方形の長さ */
typedef struct
{
    float width;
    float height;
} Length;

/* 長方形 */
typedef struct
{
    Position center;
    Length   length;
    Position leftBottom;
} Rectangle;

/* 頂点が重なっているか判定;重なっていたらいくつ重なっているか返す */
int cross(Rectangle a, Rectangle b)
{
    if(fabs(a.center.x - b.center.x) < (a.length.width + b.length.width)/2)
    {
        if(fabs(a.center.y - b.center.y) < (a.length.height + b.length.height)/2)
        {
            return 1;
        }
    }
    return 0;
}

Length getCrossedRectangleLength(Rectangle* rectangles)
{
    float sx = 0.0f;
    float sy = 0.0f;
    float ex = 0.0f;
    float ey = 0.0f;
    
    for(int i = 0; i < 2; i++)
    {
        rectangles[i].leftBottom.x = rectangles[i].center.x - rectangles[i].length.width/2;
        rectangles[i].leftBottom.y = rectangles[i].center.y - rectangles[i].length.height/2;
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
    
    Length len;
    len.width  = ex - sx;
    len.height = ey - sy;

    return len;
}

/* メイン関数 */
int main()
{
    Rectangle rectangles[2] =  {
        {{30.0f, 30.0f}, {10.0f, 20.0f}, {0.0f, 0.0f}},
        {{30.0f, 30.0f}, {20.0f, 10.0f}, {0.0f, 0.0f}}
    };
    
    if(cross(rectangles[0], rectangles[1]))
    {
        printf("crossed!\n");
        Length len = getCrossedRectangleLength(rectangles);
    }
    
    return 0;
}s