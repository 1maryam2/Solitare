#include "SolitareGame.h"

void draw(int x, int y, Card* card) {
    char names[13] = { 'A', '2', '3', '4', '5', '6', '7', '8', '9', '10', 'J', 'Q', 'K' };

    // Очистить прямоугольник
    cleardevice();

    // Нарисовать границу
    rectangle(x, y, x + width, y + height);

    // Нарисовать тело карты
    if (faceUp) {
        if (color() == red)
            setcolor(RED);
        else
            setcolor(BLUE);

        // Нарисовать название карты
        outtextxy(x + 3, y + 15, names[1].c_str());

        if (suit() == heart) {
            // Нарисовать сердце
            // ...
        }
        else if (suit() == spade) {
            // Нарисовать пику
            // ...
        }
        else if (suit() == diamond) {
            // Нарисовать бубен
            // ...
        }
        else if (suit() == club) {
            // Нарисовать трефу
            // ...
        }
    }
    else {
        setcolor(YELLOW);
        line(x + 15, y + 5, x + 15, y + 65);
    }
}