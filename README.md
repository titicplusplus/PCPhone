# Installation

You need to install xdotool.

```
git clone https://github.com/titicplusplus/PCPhone.git
cd PCPhone/
./ui
```

# Settings

To change the button's setting, you must change the "menu1.json" in the folder "client/file/".
```
	"Imprimer",             ===> name
	"PCP_commande",		===> commande type ( PCP_commande for the mouse or the keys [xdotool], PCP_open to open a file, folder or a url [xdg-open], , PCP_script to run a commande ), see example on "menu1.json".
	"key ctrl+p",	        ===> commande name
	"/file/imprimante.png"  ===> the image
```
if you would like to create a new menu, you can just create a new file "menu2.json" [ menuX.json ], and add it on the "menu.json".

Example of "menu.json":
```
{
	"nombre_menu": 3,
	"slide1" : [
		0, => position x
		0, => position y
		0,  => menu1.json [ menu[X-1].json ]
		"Home" => name
	],
	"slide2" : [
		-1, => position x
		0,  => position y
		1  => menu2.json
		"work" => name
	],
	"slide3" : [
		1, => same thing
		0,
		2 => menu3.json
		"discord" => name
	]
}
```
To change of menu, you can put your fingers on the screen the rightigts to the opposite side (swap). To apply your changes, you need to restart the program.

For the moment, there is no graphical interface for the configuration.
