# PCPhone
Control your pc with your phone (or other devices with a browser).

![alt text](https://github.com/titicplusplus/PCPhone/blob/main/screen/screen2.png?raw=true)


# Installation

You need Java, Maven and xdotool.

```
git clone https://github.com/titicplusplus/PCPhone.git
cd PCPhone/
mvn compile
mvn exec:java -Dexec.mainClass="WebPCPhone.Hello"
```
After the compilation, you can go on your browser and write http://localhost:8080/

# Settings

To change the button's settings, you must change the "menu1.json" in the folder "src/main/resources/file/".

```
	"button0": [
			"Imprimer",             ===> name
			"PCP_commande",		===> commande type ( PCP_commande for the mouse or the keys [xdotool], PCP_open to open a file, folder or a url [xdg-open], , PCP_script to run a commande ), see example on "menu1.json".
			"key ctrl+p",	        ===> commande name
			"/file/imprimante.png"  ===> the image
	],
```

if you would like to create a new menu, you can just create a new file "menu2.json" [ menuX.json ], and add it on the "menu.json".

Example of "menu.json":

```
{
	"nombre_menu": 3,
	"slide1" : [
		0, => position x
		0, => position y
		0  => menu1.json [ menu[X-1].json ]
	],
	"slide2" : [
		-1, => position x
		0,  => position y
		1  => menu2.json
	],
	"slide3" : [
		1, => same thing
		0,
		2 => menu3.json
	]
}
```


To change the menu, you can put your finger on the screen and swipe to the opposite side.
To apply your changes, you need to recompile the project ( ```mvn compile ``` and  ``` mvn exec:java -Dexec.mainClass="WebPCPhone.Hello" ``` ).

For the moment, there is no graphical interface for configuration.
