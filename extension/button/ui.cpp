#include <iostream>
#include <QApplication>
#include <QFile>
#include <QProcess>
//#include <icecream.hpp>
#include "uiqt.hpp"
#include <QDebug>
#include <icecream.hpp>
#include <nlohmann/json.hpp>
#include <unistd.h>
#include <cstdio>

#include <QString>

using json = nlohmann::json;

std::unordered_map<std::string, json> extension; //the json extension

#ifndef __has_include
	static_assert(false, "__has_include not supported");
#else
#  if __has_include(<experimental/filesystem>)
#    include <experimental/filesystem>
		namespace fs = std::experimental::filesystem;
#  elif __has_include(<filesystem>)
#    include <filesystem>
	namespace fs = std::filesystem;
#  elif __has_include(<boost/filesystem.hpp>)
#    include <boost/filesystem.hpp>
		namespace fs = boost::filesystem;
#  endif
#endif



void open_all()                                                                                 
{                                                                                                   
         std::string path = "extension/button/extension";                                                            
         for (const auto &entry : fs::directory_iterator(path))                                      
         {                                                                                           
                 std::string path_n = entry.path();                                                  
		 std::cout << "path:" << path_n << std::endl;
                 std::ifstream ext(path_n + "/config.json");                                         
         
                 if (ext.is_open()) 
                 {
                         extension.insert( make_pair( path_n.substr(10, path_n.size() - 1), json::parse(ext) ) ); 
                 }
                 
                 ext.close();
          }
                 
          //for (auto &i : extension)                                                                  
          //        std::cout << i.first << " " << i.second << std::endl;                              
          
} 

int main(int argc, char **argv)
{

	open_all();

	if (argc == 2)
	{
		QApplication app(argc, argv);
		ui win(argv[1]);

		// QString::fromStdString( win.getPath() ) + 
		QFile File("stylesheet.qss");                                                  
		File.open(QFile::ReadOnly);
		QString StyleSheet = QLatin1String(File.readAll());
		app.setStyleSheet(StyleSheet);


		win.show();
		return app.exec();
	}
	else if (argc > 2)
	{
	
		std::string type { argv[3] };
		std::cout << "go go " << type << " " << extension.size() << std::endl;

		for (auto &i : extension)
		{
			std::cout << type << " " << i.second["ext"].get<std::string>() << std::endl;
			if (i.second["ext"] == type)
			{
				std::string os {""};

				#ifdef _WIN32 || _WIN64                                                             
					os = "exe_win";                                                           
         			#elif __APPLE__ || __MACH__                                                         
					os = "exe_mac";
				#elif __linux__ || __unix || __unix__                                               
					os = "exe_linux";
				#endif


				QStringList arguments;
				QString file { QString::fromStdString( i.second[os] ) };
				file = "./extension/button/extension/" + QString::fromStdString( type ) + "/" + file;
				std::cout << file.toStdString() << std::endl;

				for (int i {1}; i < argc; i++)
					arguments << QString::fromLocal8Bit(argv[i]);

				QProcess process;

				process.start(file, arguments);	
				process.waitForFinished();
				qDebug() << process.readAllStandardOutput();

				sleep(1);

				return 1;
			}
		}
			

		

		return 0;
	}

	return 1;
}
