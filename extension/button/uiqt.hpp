#ifndef uiqt_hpp
#define uiqt_hpp


#include <icecream.hpp>

#include <QPointer>

#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include <QFileDialog>
#include <QWidget>
#include <QGroupBox>
#include <QLayout>
#include <QFormLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QComboBox>
#include <QDialog>
#include <QEvent>
#include <QTreeView>
#include <QFileSystemModel>
#include <QDebug>

using json = nlohmann::json;
extern std::unordered_map<std::string, json> extension; //the json extension


class CustomDialog : public QDialog
{
	public:
		CustomDialog( std::unordered_map<std::string, json> &ext_dia)
		{
			setWindowTitle("PCPhone");
			b = new QVBoxLayout(this);

			GBox = new QGroupBox("Add");
			lay = new QFormLayout();
			box = new QComboBox();

			/**for (auto &item : extension)
			for (auto i = extension.begin(); i != extension.end(); i++)
				box->addItem( QString::fromStdString(i->first));**/

			/**std::string path = "extension/";
			for (const auto &entry : fs::directory_iterator(path))
			{
				std::string path_n = entry.path();
				path_n = path_n.substr(10, path_n.size() - 1);
				box->addItem( QString::fromStdString(path_n));

			}**/

			for (auto &item : ext_dia)
			{
				box->addItem( QString::fromStdString( item.second["name"].get<std::string>() ));

			}



			lay->addRow("Choose a type:", box);
			GBox->setLayout(lay);
			b->addWidget(GBox);

			QPushButton *ok = new QPushButton("add", this);
			QPushButton *cc = new QPushButton("cancel", this);

			b->addWidget(ok);
			b->addWidget(cc);

			connect(ok, &QPushButton::clicked, this, [this]()
			{
				accept();
				
			});


			connect(cc, &QPushButton::clicked, this, &QDialog::reject);

			resize(550,300);
			setLayout(b);

		}
		QComboBox* comboBox() { return box; }


	private:
		QComboBox *box;
		QGroupBox *GBox;

		QFormLayout *lay;

		QVBoxLayout* b;
};



class ui : public QWidget
{
	public:
		ui(std::string filepath);
		void config_grid(bool newb, int xc, int yc);
		std::string getPath();

		bool event(QEvent *event) override;

		void click_b(int n);
		void save_b();

		void open_all();
		void open_settings();
		

		void fmove(short pos);
		void fdell();

		void fapply(std::string filename);
		
		void open(int number, bool file);
		void open_img();

		void new_b();
		

		~ui();

	private:
		int num_b;



		QPointer<QGroupBox> slide;
		QPointer<QHBoxLayout> slide_l;

		std::vector< QPointer<QPushButton> > buttons;


		QPointer<QGroupBox> settings;
		QPointer<QFormLayout> parm;

		QPointer<QLineEdit> name;
		//QPointer<QComboBox> comb;
		
		QPointer<QHBoxLayout>	img_l; 
		QPointer<QPushButton> img;
		QPointer<QLineEdit> img_line;

		//QLineEdit *comd;
		//QPushButton *comd;
		
		std::vector< QPointer<QLineEdit>> lines_ext;
		std::vector< QPointer<QComboBox>> box_ext;

		std::vector< QPointer<QPushButton >> buttons_ext;
		std::vector< QPointer<QPushButton >> buttons_ext2;
		std::vector< QPointer<QLineEdit>> lines_ext_for_b;
		std::vector< QPointer<QHBoxLayout>> layouts_ext_for_b;


		QPointer<QGroupBox> depla;
		QPointer<QHBoxLayout> depla_l;

		QPointer<QPushButton> right_p;
		QPointer<QPushButton> left_p;
		QPointer<QPushButton> suppr;


		QPointer<QGroupBox> save;
		QPointer<QHBoxLayout> save_l;

		QPointer<QPushButton> apply;
		QPointer<QPushButton> cancel;


		json client;


		/**QGroupBox *all;
		QFormLayout *all_l;

		QPushButton *img_back;**/

		QPointer<QVBoxLayout> all_config;

};

#endif
