#include "SolitareGame.h"

void draw(int x, int y, Card* card) {
    char names[13] = { 'A', '2', '3', '4', '5', '6', '7', '8', '9', '10', 'J', 'Q', 'K' };

    // �������� �������������
    cleardevice();

    // ���������� �������
    rectangle(x, y, x + width, y + height);

    // ���������� ���� �����
    if (faceUp) {
        if (color() == red)
            setcolor(RED);
        else
            setcolor(BLUE);

        // ���������� �������� �����
        outtextxy(x + 3, y + 15, names[1].c_str());

        if (suit() == heart) {
            // ���������� ������
            // ...
        }
        else if (suit() == spade) {
            // ���������� ����
            // ...
        }
        else if (suit() == diamond) {
            // ���������� �����
            // ...
        }
        else if (suit() == club) {
            // ���������� �����
            // ...
        }
    }
    else {
        setcolor(YELLOW);
        line(x + 15, y + 5, x + 15, y + 65);
    }
}