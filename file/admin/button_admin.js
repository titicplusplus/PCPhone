button = document.getElementsByClassName('send');
jsonfile = undefined;
Basejsonfile = undefined;
var who_but = -1;

function Apply() {
	if (who_but == -1) {
		return;
	}

	console.log("ui");

	if (arguments[0] == 1) {
		var type = jsonfile["button" + who_but][1];
		var text = document.getElementById("com_text").value;  


		var requestURL = '/try_commande?t=' + type + "&c=" + text; 
		var request = new XMLHttpRequest();
		request.open('GET', requestURL);
		request.responseType = 'json';
		request.send();
	}
	else if (arguments[0] == 2) {
		for (var i = who_but; i < button.length; i++) {

			jsonfile["button" + i] = jsonfile["button" + (i+1)]; 
			if (i+1 != button.length) {
				button[i+1].setAttribute("onclick","sendResquet(" + i + ")");
			}

		}
		button[who_but].remove();
		base();
		delete jsonfile["button" + button.length];
	}
	else if (arguments[0] == 3) {
		jsonfile["button" + who_but] = Basejsonfile["button" + who_but];
		sendResquet(who_but);
	}
}

function sendAll()
{
	let a = window.location.pathname;
	const url = "/CHANGE_FILE/";
	var xhr = new XMLHttpRequest();
	xhr.open("POST", url);
	//xhr.setRequestHeader('Content-Type', 'application/json');
	xhr.setRequestHeader("Content-Type", "application/x-www-form-urlencoded");

	xhr.send("data=" + JSON.stringify( jsonfile ).replaceAll("&"," ") + "&name=" + a);


}

function move()
{
	var tamp = jsonfile["button" + who_but];
	jsonfile["button" + who_but] = jsonfile["button" + (who_but + arguments[0])];
	jsonfile["button" + (who_but + arguments[0])] = tamp; 

	var tabl = AllButtons[0].innerHTML.split("</button>");
	
	tamp = tabl[who_but];

	tabl[who_but] = tabl[who_but + arguments[0]];
	tabl[who_but + arguments[0]] = tamp;

	var result = "";

	for (var i = 0; i < tabl.length; i++)
		result += tabl[i] + "</button>";

	AllButtons[0].innerHTML = result;
	button = document.getElementsByClassName('send');

	button[who_but].setAttribute('onclick','sendResquet(' + who_but + ')');
	who_but += arguments[0];

	button[who_but].setAttribute('onclick','sendResquet(' + who_but + ')');
	
}

function base()
{
	who_but = -1;
	taille(false);

	var apply = document.getElementById("Apply_button");
	apply.style.display = "none";

	buttonPart = document.getElementById('buttonConfig');

	buttonPart.textContent = "";
}	



function taille()
{
	fond = document.getElementById('fond');
	fond.style.height = ( window.innerHeight * 0.2 ) + "px";

	fond.style.width = window.innerWidth.toString() + "px";

	AllButtons = document.getElementsByClassName('button_section');
	AllButtons[0].style.height = (window.innerHeight * 0.2) + "px";


	var taille = window.innerHeight * 0.15;


	if ( taille*button.length > window.innerWidth*0.8 )
	{
		taille = window.innerWidth*0.8 / button.length;
	}
	
	for (var i = 0; i < button.length; i++)
	{
		button[i].style.height = taille + "px";
		button[i].style.width = taille + "px";
	}

	if (arguments[0] == true)
	{

	let a = window.location.pathname;
	var requestURL = '/JSON_FILES/' + a.substring(7, a.length); 
	var request = new XMLHttpRequest();
	request.open('GET', requestURL);
	request.responseType = 'json';
	request.send();

	request.onload = function() {
		jsonfile = request.response;
		Basejsonfile  = JSON.parse(JSON.stringify(jsonfile));;
		console.log(jsonfile);
	}

	}

}

buttonAdd = [];

function add_b() {
	var but = document.getElementById('slide');

	let num = buttonAdd.length;
	console.log("ui" + num);

	buttonAdd.push(document.createElement('button'));
	buttonAdd[num].className = 'send';
	
	let arg = button.length; 
	buttonAdd[num].onclick = function() { sendResquet(arg); }
	but.appendChild(buttonAdd[num]);
	
	//but.setAttribute("onclick", "sendResquet(" + button.length - 1+ ")");
	/*buttonAdd[num].addEventListener('click', event => {
		sendResquet( button.length - 1 );
	});*/
	
	who_but = button.length;	

	jsonfile["button" + (button.length-1)] = ["", "", "", "" ];

	button = document.getElementsByClassName('send');
	taille(false);

}

function sendResquet() {

	who_but = arguments[0];
	var button_n = document.getElementById('name_b');
	button_n.value = jsonfile["button" + arguments[0]][0];

	button_n.addEventListener('change', event => {
		jsonfile["button" + who_but][0] = button_n.value;
	});

	var button_i = document.getElementById('name_i');
	
	button_i.value = jsonfile["button" + who_but][3];

	button_i.addEventListener('change', event => {
		jsonfile["button" + who_but][3] = button_i.value;
	});
	
	//button_p = document.getElementById('name_p');
	//button_p.value = arguments[0] + 1;
	

	
	buttonPart = document.getElementById('buttonConfig');
	buttonPart.textContent = "";
	
	var buttonS = document.createElement('p');
	var listName = ["Open a File/Folder/Software/Link and ...","executable path", "command line", "keyboard execution" ];

	let num = -1;

	if (jsonfile["button" + arguments[0]][1] == "PCP_open")
	{
		num = 0;
	}
	else if (jsonfile["button" + arguments[0]][1] == "PCP_commande")
	{
		num = 3;
	}
	else if (jsonfile["button" + arguments[0]][1] == "PCP_script" || jsonfile["button" + arguments[0]][1] == "PCP_open_soft")
	{
		num = 2;
	}
	else if (jsonfile["button" + arguments[0]][1] == "PCP_script_open")
	{
		num = 1;
	}

	console.log(num + " mais ui " + arguments[0] + " " + jsonfile["button" + arguments[0]][1]);

	if (num != -1)
	{
		var newContent = document.createTextNode(listName[num]);
		listName.splice(num, 1);
	}
	else
		var newContent = document.createTextNode("");


	buttonS.appendChild(newContent);
	buttonS.className = "sendS";
	buttonS.setAttribute("id", "PCP_V");
	buttonPart.appendChild(buttonS);

	var button_path = document.createElement("INPUT");
	button_path.setAttribute("type", "text");
	button_path.setAttribute("id", "com_text");
	
	button_path.addEventListener('change', event => {
		jsonfile["button" + who_but][2] = button_path.value;
	});

	button_path.value = jsonfile["button" + arguments[0]][2];

	/**var button_file = document.createElement("INPUT");
	button_file.setAttribute("type", "file");
	button_file.setAttribute("id", "com_text2");
	
	button_file.addEventListener('change', (event) => {
   		 const fileList = event.target.files;
	   	 console.log(fileList);
 	 });


	buttonPart.appendChild(button_file);**/

	var buttonOther = [];
	var buttonOtherName = []
	
	for (var i = 0; i < listName.length; i++)
	{
		buttonOther.push(document.createElement("button"));
		buttonOtherName.push(document.createTextNode(listName[i]));
		buttonOther[i].value = listName[i];

		buttonOther[i].className = "sendS";
		buttonOther[i].setAttribute("onclick", "change(" + i + ")");
		buttonOther[i].appendChild(buttonOtherName[i]);
		
		buttonPart.appendChild(buttonOther[i]);
	}

	buttonPart.appendChild(button_path);

	var apply = document.getElementById("Apply_button");
	apply.style.display = "block";




}

function change() {
	var listName = ["Open a File/Folder/Software/Link and ...","executable path", "command line", "keyboard execution" ];
	var buttonS = document.getElementById("PCP_V");

	let num = listName.indexOf(buttonS.innerText);
	
	listName.splice(num, 1);

	let str = listName[arguments[0]];
	if (str == "Open a File/Folder/Software/Link and ...") {
		jsonfile["button" + who_but][1] = "PCP_open";
	}
	else if (str == "executable path") {
		jsonfile["button" + who_but][1] = "PCP_script_open"; 
	}
	else if (str == "command line")
	{
		jsonfile["button" + who_but][1] = "PCP_script";
	}
	else if (str == "keyboard execution")
	{
		jsonfile["button" + who_but][1] = "PCP_commande";
	}

	sendResquet(who_but);	
}

taille(true);
