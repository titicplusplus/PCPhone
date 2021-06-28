#include "ui.hpp"

void run(QString exe, QStringList args, int pos2)
{
	QProcess process;
	process.start( exe, args );
	
	process.waitForFinished(-1);

	std::ifstream file_new { "client/menu" + std::to_string(pos2+1) + std::string(".json") };
	file_json[pos2] = json::parse(file_new );
	file_new.close();

	std::cout << process.readAllStandardOutput().toStdString() << std::endl;
	
	return;

}



ui::ui() 
{
	server.start();
	setWindowTitle("PCPhone");

	setWindowIcon(QIcon("favicon.ico"));
	icon.addFile("file/plusB.png");

	QString link;
	const QHostAddress &localhost = QHostAddress(QHostAddress::LocalHost);
	for (const QHostAddress &address: QNetworkInterface::allAddresses()) {
	    if (address.protocol() == QAbstractSocket::IPv4Protocol && address != localhost)
		  link = address.toString();
	}

	futur_json = config_json;


	link = "http://" + link + ":" + QString::number( config_json["port"].get<int>() );


	form_layout = new QFormLayout(this);
	settings    = new QGroupBox("Settings", this); 
	main_layout = new QVBoxLayout(this);
	grid	    = new QGridLayout(this);
	all_button  = new QGroupBox("Slide", this);
	port_l      = new QSpinBox(this);
	button_f    = new QPushButton("Open Image", this);
	apply       = new QPushButton("Apply", this);
	text_f      = new QLabel( QString::fromStdString(fs::absolute(config_json["image"].get<std::string>())),this);
	reset       = new QPushButton("           Reset           ", this);
	t_link      = new QPushButton( link, this );
	
	option_b    = new QHBoxLayout(this);
	option_bb   = new QGroupBox("Slide settings", this);

	up         = new QPushButton("Up ", this);
	down       = new QPushButton("Down ", this);
	left       = new QPushButton("Left ", this);
	right      = new QPushButton("Right ", this);

	deleteB    = new QPushButton("Delete", this);
	open       = new QPushButton("Open ", this);

	ap_re_g    = new QGroupBox(this);
	ap_re      = new QHBoxLayout(this);
	combo      = new QComboBox(this);


	/**control_server       = new QHBoxLayout(this);
	control_server_group = new QGroupBox("The server", this);
	start_stop           = new QPushButton("Stop", this);
	restart              = new QPushButton("Restart", this);**/



	Bx = -1;
	By = -1;



	sticon = new QSystemTrayIcon(this); // on construit notre icône de notification

	// Création du menu contextuel de notre icône
	QMenu* stmenu = new QMenu(this);

	QAction* actTexte1 = new QAction("Open graphics interface",this);
	connect( actTexte1, SIGNAL(triggered()), this, SLOT(show()));
	QAction* actTexte2 = new QAction("Exit",this);
	//connect( actTexte2, SIGNAL(triggered()), this, SLOT(ui::end_prog_m()));//end_prog()));
	
	connect( actTexte2, &QAction::triggered, this, &QCoreApplication::quit);//end_prog()));

	stmenu->addAction(actTexte1);
	stmenu->addAction(actTexte2);

	sticon->setContextMenu(stmenu); 

	sticon->setIcon(QIcon("favicon.ico")); 

	sticon->show();

	stop_all = false;

	//resize(1000,800);
}

bool ui::agree()
{
	if (Bx == -1 || By == -1)
		return false;

	return true;

}

void ui::open_link()
{
	std::cout << "open_link" << std::endl;
	QDesktopServices::openUrl(QUrl( t_link->text() ));
}

void ui::change_file()
{
	std::string text = text_f->text().toUtf8().constData();
	fs::path p { text };
	auto fileName { QFileDialog::getOpenFileName(this, "Open Image", QString::fromStdString(p.parent_path()), ("Image Files (*.png *.jpg *.bmp *.JPG *.PNG *.jpeg *.JPEG)"))};

	if (fileName != "")	
	text_f->setText(fileName);

	futur_json["image"] = text_f->text().toUtf8().constData();
}

void ui::createNewSlide(int x, int y)
{
	CustomDialog dialog{futur_json};
	if (dialog.exec() == QDialog::Accepted)
	{
		//qDebug() << dialog.comboBox()->currentText();
		//qDebug() << dialog.name();
		
		int value { 1 };

		while (fs::exists("client/menu" + std::to_string(value) + ".json" ))
				value++;

		auto jsonObjects = json::array();

		jsonObjects.push_back(x+xy[0]-1);
		jsonObjects.push_back(y+xy[3]-1);
		std::cout << "positoin " << x << " " << y << " " << xy[0] << " " << xy[3] << std::endl;
		jsonObjects.push_back(value-1);
		jsonObjects.push_back( dialog.name().toStdString() );

		futur_json["slide" + std::to_string( futur_json["number_menu"].get<int>() )] = jsonObjects;

		/**std::ofstream file { "client/menu" + std::to_string(value) + ".json" };

		file << "{ \"type\":\"" << dialog.comboBox()->currentText().toStdString() << "\", \"name\":\"" << dialog.name().toStdString()  << "\"}" << std::endl;**/

		file_new.push_back( value );

		//std::string file = dialog.comboBox()->currentText().toStdString();
		//std::string name = dialog.name().toStdString();
		//std::cout << file << " " << name << "les types" << std::endl;

		file_new_type.push_back( dialog.comboBox()->currentText().toStdString() );
		file_new_name.push_back( dialog.name().toStdString());


		futur_json["number_menu"] = futur_json["number_menu"].get<int>() + 1;

		config_grid(dialog.name());
		
		option_bb->setEnabled(true);
	}
}

void ui::closeEvent(QCloseEvent *event)
{
	hide();

	event->ignore();
}

void ui::button_c(int x, int y)
{
	if (Bx == -1 && By == -1)
		option_bb->setEnabled(true);
	else
	{
		tab2d[Bx][By]->setStyleSheet("background-color: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #565656, stop: 0.1 #525252, stop: 0.5 #4e4e4e, stop: 0.9 #4a4a4a, stop: 1 #464646);");
	}
	
	Bx = x;
	By = y;

	tab2d[Bx][By]->setStyleSheet("background: gray");

	std::cout << "Button position " << x << " " << y << " " << tab2d[Bx][By]->text().toUtf8().constData()  << std::endl;
}

void ui::change_port()
{
	std::cout << port_l->value() << std::endl;	
	apply->setText("Apply (Need to restart to apply the port)");
	futur_json["port"] = port_l->value();

}

void ui::freset()
{
	text_f->setText(QString::fromStdString(fs::absolute(config_json["image"].get<std::string>())));
	port_l->setValue( config_json["port"].get<int>() );

	futur_json.clear();
	futur_json = config_json;

	file_delete.clear();
	file_new.clear();
	file_new_name.clear();
	file_new_type.clear();

	config_grid("");
}

void ui::fapply()
{
	int x {-1};
	int y;

	sendStarter(x, y, combo->currentText().toStdString());

	if (x != -1)
	{
		futur_json["pos"][0] = x;
		futur_json["pos"][1] = y;
	}


	std::ofstream o{"client/menu.json"};
	o << futur_json << std::endl;
	config_json.clear();
	config_json = futur_json;


	/**td::cout << "go go" << std::endl;

	int pos { futur_json["number_menu"].get<int>() +1 };

	std::cout << "ici" << std::endl;
	
	while (fs::exists("client/menu" + std::to_string(pos) + ".json" ) )
	{
		fs::remove( "client/menu" + std::to_string(pos) + ".json" );
		pos++;
	}**/

	for (auto i : file_delete)
	{
		std::cout << "go remove" << i << std::endl;
		fs::remove( "client/menu" + std::to_string(i+1) + ".json" );
	}

	for (std::size_t i {0}; i < file_new.size(); i++)
	{
		std::ofstream file { "client/menu" + std::to_string( file_new[i] ) + ".json" };

		file << "{ \"type\":\"" << file_new_type[i] << "\", \"name\":\"" << file_new_name[i]  << "\"}" << std::endl;

		file.close();
	}

	file_delete.clear();
	file_new_name.clear();
	file_new.clear();
	file_new_type.clear();

	o.close();
}

int ui::position( std::string name )
{
	for (int i = 0; i < futur_json["number_menu"];i++)
	{
		std::string value = "slide" + std::to_string(i);

		if (futur_json[value][3].get<std::string>() == name)
		{
			return i;
		}
	}

	return -1;
}	

void ui::delete_b()
{
	if (!agree())
		return;

	if (futur_json["number_menu"] < 2)
		return;

	int pos { position( tab2d[Bx][By]->text().toStdString()) };

	if (pos == -1)
		return;

	file_delete.push_back( futur_json["slide" + std::to_string(pos)][2].get<int>() );
	futur_json.erase("slide" + std::to_string(pos));

	if (pos+1 != futur_json["number_menu"])
	{
		std::string nameT1 {"slide" + std::to_string(pos)};
		std::string nameT2 {"slide" + std::to_string(futur_json["number_menu"].get<int>() -1 )};

		json::iterator it = futur_json.find(nameT2);
		std::swap(futur_json[nameT1], it.value());
		futur_json.erase(it);
	}

	futur_json["number_menu"] = futur_json["number_menu"].get<int>() -1;

	config_grid("");
}


void ui::depla_b(int x, int y)
{

	if (!agree())
		return;

	x = Bx + x;
	y = By + y;

	std::cout << Bx << " "<< By << " " << x << " " << y << std::endl;

	if (x < 0 || y < 0 || x >= tab2d.size() || y >= tab2d[0].size() || tab2d[x][y] == nullptr)
		return;


	QString exchange { tab2d[x][y]->text() };

	if (exchange.isEmpty())
	{
		int pos { position( tab2d[Bx][By]->text().toStdString() ) };
		std::string jname { "slide" + std::to_string(pos) };

		futur_json[jname][0] = futur_json[jname][0].get<int>() + (x - Bx);
		futur_json[jname][1] = futur_json[jname][1].get<int>() + (y - By);

		config_grid( tab2d[Bx][By]->text() );

	}
	else
	{
		tab2d[Bx][By]->setStyleSheet("background-color: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #565656, stop: 0.1 #525252, stop: 0.5 #4e4e4e, stop: 0.9 #4a4a4a, stop: 1 #464646);");

		tab2d[x][y]->setStyleSheet("background: gray");


		tab2d[x][y]->setText( tab2d[Bx][By]->text()  );
		tab2d[Bx][By]->setText( exchange );


		QString pos1 { tab2d[x][y]->text() };

		std::array<int , 2> pos = position2( exchange, pos1);

		if (pos[0] == -1 || pos[1] == -1)
		{
			std::cout << "avant" << std::endl;
			return;
		}

		std::string jname1 { "slide" + std::to_string(pos[0]) };
		std::string jname2 { "slide" + std::to_string(pos[1]) };


		std::swap(futur_json[jname1][0], futur_json[jname2][0]);
		std::swap(futur_json[jname1][1], futur_json[jname2][1]);


		Bx = x;
		By = y;

	}
}

std::array<int, 2> ui::position2(QString name, QString name2 )
{
	std::array<int, 2> pos = {-1,-1};
	std::string nameT1 { name.toStdString() };
	std::string nameT2 { name2.toStdString() };

	for (int i = 0; i < futur_json["number_menu"];i++)
	{
		std::string value = "slide" + std::to_string(i);

		if (futur_json[value][3].get<std::string>() == nameT1)
		{
			pos[0] = i;
		}
		else if (futur_json[value][3].get<std::string>() == nameT2)
		{
			pos[1] = i;
		}
	}

	return pos;

}

void ui::sendStarter(int &x, int &y, std::string name)
{
	for (int i = 0; i < futur_json["number_menu"]; i++)
	{
		std::string value { "slide" + std::to_string(i)};

		if (futur_json[value][3].get<std::string>() == name)
		{
			x = futur_json[value][0];
			y = futur_json[value][1];

		}
	}
	
}

std::vector<std::string> ui::getListSlide()
{
	std::vector<std::string> list_string;

	list_string.resize(futur_json["number_menu"].get<int>());

	int x { futur_json["pos"][0] };
	int y { futur_json["pos"][1] };

	int add {1};

	std::cout << list_string.size() << std::endl;

	for (std::size_t i = 0; i < list_string.size(); i++)
	{
		std::string value { "slide" + std::to_string(i)};
		std::cout << value << std::endl;
		
		if (x == futur_json[value][0] && y == futur_json[value][1])
		{
			std::cout << "gogogo" << std::endl;
			list_string[0] = futur_json[value][3];
			add = 0;
		}
		else
		{
			std::cout << i + add << " v" << std::endl;
			if (i+add != list_string.size())
				list_string[i + add] = futur_json[value][3];
			else
				std::cout << "pb" << std::endl;
		}
	}

	return list_string;
}

/**void ui::start_stop_funt()
{
	if ( start_stop->text() == "Stop" )
	{
		std::cout << "Stop" << std::endl;
		start_stop->setText("Start");
		server.quit();
	}
	else
	{
		start_stop->setText("Stop");
		std::cout << "Start" << std::endl;
		apply->setText("Apply");
		//server.start();
	}

}

void ui::restart_server()
{
	server.quit();
	server.port_conf();
	apply->setText("Apply");

	//server.start();

}**/

void ui::config_grid(QString find_r)
{

	Bx = -1;
	By = -1;

	/**for (auto& i : tab2d)
		for (auto& j : i)
			delete j**/

	for (std::size_t i = 0; i < tab2d.size(); i++)
		for (std::size_t j = 0; j < tab2d[i].size(); j++)
			delete ( tab2d[i][j] );

	tab2d.clear();

	auto &arrayJ = futur_json["slide0"];

	xy = { arrayJ[0], arrayJ[0], arrayJ[1], arrayJ[1] };


	for (int i = 0; i < futur_json["number_menu"]; i++)
	{
		std::string name = "slide" + std::to_string(i);


		if (xy[0] > futur_json[name][0])
		{
			xy[0] = futur_json[name][0];
		}
		if (xy[1] < futur_json[name][0])
		{
			xy[1] = futur_json[name][0];
		}
		if (xy[2] < futur_json[name][1])
		{
			xy[2] = futur_json[name][1];
		}
		if (xy[3] > futur_json[name][1])
		{
			xy[3] = futur_json[name][1];
		}
	}

	std::cout <<  xy[0] << " " << xy[1] << " " << xy[2] << " " << xy[3] << std::endl;	


	int yyy { std::abs( xy[2] - xy[3] + 3) }; 
	int xxx { std::abs( xy[1] - xy[0] + 3) };
	
	for (int i = 0; i < xxx; i++)
	{
		tab2d.emplace_back();
		for (int j = 0; j < yyy; j++)
		{
			tab2d[i].push_back(NULL);
		}
	}
	

	for (int i = 0; i < futur_json["number_menu"]; i++)
	{
		const std::string name { "slide" + std::to_string(i) };

		int PosX { std::abs(futur_json[name][0].get<int>() - xy[0] +1 ) };
		int PosY { std::abs(futur_json[name][1].get<int>() - xy[3] +1 ) };

		std::string text_n {futur_json[name][3].get<std::string>() }; 

		const QString ui { QString::fromStdString(text_n) };

		tab2d[PosX][PosY] = new QPushButton(ui, this);
	}


	const QSize buttonsSize { QSize(500, 500) };

	for (int i = yyy-1; i >= 0; i--)
	{
		for (int j {0}; j < xxx; j++)
		{
			if (tab2d[j][i] == nullptr)
			{
				tab2d[j][i] = new QPushButton(this);
				tab2d[j][i]->setIcon(icon);
				tab2d[j][i]->setIconSize(QSize(150,150)); //);
				tab2d[j][i]->setStyleSheet("background: none");
				
				connect(tab2d[j][i], &QPushButton::clicked, this, [this , i, j]{ createNewSlide(j,i); });

			}
			else
			{
				if (tab2d[j][i]->text() == find_r)
				{
					Bx = j;
					By = i; 
				}
				connect(tab2d[j][i], &QPushButton::clicked, this, [this , i, j]{ button_c(j,i); });
			}

			//tab2d[j][i]->setFixedSize( buttonsSize );
			tab2d[j][i]->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);		
			grid->addWidget(tab2d[j][i],yyy-1- i, j, 1, 1);
		}
		

	}

	if (Bx == -1 && By == -1)
	{
		option_bb->setEnabled(false);
	}
	else
	{
		button_c(Bx, By);
	}

	//grid->setSizeConstraint( QLayout::SetMinAndMaxSize);
	
	grid->setContentsMargins(0, 0, 0, 0);
	grid->setSpacing(20);


	std::cout << grid->verticalSpacing() << std::endl;

}

void ui::start()
{
	config_grid("");

	std::cout << "open_link" << std::endl;
	std::cout << "setting part" << std::endl;
	
	all_button->setLayout(grid);

	port_l->setMaximum(65535);
	port_l->setValue( futur_json["port"].get<int>() );

	t_link->setStyleSheet("border: none; background: none; color: rgb(0,161,254)");

	connect(button_f, &QPushButton::clicked, this, &ui::change_file);
	connect(port_l, QOverload<int>::of(&QSpinBox::valueChanged), this, &ui::change_port);
	connect(apply, &QPushButton::clicked, this, &ui::fapply);
	connect(reset, &QPushButton::clicked, this, &ui::freset);
	connect(t_link, &QPushButton::clicked, this, &ui::open_link);

	connect(up, &QPushButton::clicked, this, [this]{ depla_b(0,1); });
	connect(down, &QPushButton::clicked, this, [this]{ depla_b(0,-1); });
	connect(left, &QPushButton::clicked, this, [this]{ depla_b(-1,0); });
	connect(right, &QPushButton::clicked, this, [this]{ depla_b(1,0); });

	//connect(start_stop, &QPushButton::clicked, this, &ui::start_stop_funt);
	//connect(restart, &QPushButton::clicked, this, &ui::restart_server);

	connect(deleteB, &QPushButton::clicked, this, &ui::delete_b);
	connect(open, &QPushButton::clicked, this, &ui::open_ui_ext);

	/**option_b->setSizeConstraint( QLayout::SetFixedSize );
	form_layout->setSizeConstraint( QLayout::SetFixedSize );
	ap_re->setSizeConstraint( QLayout::SetFixedSize );**/

	
	option_b->addWidget(up);
	option_b->addWidget(down);
	option_b->addWidget(right);
	option_b->addWidget(left);
	option_b->addWidget(deleteB);
	option_b->addWidget(open);


	for (auto i : getListSlide())
	{
		combo->addItem( QString::fromStdString( i  ));
	}

	option_bb->setLayout(option_b);

	form_layout->addRow("The port", port_l);
	form_layout->addRow(text_f, button_f);
	form_layout->addRow("The starter slide", combo);
	//form_layout->addRow(reset, apply);

	settings->setLayout(form_layout);


	ap_re->addWidget(apply);
	ap_re->addWidget(reset);

	ap_re_g->setLayout(ap_re);

	/**control_server->addWidget( start_stop );
	control_server->addWidget( restart );

	control_server_group->setLayout(control_server);**/

	option_bb->setMaximumHeight(150);
	settings->setMaximumHeight(300);
	ap_re_g->setMaximumHeight(150);

	main_layout->setSizeConstraint( QLayout::SetMaximumSize );


	main_layout->addWidget(all_button);
	main_layout->addWidget(option_bb);
	main_layout->addWidget(settings);
	main_layout->addWidget(ap_re_g);
	//main_layout->addWidget(control_server_group);
	main_layout->addWidget(t_link);

	main_layout->setAlignment(t_link, Qt::AlignHCenter);

	setLayout(main_layout);
}

void ui::open_ui_ext()
{
	if (!agree())
		return;


	std::string name;

	#ifdef _WIN32 || _WIN64
		name = "ui_win";
	#elif __APPLE__ || __MACH__
		name = "ui_mac";
	#elif __linux__ || __unix || __unix__
		name = "ui_linux";
	#endif



	int pos { position( tab2d[Bx][By]->text().toStdString() ) };
	int pos2 { config_json["slide" + std::to_string(pos)][2] };

	std::cout << file_json[pos2]["type"] << std::endl;

	QStringList arguments;
	
	QString args0 = QString::fromStdString( "client/menu" + std::to_string(pos2+1) + std::string(".json"));

	IC( args0.toStdString() );

	arguments << args0;
	std::string type { file_json[pos2]["type"] };

	auto it = extension.find( type );

	if (it != extension.end())
	{
		std::string exe { "./extension/" + type + "/" + it->second[name].get<std::string>() };

		IC( exe );
		//QProcess process;
		//process.start( QString::fromStdString( exe ), arguments );

		//process.waitForFinished();
		//std::cout << process.readAllStandardOutput().toStdString() << std::endl;


		run_extensions.emplace_back(run, QString::fromStdString(exe), arguments, pos2 );
	}

}

ui::~ui()
{
	std::cout << "server end" << std::endl;
	server.quit();
	std::cout << "by" << std::endl;
}
