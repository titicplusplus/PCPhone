#include <iostream>
#include <cstdio>
#include <unistd.h>


void removeDupWord(std::string str, std::string &a, std::string &b )
{
	std::string word = "";
	a = "";
	for (auto x : str)
	{
		if (x == ' ')
		{
			a = word;
			word = "";
		}
		else {
		    word = word + x;
		}
	}
	
	b = word;
}

int main(int argc, char **argv)
{ 
	if (argc < 5)
		return 0;

	std::string path { argv[4] };
	std::string a {""};
	std::string b {""};

	removeDupWord(path, a, b);

         std::cout << path << " and " << a << " " << b << std::endl;

        #ifdef _WIN32 || _WIN64
                std::cout << "windows" << std::endl;
                execl("open", path.c_str(), NULL);
        #elif __APPLE__ || __MACH__
                std::cout << "apple" << std::endl;
                execl("open", path.c_str(), NULL);
        #elif __linux__ || __unix || __unix__
                std::cout << "linux" << std::endl;
                execl("/bin/xdotool","xdotool", a.c_str(), b.c_str(),(char *)  NULL);
        #endif
 
 
	return 0;
}
