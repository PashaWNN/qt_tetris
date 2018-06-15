#ifndef CONTROLLER_H
#define CONTROLLER_H


class controller
{

    int figures[7][4] =
    {
        1,3,5,7, // I
        2,4,5,7, // Z
        3,5,4,6, // S
        3,5,4,7, // T
        2,3,5,7, // L
        3,5,7,6, // J
        2,3,4,5, // O
    };

public:
    struct Point
    {int x,y;} a[4], b[4];
    const static int M = 20;
    const static int N = 10;
    int field[M][N];
    controller();
    int do_game_tick(int mv, bool rot);
    int color;
private:
    bool game_tick();
    int check();
    void move(int dx);
    void rotate();
    int check_lines();


};

#endif // CONTROLLER_H
