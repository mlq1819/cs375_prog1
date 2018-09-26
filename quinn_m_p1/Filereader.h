#ifndef MQ_FILEREADER_H
#define MQ_FILEREADER_H
#include <stdlib.h>
#include <cstddef>
#include <fstream>
#include <iostream>
#include <vector>

//This source file was created my Michael Quinn
//mquinn5@binghamton.edu
//This file is intended to read files line-by-line and save them into string vectors

class FileReader{
	private:
		std::ifstream * file;
		std::vector<std::string> lines;
		bool read;
		std::size_t index;
	public:
		FileReader(std::ifstream *); //constructor; requires open file pointer
		~FileReader(){file=NULL;}; //destructor
		bool isRead() const {return this->read;};
		bool readFile(); //reads the file and saves it into this->lines
		std::string operator[](std::size_t index) const {return this->lines[index];};
		bool atStart() const {return this->index==0;};
		bool atEnd() const {return this->index==this->getSize()-1;};
		bool next(); //increments index and returns true if !atEnd()
		std::string current() const {return this->lines[this->index];}; //returns current line
		void start(){this->index=0;}; //sets index to start
		void end(){this->index=this->getSize()-1;}; //sets index to end
		std::size_t getIndex() const {return this->index;};
		std::size_t getSize() const {return this->lines.size();};
};

#endif
