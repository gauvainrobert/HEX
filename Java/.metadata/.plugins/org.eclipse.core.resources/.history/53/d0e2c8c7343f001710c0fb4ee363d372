/******************************************************************
* Menu                                                   		  *
* Description: Module de gestion des fichiers textes et du        *
* platau de jeu                                                   *
* F. ANTOINE - Univ. de Toulouse III - Paul Sabatier              *
*******************************************************************/
package hex;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;

	public class Menu {

		/**
		 * Description: affiche sous forme de plateau de jeu
		 * la chaine de carractère en entréé
		 * 
		 */
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
		
		/**
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
	
		
		/**
		 * 
		 * Description: sauvegarde s dans un fichier de transition avec sa taille
		 * Si pion='a', peu importe les valeurs après on prend le fichier sauvegarde.txt
		 * qu'on recopie dans sauvegardeTemp.txt
		 * Si pion='.' sauvegarde une nouvelle partie dans sauvegardeTemp.txt
		 * Sinon pour tout autre valeur de pion, on enregistre le coup donné x,y
		 * dans le fichier sauvegardeTemp.txt a la suite des autres, sauf
		 * si x=-1 on enregistre le graphe sans mettre de coup
		 * (utile pour annuler le dernier coup, on met à jour le graphe
		 * mais il ne faut pas rentrer de coup)
		 * 
		 */
		
		public void sauvegarderTemporaire(String s,char pion, int x, int y,boolean ia, boolean commence_ia,char pionCommence,char difficulte){
			
			File f=new File("sauvegardeTemp.txt");
			int taille=(int)Math.sqrt(s.length());
			
		if(pion=='.'){
			
			
			try
			{
			    PrintWriter fw = new PrintWriter(new BufferedWriter(new FileWriter (f)));
			    /* premiere ligne pour l'ia (\ia) 
			     * 'o' pour jeu contre ia, sinon 'n'
			     * 'o' pour l'ia commence sinon 'n'
			     * 'B' pour l'ia a les blancs sinon 'N'
			     * et la difficulté, soit F/M/D/I pour
			     *  Facile,Moyen,Difficile,Impossible
			     * On peut donc avoir:
			     * \ia o o B pour jouer contre l'ia, elle commence avc les BLANC
			     * \ia n * * on joue sans l'ia
			     * 
			     */
			    if(ia){
			    	if(commence_ia)
			    		fw.println("\\ia o o "+pionCommence+ " "+ difficulte);
			    	else
			    		if(pionCommence=='b')
			    			fw.println("\\ia o n n"+" "+ difficulte);
			    		else
			    			fw.println("\\ia o n b"+" "+ difficulte);
			    }
			    else
			    	fw.println("\\ia n * * *");
			    	
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
		        while (fr.ready()){
		        	valeur += fr.readLine();
		        	valeur+="\n";
		        }
		        fr.close();

				    PrintWriter fw = new PrintWriter(new BufferedWriter(new FileWriter (f)));
				    
				    for(int i=0;i<valeur.length();i++)
			    		fw.print (valeur.charAt(i));
			    	fw.close();	
			    
				
		        	
		        }
		catch (IOException exception){
		    System.out.println ("Erreur lors de la lecture : " + exception.getMessage());
		    
		        }
			
			
			
			
		}
		else{
			try {
		        BufferedReader fr = new BufferedReader(new FileReader ("sauvegardeTemp.txt"));
		        String valeur = new String();
		        int l=0;
		        while (fr.ready() ) {
		            	valeur += fr.readLine();
		            	valeur += "\n";
		            }
		        fr.close();
		        
		        fr = new BufferedReader(new FileReader ("sauvegardeTemp.txt"));
		        String valeur2 = new String();
		        
		        while (fr.ready() && l<3 ) { /*prends juste les trois premières lignes */
		            	valeur2 += fr.readLine();
		            	valeur2 += "\n";
		            	l++;
		            }
		        fr.close();
		        
		        try
				{
		        	String n="";
		        	PrintWriter fw = new PrintWriter(new BufferedWriter(new FileWriter (f)));
		        	String nouveau;
		        	if(taille<9)
		        		/*26 correspond au nombre d'octet entre le debut et le graphe */
		        		nouveau=valeur.substring((26+((taille+1)*taille)),valeur.length()); 
		        	else
		        		/* 1 octet de plus si taille>=10 */
		        		nouveau=valeur.substring((27+((taille+1)*taille)),valeur.length());
		        	if(ia){
		        		
		        		n=valeur2;
		        		
		        	}
		        	String ajout;
		        	for(int i=0;i<s.length();i++){ 
			    		n+=s.charAt(i);
			    		
			    	if((i+1)%taille==0)
			    		n+="\n";
		        	}
		        	
		        	n+=nouveau; /* contient le nouveau graphe avc les coups deja joué */
		        	nouveau=n.substring(0,n.length()-17);
		        	
		        	if(x!=-1){ /* si le parametre x est à -1 on modifie juste le graphe */
		        		if(pion=='b')
		        			ajout="\\play BLANC"+ " " + x + " "+ y +"\n" ;
		        		else
		        			ajout="\\play NOIR"+ " " + x + " "+ y +"\n" ;
		        	nouveau+=ajout;
		        	
		        	}
		        	nouveau+="\\endgame\n\\endhex";

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
		
		
		
		/**
		 * Description: copie le fichier saugergardeTemp.txt
		 * dans sauvegardeTemp.txt
		 * 
		 */
		
		public void sauvegarder(){
				String s=chargerFichierTemp();
				int taille=s.length();
				try
				{
				    PrintWriter fw = new PrintWriter(new BufferedWriter(new FileWriter ("sauvegarde.txt")));
				    
				    for(int i=0;i<taille;i++)
				    		fw.print (s.charAt(i));
				    
				    fw.close();
				}
				catch (IOException exception){
				    System.out.println ("Erreur grave lors de la lecture : " + exception.getMessage());
				}
		}
		
		/**
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
		        fr.readLine();
		        int valeur;
		        String s1=fr.readLine();  
		        char taille=s1.charAt(s1.length()-2);
		        if(taille>='1' && taille<='2'){
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
		
		/**
		 * Description: charge le fichier sauvegarde.txt et renvoi le plateau
		 */
		
		public String charger() {
		    try {
		        BufferedReader fr = new BufferedReader(new FileReader ("sauvegarde.txt"));
		        fr.readLine();
		        fr.readLine();
		        fr.readLine();
		        int taille=recupererTaille();
		        String valeur = new String();
		        int i=0;
		        while (fr.ready() && i<taille ) {
		        	
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
		/**
		 * 
		 * Description: charge le fichier sauvegardeTemp.txt et renvoi le plateau
		 * 
		 */
		
		public String chargerPlateauTemp() {
		    try {
		        BufferedReader fr = new BufferedReader(new FileReader ("sauvegardeTemp.txt"));
		        fr.readLine();
		        fr.readLine();
		        fr.readLine();
		        int taille=recupererTaille();
		        String valeur = new String();
		        int i=0;
		        while (fr.ready() && i<taille ) {
		        	
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
		
		/**
		 * 
		 * Description: Charge le pion du dernier coup joué 
		 * dans le fichier sauvegardeTemp.txt et le renvoi.
		 * si il renvoi '.' aucun coup n'a été encore joué.
		 * 
		 */
		public char chargerDernierPion(){
			try {
				/* tableau de lignes qui contient le fichier ligne par ligne */
				String tab[]=new String[500]; 
				int i=0;
		        BufferedReader fr = new BufferedReader(new FileReader ("sauvegardeTemp.txt"));
		        while (fr.ready() ) {
		        	
		            	tab[i] = fr.readLine();
		            	i++;
		            	
		            }
		        
		        fr.close();
		        if(tab[i-3].charAt(1)!='p')
		        	return '.';
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
		
		/**
		 * Description: efface le dernier coup joué dans 
		 * le fichier sauvegardeTemp.txt
		 */
		
		public void effacerDernierPion(){
			try {
				/* tableau de lignes qui contient le fichier ligne par ligne */
				File f=new File("sauvegardeTemp.txt");
				String tab[]=new String[500]; 
				int i=0;
		        BufferedReader fr = new BufferedReader(new FileReader ("sauvegardeTemp.txt"));
		        while (fr.ready() ) {
		        	
		            	tab[i] = fr.readLine();
		            	i++;
		            	
		            }
		        
		        fr.close();
		        
		        PrintWriter fw = new PrintWriter(new BufferedWriter(new FileWriter (f)));
			    
			    for(int j=0;j<i;j++){
			    	if(j!=i-3){
			    		fw.print (tab[j]);
			    		fw.print ("\n");
			    	}
			    }
			    
			    fw.close();
		        
		        
		        
		        }
		catch (IOException exception){
		    System.out.println ("Erreur lors de la lecture : " + exception.getMessage());
		    
		        }
		
		    }
		
		/**
		 * Description: met à jour le nombre de coup des
		 * joueurs blanc, noir et le nombre de tour
		 * quand on lance des parties chargées
		 */
		public void nbCoup(Jouer j){
			int i;
			int p=1;
			int nbTour=1;
			int nbNoir=1;
			int nbBlanc=1;
			try {
				/* tableau de lignes qui contient le fichier ligne par ligne */
				String tab[]=new String[500]; 
				i=0;
		        BufferedReader fr = new BufferedReader(new FileReader ("sauvegardeTemp.txt"));
		        while (fr.ready() ) {
		        	
		            	tab[i] = fr.readLine();
		            	i++;
		            	
		            }
		        
		        fr.close();
		        
		        int taille=recupererTaille();
		        i=taille+5;
		        while(tab[i].charAt(1)!='e'){ /* s'arrete au 'e' de endgame */
		        	
		        	if(p%2==0){
		        		nbTour++;/* incremente tous les deux tours de boucle */
		        		p++;
		        	}
		        	
		        	if(tab[i].charAt(6)=='B')
		        		nbBlanc++;
		        	else
		        		nbNoir++;
		        	i++;
		        	
		        }
		        j.setNbCoupBlanc(nbBlanc);
		        j.setNbCoupNoir(nbNoir);
		        j.setNbTour(nbTour);
		        
		        
		    }
		catch (IOException exception){
		    System.out.println ("Erreur lors de la lecture : " + exception.getMessage());
		    
		        }
		
		    }
		
		public void initialisernbCoup(Jouer j){
			j.setNbCoupBlanc(1);
			j.setNbCoupNoir(1);
			j.setNbTour(1);
		}
		
		public boolean recupererJouerContreIA(){
			char c;
			try {
		        BufferedReader fr = new BufferedReader(new FileReader ("sauvegardeTemp.txt"));
		        String s=fr.readLine();
		        c=s.charAt(4);
		        fr.close();
		        if(c=='o')
		        	return true;
		        return false;
		        }
			catch (IOException exception){
				System.out.println ("Erreur lors de la lecture : " + exception.getMessage());
				return false;
		        }
		
		    }
			
		public boolean recupererIACommence(){
			char c;
			try {
		        BufferedReader fr = new BufferedReader(new FileReader ("sauvegardeTemp.txt"));
		        String s=fr.readLine();
		        c=s.charAt(6);
		        fr.close();
		        if(c=='o')
		        	return true;
		        return false;
		        }
			catch (IOException exception){
				System.out.println ("Erreur lors de la lecture : " + exception.getMessage());
				return false;
			}
		
		}
		
		public char recupererPionIA(){
			char c;
			try {
		        BufferedReader fr = new BufferedReader(new FileReader ("sauvegardeTemp.txt"));
		        String s=fr.readLine();
		        c=s.charAt(8);
		        fr.close();
		        return c;
		        }
			catch (IOException exception){
				System.out.println ("Erreur lors de la lecture : " + exception.getMessage());
				return '.';
			}
		
	  }
			
		
		/**
		 * 
		 * Deescription: recupere la difficulté de l'ia
		 * dans le fichier sauvegarde.txt
		 */
		public String recupererDifficulteIA(){
			char c;
			try {
		        BufferedReader fr = new BufferedReader(new FileReader ("sauvegardeTemp.txt"));
		        String s=fr.readLine();
		        c=s.charAt(10);
		        fr.close();
		        if(c=='F')
		        	return "Facile";
		        else if(c=='M')
		        	return "Moyen";
		        else if(c=='D')
		        	return "Difficile";
		        else 
		        	return "Impossible";
		     
		        }
		catch (IOException exception){
		    System.out.println ("Erreur lors de la lecture : " + exception.getMessage());
		    return "null";
		        }
		
		    }
		
		/**
		 * 
		 * Description: retourne le nombre de coup joué
		 */
		public int nombreDeCoupJouer(){
				int i;
				int j=0;
				try {
					/* tableau de lignes qui contient le fichier ligne par ligne */
					String tab[]=new String[500]; 
					i=0;
			        BufferedReader fr = new BufferedReader(new FileReader ("sauvegardeTemp.txt"));
			        while (fr.ready() ) {
			        	
			            	tab[i] = fr.readLine();
			            	i++;
			            	
			            }
			        
			        fr.close();
			        
			        int taille=recupererTaille();
			        ;
			        i=taille+5;
			        
			        while(tab[i].charAt(1)!='e'){ /* s'arrete au 'e' de endgame */
			        	
			        	j++;
			        	i++;
			        	
			        }
			        return j;
			        
			        
			    }
			catch (IOException exception){
			    System.out.println ("Erreur lors de la lecture : " + exception.getMessage());
			    return -1;
			        }
			
		}
			
			
}

		



