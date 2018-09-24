#ifndef MQ_PROGRAMH_H
#define MQ_PROGRAM1_H
#include <stdlib.h>
#include <cstddef>
#include <fstream>
#include <iostream>
#include <vector>
#include <stdio.h>
#include <string>

class Card{
	private:
		std::string name;
		long price;
	public:
		Card(std::string name, long price);
		std::string getName() const {return this->name;};
		long getPrice() const {return this->price;};
		bool same(Card o) const {return this->name.compare(o.getName())==0;};
		bool cheap(Card o) const {return this->price<o.getPrice();}
		bool expensive(Card o) const {return this->price>o.getPrice();};
};

class List{
	private:
		std::vector<Card> cards;
		long weight;
	public:
		List(long weight){this->weight=weight;};
		void addCard(Card c){this->cards.push_back(c);};
		void shrink_to_fit(){this->cards.shrink_to_fit();};
		Card operator[](std::size_t index) const {return this->cards[index];};
		std::size_t getSize() const {return this->cards.size();};
		long getWeight() const {return this->weight;} ;
};

#endif