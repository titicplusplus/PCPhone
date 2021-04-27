
function taille()
{
	button = document.getElementsByClassName('button_section');

	let taille = window.innerHeight*0.95;

	button[0].style.height = taille.toString() + "px";


	LesButtons = document.getElementsByClassName('send');

	let taille2 = Math.floor(taille / Math.ceil(LesButtons.length/3) - 20);
	let taille3 = Math.floor( window.innerWidth / 3 - 30);

	for (let i = 0; i < LesButtons.length; i++)
	{
		LesButtons[i].style.height = taille2.toString() + "px";

		LesButtons[i].style.width = taille3.toString() + "px";
	}	
}

	


function sendResquet()
{
	console.log("Put a message here.");

	const Http = new XMLHttpRequest();
	const url='http://192.168.1.11:8080/ui/' + arguments[0].toString();
	Http.open("GET", url);
	Http.send();

	Http.onreadystatechange = (e) => {
	  console.log(Http.responseText)
	}

}

taille();