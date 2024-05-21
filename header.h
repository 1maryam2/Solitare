#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

class Box;
class Game_Field;
class vis_Card;
class vis_field;

void Drawing();
vis_field View(vis_field& field,  Game_Field& f);
vis_field view_scrol(vis_field& field, Game_Field& f);
void view_fill_main(vis_field& field, Game_Field& f, int x, int y);
void view_shift_card(vis_field& field, Game_Field& f, int i, int x, int y);

class vis_Card{
    public:
        sf::Sprite sprite;
        sf::Texture text;
        vis_Card &operator =(const vis_Card& v);
        vis_Card(const vis_Card& v);
        vis_Card();
};

class vis_field{
    public:
        std::vector<vis_Card> card1[7];
        std::vector<vis_Card> card2[4];
        std::vector<vis_Card> card3[2];
        vis_field &operator =(const vis_field &v);
        vis_field();
};

class Card{
    private:
        enum card_suit{
            card_suit_spades,//пики
            card_suit_clubs,//трефы
            card_suit_diamonds,//буби
            card_suit_hearts//червы
        };
        card_suit suit;//масть карты
        int value;//значение карты
        bool visible;//флаг который определяет видно карту или нет
    public:
        Card& operator =(const Card& r);
        bool operator ==(const Card& r);
        Card();
        Card(const Card& card);
        Card(int v, bool vis, card_suit su);
        int dist_suit(card_suit s);
    friend class Box;
    friend class Game_Field;
    friend vis_field View(vis_field& field,  Game_Field& f);
    friend vis_field view_scrol(vis_field& field, Game_Field& f);
    friend void view_fill_main(vis_field& field, Game_Field& f, int x , int y);
    friend void view_shift_card(vis_field& field, Game_Field& f, int i, int x, int y);
};
class Box{
    private:
        std::vector<Card> cards;
    public:
        Box();
        bool isEmpty();//если box пуст - true, если нет - false
        void show_last_card();//метод который проявляет последнюю карту в боксе
    friend class Game_Field;
    friend vis_field View(vis_field& field,  Game_Field& f);
    friend vis_field view_scrol(vis_field& field, Game_Field& f);
};
class Game_Field{
    public:
        Box main[4];
        Box sim[7];
        Box base[2];
        void scrol_base();
        void plant(Card* card);//метод который заполняет карты согласено переданному массиву card
        Card* random_change(int x);//метод который произвольно перемешивает колоду и возращает массив карт(если передается 1 - колода премешивается на половину , если 2 - колода перемешаивается полностью)
        void fill_main(int x, int y);//метод который перемещает карту из бокса x в соотвествующий бокс y(main)
        void shiftCard(int i, int  x, int y);//метод который перемещает между семью игровыми полями(i - сколько,x-откуда перемещается,y-куда перемещается)
        bool isRightFillmain(Card& card, int x);
        bool isRightShiftCard(Card& card, int x);
};

