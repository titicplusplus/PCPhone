#include <string>
#include <iostream>
#include <thread>


#include <nlohmann/json.hpp>

#include <QApplication>
#include <QtCore>
//#include "website.hpp"
#include "ui.hpp"

using json = nlohmann::json;

std::vector<json> file_json; // menuX.json
json config_json;	// menu.json

std::unordered_map<std::string, int> posi_json;
std::unordered_map<std::string, json> extension; //the json extension


int main(int argc, char *argv[]) {

	//server_pcphone server;
	//server.start();

	QApplication app(argc,argv);
	QFile File(":/stylesheet.qss");                                                  
	File.open(QFile::ReadOnly);
	QString StyleSheet = QLatin1String(File.readAll());

	app.setStyleSheet(StyleSheet);
	

	ui interface;

	interface.start();

  	interface.show();
	//server.quit();
	return app.exec();
}
