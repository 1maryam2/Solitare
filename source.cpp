#include "header.h"

Card& Card::operator= (Card& r){
    visible = r.visible;
    value = r.value;
    suit = r.suit;
    return *this;
}

bool Card::operator== (Card& r){
    if(value == r.value && suit == r.suit){
        return true;
    }
    else{
        return false;
    }
}

Card::Card(){
    value = 2;
    suit = card_suit::card_suit_hearts;
    visible = false;
}

Card::Card(Card& card){
    value = card.value;
    suit = card.suit;
    visible = card.visible;
}

bool Box::isEmpty(){
    return cards.empty();
}

void Box::show_last_card(){
    cards[cards.size() - 1].visible = true;
}

