/*
 * METISParser.h
 *
 *  Created on: 27.11.2012
 *      Author: Christian Staudt (christian.staudt@kit.edu)
 */

#ifndef METISPARSER_H_
#define METISPARSER_H_

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <utility>
#include <stdexcept>
#include <cassert>

#include "../aux/Log.h"


namespace EnsembleClustering {

typedef int64_t node;

class METISParser {


protected:

	std::ifstream graphFile;


public:

	METISParser(std::string path);

	virtual ~METISParser();


	/**
	 * Get the METIS graph file header
	 */
	std::pair<int, int> getHeader();

	/**
	 * Test if graph file has a next line.
	 */
	bool hasNext();

	/**
	 * Get adjacencies from the next line in the METIS graph file.
	 */
	std::vector<node> getNext();


};

} /* namespace EnsembleClustering */
#endif /* METISPARSER_H_ */
