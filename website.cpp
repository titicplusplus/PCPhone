#include "website.hpp"
#include "dependency/icecream/icecream.hpp"
using json = nlohmann::json;


website::website() {

	/** open all of the json file **/

	std::ifstream big_m("client/menu.json");
	config_json = json::parse(big_m);
	big_m.close();

	std::cout << config_json.dump() << std::endl;
	int size { config_json["number_menu"] }; 
	std::cout << size << std::endl;
	
	file_json.resize(size);

	for (int i = 0; i < size; i++)	
	{
		std::string name { "slide" + std::to_string(i)};
		int v1 = config_json[name][0];
		int v2 = config_json[name][1];

		posi_json.insert( make_pair( std::to_string(v1) + "_" + std::to_string(v2), config_json[name][2]));


		std::cout << name << " " << config_json[name][2] << std::endl;

		std::ifstream ifs_n("client/menu" + std::to_string( config_json[name][2].get<int>()+1 ) + ".json");
		//file_json.push_back( json::parse(ifs_n) );
		file_json[ config_json[name][2] ] = json::parse(ifs_n);
		ifs_n.close();
	}

	std::string path = "extension/";
	for (const auto &entry : fs::directory_iterator(path))
	{
		std::string path_n = entry.path();
		std::ifstream ext(path_n + "/config.json");	

		if (ext.is_open())
		{
			extension.insert( make_pair( path_n.substr(10, path_n.size() - 1), json::parse(ext) ) ); 
		}

		ext.close();
	}

	for (auto &i : file_json)
		std::cout << i << std::endl;

	for (auto &i : extension)
		std::cout << i.first << " " << i.second << std::endl; 

}



void website::back_end( std::unordered_multimap<std::__cxx11::basic_string<char>, std::__cxx11::basic_string<char>, SimpleWeb::CaseInsensitiveHash, SimpleWeb::CaseInsensitiveEqual> query_fields)
{
	/** to execute the extension s code **/

	int pos = find_json_str( query_fields.find("x")->second,query_fields.find("y")->second);


	std::string type { file_json[pos]["type"] };

	auto it = extension.find(type);

	if (it == extension.end())
		return;

	std::string name;

	#ifdef _WIN32 || _WIN64
		name = "exe_win";
	#elif __APPLE__ || __MACH__
		name = "exe_mac";
	#elif __linux__ || __unix || __unix__
		name = "exe_linux";
	#endif

	QStringList arguments;

	if (it->second["exe_argu"] == "auto")
	{
		auto it2 = query_fields.find("position");

		if (it2 == query_fields.end())
			return;

		int position = std::stoi(it2->second);

		int i { 0 };
		std::string value = "args0"; 

		while (file_json[pos].find(value) != file_json[pos].end())
		{
			//args.push_back(value.c_str());
			//args.push_back( file_json[pos][value][position].get<std::string>().c_str()); 
			//IC( value.c_str(), file_json[pos][value][position].get<std::string>() );

			arguments << QString::fromStdString( file_json[pos][value][position].get<std::string>() );

			i++;
			value = "args" + std::to_string(i);
		}
	}
	else if (it->second["exe_argu"] == "manual")
	{
		//args += " -file ../../client/menu" + std::to_string(pos) + ".json";

		//args.push_back( "-file" );
		//args.push_back( (" ../.../client/menu" + std::to_string(pos) + ".json").c_str() ) ;
		
		arguments << "-file" << QString::fromStdString( " ../.../client/menu" + std::to_string(pos) + ".json" );

		for (auto &it : query_fields)
		{
			if (it.first != "x" && it.first != "y")
			{
				//args += " -" + it.first + " \"" + it.second + "\"";

				arguments << QString::fromStdString( it.first ) << QString::fromStdString( it.second );
			}

		}

	}


	std::string exe = "./extension/" + type + "/" + it->second[name].get<std::string>();
	std::cout <<  exe  << std::endl;

	
	std::cout << "Program started" << std::endl;
	
	
	QProcess start_prog;
	start_prog.start( QString::fromStdString( exe ), arguments );

	start_prog.waitForFinished();
	std::cout << start_prog.readAllStandardOutput().toStdString() << std::endl;

	return;
	
}

int website::port()
{
	// to get the port of the server
	return config_json["port"]; 

}

int website::find_json(int x, int y)
{
	/** return the position in json's vector with coodinate **/

	auto it = posi_json.find( std::to_string(x) + "_" + std::to_string(y));
	if (it != posi_json.end())
	{
		return it->second;
	}

	return 2000;

}

int website::find_json_str(std::string x, std::string y)
{
	/** return the position in json's vector with coodinate **/

	auto it = posi_json.find( x + "_" + y);
	if (it != posi_json.end())
	{
		return it->second;
	}

	return 2000;

}


std::string website::json_f(std::string x, std::string y)
{
	/** open the html file **/

	int pos = find_json_str(x,y);	
	if (2000 == pos)
	{
		return "nochange";
	}


	std::string result;
	
	result = file_json[pos]["type"];
	result += '\n' +  x + '\n';
	result += y + '\n';


//	int size { file_json[pos]["number"] };

	std::string type { file_json[pos]["type"] };

	auto it = extension.find(type);

	if (it == extension.end())
		return "";

	std::string file_n { "extension/"  + type + "/" +  it->second["html"].get<std::string>()}; 

	std::cout << file_n << std::endl;

	
	std::string returnS { f_open.open_file( file_n, file_json[pos])};	
	std::replace( returnS.begin(), returnS.end(), '\n', ' ');	

	result += returnS;


	std::cout << result  << std::endl;

	return result;

}

std::string website::arround_pos(int x, int y)
{
	/** to get the arrows on the slide **/

	std::string valeur = "0000";
	
	auto it = posi_json.find( std::to_string(x-1) + "_" + std::to_string(y));
	
	if (it != posi_json.end())
	{
		valeur[0] = '1';
	}

	it = posi_json.find( std::to_string(x) + "_" +  std::to_string(y+1));
	
	if (it != posi_json.end())
		valeur[1] = '1';

	it = posi_json.find( std::to_string(x+1) + "_" + std::to_string(y));
	
	if (it != posi_json.end())
		valeur[2] = '1';

	it = posi_json.find( std::to_string(x) + "_" + std::to_string(y-1));
	
	if (it != posi_json.end())
		valeur[3] = '1';

	std::cout << "val:" << valeur << std::endl;


	return valeur;
}

std::string website::ext_style(std::string x, std::string y)
{
	/** to get the css code the extension **/

	int pos = find_json_str(x,y);

	std::string type { file_json[pos]["type"] };

	auto it = extension.find(type);

	if (it == extension.end())
		return "";

	std::string file_n { "extension/"  + type + "/" +  it->second["css"].get<std::string>()}; 

	
	std::string returnS { f_open.open_file( file_n, file_json[pos])};	
	//std::cout << returnS << std::endl;

	return returnS;
	

}

std::string website::ext_script(std::string x, std::string y)
{
	/** to get the js code the extension **/

	int pos = find_json_str(x,y);

	std::string type { file_json[pos]["type"] };

	auto it = extension.find(type);

	if (it == extension.end())
		return "";

	std::string file_n { "extension/"  + type + "/" +  it->second["js"].get<std::string>()}; 

	std::string returnS { f_open.open_file( file_n, file_json[pos])};	

	return returnS;
	

}

std::string website::html_p()
{
	/** open the default page **/

	int x { config_json["pos"][0].get<int>() };
	int y { config_json["pos"][1].get<int>() };

	std::cout << "The positions are " << x << " " << y << std::endl;
	
	std::ifstream flux("file/index.html");

	std::string html;
	std::string line;


	while ( std::getline(flux, line) )
	{
		if (line == "<!-- Style -->")
		{
			html +=" <link rel=\"stylesheet\" href=\"/file/style.css\">";
			//html +=" <link rel=\"stylesheet\" href=\"/ext/style.css?x=0&y=0\">";
		}
		else if (line == "<!--Element -->")
		{
			int pos { find_json(x,y) };
			std::string type { file_json[pos]["type"] };
			IC(type, x, y, pos);

			auto it = extension.find(type);

			if (it == extension.end())
				std::cout << "pb" << std::endl;


			IC();
			std::string file_n { "extension/"  + type + "/" +  it->second["html"].get<std::string>()}; 
			IC();
			std::string result { f_open.open_file( file_n, file_json[pos] )};	
			html += result;
		}
		else
		{
			html += line;
		}
	}


	flux.close();

	IC();

	return html;

}

website::~website() {}

