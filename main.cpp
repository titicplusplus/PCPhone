#include <string>
#include <iostream>
#include "website.hpp"

#include <simple-web-server/server_http.hpp>
using HttpServer = SimpleWeb::Server<SimpleWeb::HTTP>;

webserver web;

int main() {

  	HttpServer server; //The server
	server.config.port = web.port(); //The port

	server.resource["^/$"]["GET"] = [](std::shared_ptr<HttpServer::Response> response, std::shared_ptr<HttpServer::Request> request) {
    		response->write( web.html_p(0,0) );
 	}; //main page

	server.resource["^/arround$"]["GET"] = [](std::shared_ptr<HttpServer::Response> response, std::shared_ptr<HttpServer::Request> request) {
		std::cout << request->path << " " << request->method << std::endl;
		auto query_fields = request->parse_query_string();

		for (auto& field : query_fields)
			std::cout << field.first << ": " << field.second<< std::endl;

    		response->write( web.arround_pos( std::stoi( query_fields.find("x")->second ), std::stoi( query_fields.find("y")->second ) ) );
 	}; //For the arround

	server.resource["^/json$"]["GET"] = [](std::shared_ptr<HttpServer::Response> response, std::shared_ptr<HttpServer::Request> request) {
		std::cout << request->path << " " << request->method << std::endl;
		auto query_fields = request->parse_query_string();

		for (auto& field : query_fields)
			std::cout << field.first << ": " << field.second<< std::endl;

    		response->write( web.json_f(  query_fields.find("x")->second , query_fields.find("y")->second  ) );
 	}; //to get the new html code of the extension


	server.resource["^/ext/style.css$"]["GET"] = [](std::shared_ptr<HttpServer::Response> response, std::shared_ptr<HttpServer::Request> request) {
		std::cout << request->path << " " << request->method << std::endl;
		auto query_fields = request->parse_query_string();

		for (auto& field : query_fields)
			std::cout << field.first << ": " << field.second<< std::endl;

    		response->write( web.ext_style(  query_fields.find("x")->second , query_fields.find("y")->second  ) );
 	}; //to get the new css code of the extension


	server.resource["^/ext/script.js$"]["GET"] = [](std::shared_ptr<HttpServer::Response> response, std::shared_ptr<HttpServer::Request> request) {
		std::cout << request->path << " " << request->method << std::endl;
		auto query_fields = request->parse_query_string();

		for (auto& field : query_fields)
			std::cout << field.first << ": " << field.second<< std::endl;

    		response->write( web.ext_script(  query_fields.find("x")->second , query_fields.find("y")->second  ) );
 	}; //to get the new js code of the extension

	server.resource["^/exe$"]["GET"] = [](std::shared_ptr<HttpServer::Response> response, std::shared_ptr<HttpServer::Request> request) {
		std::cout << request->path << " " << request->method << std::endl;
		auto query_fields = request->parse_query_string();

		for (auto& field : query_fields)
			std::cout << field.first << ": " << field.second<< std::endl;

		web.back_end( query_fields );

    		response->write("200 OK" );
 	}; //to execute the application


	server.default_resource["GET"] = [](std::shared_ptr<HttpServer::Response> response, std::shared_ptr<HttpServer::Request> request) {

		std::string path { request->path };
		std::cout << path.substr(1) << std::endl;

		std::ifstream ifs(path.substr(1));
	
		if(ifs) {

			std::string result;

			std::string line;

			while (std::getline(ifs, line))
				result += line + "\n";
			
		        response->write(result );
		}
		else
		{
			std::cout << "non" << std::endl;
		}


	}; //to get all of the file (image, file)

	server.start(); // to start the server
	
	return 0;

}

