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
		bool same(Card o) const {return this->name.compare(o.getName())==0};
		bool cheap(Card o) const {return this->price<o.getPrice();}
		bool expensive(Card o) const {return this->price>o.getPrice();};
};

#endif