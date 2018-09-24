#include "program1.h"
#include "Filereader.h"
#define DEBUG false

using namespace std;

vector<string> parser(string str){
	vector<string> str_v = vector<string>();
	string s = "";
	for(unsigned int i=0; i<str.size(); i++){
		char c = str.at(i);
		if(c==' '){
			if(s.size()>0){
				str_v.push_back(s);
				s="";
			}
		} else {
			s.append(1, c);
		}
	}
	if(s.size()>0)
		str_v.push_back(s);
	str_v.shrink_to_fit();
	return str_v;
}

Card::Card(string name, long price){
	this->name=name;
	this->price=price;
}

Card makeCard(vector<string> str_v){
	string name = str_v[0];
	long price = stol(str_v[1], nullptr, 10);
	return Card(name, price);
}

int main(int argc, char** argv){
	if(DEBUG){
		for(int i=0; i<argc; i++){
			if(i!=0)
				cout << ' ';
			cout << argv[i];
		}
		cout << endl;
	}
	if(argc<5){
		cout << "Not enough arguments" << endl;
		return 1;
	}
	string mp_fname = "";
	string pl_fname = "";
	string m = "-m";
	string p = "-p";
	for(int i=1; i<argc; i++){
		if(m.compare(argv[i])==0 && i<argc-1){
			if(mp_fname.compare("")==0){
				cout << "market-price-file given multiple times" << endl;
				return 1;
			}
			mp_fname=argv[++i];
		} else if(p.compare(argv[i])==0 && i<argc-1){
			if(pl_fname.compare("")==0){
				cout << "price-list-file given multiple times" << endl;
				return 1;
			}
			pl_fname=argv[++i];
		}
	}
	if(mp_fname.compare("")==0 || pl_fname.compare("")==0){
		if(mp_fname.compare("")==0)
			cout << "market-price-file name not given" << endl;
		else if(DEBUG)
			cout << "market-price-file name: " << mp_fname << endl;
		if(pl_fname.compare("")==0)
			cout << "price-list-file name not given" << endl;
		else if(DEBUG)
			cout << "price-list-file name: " << mp_fname << endl;
		return 1;
	} else if(DEBUG){
		cout << "market-price-file name: " << mp_fname << endl;
		cout << "price-list-file name: " << mp_fname << endl;
		cout << endl;
	}
	
	ifstream mpf, plf;
	mpf.open(mp_fname);
	if(!mpf.is_open()){
		cout << "Bad File Name: " << mp_fname << endl;
		plf.open(pl_fname);
		if(!plf.is_open())
			cout << "Bad File Name: " << pl_fname << endl;
		return 1;
	}
	FileReader mpf_r(&mpf);
	if(!mpf_r.readFile()){
		cout << "Reader Failure" << endl;
		mpf.close();
		return 1;
	}
	mpf.close();
	
	plf.open(pl_fname);
	if(!plf.is_open()){
		cout << "Bad File Name: " << pl_fname << endl;
		return 1;
	}
	FileReader plf_r(&plf);
	if(!plf_r.readFile()){
		cout << "Reader Failure" << endl;
		plf.close();
		return 1;
	}
	plf.close();
	
	vector<Card> mp_cards = vector<Card>();
	mpf_r.start();
	unsigned int num_cards = stoi(mpf_r.current(), nullptr, 10);
	if(num_cards+1!=mpf_r.getSize()){
		cout << "File size does not match Indicated File size" << endl;
	}
	while(mpf_r.next()){
		vector<string> str_v = parser(mpf_r.current());
		if(str_v.size()!=2){
			cout << "Bad Format: \"";
			for(unsigned int i=0; i<str_v.size(); i++){
				if(i!=0)
					cout << ' ';
				cout << str_v[i];
			}
			cout << "\" not \"ssssssss llll\"" << endl;
			return 1;
		}
		mp_cards.push_back(makeCard(str_v));
	}
	mp_cards.shrink_to_fit();
	
	vector<List> pl_lists = vector<List>();
	plf_r.start();
	num_cards=0;
	int vector_index=-1;
	int cur=-1;
	do{
		cur++;
		if(cur==((int) num_cards)){
			if(vector_index>-1){
				pl_lists[vector_index].shrink_to_fit();
			}
			vector_index++;
			cur=-1;
			vector<string> str_v = parser(plf_r.current());
			if(str_v.size()!=2){
				cout << "Bad Format: \"";
				for(unsigned int i=0; i<str_v.size(); i++){
					if(i!=0)
						cout << ' ';
					cout << str_v[i];
				}
				cout << "\" not \"llll llll\"" << endl;
				return 1;
			}
			num_cards = stoi(str_v[0], nullptr, 10);
			long weight = stol(str_v[1], nullptr, 10);
			List list = List(weight);
			pl_lists.push_back(list);
		} 
		else {
			vector<string> str_v = parser(plf_r.current());
			if(str_v.size()!=2){
				cout << "Bad Format: \"";
				for(unsigned int i=0; i<str_v.size(); i++){
					if(i!=0)
						cout << ' ';
					cout << str_v[i];
				}
				cout << "\" not \"ssssssss llll\"" << endl;
				return 1;
			}
			pl_lists[vector_index].addCard(makeCard(str_v));
		}
	} while(plf_r.next());
	pl_lists.shrink_to_fit();
	
	
	
	return 0;
}