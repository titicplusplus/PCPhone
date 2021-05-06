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
import java.util.List;
import java.util.Arrays;

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
	private conf_json json = new conf_json();
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
		BufferedReader br = new BufferedReader(new InputStreamReader(getClass().getResourceAsStream("/file/admin/admin_base.html"), "UTF-8"));
		
		String line;
		StringBuffer sb = new StringBuffer();

		int numberLine = 0;    

		while((line = br.readLine()) != null)
		{
			numberLine++;
			sb.append(line);      
			sb.append("\n");
   
		}
		return sb.toString();
	}

	@Route("/admin/:valeur")
	public String admin_valeur(String valeur)  throws IOException
	{
		BufferedReader br = new BufferedReader(new InputStreamReader(getClass().getResourceAsStream("/file/admin/admin_base.html"), "UTF-8"));
		
		String line;
		StringBuffer sb = new StringBuffer();

		int numberLine = 0;    

		while((line = br.readLine()) != null)
		{
			numberLine++;
			sb.append(line);      
			sb.append("\n");
   
		}
		return sb.toString();
	}

	@Route("/JSON_VERSION/:version")
	public String getJSONVersion(String version)
	{
		int versionReal = Integer.parseInt(version);
		if (versionReal	==  0)
		{
			return menu.toString();
		}
		else
		{
			String result = "";			
			
			for (int i = 0; i < LesBoutons.get(versionReal).size(); i++)
			{
				for (int j = 0; j < LesBoutons.get(versionReal).get(i).length(); j++)
				{
					result += LesBoutons.get(versionReal).get(i).get(j).toString() + "\n";
				}
			}

			return result;
		}
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
			if (line.equals("<!--Element -->"))
			{
				sb.append(json.getStringSlide(0,0, false));
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
		List<String> position = Arrays.asList(numero.split("_"));
		String result = json.getStringSlide(Integer.parseInt(position.get(0)),Integer.parseInt(position.get(1)), true);
		
		return result;
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
			if (line.equals("/* BUTTON *mais ui c sur/"))
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
		json.commande(name);
		return "200";
		
	}

	@Route("/text/:name")
	public String text(String name)
	{
		System.out.println(name);
		json.text(name);
		return "200";
	}


	public WebSite() throws Exception
	{
       	}




}
