package WebPCPhone;


import java.awt.Desktop;
import java.net.URI;

import flak.App;
import flak.Flak;
import flak.annotations.Route;



import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.nio.charset.StandardCharsets;

import java.nio.file.Files;
import java.nio.file.Paths;

/**
 * Minimal Hello world web application.
 */
public class Hello {

	public String open(String path) throws IOException
	{
		try
		{
			path ="/mnt/704E048C4E044D72/Programmation/ComPhone2/WebPCPhone/src/main/java/WebPCPhone/" + path;


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

	@Route("/") 
	public String index() throws IOException
	{
		//return open("index.html");
		return getClass().getResourceAsStream("/index.html");
	}


	@Route("/*chemin")
	public String ouvrir(String chemin)  throws IOException
	{
		System.out.println(chemin);

	    return open(chemin);
	}

	@Route("/ui/:name")
	public void ui(String name)
	{
		System.out.println(name);
	}

	public static void main(String[] args) throws Exception
	{
		App app = Flak.createHttpApp(8080);
		app.scan(new Hello());
		app.start();
		//Desktop.getDesktop().browse(new URI(app.getRootUrl()));
	}
}
