# Extension

An important part of PCPhone is the extension and you can develop your own extension very easy.

# How to create an extension

All of the extensions are in this directory ``` extension/ ```
To create a new extension, you simply need to create a folder on this folder.

Example: ``` extension/TheNewExtensionName/ ```

For this tutorial, I will use the preinstalled extension ```button```.

The typical scheme is:

	extension/button/
		config.json 	#The most important file, you can change this name

		#For the frontend:

		button.html
		style.css
		script.js

		#For the backend:

		exe_linux
		exe_windows.exe
		exe_mac


		#The user interface

		ui_linux
		ui_windows.exe
		ui_mac
		(I would like to simplify this part)

But to keep data of user, in the folder ``` client/ ```, PCPhone creates json file.
Here is the json file of a extension button :


	{
		"type" : "button", #The extension name
		"number" : 8,	   #The number of arguments in the arrays


		"args0" : [
			"Bureau",
			"Capture d'Ecran",
			"MStream",
			"Thunderbird",
			"Photos boulot",
			"Dossier Entreprise",
			"Devis 2021",
			"Facture 2021"
		],

		"args1" : [
			"PCP_commande",
			"PCP_commande",
			"PCP_open",
			"PCP_script",
			"PCP_open",
			"PCP_open",
			"PCP_open",
			"PCP_open"
		],

		"args2" : [
			"key Super_L+d",
			"key super+F11",
			"http://192.168.1.68:3000",
			"thunderbird &",
			"/mnt/704E048C4E044D72/LesImages/Photos boulot/",
			"/mnt/704E048C4E044D72/Entreprise/",
			"/mnt/704E048C4E044D72/Entreprise/DEVIS 2021/",
			"/mnt/704E048C4E044D72/Entreprise/FACTURE 2021/"
		],

		"args3" : [
			"/file/ub.png",
			"/file/cam.png",
			"/file/ms.png",
			"/file/th.png",
			"/file/img4.png",
			"/file/devis.png",
			"/file/ma.png",
			"/file/ent.png"
		]
	}

The file is very important when you load the html, css and javascript files, but also when the extension open the executables files.


# The config.json file

The config.json is the fist file that opens PCPhone. If there are no config.json, PCPhone will not be able to open the extention.

Here is a typical config.json:

	{
		"html": "button.html",
		"css":  "style.css",
		"js": "script.js",

		"exe_argu": "auto",
		"exe_linux": "exe_linux",
		"exe_win": "exe_win",
		"exe_mac": "exe_mac",


		"ui_linux": "ui_linux",
		"ui_win": "ui_win",
		"ui_mac": "ui_mac"


	}

That looks like the typical scheme.

# The frontend part

When the user asks a new slide, PCPhone give for the browser 3 thinks.

- The html code, to create the Element.
- The css part, to make this beautiful.
- And the js code, to improve all.

The simplify the process, I add a template engine in PCPhone : [inja](https://github.com/pantor/inja) .

With this, you can do like a bridge between the 
