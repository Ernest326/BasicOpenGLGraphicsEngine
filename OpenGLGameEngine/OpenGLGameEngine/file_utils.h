#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class fileutils {

public:

	static std::string read_file(const char* filepath)
	{

		std::ifstream file;
		std::string stringresult;

		file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

		try
		{
			file.open(filepath);
			std::stringstream streamresult;

			streamresult << file.rdbuf();

			file.close();

			stringresult = streamresult.str();

		}
		catch (std::ifstream::failure e)
		{
			std::cout << "Failed to read file: " << filepath << std::endl;
		}

		const char* result = stringresult.c_str();

		return result;
	}

};
