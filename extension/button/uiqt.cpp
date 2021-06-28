
#include "uiqt.hpp"

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

ui::ui(std::string filepath)
{
	setWindowTitle("buttons extension");
	setWindowIcon(QIcon("favicon.ico"));
	

	slide = new QGroupBox("The buttons", this);
	slide_l = new QHBoxLayout(this);

	settings = new QGroupBox("Settings", this);
	parm = new QFormLayout(this);

	name = new QLineEdit(this);
	//comd = new QLineEdit(this);
	//comb = new QComboBox(this);

	img_l = new QHBoxLayout(this);
	img  = new QPushButton("Change Image", this);
	img_line = new QLineEdit(this);


	depla   = new QGroupBox("Move", this);
	depla_l = new QHBoxLayout(this);

	right_p = new QPushButton("Right", this);
	left_p  = new QPushButton("Left", this);

	suppr = new QPushButton("Delete it",this);

	save  = new QGroupBox("Apply", this);
	save_l = new QHBoxLayout(this);

	apply = new QPushButton("Apply", this);
	cancel = new QPushButton("cancel", this);



	////////////////// The buttons ///////////////////


	std::ifstream filux(filepath);

	client = json::parse(filux);

	if (client.size() == 2)
	{
		client["number"] = 0;

		std::cout << "ui mais non" << std::endl;

		client["args0"] = json::array();
		client["args1"] = json::array();
		client["args2"] = json::array();
		client["args3"] = json::array();
		std::cout << "ui" << std::endl;
	}
	else if (client["number"] != 0)
	{
		config_grid(true, 0,0);	
	}
	
	buttons.push_back( new QPushButton(this));
	int end_v = buttons.size() - 1;
	buttons[end_v]->setIcon(QIcon( QString::fromStdString(  "file/plusB.png"  )) );
	buttons[end_v]->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
	connect(buttons[end_v], &QPushButton::clicked, this, &ui::new_b);

	slide_l->addWidget(buttons[buttons.size() -1]);
	//slide_l->setSizeConstraint( QLayout::SetMaximumSize );

	slide->setLayout(slide_l);


	////////////////// The settings of buttons ///////////////////
	
	img_l->addWidget(img_line);
	img_l->addWidget(img);
	

	settings->setEnabled(false);

	parm->addRow("The button's name", name);
	parm->addRow("The button's image", img_l);

	connect(img, &QPushButton::clicked, this, &ui::open_img);

	settings->setLayout(parm);

	////////////////// The moves ///////////////////
	
	depla->setEnabled(false);

	depla_l->addWidget(left_p);
	depla_l->addWidget(right_p);
	depla_l->addWidget(suppr);
	depla->setMaximumHeight(150);

	depla->setLayout(depla_l);

	connect(left_p, &QPushButton::clicked, this,[this]{ fmove(-1); });
	connect(right_p, &QPushButton::clicked, this, [this] { fmove(1);} );
	connect(suppr, &QPushButton::clicked, this, &ui::fdell);

	////////////////// Apply or Cancel ////////////////////
	
	save_l->addWidget( apply );
	save_l->addWidget( cancel );

	save->setMaximumHeight(150);
	save->setLayout(save_l);
	
	connect(cancel, &QPushButton::clicked, this, &QWidget::close);
	connect( apply, &QPushButton::clicked, this, [this, filepath] { fapply( filepath ); });
	


	all_config = new QVBoxLayout(this);

	all_config->addWidget(slide);
	all_config->addWidget(depla);
	all_config->addWidget(settings);
	all_config->addWidget(save);

	setLayout(all_config);
	resize(800, 600);

	num_b = -1;


}

bool ui::event( QEvent *event )
{
	if ( event->type() == QEvent::Resize)
	{
		for ( std::size_t n {0}; n < buttons.size(); ++n )
		{
			buttons[n]->setIconSize( QSize( buttons[n]->size().width()*0.75, buttons[n]->size().height()*0.75));
		}

	}

	return QWidget::event( event );
}


void ui::config_grid(bool newb, int xc, int yc)
{
	for (auto i : buttons )
	       delete i;	

	buttons.clear();


	for (std::size_t i {0}; i < client["number"]; i++)
	{
		buttons.push_back( new QPushButton(this));
		buttons[i]->setIcon(QIcon( QString::fromStdString( getPath() + client["args1"][i].get<std::string>() )) );
		buttons[i]->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

		if (xc != 0)
			buttons[i]->setIconSize( QSize( xc*0.75, yc*0.75 ));

		connect(buttons[i], &QPushButton::clicked, this, [this , i]{ click_b(i); });

		slide_l->addWidget(buttons[i]);

	}

	
	if (!newb)
	{
		IC(newb);
		buttons.push_back( new QPushButton(this));
		int end_v = buttons.size() - 1;
		buttons[end_v]->setIcon(QIcon( QString::fromStdString(  "file/plusB.png"  )) );
		buttons[end_v]->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
		slide_l->addWidget(buttons[buttons.size() -1]);

		if (xc != 0)
			buttons[end_v]->setIconSize( QSize( xc*0.75, yc*0.75 ));
		connect(buttons[end_v], &QPushButton::clicked, this, &ui::new_b);
	}

}


std::string ui::getPath()
{
	/**std::string pathA { fs::current_path() };

	std::size_t size { pathA.find("extension/") };
	pathA = pathA.substr(0, size); **/

	return "";
}


void ui::click_b(int n)
{
	if (num_b == -1)
	{
		settings->setEnabled(true);
		depla->setEnabled(true);
	}
	else
	{
		save_b();	

		buttons[num_b]->setStyleSheet("background-color: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #565656, stop: 0.1 #525252, stop: 0.5 #4e4e4e, stop: 0.9 #4a4a4a, stop: 1 #464646);");
	}

	num_b = n;
	
	buttons[num_b]->setStyleSheet("background: gray");

	name->setText( QString::fromStdString( client["args0"][num_b].get<std::string>() ));
	img_line->setText(QString::fromStdString( client["args1"][num_b].get<std::string>() ));

	open_settings();
	


}

void ui::save_b()
{
	client["args0"][num_b] = name->text().toStdString();
	client["args1"][num_b] = img_line->text().toStdString();

	std::string type { client["args2"][num_b] };

	int i1 { 0 };
	int i2 { 0 };
	int i3 { 0 };

	for (auto &i : extension)
	{
		if (i.second["ext"] == type)
		{
			for (auto &element : i.second["arguments"].items())
			{
				std::string value = element.value()[0];
				if (element.key() == "QFileExplorer")
				{
					client[value][num_b] = lines_ext_for_b[i1]->text().toStdString();	

					i1++;	
				}
				else if (element.key() == "QLineEdit")
				{
					client[value][num_b] = lines_ext[i2]->text().toStdString();	

					i2++;	
				}
				else if (element.key() == "QComboBox")
				{
					client[value][num_b] = box_ext[i3]->currentText().toStdString();

					i3++;	
				}
			}
		}
	}
}



void ui::open_settings()
{
	std::string type { client["args2"][num_b] };

	for (auto &i : extension)
	{
		if (i.second["ext"] == type)
		{
			for (int i {parm->rowCount() -1}; i > 1; i--)
			{
				parm->removeRow(i);
			}


			for (auto &i : lines_ext)
				i.clear();	
			lines_ext.clear();

			for (auto &i : buttons_ext)
				i.clear();	
			buttons_ext.clear();

			for (auto &i : box_ext)
				i.clear();	
			box_ext.clear();

			for (auto &i : lines_ext_for_b)
				i.clear();	
			lines_ext_for_b.clear();

			for (auto &i : layouts_ext_for_b)
				i.clear();	
			layouts_ext_for_b.clear();

			for (auto &i : buttons_ext2)
				i.clear();	
			buttons_ext2.clear();


			for (auto &element : i.second["arguments"].items())
			{

				if (element.key() == "QFileExplorer")
				{
					int size { layouts_ext_for_b.size() };

					layouts_ext_for_b.push_back( new QHBoxLayout() );
					buttons_ext.push_back(new QPushButton("Open Directory" ));
					buttons_ext2.push_back( new QPushButton("Open File"));

					lines_ext_for_b.push_back(new QLineEdit());
					lines_ext_for_b[ size ]->setText( QString::fromStdString(
							       	client[ element.value()[0].get<std::string>()  ][num_b].get<std::string>() ));

					layouts_ext_for_b[size]->addWidget( lines_ext_for_b[size] );
					layouts_ext_for_b[size]->addWidget( buttons_ext[size] );
					layouts_ext_for_b[size]->addWidget( buttons_ext2[size] );

					connect(buttons_ext[size], &QPushButton::clicked, this, [this, size]{ open(size, true); });
					connect(buttons_ext2[size], &QPushButton::clicked, this, [this, size]{ open(size, false); });


					parm->addRow( QString::fromStdString( element.value()[1].get<std::string>() ),
						       layouts_ext_for_b[size] );

				}
				else if (element.key() == "QLineEdit")
				{
					lines_ext.push_back(new QLineEdit());
					lines_ext[ lines_ext.size() - 1 ]->setText( QString::fromStdString(
							       	client[ element.value()[0].get<std::string>()  ][num_b].get<std::string>() ));

					parm->addRow( QString::fromStdString( element.value()[1].get<std::string>() ),
						       	lines_ext[ lines_ext.size() - 1 ] );

				}
				else if (element.key() == "QComboBox")
				{
					box_ext.push_back(new QComboBox());
					parm->addRow( QString::fromStdString( element.value()[1].get<std::string>() ),
						       	box_ext[ box_ext.size() - 1 ] );

				}

			}

			return;
		}

	}
	
}


void ui::open_all()
{
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
 
	 for (auto &i : extension)
		 std::cout << i.first << " " << i.second << std::endl; 

}

void ui::fmove(short pos)
{	
	if ( (num_b > 0 && pos == -1) || (num_b < buttons.size() - 2 && pos == 1) )
	{
		int i { 0 };
		std::string value = "args0";
 
                while (client.find(value) != client.end())
                {
			std::swap( client[value][num_b], client[value][num_b+pos]);
                        i++;
                        value = "args" + std::to_string(i);
                }

		config_grid(false, buttons[0]->size().width(), buttons[0]->size().height());
		click_b(num_b + pos);
	}

	
	return;	
}

void ui::fdell()
{
	if (num_b > -1 && client["number"] != 0)
	{
		int i { 0 };
		std::string value = "args0";
 
                while (client.find(value) != client.end())
                {
			client[value].erase( client[value].begin() + num_b );
                        i++;
                        value = "args" + std::to_string(i);

                }

		num_b = -1;
		client["number"] = client["number"].get<int>() -1;
		settings->setEnabled(false);
		depla->setEnabled(false);
		config_grid(false, buttons[0]->size().width(), buttons[0]->size().height());
	}

	
	return;	

}

void ui::fapply(std::string filename)
{
	save_b();
	std::ofstream file { filename };

	file << client << std::endl;
	file.close();
	close();

}

void ui::open(int number, bool file)
{
	QString filename;

	if (file)
	{
		filename = QFileDialog::getExistingDirectory(this, "Open Directory");
	}
	else
	{
		filename = QFileDialog::getOpenFileName(this, "Open File");
	}

	if (!filename.isEmpty())
		lines_ext_for_b[number]->setText(filename);
}

void ui::open_img()
{
	QFileInfo file ( img_line->text()  );
	QString filename { QFileDialog::getOpenFileName(this, "Open File", file.absoluteFilePath(), "Images (*.png *.xpm *.jpg *.PNG *.JPG *.XPM *.bmp *.BMP)" ) }; 

	IC( filename.toStdString() );

	if (!filename.isEmpty())
	{
		std::string path { filename.toStdString() };

		std::size_t index = path.find( fs::current_path() );

		if (index == std::string::npos)
			img_line->setText(filename);
		else
		{
			QDir dir;
			img_line->setText(dir.relativeFilePath(filename));
		}

		
		buttons[num_b]->setIcon(QIcon( img_line->text() ));
	}

}

void ui::new_b()
{
	CustomDialog dialog( extension );

	if (dialog.exec() == QDialog::Accepted)
	{
		std::string value = "args0";
		int i{ 0 };
		//num_b = buttons.size();
 
                while (client.find(value) != client.end())
                {
			client[value] += "";
                        i++;
                        value = "args" + std::to_string(i);
                }

		std::string name { dialog.comboBox()->currentText().toStdString() };

		for (auto &i : extension)
		{
			if (i.second["name"] == name)
			{
				client["args2"][ client["number"].get<int>()  ] = i.second["ext"];
				break;
			}

		}

		client["number"] = client["number"].get<int>() + 1;
		config_grid(false, buttons[0]->size().width(), buttons[0]->size().height());
		click_b( buttons.size() -2);
		
		settings->setEnabled(true);
		depla->setEnabled(true);

	}
}

ui::~ui()
{

}


