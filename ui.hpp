#ifndef UI_HPP
#define UI_HPP
#include <memory>
#include <cmath>  
#include "openf.hpp"
#include <array>
#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QFormLayout>
#include <QGroupBox>
#include <QTranslator>
#include <QFileDialog>
#include <QSpinBox>
#include <QObject>
#include <QIcon> 
#include <QFile>
#include <QtNetwork>
#include <QUrl> 
#include <QDesktopServices>
#include <QComboBox>
#include <QMessageBox>
#include <QDialog>
#include <QTextEdit>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QCloseEvent> 
#include "server.hpp"
#include <QSpacerItem>
#include "dependency/icecream/icecream.hpp"

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


extern std::vector<json> file_json; // menuX.json
extern json config_json;	// menu.json

extern std::unordered_map<std::string, int> posi_json;
extern std::unordered_map<std::string, json> extension; //the json extension

void run(QString exe, QStringList args, int pos2);

class CustomDialog : public QDialog
{
	public:
		CustomDialog(json &futur_json_f) : futur_j{futur_json_f}
		{
			setWindowTitle("PCPhone");
			b = new QVBoxLayout(this);

			GBox = new QGroupBox("Add");
			lay = new QFormLayout();
			box = new QComboBox();

			text = new QLineEdit(this);

			/**for (auto &item : extension)
			for (auto i = extension.begin(); i != extension.end(); i++)
				box->addItem( QString::fromStdString(i->first));**/

			std::string path = "extension/";
			for (const auto &entry : fs::directory_iterator(path))
			{
				std::string path_n = entry.path();
				path_n = path_n.substr(10, path_n.size() - 1);
				box->addItem( QString::fromStdString(path_n));

			}



			lay->addRow("Slide's name:", text);
			lay->addRow("Choose a type:", box);
			GBox->setLayout(lay);
			b->addWidget(GBox);

			QPushButton *ok = new QPushButton("add", this);
			QPushButton *cc = new QPushButton("cancel", this);
			
			b->addWidget(ok);
			b->addWidget(cc);

			connect(ok, &QPushButton::clicked, this, [this]()
			{
				if ( name_ok(text->text()) )
					accept();
				else
				{
					QMessageBox msgBox;
					msgBox.setWindowTitle("PCPhone");
					msgBox.setText("You can't use this name.");
					msgBox.exec();
				}
			});


			connect(cc, &QPushButton::clicked, this, &QDialog::reject);

			resize(550,300);
			setLayout(b);

		}
		QComboBox* comboBox() { return box; }
		QString name() { return text->text(); }

		bool name_ok(QString text)
		{
			if (text == "")
				return false;

			for (int i {0}; i < futur_j["number_menu"]; i++)
			{
				if (text == QString::fromStdString(futur_j["slide" + std::to_string(i)][3]))
					return false;	
			}


			return true;

		}


	private:
		QComboBox *box;
		QGroupBox *GBox;

		QLineEdit *text;

		
		QFormLayout *lay;

		QVBoxLayout* b;

		json &futur_j;
		

};

class ui : public QWidget
{
	public:
		ui();
		void start();
		void change_file();
		void change_port();
		void open_link();

		void depla_b(int x, int y);
		int position(std::string name);
		std::array<int, 2> position2(QString name, QString name2);

		void config_grid(QString find_r);

		void delete_b();
		void open_b();

		void button_c(int x, int y);

		void freset();
		void fapply();

		std::vector<std::string> getListSlide();
		void sendStarter(int &x, int &y, std::string name);

		void createNewSlide(int x, int y);

		bool agree();
		//void start_stop_funt();

		//void restart_server();

		void open_ui_ext();


		~ui();
	
	protected:
		void closeEvent(QCloseEvent *event) override;


	private:
		openf f_open; //to open the extension s file

		QIcon icon;

		QFormLayout *form_layout;
		QGroupBox *settings;
		QGroupBox *option_bb;
		QVBoxLayout *main_layout;
		QHBoxLayout *option_b;


		QGroupBox *ap_re_g;
		QHBoxLayout *ap_re;

		int Bx;
		int By;


		QPushButton* left;
		QPushButton* right;
		QPushButton* up;
		QPushButton* down;

		QPushButton *deleteB;
		QPushButton *open;

		

		QGridLayout *grid;
		std::vector< std::vector< QPushButton* > > tab2d;
		QGroupBox *all_button;
		QSpinBox *port_l;
		QPushButton *button_f;
		QPushButton *apply;
		QPushButton *reset;
		QLabel *text_f;


		QPushButton*t_link;

		QComboBox *combo;
		
		json futur_json;

		std::vector<int> file_delete;
		std::vector<int> file_new;

		std::vector<std::string> file_new_type;
		std::vector<std::string> file_new_name;

		std::array<int, 4> xy;
		
		QSystemTrayIcon *sticon;
		bool stop_all;

		server_pcphone server;


		std::vector<std::thread> run_extensions;

};



#endif // ui.cpp
