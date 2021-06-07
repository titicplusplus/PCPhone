#include <iostream>
#include <cstring>

int main(int argc, char **argv)
{
	/**for (int i = 0; i < argc; i++)
	{
		std::cout << argv[i] << std::endl;
	}**/

	int os {-1};

	#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
		os = 1;
	#elif TARGET_OS_MAC
		os = 2;
	#elif __linux__ || __unix__
		os = 3;
	#elif defined(_POSIX_VERSION)
		os = 4;
	#else
	#   error "Unknown compiler"
		return -1;
	#endif	

	if (argc < 7)
		return -1;

	std::string start {""};


	if (strcmp ("PCP_open", argv[4]) == 0)//		argv[4] == "PCP_open")
	{
		std::cout << "PCP_open" << std::endl;

		if (os == 3)
		{
			start += "xdg-open ";
		}

		start += argv[6];

	}	
	else if (strcmp ("PCP_commande", argv[4]) == 0)
	{
		std::cout << "PCP_commande" << std::endl;

		if (os == 3)
		{
			start += "xdotool ";
		}

		start += argv[6];
	}
	else if (strcmp ("PCP_script", argv[4]) == 0)
	{
		std::cout << "PCP_script" << std::endl;
		start = argv[6];

	}

	std::cout << start << " " << argv[4] << " " << argv[6]  << " os:" << os << std::endl;
	system( start.c_str() );
}
