/******************************************************************
* Menu                                                   *
* Description: Module qui permet de représenter un plateau de jeu *
* de taille variable                                              *
* F. ANTOINE - Univ. de Toulouse III - Paul Sabatier               *
*******************************************************************/


import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;

	public class Menu {

		public static void afficher(String s){
			int taille=s.length();
			taille=(int) Math.sqrt(taille);
			
			int h=0;
			for(int j=0;j<=taille+1;j++){	/* boucle correspondant au nombre de ligne à afficher*/
				
				for(int a=0;a<j+1;a++){
					System.out.print(" ");
				}
				if(j==0){
					/*  affichage de la première ligne 	*/
					for(int i=0;i<=taille;i++){
						if(i==taille)
							System.out.print("W/");
						else
							System.out.print("W ");
					}
							
							
					System.out.println("B");
				}
				
				
				/* affichage du centre */
				else if(j>0 && j<=taille){
					
					for(int x=0;x<=taille+1;x++){
						if(x==0 || x==taille+1)
							System.out.print("B ");
						else if(x>0 && x<taille+1){
							System.out.print(s.charAt(h) + " ");
							h++;
						}
							
					}
					System.out.println("");
				}
				else{ /* affichage dernière ligne */
					
					System.out.print("B/");
					for(int i=0;i<=taille;i++)
							System.out.print("W ");
						
						
				
					
				}
				
				
				
			}
			System.out.println("\n");
		}
		
		/*
		 * Description: affiche le menu et demande à l'utilisateur
		 * un choix, retourne ce choix avec un int
		 */
		
		public int afficherMenu(){
			
			System.out.println("=======================");
			System.out.println("1: Nouvelle partie");
			System.out.println("2: Sauvegarder partie");
			System.out.println("3: Charger partie");
			System.out.println("4: Annuler dernier coup");
			System.out.println("5: Quitter le jeu");
			System.out.println("=======================");
			System.out.print("Que voulez vous faire? (Donnez le chiffre correspondant): ");
			GererErreur g=new GererErreur();
			int valeur=g.gererErreurInt();
			return g.verifierIntervalle(valeur,1,5);
			
				
		}
		
		/*
		 * 
		 * Description: sauvegarde s dans un fichier de transition avec sa taille
		 * 
		 */
		
		public void sauvegarderTemporaire(String s,char pion, int x, int y){
			
			File f=new File("sauvegardeTemp.txt");
			int taille=(int)Math.sqrt(s.length());
		if(pion=='.'){
			
			
			try
			{
			    PrintWriter fw = new PrintWriter(new BufferedWriter(new FileWriter (f)));
			    
			    fw.println("\\hex");
			    fw.println("\\board "+taille);
			    
		       
		        
			    for(int i=0;i<s.length();i++){
			    	
			    
			    		fw.print (s.charAt(i));
			    		
			    	if((i+1)%taille==0)
			    		fw.println ();
			    }
			    fw.println("\\endboard");
			    fw.println("\\game");
			    fw.println("\\endgame");
			    fw.println("\\endhex");
			    fw.close();
			}
			catch (IOException exception)
			{
			    System.out.println ("Erreur lors de la lecture : " + exception.getMessage());
			}
		}
		else if(pion=='a'){
			String valeur="";
			try {
				
			    BufferedReader fr = new BufferedReader(new FileReader ("sauvegarde.txt"));
		        while (fr.ready())
		        	valeur += fr.readLine();
		        fr.close();
		        
		        try
				{
				    PrintWriter fw = new PrintWriter(new BufferedWriter(new FileWriter (f)));
				    
				    for(int i=0;i<valeur.length();i++){
			    		fw.print (valeur.charAt(i));
			    	fw.close();	
			    }
				}
				catch (IOException exception){
				    System.out.println ("Erreur lors de la lecture : " + exception.getMessage());
				}
		        	
		        }
		catch (IOException exception){
		    System.out.println ("Erreur lors de la lecture : " + exception.getMessage());
		    
		        }
			
			
			
			
		}
		else{
			try {
		        BufferedReader fr = new BufferedReader(new FileReader ("sauvegardeTemp.txt"));
		        String valeur = new String();
		        
		        while (fr.ready() ) {
		            	valeur += fr.readLine();
		            	valeur += "\n";
		            }
		        fr.close();
		        
		        
		        try
				{
		        	PrintWriter fw = new PrintWriter(new BufferedWriter(new FileWriter (f)));
		        	String nouveau=valeur.substring(14+((taille+1)*taille),valeur.length());
		        	String n="\\hex\n\\board\n";
		        	String ajout;
		        	for(int i=0;i<s.length();i++){ 
			    		n+=s.charAt(i);
			    		
			    	if((i+1)%taille==0)
			    		n+="\n";
		        	}
		        	
		        	n+=nouveau; /* contient le nouveau graphe avc les coups deja joué */
		        	nouveau=n.substring(0,n.length()-17);
		        	
		        	if(pion=='b')
						ajout="\\play BLANC"+ " " + x + " "+ y +"\n" ;
					else
						ajout="\\play NOIR"+ " " + x + " "+ y +"\n" ;
		        	nouveau+=ajout+"\\endgame\n\\endhex";

				    for(int i=0;i<nouveau.length();i++){
				    		fw.print (nouveau.charAt(i));
				    }
				   
				    fw.close();
				}
				catch (IOException exception)
				{
				    System.out.println ("Erreur lors de la lecture : " + exception.getMessage());
				}
		        
		        }
		catch (IOException exception){
		    System.out.println ("Erreur lors de la lecture : " + exception.getMessage());
		        }
			
			
			
			
			
			
		}
	}
		
		
		
		/*
		 * Description: copie le fichier saugergardeTemp.txt
		 * dans sauvegardeTemp.txt
		 * 
		 */
		
		public void sauvegarder(){
				String s=chargerFichierTemp();
				File f=new File("sauvegarde.txt");
				int taille=s.length();
				try
				{
				    PrintWriter fw = new PrintWriter(new BufferedWriter(new FileWriter (f)));
				    
				    for(int i=0;i<taille;i++)
				    		fw.print (s.charAt(i));
				    
				    fw.close();
				}
				catch (IOException exception){
				    System.out.println ("Erreur lors de la lecture : " + exception.getMessage());
				}
		}
		
		/*
		 * Description: Charge le fichier temporaraire en entier et le met 
		 * dans un string qu'on retourne
		 */
		
		public String chargerFichierTemp(){
			try {
		        BufferedReader fr = new BufferedReader(new FileReader ("sauvegardeTemp.txt"));
		        String valeur = new String();
		        
		        while (fr.ready() ) {
		            	valeur += fr.readLine();
		            	valeur += "\n";
		            }
		    fr.close();
		        return valeur;
		        }
		catch (IOException exception){
		    System.out.println ("Erreur lors de la lecture : " + exception.getMessage());
		        }
		return null;
			
			
			
			
		}	
		
		/**
		 * Description: recupere la taille du graphe 
		 * dans le fichier sauvegardeTemp.txt
		 * 
		 */
		
		public int recupererTaille(){
			try {
		        BufferedReader fr = new BufferedReader(new FileReader ("sauvegardeTemp.txt"));
		        fr.readLine();
		        int valeur;
		        String s1=fr.readLine();  
		        char taille=s1.charAt(s1.length()-2);
		        if(taille>='1' && taille<='2'){
		        	System.out.println("ok");
		        	if(taille=='1'){
		        		valeur=10;
		        		for(int j=0;j<(int)s1.charAt(s1.length()-1)-'0';j++)
		        			valeur++;
		        		fr.close();
		        		return valeur;
		        	}
		        	else {
		        		fr.close();
		        		return 20;
		        	}
		        }
		        else{
		        	taille=s1.charAt(s1.length()-1);
		        	valeur=(int)taille;
		        	valeur-='0';
		        	fr.close();
		        	return valeur;
		        	
		        }
		        	
		        
		        
		    
		        
		        
		        }
		catch (IOException exception){
		    System.out.println ("Erreur lors de la lecture : " + exception.getMessage());
		        }
			
			return -1;
			
			
		}
		
		/**
		 * Description: trouve le dernier coup joué par un jour
		 * et donne l'entier pour la coordonné en y
		 * 
		 */
		
		public int recuperDernierCoupY(){
			try {
		        BufferedReader fr = new BufferedReader(new FileReader ("sauvegardeTemp.txt"));
		        String valeur = new String();
		        int y;
		        while (fr.ready() ) {
		            	valeur += fr.readLine();
		            	valeur += "\n";
		            }
		        
		        
		        char taille=valeur.charAt(valeur.length()-20);
		        if(taille>='1' && taille<='2'){
		        	if(taille=='1'){
		        		y=10;
		        		for(int j=0;j<(int)valeur.charAt(valeur.length()-19)-'0';j++)
		        			y++;
		        		fr.close();
		        		return y;
		        	}
		        	else {
		        		fr.close();
		        		return 20;
		        	}
		        }
		        else{
		        	taille=valeur.charAt(valeur.length()-19);
		        	y=(int)taille;
		        	y-='0';
		        	fr.close();
		        	return y;
		        	
		        }
		    }
			catch (IOException exception){
				System.out.println ("Erreur lors de la lecture : " + exception.getMessage());
				return -1;
		    }
		
			
			
		}
		
		/**
		 * Description: trouve le dernier coup joué par un jour
		 * et donne l'entier pour la coordonné en x
		 * 
		 */
		
		public int recuperDernierCoupX(){
			try {
		        BufferedReader fr = new BufferedReader(new FileReader ("sauvegardeTemp.txt"));
		        String valeur = new String();
		        int y;
		        while (fr.ready() ) {
		            	valeur += fr.readLine();
		            	valeur += "\n";
		            }
		        
		        if(recuperDernierCoupY()>9){
		        	char taille=valeur.charAt(valeur.length()-23);
		        	if(taille>='1' && taille<='2'){
		        		if(taille=='1'){
		        			y=10;
		        			for(int j=0;j<(int)valeur.charAt(valeur.length()-22)-'0';j++)
		        				y++;
		        			fr.close();
		        			return y;
		        		}
		        		else {
		        			fr.close();
		        			return 20;
		        		}
		        	}
		        	else{
		        		taille=valeur.charAt(valeur.length()-22);
		        		y=(int)taille;
		        		y-='0';
		        		fr.close();
		        		return y;
		        	
		        	}
		        }
		        else{
		        	char taille=valeur.charAt(valeur.length()-22);
		        	if(taille>='1' && taille<='2'){
		        		if(taille=='1'){
		        			y=10;
		        			for(int j=0;j<(int)valeur.charAt(valeur.length()-21)-'0';j++)
		        				y++;
		        			fr.close();
		        			return y;
		        		}
		        		else {
		        			fr.close();
		        			return 20;
		        		}
		        	}
		        	else{
		        		taille=valeur.charAt(valeur.length()-21);
		        		y=(int)taille;
		        		y-='0';
		        		fr.close();
		        		return y;
		        	
		        	}
		        	
		        }
			}
			catch (IOException exception){
				System.out.println ("Erreur lors de la lecture : " + exception.getMessage());
				return -1;
		    }
		
			
			
		}
		
		/*
		 * Description: charge le fichier sauvegarde.txt et renvoi le plateau
		 */
		
		public String charger() {
		    try {
		        BufferedReader fr = new BufferedReader(new FileReader ("sauvegarde.txt"));
		        fr.readLine();
		        String s1=fr.readLine();  
		        char taille=s1.charAt(s1.length()-1);
		        String valeur = new String();
		        int i=0;
		        while (fr.ready() && i+'0'<taille ) {
		        	
		            	valeur += fr.readLine();
		            	i++;
		            }
		    fr.close();
		        return valeur;
		        }
		catch (IOException exception){
		    System.out.println ("Erreur lors de la lecture : " + exception.getMessage());
		    return "null";
		        }
		
		    }
		
		public char chargerDernierPion(){
			try {
				/* tableau de lignes qui contient le fichier ligne par ligne */
				String tab[]=new String[500]; 
				int i=0;
		        BufferedReader fr = new BufferedReader(new FileReader ("sauvegarde.txt"));
		        while (fr.ready() ) {
		        	
		            	tab[i] = fr.readLine();
		            	i++;
		            	
		            }
		        fr.close();
		        if(tab[i-3].charAt(2)!='p'){
		        	return '.';
		        }
		        else if(tab[i-3].charAt(6)=='B') /* tab[i-3] contient le dernier "\play PION x y " jouer */
		        	return 'b';
		        else if(tab[i-3].charAt(6)=='N')
		        	return 'n';
		        else
		        	return '.';
		        
		        
		        
		        
		        }
		catch (IOException exception){
		    System.out.println ("Erreur lors de la lecture : " + exception.getMessage());
		    return '.';
		        }
		
		    }
		
		public int nbCoupNoirjoue(){
			
			
			
			return 1;
		}
		
}


