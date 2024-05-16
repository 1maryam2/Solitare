#include <SFML/Graphics.hpp>
#include <vector>
class Box;



class Card{
    private:
        enum card_suit{
            card_suit_spades,//пики
            card_suit_clubs,//трефы
            card_suit_diamonds,//буби
            card_suit_hearts//червы
        };
        Card& operator =(Card& r);
        bool operator ==(Card& r);
        Card();
        Card(Card& card);
        card_suit suit;
        int value;//значение карты
        bool visible;//флаг который определяет видно карту или нет
        friend class Box;
};

class Box{
    private:
        std::vector<Card> cards;
    public:
        bool isEmpty();
        void show_last_card();
};

class Game_Filed{
    Box main[4];
    
};
