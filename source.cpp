#include "header.h"

const int width = 155;
const int height = 227;
const int dist_x = 20;
const int dist_y = 20;
const int dist = 2;
const float Scale = 0.5;
const int distantion = 25;
int queue = 0;


bool wasMouseButtonReleased = false;

vis_Card::vis_Card(){}

vis_field::vis_field(){
    card1[0].resize(28);
    card1[1].resize(28);
    for(int i = 0; i < 7; i++)
        card3[i].resize(i + 1);
}

vis_field& vis_field::operator =(const vis_field& v){
    for(int i = 0; i < 7; i++)
        card1[i] = v.card1[i];
    for(int i = 0; i < 4; i++)
        card2[i] = v.card2[i];
    for(int i = 0; i < 2; i++)
        card3[i] = v.card3[i];
    return *this;
}

vis_Card::vis_Card(const vis_Card& v){
    sprite = v.sprite;
    text = v.text;
    sprite.setTexture(text);
    sprite.setScale(Scale,Scale);
}

vis_Card& vis_Card::operator=(const vis_Card& v){
    sprite = v.sprite;
    text = v.text;
    sprite.setTexture(text);
    sprite.setScale(Scale, Scale);
    return *this;
}

Card& Card::operator =(const Card& r){
    visible = r.visible;
    value = r.value;
    suit = r.suit;
    return *this;
}

bool Card::operator ==(const Card& r){
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

Card::Card(const Card& card){
    value = card.value;
    suit = card.suit;
    visible = card.visible;
}

Card::Card(int v, bool vis, card_suit su){
    value = v;
    visible = vis;
    suit = su;
}

int Card::dist_suit(card_suit s){
    if(s == Card::card_suit::card_suit_clubs){
        return 0;
    }
    if(s == Card::card_suit::card_suit_diamonds){
        return 1;
    }
    if(s == Card::card_suit::card_suit_hearts){
        return 2;
    }
    if(s == Card::card_suit::card_suit_spades){
        return 3;
    }
    return -1;
}

Box::Box(){}

bool Box::isEmpty(){
    return cards.empty();
}

void Box::show_last_card(){
    cards[cards.size() - 1].visible = true;
}

void Game_Field::plant(Card* card){
    int k = 0;
    for(int i = 0; i < 7; i++){
        for(int j = 0; j <= i; j++){
            sim[i].cards.push_back(card[k]);
            k++;
        }
    }
    for(int i = k; i < 52; i++){
        base[0].cards.push_back(card[i]);
    }
    for(int i = 0; i < 7; i++){
        sim[i].show_last_card();
    }
}

Card* Game_Field::random_change(){
    Card* card = new Card[52];
    int value = 0;
    int k = 1;
    Card::card_suit s = Card::card_suit::card_suit_clubs;
    for(int i = 0; i < 52; i++){
        card[i].visible = false;
        value++;
        if(value == 14){
            value = 1;
            k++;
            switch(k){
                case 2: s = Card::card_suit::card_suit_diamonds; break;
                case 3: s = Card::card_suit::card_suit_hearts; break;
                case 4: s = Card::card_suit::card_suit_spades; break;
            }
        }
        card[i].suit = s;
        card[i].value = value;
    }
    int random_change = 0;
    while(random_change == 0){
        random_change = rand() % 52;
    }
    for(int i = 0; i < 52; i++){
        Card temp = card[i];
        card[i] = card[random_change];
        card[random_change] = temp;
        random_change = rand() % 52;
        while(random_change == 0)
            random_change = rand() % 52;
    }
    return card;
}

void Game_Field::scrol_base(){
    if(base[0].isEmpty()){
        for (auto &i : base[1].cards){
            base[0].cards.push_back(i);
        }
        base[1].cards.clear();
    }
    else{
        base[1].cards.push_back(base[0].cards[0]);
        base[1].cards[base[1].cards.size() - 1].visible = true;
        base[0].cards.erase(base[0].cards.begin());
    }
}

bool Game_Field::isRightFillmain(Card& card, int x){
    switch (x){
    case 1: 
        if(main[0].isEmpty() && card.value == 1) return true;
        if(main[0].cards[main[0].cards.size() - 1].value == card.value - 1 && main[0].cards[main[0].cards.size() - 1].suit == card.suit) return true;
        break;
    case 2: 
        if(main[1].isEmpty() && card.value == 1) return true;
        if(main[1].cards[main[2].cards.size() - 1].value == card.value - 1 && main[2].cards[main[0].cards.size() - 1].suit == card.suit) return true;
        break;
    case 3: 
        if(main[2].isEmpty() && card.value == 1) return true;
        if(main[2].cards[main[2].cards.size() - 1].value == card.value - 1 && main[2].cards[main[0].cards.size() - 1].suit == card.suit) return true;
        break;
    case 4: 
        if(main[3].isEmpty() && card.value == 1) return true;
        if(main[3].cards[main[3].cards.size() - 1].value == card.value - 1 && main[3].cards[main[0].cards.size() - 1].suit == card.suit) return true;
        break;
    default:break;
    }
    return false;
}

bool Game_Field::isRightShiftCard(Card& card, int x){
    switch (x){
    case 1:    
        if(sim[0].isEmpty()) return true;
        if(sim[0].cards[sim[0].cards.size() - 1].value == card.value + 1){
            if(sim[0].cards[sim[0].cards.size() - 1].suit == Card::card_suit::card_suit_diamonds || sim[0].cards[sim[0].cards.size() - 1].suit == Card::card_suit::card_suit_hearts){
                if(card.suit == Card::card_suit::card_suit_clubs || card.suit == Card::card_suit::card_suit_spades) return true;
            }
            else{
                if(card.suit == Card::card_suit::card_suit_diamonds || card.suit == Card::card_suit::card_suit_hearts) return true;
            }
        }
        break;
    case 2:
        if(sim[1].isEmpty()) return true;
        if(sim[1].cards[sim[1].cards.size() - 1].value == card.value + 1){
            if(sim[1].cards[sim[1].cards.size() - 1].suit == Card::card_suit::card_suit_diamonds || sim[1].cards[sim[1].cards.size() - 1].suit == Card::card_suit::card_suit_hearts){
                if(card.suit == Card::card_suit::card_suit_clubs || card.suit == Card::card_suit::card_suit_spades) return true;
            }
            else{
                if(card.suit == Card::card_suit::card_suit_diamonds || card.suit == Card::card_suit::card_suit_hearts) return true;
            }
        }
        break;
    case 3:
        if(sim[2].isEmpty()) return true;
        if(sim[2].cards[sim[2].cards.size() - 1].value == card.value + 1){
            if(sim[2].cards[sim[2].cards.size() - 1].suit == Card::card_suit::card_suit_diamonds || sim[2].cards[sim[2].cards.size() - 1].suit == Card::card_suit::card_suit_hearts){
                if(card.suit == Card::card_suit::card_suit_clubs || card.suit == Card::card_suit::card_suit_spades) return true;
            }
            else{
                if(card.suit == Card::card_suit::card_suit_diamonds || card.suit == Card::card_suit::card_suit_hearts) return true;
            }
        }
        break;
    case 4:
        if(sim[3].isEmpty()) return true;
        if(sim[3].cards[sim[3].cards.size() - 1].value == card.value + 1){
            if(sim[3].cards[sim[3].cards.size() - 1].suit == Card::card_suit::card_suit_diamonds || sim[3].cards[sim[3].cards.size() - 1].suit == Card::card_suit::card_suit_hearts){
                if(card.suit == Card::card_suit::card_suit_clubs || card.suit == Card::card_suit::card_suit_spades) return true;
            }
            else{
                if(card.suit == Card::card_suit::card_suit_diamonds || card.suit == Card::card_suit::card_suit_hearts) return true;
            }
        }
        break;
    case 5:
        if(sim[4].isEmpty()) return true;
        if(sim[4].cards[sim[4].cards.size() - 1].value == card.value + 1){
            if(sim[4].cards[sim[4].cards.size() - 1].suit == Card::card_suit::card_suit_diamonds || sim[4].cards[sim[4].cards.size() - 1].suit == Card::card_suit::card_suit_hearts){
                if(card.suit == Card::card_suit::card_suit_clubs || card.suit == Card::card_suit::card_suit_spades) return true;
            }
            else{
                if(card.suit == Card::card_suit::card_suit_diamonds || card.suit == Card::card_suit::card_suit_hearts) return true;
            }
        }
        break;
    case 6:
        if(sim[5].isEmpty()) return true;
        if(sim[5].cards[sim[5].cards.size() - 1].value == card.value + 1){
            if(sim[5].cards[sim[5].cards.size() - 1].suit == Card::card_suit::card_suit_diamonds || sim[5].cards[sim[5].cards.size() - 1].suit == Card::card_suit::card_suit_hearts){
                if(card.suit == Card::card_suit::card_suit_clubs || card.suit == Card::card_suit::card_suit_spades) return true;
            }
            else{
                if(card.suit == Card::card_suit::card_suit_diamonds || card.suit == Card::card_suit::card_suit_hearts) return true;
            }
        }
        break;
    case 7:
        if(sim[6].isEmpty()) return true;
        if(sim[6].cards[sim[6].cards.size() - 1].value == card.value + 1){
            if(sim[6].cards[sim[6].cards.size() - 1].suit == Card::card_suit::card_suit_diamonds || sim[6].cards[sim[6].cards.size() - 1].suit == Card::card_suit::card_suit_hearts){
                if(card.suit == Card::card_suit::card_suit_clubs || card.suit == Card::card_suit::card_suit_spades) return true;
            }
            else{
                if(card.suit == Card::card_suit::card_suit_diamonds || card.suit == Card::card_suit::card_suit_hearts) return true;
            }
        }
        break;
    default:break;
    }
    return false;
}

void Game_Field::fill_main(int x, int y){
    switch (x){
        case 0:
            if(isRightFillmain(base[1].cards[base[1].cards.size() - 1], y)){
                main[y - 1].cards.push_back(base[1].cards[base[1].cards.size() - 1]);
            }
            break;
        case 1:
            if(isRightFillmain(sim[0].cards[sim[0].cards.size() - 1], y)){
                main[y - 1].cards.push_back(sim[0].cards[sim[0].cards.size() - 1]);
            }
            break;
        case 2:
            if(isRightFillmain(sim[1].cards[sim[1].cards.size() - 1], y)){
                main[y - 1].cards.push_back(sim[1].cards[sim[1].cards.size() - 1]);
            }
            break;
        case 3:
            if(isRightFillmain(sim[2].cards[sim[2].cards.size() - 1], y)){
                main[y - 1].cards.push_back(sim[2].cards[sim[2].cards.size() - 1]);
            }
            break;
        case 4:
            if(isRightFillmain(sim[3].cards[sim[3].cards.size() - 1], y)){
                main[y - 1].cards.push_back(sim[3].cards[sim[3].cards.size() - 1]);
            }
            break;
        case 5:
            if(isRightFillmain(sim[4].cards[sim[4].cards.size() - 1], y)){
                main[y - 1].cards.push_back(sim[4].cards[sim[4].cards.size() - 1]);
            }
            break;
        case 6:
            if(isRightFillmain(sim[5].cards[sim[5].cards.size() - 1], y)){
                main[y - 1].cards.push_back(sim[5].cards[sim[5].cards.size() - 1]);
            }
            break;
        case 7:
            if(isRightFillmain(sim[6].cards[sim[6].cards.size() - 1], y)){
                main[y - 1].cards.push_back(sim[6].cards[sim[6].cards.size() - 1]);
            }
            break;
        default:break;
    }
}

void Game_Field::shiftCard(int i, int x, int y){
    switch (x){
    case 0:
        if(isRightShiftCard(base[1].cards[base[1].cards.size() - 1], y)){
            sim[y - 1].cards.push_back(base[1].cards[base[1].cards.size() - 1]);
            base[1].cards.pop_back();
        }
        break;
    case 1:
        if(isRightShiftCard(sim[0].cards[i], y) && sim[0].cards[i].visible){
            sim[y - 1].cards.resize(sim[0].cards.size());
            for(int j = sim[0].cards.size() - 1; j >= i; j--)
                sim[y - 1].cards[j] = sim[0].cards[j]; 
            for(int j = sim[0].cards.size() - 1; j >= i; j--)
                sim[0].cards.pop_back();
        }
        break;
    case 2:
        if(isRightShiftCard(sim[1].cards[i], y) && sim[1].cards[i].visible){
            sim[y - 1].cards.resize(sim[1].cards.size());
            for(int j = sim[1].cards.size() - 1; j >= i; j--)
                sim[y - 1].cards[j] = sim[1].cards[j]; 
            for(int j = sim[1].cards.size() - 1; j >= i; j--)
                sim[1].cards.pop_back();
        }
        break;
    case 3:
        if(isRightShiftCard(sim[2].cards[i], y) && sim[2].cards[i].visible){
            sim[y - 1].cards.resize(sim[2].cards.size());
            for(int j = sim[2].cards.size() - 1; j >= i; j--)
                sim[y - 1].cards[j] = sim[2].cards[j]; 
            for(int j = sim[2].cards.size() - 1; j >= i; j--)
                sim[2].cards.pop_back();
        }
        break;
    case 4:
        if(isRightShiftCard(sim[3].cards[i], y) && sim[3].cards[i].visible){
            sim[y - 1].cards.resize(sim[3].cards.size());
            for(int j = sim[3].cards.size() - 1; j >= i; j--)
                sim[y - 1].cards[j] = sim[3].cards[j]; 
            for(int j = sim[3].cards.size() - 1; j >= i; j--)
                sim[3].cards.pop_back();
        }       
        break;
    case 5:
        if(isRightShiftCard(sim[4].cards[i], y) && sim[4].cards[i].visible){
            sim[y - 1].cards.resize(sim[4].cards.size());
            for(int j = sim[4].cards.size() - 1; j >= i; j--)
                sim[y - 1].cards[j] = sim[4].cards[j]; 
            for(int j = sim[4].cards.size() - 1; j >= i; j--)
                sim[4].cards.pop_back();
        }
        break;
    case 6:
        if(isRightShiftCard(sim[5].cards[i], y) && sim[5].cards[i].visible){
            sim[y - 1].cards.resize(sim[5].cards.size());
            for(int j = sim[5].cards.size() - 1; j >= i; j--)
                sim[y - 1].cards[j] = sim[5].cards[j]; 
            for(int j = sim[5].cards.size() - 1; j >= i; j--)
                sim[5].cards.pop_back();
        }
        break;
    case 7:
        if(isRightShiftCard(sim[6].cards[i], y) && sim[6].cards[i].visible){
            sim[y - 1].cards.resize(sim[6].cards.size());
            for(int j = sim[6].cards.size() - 1; j >= i; j--)
                sim[y - 1].cards[6] = sim[6].cards[j]; 
            for(int j = sim[6].cards.size() - 1; j >= i; j--)
                sim[6].cards.pop_back();
        }
        break;
    default:break;
    }
}

