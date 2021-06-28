# Welcome to PCPhone

## What is PCPhone ?

The goal of PCPhone is to control all devices with any devices.
For now, it's the beginning of PCPhone but I hope with the time, I will become a very good project.

## Installation 

### The simple way

	git clone https://github.com/titicplusplus/PCPhone.git
	cd PCPhone/
	./ui

### The hard way
To build this, you need to install:

	https://github.com/nlohmann/json
	https://github.com/pantor/inja
	https://gitlab.com/eidheim/Simple-Web-Server

Also, you need `xdotool` and `g++` and after you can write:

	g++ openf.cpp website.cpp main.cpp -lpthread -o ui -g -lstdc++fs	
	./ui


## How does it work ?

PCPhone has 3 important folders to work :
	
	PCPhone/
		client/		#The client's configuration with the json file
		extension/	#The extension's code like "button"
		file/		#The file like image, default page et etcv ...
		ui		#The executable
		
		#if you add the c++ file

		main.cpp	#The file that load web server and the class webserver

		website.cpp	#In this files, there is webserver class, she opens the file's configuration of the user, extension (in json in general) for the web server.
		website.hpp

		openf.cpp	#The is the openf class, she opens the file's configuration like html, css, js for webserver. 
		openf.hpp

		ui.cpp		#The user interface with qt 
		ui.hpp
		
