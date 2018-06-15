#include "controller.h"
#include "QTimer"

controller::controller()
{
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            this->field[i][j] = 0;
        }
    }
    for (int i = 0; i < 4; i++) {
        a[i].x = -1; b[i].x = 0;
        a[i].y = -1; b[i].y = 0;
    }
    color = 1+rand()%6;
}

int controller::check()
{
   for (int i=0;i<4;i++)
      if (a[i].x<0 || a[i].x>=N || a[i].y>=M) return 0;
      else if (field[a[i].y][a[i].x]) return 0;

   return 1;
}

bool controller::game_tick()
{
    for (int i=0;i<4;i++) { b[i]=a[i]; a[i].y+=1; }

    if (!check())
    {

     for (int i=0;i<4;i++) field[b[i].y][b[i].x]=color;
     int n=rand()%7;
     for (int i=0;i<4;i++)
       {
        a[i].x = (figures[n][i] % 2) + 5;
        a[i].y = (figures[n][i] / 2) + 0;
       }
     color=1+rand()%6;
    }
    return check();
}

void controller::move(int dx)
{
    for (int i=0;i<4;i++)  { b[i]=a[i]; a[i].x+=dx; }
        if (!check()) for (int i=0;i<4;i++) a[i]=b[i];
}

void controller::rotate()
{
   Point p = a[1]; //center of rotation
    for (int i=0;i<4;i++)
     {
       int x = a[i].y-p.y;
       int y = a[i].x-p.x;
       a[i].x = p.x - x;
       a[i].y = p.y + y;
     }
   if (!check()) for (int i=0;i<4;i++) a[i]=b[i];
}

int controller::check_lines()
{
    int lines = 0;
    int k=M-1;
       for (int i=M-1;i>0;i--)
       {
           int count=0;
           for (int j=0;j<N;j++)
           {
               if (field[i][j]) count++;

               field[k][j]=field[i][j];

           }
           if (count<N) {
               k--;
           } else lines++;
       }
   return lines;
}

int controller::do_game_tick(int mv, bool rot)
{
    move(mv);
    if (rot) rotate();
    if (!game_tick()) return -1;
    return check_lines();
}
