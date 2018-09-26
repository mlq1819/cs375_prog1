#include "Filereader.h"
#ifndef DEBUG
#define DEBUG false
#endif
//This source file was created my Michael Quinn
//mquinn5@binghamton.edu
//This file is intended to read files line-by-line and save them into string vectors
//if the file causes segmentation faults, set DEBUG to true

using namespace std;

FileReader::FileReader(ifstream * file){
	this->file=file;
	this->read=false;
	this->lines=vector<string>();
	this->index=(size_t) 0;
}

bool FileReader::readFile(){
	if(!this->file->is_open())
		return false;
	this->file->clear();
	this->file->seekg(0, ios_base::beg);
	string str;
	if(DEBUG)
		cout << "Reading file ..." << endl;
	while(getline(*file, str))
		this->lines.push_back(str);
	if(DEBUG)
		cout << "File read" << endl;
	this->lines.shrink_to_fit();
	this->read=true;
	return true;
}

bool FileReader::next(){
	if(this->index<this->getSize()-1){
		this->index++;
		return true;
	}
	return false;
}
