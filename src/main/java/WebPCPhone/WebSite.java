package WebPCPhone;

/** WebSite.java **/

import java.awt.Desktop;
import java.net.URI;

import flak.App;
import flak.Flak;
import flak.Request;
import flak.annotations.Route;

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

public class WebSite {
	

	private ArrayList<ArrayList<JSONArray>> LesBoutons;
	private ProcessBuilder processBuilder = new ProcessBuilder();

	private JSONObject menu = new JSONObject(openJSONFile("/file/menu.json"));


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




	@Route("/admin")
	public String admin()  throws IOException
	{
		BufferedReader br = new BufferedReader(new InputStreamReader(getClass().getResourceAsStream("/file/admin/admin.html"), "UTF-8"));
		
		String line;
		StringBuffer sb = new StringBuffer();

		int numberLine = 0;    

		while((line = br.readLine()) != null)
		{
			numberLine++;
			if (line.length() == 15 && numberLine == 20)
			{
				for (int i = 0; i < LesBoutons.size(); i++)
				{
					sb.append("<button type=\"button\" class=\"send\" onclick=\"sendResquet(" + i + ")\">" + LesBoutons.get(i).get(0) + "</button>\n");	
				}
			}
			else
			{
				sb.append(line);      
				sb.append("\n");
			}
   
		}
		return sb.toString();
	}

	@Route("/")
	public String index()  throws IOException
	{
		BufferedReader br = new BufferedReader(new InputStreamReader(getClass().getResourceAsStream("/file/index.html"), "UTF-8"));

		String line;
		StringBuffer sb = new StringBuffer();

		int numberLine = 0;    

		while((line = br.readLine()) != null)
		{
			numberLine++;
			if (line.length() == 15 && numberLine == 20)
			{

				sb.append("<button type=\"button\" class=\"send\" onclick=\"sendResquet(0)\" >" + LesBoutons.get(0).get(0).get(0) + "</button>\n");
				for (int i = 1; i < LesBoutons.get(0).size(); i++)
				{
					sb.append("<button type=\"button\" class=\"send\" onclick=\"sendResquet(" + i + ")\" ></button>\n");
					// 					sb.append("<button type=\"button\" class=\"send\" onclick=\"sendResquet(" + i + ")\" style=\"background: contain url(\"" + LesBoutons.get(i).get(3) + "\" ); \" >" + LesBoutons.get(i).get(0) + "</button>\n");

				}
			}
			else if (line.equals("<!-- Style -->"))
			{
				sb.append("<link rel=\"stylesheet\" href=\"/file/style.css\" > \n");						
			}
			else
			{
				sb.append(line);
				sb.append("\n");
			}
		}
		return sb.toString();
	}

	@Route("/JSON/:numero")
	public String JSONRenvoie(String numero) throws IOException
	{
		int number = Character.getNumericValue( numero.charAt(0) );
		numero = numero.substring(2, numero.length());
		int LesBoutonsValue = 0;	

		for (int i = 0;i < LesBoutons.size();i++)
		{
			if (LesBoutons.get(i).get(0).get(0).toString().equals(numero))
			{
				LesBoutonsValue = i;

			}

		}
		System.out.println(LesBoutons.size());

		JSONArray tab = new JSONArray();
		for (int i = 0; i < LesBoutons.size();i++)
		{
			tab  = menu.getJSONArray("slide" + (i+1));	
			if ( (int) tab.get(2) == LesBoutonsValue)
				break;
		}

		int x = (int) tab.get(0);
		int y = (int) tab.get(1);
		System.out.println("x et y " + x + " " + y);
		if (number < 3)
			x += number*2-3;
		else
			y += number*2-7;

		System.out.println("x et y " + x + " " + y);
		for (int i = 0; i < LesBoutons.size();i++)
		{
			tab  = menu.getJSONArray("slide" + (i+1));	
			if ( (int) tab.get(0) == x && (int) tab.get(1) == y)
			{
				LesBoutonsValue = (int) tab.get(2);
				System.out.println(LesBoutonsValue + " valeur");
				break;
			}
		}

		String result = "";
		result += LesBoutons.get(LesBoutonsValue).get(0).get(0) + "\n";

		for (int i = 0;i < LesBoutons.get(LesBoutonsValue).size();i++)
		{
			result += LesBoutons.get(LesBoutonsValue).get(i).get(3) + "\n";
		}
		System.out.println(result);
		return result;
	}
		
	@Route("/menu/:menu")
	public String index_meun(String menu)  throws IOException
	{

		int number = Character.getNumericValue( menu.charAt(0) );
		menu = menu.substring(2, menu.length());
		System.out.println(number + " " + menu);
		BufferedReader br = new BufferedReader(new InputStreamReader(getClass().getResourceAsStream("/file/index.html"), "UTF-8"));

		String line;
		StringBuffer sb = new StringBuffer();

		int numberLine = 0;    
		int LesBoutonsValue = 0;

		for (int i = 0;i < LesBoutons.size();i++)
		{
			if (LesBoutons.get(i).get(0).get(0).toString().equals(menu))
			{
				LesBoutonsValue = i;

				if (number == 1 && i+1 != LesBoutons.size())
					LesBoutonsValue++;

				if (number == 2 && i-1 != -1)
					LesBoutonsValue--;
			}

		}

		while((line = br.readLine()) != null)
		{
			numberLine++;
			if (line.length() == 15 && numberLine == 20)
			{
				
				sb.append("<button type=\"button\" class=\"send\" onclick=\"sendResquet(0)\" >" + LesBoutons.get(LesBoutonsValue).get(0).get(0) + "</button>\n");
				for (int i = 1; i < LesBoutons.get(LesBoutonsValue).size(); i++)
				{
					sb.append("<button type=\"button\" class=\"send\" onclick=\"sendResquet(" + i + ")\" ></button>\n");
					// 					sb.append("<button type=\"button\" class=\"send\" onclick=\"sendResquet(" + i + ")\" style=\"background: contain url(\"" + LesBoutons.get(i).get(3) + "\" ); \" >" + LesBoutons.get(i).get(0) + "</button>\n");

				}
			}
			else if (line.equals("<!-- Style -->"))
			{
				sb.append("<link rel=\"stylesheet\" href=\"/menu/style.css/" + LesBoutonsValue  + "\" > \n");						
			}
			else
			{
				sb.append(line);      
				sb.append("\n");
			}
   
		}
		return sb.toString();
	}

	@Route("/menu/style.css/:number")
	public String styleMenu(String number) throws IOException
	{

		int number_valeur = Integer. parseInt(number);
		BufferedReader br = new BufferedReader(new InputStreamReader(getClass().getResourceAsStream("/file/style.css"), "UTF-8"));

		String line;
		StringBuffer sb = new StringBuffer();

		int numberLine = 0;    

		while((line = br.readLine()) != null)
		{
			numberLine++;
			if (line.equals("/* BUTTON */"))
			{
				for (int i = 0; i < LesBoutons.get(0).size(); i++)
				{
					if (LesBoutons.get(number_valeur ).get(i).get(3).toString().equals("") == false)
					{
						sb.append(".send:nth-of-type("+ (i+1) +") { background: no-repeat url(\"" + LesBoutons.get(number_valeur).get(i).get(3) + "\"); background-size: contain; } \n");
					}
				}
			}
			else
			{
				sb.append(line);      
				sb.append("\n");
			}
   
		}
		return sb.toString();
	}


	@Route("/file/style.css")
	public String style()  throws IOException
	{
		BufferedReader br = new BufferedReader(new InputStreamReader(getClass().getResourceAsStream("/file/style.css"), "UTF-8"));

		String line;
		StringBuffer sb = new StringBuffer();

		int numberLine = 0;    

		while((line = br.readLine()) != null)
		{
			numberLine++;
			if (line.equals("/* BUTTON */"))
			{
				for (int i = 0; i < LesBoutons.get(0).size(); i++)
				{
					if (LesBoutons.get(0).get(i).get(3).toString().equals("") == false)
					{
						sb.append(".send:nth-of-type("+ (i+1) +") { background: no-repeat url(\"" + LesBoutons.get(0).get(i).get(3) + "\"); background-size: contain; background-position: center;} \n");
					}
				}
			}
			else
			{
				sb.append(line);      
				sb.append("\n");
			}
   
		}
		return sb.toString();
	}

	@Route("/file/*chemin")
	public InputStream fichier(String chemin)
	{
		return getClass().getResourceAsStream("/file/" + chemin);
	}

	@Route("/*chemin")
	public InputStream icone(String chemin)
	{
		return getClass().getResourceAsStream("/file/" + chemin);
	}

	@Route("/commande/:name")
	public String ui(String name)
	{
		
		int number = Character.getNumericValue( name.charAt(0) );
		name = name.substring(2, name.length());
		
		int LesBoutonsValue = 0;
		
		for (int i = 0;i < LesBoutons.size();i++)
		{
			if (LesBoutons.get(i).get(0).get(0).toString().equals(name))
			{
				LesBoutonsValue = i;

				if (number == 1 && i+1 != LesBoutons.size())
					LesBoutonsValue++;

				if (number == 2 && i-1 != -1)
					LesBoutonsValue--;
			}
		}
		



		if (name.equals("1000"))
		{
			System.out.println("mais ui");
			return "200";
		}

		String os = System.getProperty("os.name");
		
		System.out.println("Os: " + os);

		String start = "";

		if (os.equals("Linux"))
		{
			String commandeBase = LesBoutons.get(LesBoutonsValue).get( number ).get(1).toString();

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

			start +=  " " + LesBoutons.get(LesBoutonsValue ).get(number).get(2).toString();
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


		return "status: 200";
	}

	public WebSite(ArrayList<ArrayList<JSONArray>> LesBoutonsJSON) throws Exception
	{
		LesBoutons = new ArrayList<ArrayList<JSONArray>>(LesBoutonsJSON);
       	}




}
