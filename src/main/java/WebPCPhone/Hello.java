package WebPCPhone;

/** Hello.java **/

import java.awt.Desktop;
import java.net.URI;

import flak.App;
import flak.Flak;
import flak.Request;
import flak.annotations.Route;

import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;

import java.io.BufferedReader;

import java.util.ArrayList;

import java.io.ByteArrayOutputStream;
import java.nio.charset.StandardCharsets;


import java.nio.charset.StandardCharsets;

import java.nio.file.Files;
import java.nio.file.Paths;
import java.lang.Object;

import org.json.*;

import org.apache.commons.io.IOUtils;



public class Hello {

	private ArrayList<JSONObject > objson = new ArrayList<JSONObject>();
	private ArrayList<ArrayList<JSONArray> > LesBoutons = new ArrayList<ArrayList<JSONArray >>();

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

	public ArrayList<ArrayList<JSONArray>> JSON()
	{
		return LesBoutons;
	}

	public String InputStreamToString(InputStream is)  throws IOException
	{
		String result = IOUtils.toString(is, StandardCharsets.UTF_8);
		return result;
	}

	public String open(String path) throws IOException
	{
		try
		{
			InputStream is = new FileInputStream(path);
			BufferedReader buf = new BufferedReader(new InputStreamReader(is));
			        
			String line = buf.readLine();
			StringBuilder sb = new StringBuilder();
			        
			while(line != null){
			   sb.append(line).append("\n");
			   line = buf.readLine();
			}
			        
			String fileAsString = sb.toString();
			return fileAsString;

		}
		catch (Exception e)
		{
			e.printStackTrace();  
		}


		System.out.println("error");

		return "error";
	}

	public Hello() throws IOException
	{

		JSONObject menu = new JSONObject(openJSONFile("/file/menu.json"));
		
		for (int i = 0; i < menu.getInt("nombre_menu"); i++)
		{
		
			try
			{
				objson.add( new JSONObject(openJSONFile("/file/menu" + (i+1) + ".json")));
			}
			catch (Exception e)
			{
				System.out.println("mais non mais ui");
				e.printStackTrace();
				break;
			}
		}

		int nmbr = objson.get(0).getInt("number");
		
		for (int b = 0;b < objson.size(); b++)
		{
			ArrayList<JSONArray> TamList = new ArrayList<JSONArray>();
			for (int a = 0;a <nmbr;a++)
			{
				TamList.add( objson.get(b).getJSONArray("button" + a) );
			}

			LesBoutons.add(TamList);
		}
	}

	public static void main(String[] args) throws Exception
	{
		Hello ui = new Hello();
		//Interface utilisateur = new Interface(ui.LesBoutons);
		//utilisateur.start();

		App app = Flak.createHttpApp(8080);

		app.scan(new WebSite(ui.JSON()));
		app.start();
	}
}
