function config_all()
{

	/** SCREEN SIZE **/

	button = document.getElementsByClassName('button_section');

	let taille = window.innerHeight*0.95;

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

		}
		else if ( Number.isInteger(LesButtons.length / i) )
		{
			OldProportion = NewProportion;

			NewProportion = Math.abs( Proportion - (i / (LesButtons.length/i))) ;


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
