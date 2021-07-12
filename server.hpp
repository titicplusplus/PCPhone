#ifndef SERVER_HPP
#define SERVER_HPP


#include "dependency/web-server/server_http.hpp"
#include "website.hpp"
#include <QThread>

class server_pcphone : public QThread
{
	public:
		server_pcphone();
		void port_conf()
		{
			server.config.port = web.port(); //The port
		}
		void run() override;
		void stop_server();
		~server_pcphone();

	private:
		website web;
		HttpServer server; //The server

};	


#endif
