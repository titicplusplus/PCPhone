function Apply()
{

}

function sendResquetJSON()
{
	
	const url='/JSON_VERSION/' + arguments[0].toString(); 
	var request = new XMLHttpRequest();
	request.open('GET', url, false);

	request.send();

	var strR = "mais ui";
	
	if (request.status === 200) {
	  	strR = request.response;
	}
	else
	{
		console.log("merde");
	}
	console.log(strR);
	return strR;

}

function configuration()
{
	if (window.location.pathname == "/admin")
	{
		fond = document.getElementById('fond');
		fond.style.height = window.innerHeight.toString() + "px";

		fond.style.width = window.innerWidth.toString() + "px";
		console.log("base config");
		let obJ = JSON.parse(sendResquetJSON(0));

		let x_moins = obJ["slide1"][0], x_plus = obJ["slide1"][0], y_moins = obJ["slide1"][1], y_plus = obJ["slide1"][1];
		for (let i = 0; i < obJ.nombre_menu; i++)
		{
			console.log("i");
			if (x_moins > obJ["slide" + i.toString()][0])
			{
				x_moins = obJ["slide" + i.toString()][0];
			} 
			if (x_plus < obJ["slide" + i.toString()][0]) {
				console.log(i);
				x_plus = obJ["slide" + i.toString()][0];
			}

			if (y_moins > obJ["slide" + i.toString()][1])
			{
				y_moins = obJ["slide" + i.toString()][1];
			} 
			if (y_plus < obJ["slide" + i.toString()][1]) {
				y_plus = obJ["slide" + i.toString()][1];
			}
		}
		let tab2d = new Array(Math.abs(x_plus - x_moins + 3));
		console.log("taille x:" + Math.abs(x_plus - x_moins + 3) + "avec" + x_plus + " " + x_moins + " " + y_plus + " " + y_moins);
		for (let i = 0; i < tab2d.length; i++)
		{
			tab2d[i] = new Array(Math.abs(y_plus - y_moins + 3));
		}

		for (let i = 0; i < obJ.nombre_menu; i++)
		{
			let PosX = Math.abs(obJ["slide" + i.toString()][0] - x_moins + 1);
			let PosY = Math.abs(obJ["slide" + i.toString()][1] - y_moins +  1);
			tab2d[PosX][PosY] =  obJ["slide" + i.toString()][3].toString();

			if (tab2d[PosX+1][PosY] == undefined)
				tab2d[PosX+1][PosY] = "New";
			if (tab2d[PosX-1][PosY] == undefined)
				tab2d[PosX-1][PosY] = "New";
			if (tab2d[PosX][PosY-1] == undefined)
				tab2d[PosX][PosY-1] = "New";
			if (tab2d[PosX][PosY+1] == undefined)
				tab2d[PosX][PosY+1] = "New";
		}
		tableau = document.getElementById("table_base");

		tailleX = tab2d.length;
		tailleY = tab2d[0].length;

		for (let i = 0; i < tab2d[0].length; i++)
		{
			 let row = document.createElement("tr");

   			 for (let j = 0; j < tab2d.length; j++) {
				console.log("x:"+ j + " y:" + i + " " + tab2d[j][i]);
				let cell = document.createElement("td");
				let button = document.createElement("button");
				if (tab2d[j][i] != undefined)
				{
					let cellText= document.createTextNode(tab2d[j][i]);
					button.onclick = function(){go(j,i)};
					button.appendChild(cellText);					
					button.style.width = (window.innerWidth / tab2d.length * 0.95) + "px";
					button.style.height = (window.innerHeight / tab2d[0].length * 0.95) + "px";
					button.className = "button_send";
					cell.appendChild(button);
				}
      				row.appendChild(cell);
   			 }

			tableau.appendChild(row);
		}
		
	}
}

function go()
{
	console.log(arguments[0] + " " + arguments[1]);
}


function taille()
{
	fond = document.getElementById('fond');
	fond.style.height = window.innerHeight.toString() + "px";

	fond.style.width = window.innerWidth.toString() + "px";

	all_button = document.getElementsByClassName('button_send');	
	
	for (var i = 0; i < all_button.length; i++)
	{
		all_button[i].style.width = (window.innerWidth / tailleX * 0.95) + "px";
		all_button[i].style.height = (window.innerHeight / tailleY * 0.95) + "px";
	}

		
}
window.onresize = function(){ taille();}

configuration();
