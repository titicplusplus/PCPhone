package WebPCPhone;

import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;

import java.util.ArrayList;

import java.io.ByteArrayOutputStream;
import java.nio.charset.StandardCharsets;


import java.nio.charset.StandardCharsets;

import java.nio.file.Files;
import java.nio.file.Paths;
import java.lang.Object;

import java.io.File;

import org.json.*;

import org.apache.commons.io.IOUtils;

public class conf_json {


	private JSONObject menu = new JSONObject(openJSONFile("/file/menu.json"));

	private ArrayList<JSONObject> menu_conf = new ArrayList<JSONObject>();

	public String openJSONFile(String chemin_file)  throws IOException
	{
		try
		{
			System.out.println(chemin_file);
			InputStream is = getClass().getResourceAsStream(chemin_file);
			String result = IOUtils.toString(is, StandardCharsets.UTF_8);
			return result;


		}
		catch (Exception e)
		{
			System.out.println("mais non");	
			e.printStackTrace();  
		}

		return "";
	}

	public conf_json() throws IOException
	{

		for (int i = 0; i < menu.getInt("nombre_menu"); i++)
		{
		
			try
			{
				menu_conf.add( new JSONObject(openJSONFile("/file/menu" + (i+1) + ".json")));
			}
			catch (Exception e)
			{
				System.out.println("mais non mais ui");
				e.printStackTrace();
				break;
			}
		}
	}

	public int getIntMenu(String valeur) {
		return menu.getInt(valeur);
	}

	public String getStringMenu(String valeur) {
		return menu.getString(valeur);
	}
	
	public int getIntNbrMenu() {
		return menu.getInt("nombre_menu");
	}

	public int text(String name)
	{
		String os = System.getProperty("os.name");
		ProcessBuilder processBuilder = new ProcessBuilder();

		if (os.equals("Linux"))
		{
			String command = "xdotool key " + name;
			System.out.println(command);
			processBuilder.command("bash","-c", command);
		}

        	try {

            		Process process = processBuilder.start();

            		int exitCode = process.waitFor();

	        } catch (IOException e) {
        	    e.printStackTrace();
       		 } catch (InterruptedException e) {
           		 e.printStackTrace();
		 }

		return 0;
	}

	public int commande(String commmande) {
		String[] str = commmande.split("_");
		int num = Integer.parseInt(str[0]);
		int posX = Integer.parseInt(str[1]);
		int posY = Integer.parseInt(str[2]);
		int LesBoutonsValue = 0;	

		JSONArray tab = new JSONArray();
		for (int i = 0; i < menu.getInt("nombre_menu"); i++)
		{
			tab  = menu.getJSONArray("slide" + i);	
			if ( (int) tab.get(0) == posX && (int) tab.get(1) == posY)
			{
				LesBoutonsValue = (int) tab.get(2);
				System.out.println(LesBoutonsValue + " valeur");
				break;
			}
		}


		String os = System.getProperty("os.name");
		
		System.out.println("Os: " + os);

		String start = "";
		String name = "button" + num;
		ProcessBuilder processBuilder = new ProcessBuilder();
		
		if (os.equals("Linux"))
		{
			String commandeBase = menu_conf.get(LesBoutonsValue).getJSONArray(name).get(1).toString();

			if (commandeBase.equals("PCP_open"))
			{
				start = "xdg-open";
			}
			else if (commandeBase.equals("PCP_Exe_File"))
			{
				start = "bash";
			}
			else if (commandeBase.equals("PCP_commande"))
			{
				start = "xdotool";
			}

			start +=  " " + menu_conf.get(LesBoutonsValue).getJSONArray(name).get(2).toString();
			System.out.println(start);

			processBuilder.command("bash", "-c", start );
		}

        	try {

            		Process process = processBuilder.start();

            		int exitCode = process.waitFor();

	        } catch (IOException e) {
        	    e.printStackTrace();
       		 } catch (InterruptedException e) {
           		 e.printStackTrace();
        	}

		return 0;
	}


	public String getStringSlide(int x, int y, boolean draw_value) throws IOException
	{
		JSONArray tab = new JSONArray(); 
		int LesBoutonsValue = 20000;

		System.out.println(x + " " + y);
		for (int i = 0; i < menu.getInt("nombre_menu"); i++)
		{
			tab  = menu.getJSONArray("slide" + i);	
			if ( (int) tab.get(0) == x && (int) tab.get(1) == y)
			{
				LesBoutonsValue = (int) tab.get(2);
				System.out.println(LesBoutonsValue + " valeur");
				break;
			}
		}

		if (LesBoutonsValue == 20000)
		{
			return "nochange";
		}

		String result = "";
		if (LesBoutonsValue < menu_conf.size())
		{
		

			if (menu_conf.get(LesBoutonsValue).getString("type").equals("button"))
			{
				if (draw_value)
				{
					result += "button" + "\n";
					result += x + "\n";
					result += y + "\n";
				}

				result += "<section class=\"button_section\" id=\"slide\">";

				for (int i = 0; i < menu_conf.get(LesBoutonsValue).getInt("number");  i++)
				{
					result += "<button type=\"button\" class=\"send\" onclick=\"sendResquet(" + i + ")\" style=\"background-image:url(" +
						menu_conf.get(LesBoutonsValue).getJSONArray("button" + i).get(3)  + "); background-color: transparent; background-repeat: no-repeat; background-size: contain; background-position: center\"; ></button> ";	
				}

				result += "</section>";
			
			
			}
			else if (menu_conf.get(LesBoutonsValue).getString("type").equals("keyboard"))
			{
				/*JSONObject keyboard = new JSONObject();
				try
				{
					keyboard = new JSONObject(openJSONFile("/file/keyboard/" + menu_conf.get(LesBoutonsValue).getString("version")));
				}
				catch (JSONException e)
				{
					e.printStackTrace();
				}

				if (draw_value)
				{
					result += "keyboard" + "\n";
					result += x + "\n";
					result += y + "\n";
				}

				result += "<section class=\"keyboard_section\" id=\"slide\"> <table> <tbody> ";
				
				for (int i = 0; i < keyboard.getInt("number"); i++)
				{
					result += "<tr class=\"tableau\">";

					int len = keyboard.getJSONArray("ligne" + i).length();
					for (int j = 0; j < len; j++) 
					{
						String chararcter = keyboard.getJSONArray("ligne" + i).get(j).toString();
						if (chararcter.contains("::"))
						{
							int depP = chararcter.indexOf("::", 1);
							result += "<td> <button class=\"key\"> <div class=\"normal\" id=\"" + chararcter.substring(0, depP) + "\"  onclick=\"key_press(this.id)\" >" +
							       	chararcter.substring(0, depP) + "</div> <div class=\"maj\" id=\"" + chararcter.substring(depP+2, chararcter.length()) +
							       	"\" onclick=\"key_press(this.id)\"> " + chararcter.substring(depP + 2, chararcter.length()) + "</div> </button> </td>";
							
						}
						else
						{
							result += "<td> <button class=\"key\" id=\"" + chararcter + "\" onclick=\"key_press(this.id)\">" + chararcter + "</button> </td>";
						}
					}
					result += "</tr>";
						
						
				}

				result += "</tbody></table></section>";

				return result;*/

				if (draw_value)
				{
					result += "keyboard" + "\n";
					result += x + "\n";
					result += y + "\n";
				}
				result += "<section id=\"key\">";

				result += "<div class=\"part\"> <input class=\"buR\" onkeydown=\"entertext(event)\" type=\"text\"> <button id=\"windows\" class=\"buR\" onclick=\"key_press(this.id)\">Windows</button> <button id=\"Alt_Tab\" class=\"buR\" onclick=\"key_press(this.id)\">Alt Tab</button> </div>"; 
				result += "<div id=\"touchepad\" class=\"part\"> </div> </section>";
				return result;
			}

		}
		else
		{
			System.out.println("error, valeur out of the range");
			result = "error";
		}

		return result;

	}
}
