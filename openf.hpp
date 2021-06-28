#ifndef OPENF_HPP
#define OPENF_HPP

#include <string>
#include <iostream>
#include <fstream>
#include "dependency/inja/inja.hpp"
#include <nlohmann/json.hpp>

using json = nlohmann::json;

/** to open the file with inja **/

class openf {
	public:
		openf();
		std::string open_file( std::string filename,  json &j ); /** open a file with inja **/
		~openf();

};

#endif
