function config_all()                                                                                      
{                                                                                                               
	valeur = 0;                                                                                             

	let tailleX = window.innerWidth  * 0.95 ;                                                               
	let tailleY = window.innerHeight  * 0.95;                                                               

	tableau = document.getElementsByClassName('tableau');                                                   
	key = document.getElementsByClassName('key');                                                           
	maj = document.getElementsByClassName('maj');                                                           

	tailleY /= tableau.length;                                                                              

	let keynbr = 0;                                                                                         
	let majnbr = 0;                                                                                         

	for (let i = 0; i < tableau.length; i++)                                                                
	{                                                                                                       
		let size = tableau[i].childElementCount;                                                        
		for (let j = 0; j < size; j++)                                                                  
		{                                                                                               
			key[keynbr].style.width = ( tailleX / size ) + "px";                                    
			key[keynbr].style.height = tailleY + "px";                                              
			keynbr++;                                                                               

			if (majnbr != maj.length)                                                               
			{                                                                                       
				maj[majnbr].style.display = "none";                                             
				majnbr++;                                                                       
			}                                                                                       
		}                                                                                               
	}                                                                                                       


}

config_all();
