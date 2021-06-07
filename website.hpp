#ifndef WEBSITE_HPP
#define WEBSITE_HPP

//#include <experimental/filesystem>

#include <string>
#include <nlohmann/json.hpp>
#include <fstream>
#include "openf.hpp"
#include <unordered_map>
#include <bits/stdc++.h>


#include <simple-web-server/server_http.hpp>
using HttpServer = SimpleWeb::Server<SimpleWeb::HTTP>;

using json = nlohmann::json;


/** webserver do the link between the extension's file and the client's configuration **/

class webserver {
	public:
		webserver(); // open all of the json file
		std::string html_p(int x, int y); //open the default page
		std::string arround_pos(int x, int y); //to get the arrows on the slide
		std::string json_f(std::string x, std::string y); // open the html file
		std::string ext_style(std::string x, std::string y); //open the css file
		std::string ext_script(std::string x, std::string y); //open the js file

		void back_end( std::unordered_multimap<std::__cxx11::basic_string<char>, std::__cxx11::basic_string<char>, SimpleWeb::CaseInsensitiveHash, SimpleWeb::CaseInsensitiveEqual> query_fields); //to execute the extension's code

		int port(); //to get the port
		int find_json(int x, int y); //return the position in json's vector with coodinate
		int find_json_str(std::string x, std::string y); //same but with string arguments
		~webserver();


	private:

		
		std::vector<json> file_json; // menuX.json
		json config_json;	// menu.json
		openf f_open; //to open the extension's file


		std::unordered_map<std::string, int> posi_json;
		std::unordered_map<std::string, json> extension; //the json extension


};

#endif // 

