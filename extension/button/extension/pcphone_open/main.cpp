#include <iostream>
#include <unistd.h>
#include <cstdio>

int main(int argc, char **argv)
{
	std::cout << "hello" << std::endl;
	for (int i = 0; i < argc; i++)
		std::cout << argv[i] << std::endl;
	if (argc != 5)
		return 1;


	std::string path { argv[4] };
	#ifdef _WIN32 || _WIN64
		std::cout << "windows" << std::endl;
		execl("open", path.c_str(), NULL);	
	#elif __APPLE__ || __MACH__
		std::cout << "apple" << std::endl;
		execl("open", path.c_str(), NULL);	
	#elif __linux__ || __unix || __unix__
		std::cout << "linux" << std::endl;
		execl("/usr/bin/xdg-open","xdg-open", path.c_str(), NULL);	

	#endif

	std::cout << path << std::endl;

	return 0;
}
