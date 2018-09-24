#include "Filereader.h"
#include <stdlib.h>
#include <cstddef>
#include <fstream>
#include <iostream>
#include <vector>
#include <stdio.h>
#include <string>
#define DEBUG false

using namespace std;

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
		cout << "Too many arguments" << endl;
		return 1;
	}
	string mp_fname = "";
	string pl_fname = "";
	for(int i=1; i<argc; i++){
		if(argv[i].compare("-m")==0 && i<argc-1){
			mp_fname=argv[++i];
		} else if(argv[i].compare("-p") && i<argc-1){
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
		return 1;
	}
	FileReader mkf_r(&mpf);
	if(!mkf_r.readFile()){
		cout << "Reader Failure" << endl;
		mkf.close();
		return 1;
	}
	mkf.close();
	
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
	
	
	
	return 0;
}