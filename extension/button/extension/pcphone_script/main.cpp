#include <iostream>
#include <cstdio>
#include <unistd.h>

int main(int argc, char **argv)
{ 
	if (argc < 5)
		return 0;

	std::string path { argv[4] };
        #ifdef _WIN32 || _WIN64
                std::cout << "windows" << std::endl;
                execl("open", path.c_str(), NULL);
        #elif __APPLE__ || __MACH__
                std::cout << "apple" << std::endl;
                execl("open", path.c_str(), NULL);
        #elif __linux__ || __unix || __unix__
                std::cout << "linux" << std::endl;
                execl("/bin/bash","bash", path.c_str(), NULL);
        #endif
 
         std::cout << path << std::endl;
 
	return 0;
}
