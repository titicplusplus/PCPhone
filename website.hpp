#ifndef WEBSITE_HPP
#define WEBSITE_HPP

//#include <experimental/filesystem>

#include <string>
#include <fstream>
#include "openf.hpp"
#include <unordered_map>
#include <bits/stdc++.h>
#include <unistd.h>
#include <cstdio>
#include <QString>
#include <QStringList>
#include <QProcess>
#include <QDebug>

#ifndef __has_include
  static_assert(false, "__has_include not supported");
#else
#  if __has_include(<experimental/filesystem>)
#    include <experimental/filesystem>
     namespace fs = std::experimental::filesystem;
#  elif __has_include(<filesystem>)
    #include <filesystem>
    namespace fs = std::filesystem;
#  elif __has_include(<boost/filesystem.hpp>)
#    include <boost/filesystem.hpp>
     namespace fs = boost::filesystem;
#  endif
#endif

#include "dependency/web-server/server_http.hpp"
using HttpServer = SimpleWeb::Server<SimpleWeb::HTTP>;


extern std::vector<json> file_json; // menuX.json
extern json config_json;	// menu.json

extern std::unordered_map<std::string, int> posi_json;
extern std::unordered_map<std::string, json> extension; //the json extension



/** webserver do the link between the extension s file and the client s configuration **/

class website {
	public:
		website(); // open all of the json file
		std::string html_p(); //open the default page
		std::string arround_pos(int x, int y); //to get the arrows on the slide
		std::string json_f(std::string x, std::string y); // open the html file
		std::string ext_style(std::string x, std::string y); //open the css file
		std::string ext_script(std::string x, std::string y); //open the js file

		void back_end( std::unordered_multimap<std::__cxx11::basic_string<char>, std::__cxx11::basic_string<char>, SimpleWeb::CaseInsensitiveHash, SimpleWeb::CaseInsensitiveEqual> query_fields); //to execute the extension's code

		int port(); //to get the port
		int find_json(int x, int y); //return the position in json s vector with coodinate
		int find_json_str(std::string x, std::string y); //same but with string arguments
		~website();


	private:

		
		openf f_open; //to open the extension s file

};

#endif // 


