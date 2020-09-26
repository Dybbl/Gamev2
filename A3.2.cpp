#include "TXlib.h"

#include "math.h"

struct Game_object
{

    double x;
    double y;
    double r;

    double light_point_x;
    double light_point_y;

    int Red;
    int Green;
    int Blue;

    int drawing_level;

    double Vx;
    double Vy;

};

struct General
{

    double Screen_height;
    double Screen_width;

    int Game_is_over;

    int Game_level;

};

void DrowSphere(Game_object Sphere)
{

    COLORREF OldFillColor = txGetFillColor();
    COLORREF OldColor = txGetColor();
    for(int i = 0; i <= Sphere.drawing_level; i++)
    {
        txSetFillColor(RGB(Sphere.Red * i / Sphere.drawing_level, Sphere.Green * i / Sphere.drawing_level, Sphere.Blue * i / Sphere.drawing_level));
        txSetColor(RGB(Sphere.Red * i / Sphere.drawing_level, Sphere.Green * i / Sphere.drawing_level ,Sphere.Blue * i / Sphere.drawing_level));
        txCircle(Sphere.x + (Sphere.light_point_x - Sphere.x) * i / Sphere.drawing_level, Sphere.y + (Sphere.light_point_y - Sphere.y) * i / Sphere.drawing_level, Sphere.r - ((Sphere.r * i) / Sphere.drawing_level));

    }
    txSetFillColor(OldFillColor);
    txSetColor(OldColor);

}
void MoveSphere(Game_object* Sphere)
{

    Sphere->x += Sphere->Vx;
    Sphere->y += Sphere->Vy;
    Sphere->light_point_x += Sphere->Vx;
    Sphere->light_point_y += Sphere->Vy;

}
void CheckColission(Game_object* Sphere, General Game_options)
{

    if (Sphere->x <= Sphere->r or Sphere->x >= Game_options.Screen_height - Sphere->r)
        {
            Sphere->Vx = -Sphere->Vx;
        }

    if (Sphere->y <= Sphere->r or Sphere->y >= Game_options.Screen_width - Sphere->r)
        {
            Sphere->Vy = -Sphere->Vy;
        }

}
bool CheckColossionTwoSphere(Game_object Sphere1, Game_object Sphere2)
{

    if((pow((Sphere1.x - Sphere2.x),2)) + pow((Sphere1.y - Sphere2.y),2) <= pow((Sphere1.r + Sphere2.r),2))
        {
            return true;
        }

}
void Speed_button(Game_object* Sphere, General Game_options)
{

    if(txMouseButtons() == 1)
    {
       Sphere->Vx += (txMouseX() - Sphere->x) / (Game_options.Game_level * 1000 );
       Sphere->Vy += (txMouseY() - Sphere->y) / (Game_options.Game_level * 1000 );
    }

}
void Game_Over(General* Game_options)
{

    Game_options->Game_is_over = 1;
    txSetColor(RGB(100,0,0));
    txSelectFont("Arial",90,90);
    txDrawText(4 * Game_options->Screen_height / 10, 4 * Game_options->Screen_width / 10, 6 * Game_options->Screen_height / 10, 6 * Game_options->Screen_width / 10, "GG" );



}
void Colission(Game_object* Sphere1, Game_object* Sphere2)
{

    double Bufer = 0;

    Bufer = Sphere1->Vx;
    Sphere1->Vx = Sphere2->Vx;
    Sphere2->Vx = Bufer;

    Bufer = Sphere1->Vy;
    Sphere1->Vy = Sphere2->Vy;
    Sphere2->Vy = Bufer;

}
int main()
{

    General Game_options;

    Game_options = {1600, 900, 0, 8};

    txCreateWindow(Game_options.Screen_height, Game_options.Screen_width);
    txSetFillColor(RGB(0,0,0));
    txSetColor(RGB(0,0,0));

    Game_object Sphere1;

    Sphere1 = {700, 700, 100, 650, 650, 0 , 0, 200, 100, 0.5, 0.5};

    Game_object Sphere2;

    Sphere2 = {500, 500, 50, 480, 480, 100 , 0, 0, 100, -4, -4};

    Game_object Sphere3;

    Sphere3 = {1300, 600, 100, 1350, 550, 0 , 100, 0, 100, 2, -2};


    while (Game_options.Game_is_over != 1)
    {

        Speed_button(&Sphere1, Game_options);

        CheckColission(&Sphere1, Game_options);

        CheckColission(&Sphere2, Game_options);

        CheckColission(&Sphere3, Game_options);

        MoveSphere(&Sphere1);

        MoveSphere(&Sphere2);

        MoveSphere(&Sphere3);

        txBegin();
        txClear();

        DrowSphere(Sphere1);

        DrowSphere(Sphere2);

        DrowSphere(Sphere3);

        txEnd();

        if(CheckColossionTwoSphere(Sphere2, Sphere3))
            {
                Colission(&Sphere2, &Sphere3);
            }

        if(CheckColossionTwoSphere(Sphere1, Sphere2))
            {
                Game_Over(&Game_options);
            }

        if(CheckColossionTwoSphere(Sphere1, Sphere3))
            {
                Game_Over(&Game_options);
            }

    }

    return 0;
}
