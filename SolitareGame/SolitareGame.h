//для реализации интерфейса будем использовать библтотеку 
//у каждого элемента класса должна быть масть и значение карты(типа король, валет, шестерка и т.д.)
#include <iostream>
class Card {
private:
	char rank[1]; //= { 'A', '2', '3', '4', '5', '6', '7', '8', '9', '10', 'J', 'Q', 'K' };//ранг 
	char suit[1];//масть (D, C, H, S)
public:
	Card(char rank1[1], char suit1[1]) {
		rank1 = rank;
		suit1 = suit;
	}
	~Card() {}
	int GetRank() {
		return rank[1];
	}
	int GetSuit() {
		return suit[1];
	}
	void SetRank(char rank1[1]) {
		rank1 = rank;
	}
	void SetSuit(char suit1[1]) {
		suit1 = suit;
	}
	int Colour() {
		if (suit[1] == 'H' || suit[1] == 'D') {
			return red;//как вернуть тут цвет хз
		}
		else {
			return black;
		}
	}


};
