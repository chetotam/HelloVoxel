#include "File_util.h"

#include <fstream>
#include <sstream>
#include <iostream>


std::string util::file_to_string(const std::string & path)
{
	std::ifstream file;
	file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	std::stringstream data;
	try {
		file.open(path);
		data << file.rdbuf();
		file.close();
	}
	catch (const std::ifstream::failure& e) {
		// Maybe should pass exception up to caller
		std::cerr << "Could not read file " << path << "\n";
	}
	return data.str();
}
