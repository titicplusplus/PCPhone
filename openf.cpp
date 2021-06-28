#include "openf.hpp"
#include <nlohmann/json.hpp>

using namespace inja;

openf::openf() {}

std::string openf::open_file(std::string filename, json &j)
{
	/** open a file with inja **/

	Environment env;
	Template temp = env.parse_template(filename);

	/**env.add_callback("find", 2, [](Arguments& args) {

		if ( args.at(0)->get<std::string>().find( args.at(1)->get<std::string>() ) == std::string::npos)
		{
			return 0;
		}

		return 1;
	});


	env.add_callback("f_part", 3, [](Arguments& args) {
		std::string send = args.at(0)->get<std::string>();

		std::size_t found;
		std::string ui = args.at(1)->get<std::string>();

		for (int i {0}; i < args.at(2)->get<int>(); i++)
		{
			found = send.find(ui);

			if (found != std::string::npos and found+1 < send.size())
			{
				send.erase(0, found+1);
			}
			else
			{
				return "";
			}

		}

		
		found = send.find(ui);

		if (found != std::string::npos)
		{
			send.erase(found, send.size() - found);
			return send.c_str();
		}
		

		return send.c_str();

	});**/

	std::string result = env.render(temp, j);	
	return result;

}


openf::~openf() {}
