function taille()
{
	/** FOND **/
	fond = document.getElementsByClassName('fond');
	let taille = window.innerHeight * 0.2;


	fond[0].style.height = (window.innerHeight * 0.21).toString() + "px";

	fond[0].style.width = window.innerWidth.toString() + "px";

	/** SCREEN SIZE **/

	button = document.getElementsByClassName('button_section');


	button[0].style.height = taille.toString() + "px";
	
	
	/** LES BUTONS **/


	LesButtons = document.getElementsByClassName('send');

	var Proportion = taille/window.innerWidth;
	var NewProportion = 20.0;
	var OldProportion = 1000.0;

	var supposition;
	

	for (var i = 1; i < LesButtons.length; i++)
	{
		if (i == 1)
		{
			supposition = 1;
			NewProportion = Math.abs( Proportion - (i / (LesButtons.length/i))) ;
			console.log(OldProportion + " " + NewProportion + " " + Proportion + " " + i);

		}
		else if ( Number.isInteger(LesButtons.length / i) )
		{
			OldProportion = NewProportion;

			NewProportion = Math.abs( Proportion - (i / (LesButtons.length/i))) ;
			console.log(OldProportion + " " + NewProportion + " " + Proportion + " " + i);


			if (OldProportion < NewProportion)
			{
				break;
			}

			supposition = i;

		}
	}


	let tailleXY = Math.floor(taille / supposition - 10);
	
	if (tailleXY*(LesButtons.length / supposition) > window.innerWidth*0.98)
	{
		tailleXY = Math.floor(window.innerWidth / (LesButtons.length / supposition) - 20);
	}


	let tailleEsp = (Math.floor( window.innerWidth / Math.ceil(LesButtons.length / supposition) - 10) - tailleXY) / 2;

	for (let a = 0; a < LesButtons.length; a++)
	{
		LesButtons[a].style.height = tailleXY.toString() + "px";

		LesButtons[a].style.width = tailleXY.toString() + "px";

		LesButtons[a].style.marginLeft = tailleEsp.toString() + "px";
		LesButtons[a].style.marginRight = tailleEsp.toString() + "px";
	}
}

function sendResquetS()
{
	if (arguments[0].toString() == 0)
	{
  		document.getElementById("p1").innerHTML = " element's path ";
  		let elementMOD  = document.getElementById("modification");
  		elementMOD.style.display = "flex";
  		elementMOD.style.justifyContent = "center";

  		let elementAPP  = document.getElementById("Apply_button");
  		elementAPP.style.display = "flex";
  		elementAPP.style.justifyContent = "center";

	}
	else if (arguments[0].toString() == 1)
	{
  		document.getElementById("p1").innerHTML = " executable's path ";
  		let elementMOD  = document.getElementById("modification");
  		elementMOD.style.display = "flex";
  		elementMOD.style.justifyContent = "center";

  		let elementAPP  = document.getElementById("Apply_button");
  		elementAPP.style.display = "flex";
  		elementAPP.style.justifyContent = "center";

	}
	else if (arguments[0].toString() == 3)
	{
  		document.getElementById("p1").innerHTML = " command line ";
  		let elementMOD  = document.getElementById("modification");
  		elementMOD.style.display = "flex";
  		elementMOD.style.justifyContent = "center";

  		let elementAPP  = document.getElementById("Apply_button");
  		elementAPP.style.display = "flex";
  		elementAPP.style.justifyContent = "center";

	}
}

function Apply()
{

}


taille();