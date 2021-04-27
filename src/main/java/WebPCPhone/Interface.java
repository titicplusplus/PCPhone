package WebPCPhone;

/** Interface.java **/

import java.net.*;
import java.io.*;

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;


import java.util.Arrays;
import java.util.ArrayList;


import java.awt.Desktop;
import java.io.File;

import java.util.Scanner;

import org.json.*;

class Interface extends Thread  implements ActionListener {

	/**private ArrayList<JButton> LesBoutonsExe = new ArrayList<JButton>();
	private ArrayList<JButton> LesBoutonsSuppr = new ArrayList<JButton>();
	private JButton buttonAdd;
	private JLabel label;
	private JTextField labelText;
	private ArrayList<JTextField> LesTextes = new ArrayList<JTextField>();
	private ArrayList<JSONArray> LesBoutons = new ArrayList<JSONArray>();**/
	private ArrayList<JSONArray> LesBoutons = new ArrayList<JSONArray>();
	private ArrayList<JButton> TypeButton = new ArrayList<JButton>();
	private ArrayList<JButton> buttonAdd = new ArrayList<JButton>();
	private JTextField Name;
	private JButton Icone;


	private JFrame f;

	public Interface(ArrayList<JSONArray> LesBoutonsJSON) throws Exception
	{
		LesBoutons = new ArrayList<>(LesBoutonsJSON);
	}



	@Override
	public void run()
    {
    	int nbrLigne = 0;

	    f = new JFrame("PCPhone");
	    f.setSize(800,600);
	    f.setExtendedState(JFrame.MAXIMIZED_BOTH);

		JPanel buttonPanel = new JPanel();
		

		Dimension screenSize = Toolkit.getDefaultToolkit().getScreenSize();

		Dimension dim = new Dimension();

		if (screenSize.getHeight() * 0.15 * LesBoutons.size() < screenSize.getWidth())
		{
			dim.height = (int) (screenSize.getHeight() * 0.15);
			dim.width = dim.height;
		}
		else
		{
			dim.height = (int) (screenSize.getWidth() / LesBoutons.size() * 0.95);
			dim.width = dim.height;
		}


	    for (int i = 0;i < LesBoutons.size() ; i++) {
	    	buttonAdd.add(new JButton(LesBoutons.get(i).get(0).toString()));
	    	buttonAdd.get(i).setFont(new Font("Serif", Font.BOLD, 30));
			buttonAdd.get(i).addActionListener(this);
			buttonAdd.get(i).setAlignmentY(Component.TOP_ALIGNMENT);
	    	buttonAdd.get(i).setPreferredSize(dim);
	    	buttonPanel.add(buttonAdd.get(i));
	    }

	    buttonPanel.setFont(new Font("Serif", Font.BOLD, 30));
	    buttonPanel.setBorder(BorderFactory.createTitledBorder("The Buttons"));

        JPanel Classic = new JPanel();

 
        // Put constraints on different buttons

        ArrayList<String> AllTypeButton = new ArrayList<String>() {{ add("Open a File"); add("Open a Folder"); add("Open a software"); add("executable path"); add("keyboard/mouse execution"); }};


	 	JLabel name = new JLabel(" Button's Name:   ");
	 	name.setFont(new Font("Serif", Font.BOLD, 30));
	 	name.setAlignmentX(Component.LEFT_ALIGNMENT);


        Classic.add( name);



	 	Name = new JTextField("button's name ");
	 	Name.setFont(new Font("Serif", Font.BOLD, 30));
	 	Name.setAlignmentX(Component.LEFT_ALIGNMENT);

        Classic.add( Name);



        JLabel icone = new JLabel(" Icone's path   ");
	 	icone.setFont(new Font("Serif", Font.BOLD, 30));
        icone.setAlignmentX(Component.LEFT_ALIGNMENT);

        Classic.add( icone);


		Icone = new JButton(LesBoutons.get(0).get(3).toString() );
	 	Icone.setFont(new Font("Serif", Font.BOLD, 30));
	 	Icone.setAlignmentX(Component.LEFT_ALIGNMENT);

        Classic.add( Icone);

        JPanel SettingButton = new JPanel();

        for (int i = 0;i < AllTypeButton.size();i++ ) {

	    	TypeButton.add(new JButton(AllTypeButton.get(i) ));
	    	TypeButton.get(i).setFont(new Font("Serif", Font.BOLD, 30));
			TypeButton.get(i).addActionListener(this);
			TypeButton.get(i).setAlignmentX(Component.LEFT_ALIGNMENT);


        	SettingButton.add( TypeButton.get(i), BorderLayout.SOUTH);
        }

        GridBagLayout layout = new GridBagLayout();
        GridBagConstraints gbc = new GridBagConstraints();

		f.setLayout(layout);

        gbc.fill = GridBagConstraints.HORIZONTAL;
        gbc.gridx = 0;
        gbc.gridy = 0;
        gbc.gridwidth = 20;

		f.add( buttonPanel , gbc );

        gbc.fill = GridBagConstraints.HORIZONTAL;
        gbc.gridx = 0;
        gbc.gridy = 1;
        gbc.gridwidth = 10;


		f.add( Classic , gbc);

        gbc.fill = GridBagConstraints.HORIZONTAL;
        gbc.gridx = 10;
        gbc.gridy = 1;
        gbc.gridwidth = 10;

		f.add( SettingButton , gbc);

	    f.setDefaultCloseOperation(WindowConstants.DISPOSE_ON_CLOSE);

	    f.pack();

	    f.setVisible(true);
    }


    public void run2()
    {
    	int nbrLigne = 0;

	    f = new JFrame("PCPhone");
	    f.setSize(800,600);
	    f.setExtendedState(JFrame.MAXIMIZED_BOTH);

		JPanel buttonPanel = new JPanel();
		

		Dimension screenSize = Toolkit.getDefaultToolkit().getScreenSize();

		Dimension dim = new Dimension();

		if (screenSize.getHeight() * 0.15 * LesBoutons.size() < screenSize.getWidth())
		{
			dim.height = (int) (screenSize.getHeight() * 0.15);
			dim.width = dim.height;
		}
		else
		{
			dim.height = (int) (screenSize.getWidth() / LesBoutons.size() * 0.95);
			dim.width = dim.height;
		}


	    for (int i = 0;i < LesBoutons.size() ; i++) {
	    	buttonAdd.add(new JButton(LesBoutons.get(i).get(0).toString()));
	    	buttonAdd.get(i).setFont(new Font("Serif", Font.BOLD, 30));
			buttonAdd.get(i).addActionListener(this);

	    	buttonAdd.get(i).setPreferredSize(dim);
	    	buttonPanel.add(buttonAdd.get(i));
	    }

	    buttonPanel.setFont(new Font("Serif", Font.BOLD, 30));
	    buttonPanel.setBorder(BorderFactory.createTitledBorder("The Buttons"));

        JPanel SettingButton = new JPanel();

        GridBagLayout layout = new GridBagLayout();

        SettingButton.setLayout(layout);
        GridBagConstraints gbc = new GridBagConstraints();
 
        // Put constraints on different buttons
        gbc.fill = GridBagConstraints.HORIZONTAL;

        ArrayList<String> AllTypeButton = new ArrayList<String>() {{ add("Open a File"); add("Open a Folder"); add("Open a software"); add("executable path"); add("keyboard/mouse execution"); }};

        gbc.gridy = 0;

        gbc.gridx = 0;
	 	JLabel name = new JLabel(" Button's Name:   ");
	 	name.setFont(new Font("Serif", Font.BOLD, 30));
        SettingButton.add( name, gbc);


	 	gbc.gridx = 1;

	 	Name = new JTextField("button's name ");
	 	Name.setFont(new Font("Serif", Font.BOLD, 30));

        SettingButton.add( Name, gbc);

        gbc.fill = GridBagConstraints.HORIZONTAL;

	 	gbc.gridx = 2;

        JLabel icone = new JLabel(" Icone's path   ");
	 	icone.setFont(new Font("Serif", Font.BOLD, 30));
        SettingButton.add( icone, gbc);

	 	gbc.gridx = 3;

		Icone = new JButton(LesBoutons.get(0).get(3).toString() );
	 	Icone.setFont(new Font("Serif", Font.BOLD, 30));
        SettingButton.add( Icone, gbc);

        gbc.gridy = 2;

        for (int i = 0;i < AllTypeButton.size();i++ ) {
        	gbc.gridx = i;

	    	TypeButton.add(new JButton(AllTypeButton.get(i) ));
	    	TypeButton.get(i).setFont(new Font("Serif", Font.BOLD, 30));
			TypeButton.get(i).addActionListener(this);


        	SettingButton.add( TypeButton.get(i), gbc);
        }


		JPanel AllPanel = new JPanel();
   		AllPanel.setLayout(new BorderLayout());//Setting BoxLayout Vertically
		AllPanel.add(buttonPanel, BorderLayout.NORTH);
		AllPanel.add(SettingButton, BorderLayout.WEST);


		f.add(AllPanel);

	    f.setDefaultCloseOperation(WindowConstants.DISPOSE_ON_CLOSE);

	    f.setVisible(true);
    }
	

	public void actionPerformed(ActionEvent evt) {
		Object source = evt.getSource();

		if (source == TypeButton.get(0))
		{
			System.out.println("ams u c s");
		}
	};
}
