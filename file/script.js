!function(A,e){"object"==typeof exports&&"object"==typeof module?module.exports=e():"function"==typeof define&&define.amd?define([],e):"object"==typeof exports?exports.NoSleep=e():A.NoSleep=e()}(this,(function(){return function(A){var e={};function B(g){if(e[g])return e[g].exports;var o=e[g]={i:g,l:!1,exports:{}};return A[g].call(o.exports,o,o.exports,B),o.l=!0,o.exports}return B.m=A,B.c=e,B.d=function(A,e,g){B.o(A,e)||Object.defineProperty(A,e,{enumerable:!0,get:g})},B.r=function(A){"undefined"!=typeof Symbol&&Symbol.toStringTag&&Object.defineProperty(A,Symbol.toStringTag,{value:"Module"}),Object.defineProperty(A,"__esModule",{value:!0})},B.t=function(A,e){if(1&e&&(A=B(A)),8&e)return A;if(4&e&&"object"==typeof A&&A&&A.__esModule)return A;var g=Object.create(null);if(B.r(g),Object.defineProperty(g,"default",{enumerable:!0,value:A}),2&e&&"string"!=typeof A)for(var o in A)B.d(g,o,function(e){return A[e]}.bind(null,o));return g},B.n=function(A){var e=A&&A.__esModule?function(){return A.default}:function(){return A};return B.d(e,"a",e),e},B.o=function(A,e){return Object.prototype.hasOwnProperty.call(A,e)},B.p="",B(B.s=0)}([function(A,e,B){"use strict";var g=function(){function A(A,e){for(var B=0;B<e.length;B++){var g=e[B];g.enumerable=g.enumerable||!1,g.configurable=!0,"value"in g&&(g.writable=!0),Object.defineProperty(A,g.key,g)}}return function(e,B,g){return B&&A(e.prototype,B),g&&A(e,g),e}}();var o=B(1),E=o.webm,n=o.mp4,C=function(){return"undefined"!=typeof navigator&&parseFloat((""+(/CPU.*OS ([0-9_]{3,4})[0-9_]{0,1}|(CPU like).*AppleWebKit.*Mobile/i.exec(navigator.userAgent)||[0,""])[1]).replace("undefined","3_2").replace("_",".").replace("_",""))<10&&!window.MSStream},Q=function(){return"wakeLock"in navigator},i=function(){function A(){var e=this;if(function(A,e){if(!(A instanceof e))throw new TypeError("Cannot call a class as a function")}(this,A),this.enabled=!1,Q()){this._wakeLock=null;var B=function(){null!==e._wakeLock&&"visible"===document.visibilityState&&e.enable()};document.addEventListener("visibilitychange",B),document.addEventListener("fullscreenchange",B)}else C()?this.noSleepTimer=null:(this.noSleepVideo=document.createElement("video"),this.noSleepVideo.setAttribute("title","No Sleep"),this.noSleepVideo.setAttribute("playsinline",""),this._addSourceToVideo(this.noSleepVideo,"webm",E),this._addSourceToVideo(this.noSleepVideo,"mp4",n),this.noSleepVideo.addEventListener("loadedmetadata",(function(){e.noSleepVideo.duration<=1?e.noSleepVideo.setAttribute("loop",""):e.noSleepVideo.addEventListener("timeupdate",(function(){e.noSleepVideo.currentTime>.5&&(e.noSleepVideo.currentTime=Math.random())}))})))}return g(A,[{key:"_addSourceToVideo",value:function(A,e,B){var g=document.createElement("source");g.src=B,g.type="video/"+e,A.appendChild(g)}},{key:"enable",value:function(){var A=this;return Q()?navigator.wakeLock.request("screen").then((function(e){A._wakeLock=e,A.enabled=!0,console.log("Wake Lock active."),A._wakeLock.addEventListener("release",(function(){console.log("Wake Lock released.")}))})).catch((function(e){throw A.enabled=!1,console.error(e.name+", "+e.message),e})):C()?(this.disable(),console.warn("\n        NoSleep enabled for older iOS devices. This can interrupt\n        active or long-running network requests from completing successfully.\n        See https://github.com/richtr/NoSleep.js/issues/15 for more details.\n      "),this.noSleepTimer=window.setInterval((function(){document.hidden||(window.location.href=window.location.href.split("#")[0],window.setTimeout(window.stop,0))}),15e3),this.enabled=!0,Promise.resolve()):this.noSleepVideo.play().then((function(e){return A.enabled=!0,e})).catch((function(e){throw A.enabled=!1,e}))}},{key:"disable",value:function(){Q()?(this._wakeLock&&this._wakeLock.release(),this._wakeLock=null):C()?this.noSleepTimer&&(console.warn("\n          NoSleep now disabled for older iOS devices.\n        "),window.clearInterval(this.noSleepTimer),this.noSleepTimer=null):this.noSleepVideo.pause(),this.enabled=!1}},{key:"isEnabled",get:function(){return this.enabled}}]),A}();A.exports=i},function(A,e,B){"use strict";A.exports={webm:"data:video/webm;base64,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",mp4:"data:video/mp4;base64,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"}}])}));





var noSleep = new NoSleep();
noSleep.enable();

var positionX = -1;
var positionY = -1;

PositionSlideX = 0;
PositionSlideY = 0;
type = "button";

cha = "";

class TouchPad {
	constructor() {
		this.PosFX = [];
		this.PosFY = [];

		this.NewPosFX = [];
		this.NewPosFY = [];
		this.click = 0;
	}

	start(event) {
		let touches = event.changedTouches;

		this.PosFX = [];
		this.PosFY = [];

		for (var i = 0; i < touches.length; i++)
		{
			this.PosFX.push(touches[i].clientX);
			this.PosFY.push(touches[i].clientY);
		}
			
	}

	move(event) {
		let touches = event.changedTouches;

		this.click = -1;

		var moveX = 0;
		var moveY = 0;
		var url = "";

		for (var i = 0;i  < touches.length; i++)
		{
			if (i < this.PosFX.length)
			{
				moveX = touches[i].clientX - this.PosFX[i];
				moveY = touches[i].clientY - this.PosFY[i];

				url += moveX + "_" + moveY + "_";

				this.PosFX[i] = touches[i].clientX;
				this.PosFY[i] = touches[i].clientY;
			}
		}

		this.url += "/";
		sendResquetMouse(url);
	}

	end(event) {
		if (this.click == 0)
		{
			sendResquetClick(event.touches.length);	
		}
		else
		{
			this.click = 0;
		}
	}




}
	function sendResquetMouse()
	{
		var url = "/mousemove/";
		url += arguments[0];
		

		const Http = new XMLHttpRequest();
		Http.open("GET", url);
		Http.send();

		Http.onreadystatechange = (e) => {
		  console.log(Http.responseText)
		}

	}

	function sendResquetClick()
	{
		
		let url = "/mouseclick/";

		const Http = new XMLHttpRequest();
		Http.open("GET", url);
		Http.send();

		Http.onreadystatechange = (e) => {
		  console.log(Http.responseText)
		}
	}



var phone = new TouchPad();



window.onresize = function()
{
	resize();
}

/*
window.addEventListener("keydown", function(event) {
	if (type == "keyboard")
		entertext(event);
} ,true);
*/	


function entertext(key_name)
{
	console.log(key_name);
	/**let text = document.getElementsByClassName('buR');

	finT = new Date();

	if (finT.getTime() - debT.getTime() > 200)
	{
		let cha2 = "";
		if (cha.length > text[0].value.length)
		{
			cha2 = "BackSpace";
			cha = text[0].value;	
		}
		else
		{
			cha = text[0].value;
			console.log(cha);
			cha2 = cha[cha.length - 1];
			if (cha2 == " ")
				cha2 = "KP_Space";
		}
		console.log(cha2 + " valeursend");

		const Http = new XMLHttpRequest();
		const url='/text/' + cha2;
		Http.open("GET", url);
		Http.send();

		Http.onreadystatechange = (e) => {
		  console.log(Http.responseText)
		}
		debT = new Date();
	}
	**/

	
	const Http = new XMLHttpRequest();
	const url='/text/' + key_name;
	Http.open("GET", url);
	Http.send();

	Http.onreadystatechange = (e) => {
	  console.log(Http.responseText)
	}
}

function taille_touchpad()
{
	size_all();

	/** Reste **/

	touchpad = document.getElementById("touchpad");
	touchpad.style.width = window.innerWidth.toString()*0.95 + "px";
	touchpad.style.height = window.innerHeight.toString()*0.95 + "px";
	
	th = document.getElementById("touchpad");

	th.addEventListener("touchstart", phone.start);
	th.addEventListener("touchmove", phone.move);
	th.addEventListener("touchend", phone.end);
}

function touchapdMove(event) {
	console.log(event.touches[0].clientX);
	console.log(event.touches[0].clientY);
}


function color()
{
	let maj_button = arguments[0];
	
	if (maj_button.style.backgroundColor == "black" || maj_button.style.backgroundColor == "" )
		maj_button.style.backgroundColor = "red";
	else
		maj_button.style.backgroundColor = "black";
}

function key_press()
{
	let key = arguments[0];
	console.log(key + " " + typeof(key));

	if (key == "MAJ")
	{
		console.log("ui");
		let maj = document.getElementsByClassName("maj");
		let maj2 = document.getElementsByClassName("normal");
		let swap;
		
		let maj_button = document.getElementById("MAJ");

		if (maj2[0].style.display == "none")
		{
			swap = maj;
			maj = maj2;
			maj2 = swap;

			maj_button.style.backgroundColor = "black";
		}
		else
		{
			maj_button.style.backgroundColor = "red";
		}
		

		for (let i = 0; i < maj.length; i++)
		{
			maj2[i].style.display = "none";
			maj[i].style.display = "block";
		}
	}
	else
	{
		entertext(key);
	}
}

function open_f()
{
	link = document.getElementById("style_c");
	if ( link != null )
	{
        	link.href = '/ext/style.css?x=' + PositionSlideX + '&y=' + PositionSlideY; 
	}
	else
	{
		var head = document.getElementsByTagName('HEAD')[0]; 
	  
		var link2 = document.createElement('link');
	  
		link2.rel = 'stylesheet'; 
		link2.type = 'text/css';
		link2.id = 'style_c';
		link2.href = '/ext/style.css?x=' + PositionSlideX + '&y=' + PositionSlideY; 
	  
		head.appendChild(link2);


	}

	const url='/ext/script.js?x=' + PositionSlideX + "&y=" + PositionSlideY;
		
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

	config_all= new Function( strR.substring(strR.indexOf('{')+1,strR.lastIndexOf('}')) ); 
}


function size_all()
{
	/** FOND **/
	fond = document.getElementsByClassName('fond');
	fond[0].style.height = window.innerHeight.toString() + "px";

	fond[0].style.width = window.innerWidth.toString() + "px";

	/** FULLSCREEN **/

	fullscreen = document.getElementById("full");
	fullscreen.style.top = (window.innerHeight - 50).toString() + "px";
	fullscreen.style.left = (window.innerWidth - 50).toString() + "px";

	/** Arrows **/
	const url='/arround?x=' + PositionSlideX + "&y=" + PositionSlideY;
	
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



	arrows = document.getElementsByClassName('arrow');

	tailleUI = (window.innerHeight*0.1);
	tailleUI2 = tailleUI  * 200 / 200; 

	for (var i = 0; i < arrows.length; i++) {
		if (strR[i] == "0")
		{
			arrows[i].style.display = "none";
			continue;
		}

		arrows[i].style.display = "block";

		arrows[i].style.transform       = 'rotate('+(i*90)+'deg)';
		arrows[i].style.width = tailleUI2 + "px";
		arrows[i].style.height =  tailleUI + "px";
	}

 	arrows[0].style.top = ( window.innerHeight/2 - tailleUI/2 ) +  "px";
 	arrows[1].style.left = ( window.innerWidth/2 - tailleUI2/2 ) +  "px";
 	arrows[2].style.top = arrows[0].style.top; 
 	arrows[2].style.left = (window.innerWidth - tailleUI2) + "px"; 
	console.log( window.innerWidth + " " + tailleUI );
 	arrows[3].style.left = arrows[1].style.left; 
 	arrows[3].style.top = (window.innerHeight - tailleUI ) + "px"; 
}

function taille_button()
{
	size_all();


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

function toggleFullscreen(elem) {
	elem = elem || document.documentElement;

	if (!document.fullscreenElement && !document.mozFullScreenElement &&
	!document.webkitFullscreenElement && !document.msFullscreenElement)
	{
		if (elem.requestFullscreen) {
	 	 	elem.requestFullscreen();
		} else if (elem.msRequestFullscreen) {
		 	elem.msRequestFullscreen();
		} else if (elem.mozRequestFullScreen) {
		  	elem.mozRequestFullScreen();
		} else if (elem.webkitRequestFullscreen) {
		  	elem.webkitRequestFullscreen(Element.ALLOW_KEYBOARD_INPUT);
	}
	}
	else {
		if (document.exitFullscreen) {
		  document.exitFullscreen();
		} else if (document.msExitFullscreen) {
		  document.msExitFullscreen();
		} else if (document.mozCancelFullScreen) {
		  document.mozCancelFullScreen();
		} else if (document.webkitExitFullscreen) {
		  document.webkitExitFullscreen();
	}
	}

	resize()
}


function start(event)
{
	if (type == "touchpad")
		return;
	if (positionX == -1)
	{
		positionX = event.pageX;
		positionY = event.pageY;
	}
}



function fin(event)
{
	if (type == "touchpad")
		return;
	
	finch(event.pageX, event.pageY)
}

function startM(event)
{
	if (positionX == -1 && type != "touchpad")
	{
		positionX = event.touches[0].clientX;
		positionY = event.touches[0].clientY;
	}
}

function finM(event)
{
	if (type == "touchpad")
		return;
	
	let goX = event.changedTouches[0].clientX;
	let goY = event.changedTouches[0].clientY;

	finch(goX,goY);
}



function finch()
{
	let x = arguments[0];
	let y = arguments[1];

	if ( Math.abs(x - positionX) > 100 || Math.abs(y - positionY) > 100 )
	{
		if ( Math.abs(x - positionX) > Math.abs(y - positionY) )
		{
			if (x - positionX > 0)
			{
				sendResquetJSON( PositionSlideX-1, PositionSlideY);
			}
			else
			{
				sendResquetJSON( PositionSlideX+1, PositionSlideY);

			}
		}
		else
		{
			if (y - positionY > 0)
			{
				sendResquetJSON( PositionSlideX, PositionSlideY+1);
			}
			else
			{
				sendResquetJSON( PositionSlideX, PositionSlideY-1);
			}
		}
	}
	
	positionX = -1;
}


function sendResquetMenu()
{
	let direction = arguments[0];

	const Http = new XMLHttpRequest();
	const url='/menu/' + arguments[0].toString() + "_" + LesButtons[0].textContent + "/";
	document.location.href = url;
}


function sendResquet()
{
	const Http = new XMLHttpRequest();
	const url='/exe?x=' + PositionSlideX + "&y=" + PositionSlideY + "&position=" + arguments[0].toString();
	Http.open("GET", url);
	Http.send();

	Http.onreadystatechange = (e) => {
	  console.log(Http.responseText)
	}

}

function sendResquetJSON()
{
	NewPosX = arguments[0];
	NewPosY = arguments[1];

	const url='/json?x=' + NewPosX + "&y=" + NewPosY;
	
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

	if (strR != "nochange") {

		PositionSlideX = NewPosX;
		PositionSlideY = NewPosY;
	
		let id = document.getElementById("slide");
		let id2 = document.getElementById("full");

		let all = document.getElementById("all");
		all.removeChild(id);

		let array = strR.split(/\r?\n/);

		type = array[0];
		x = array[1];
		y = array[2];

		template = document.createElement("template");
		template.innerHTML = array[3];
		//all.appendChild(template.content.firstChild);
		all.insertBefore(template.content.firstChild, id2);
		resize();

	}
}

function config_all() { console.log("nothing");}

function resize()
{
	size_all();
	open_f();
	config_all();
}


open_f();
size_all();
config_all();

