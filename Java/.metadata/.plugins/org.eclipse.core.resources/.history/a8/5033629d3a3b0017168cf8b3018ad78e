/*
 * Description: Classe pour jouer une partie en entier ou non
 */


public class Jouer {
 
	
	private int nbCoupBlanc;
	private int nbCoupNoir;
	private int nbTour;
	
	/*Constructeur*/
	public Jouer(int nbCoupBlanc, int nbCoupNoir, int nbTour) {
		super();
		this.nbCoupBlanc = nbCoupBlanc;
		this.nbCoupNoir = nbCoupNoir;
		this.nbTour = nbTour;
	}


	/*
	 * Description: vérifie si le coup qu'on joue apaprtient 
	 * au plateau et si il n'est pas deja occupé, 
	 * renvoi true si on peut mettre la valeur
	 * false sinon
	 * 
	 * pré-condition: s!=NULL 
	 */
	private boolean verifierCoup(String s, int x,int y){
		
		int max=(int) Math.sqrt(s.length());
		if(x<0 || x>max-1 || y<0 || y>max-1){
			System.out.println("Coordonnées incorrect. Les valeurs doivent être comprise entre 0 et "+ (max-1));
			return false;
		}
		if(Plateau.verifierCase(s,x,y)!='.'){
			System.out.println("Case déjà occupée par un pion ");
			return false;
		}
		return true;
	}
	
	
	/*
	 * Description: permet de rentrer un pion dans le graphe
	 * avec les cordonnées rentrés par l'utilisateur et
	 * retourne le graphe ou la chaine de caractere
	 * "Menu" pour interrompre le coup
	 * 
	 * pré-condtion: graphe!=null
	 */
	
	private String rentrerCoup(String graphe,char pion){
		Menu m=new Menu();
		boolean b;
		GererErreur g=new GererErreur();
		int reponse1;
		int reponse2;
		System.out.print("Veuillez donner la ligne à rentrer (ou -1 pour accéder au menu):");
		reponse1=g.gererErreurInt();
		
		
		if(reponse1==-1){
			return "Menu";
		}
			
		
		System.out.print("Veuillez donner la colonne à rentrer (ou -1 pour accéder au menu):");
		reponse2=g.gererErreurInt();
		
		
		if(reponse2==-1){
			return "Menu";
		}
		
		b=verifierCoup(graphe,reponse1,reponse2);
		while(!b){
			
			System.out.print("Veuillez donner la ligne à rentrer (ou -1 pour accéder au menu): ");
			reponse1=g.gererErreurInt();
			
			
			if(reponse1==-1){
				return "Menu";
			}
			
			System.out.print("Veuillez donner la colonne à rentrer (ou -1 pour accéder au menu): ");
			reponse2=g.gererErreurInt();
			
			if(reponse2==-1){
				return "Menu";
			}
			
			b=verifierCoup(graphe,reponse1,reponse2);
			
			
		}
		graphe=Plateau.rentrerCoup(graphe,pion,reponse1,reponse2);
		m.sauvegarderTemporaire(graphe,pion,reponse1,reponse2);
	
		
		if(pion=='b'){
			Menu.afficher(graphe);
			System.out.println("Le joueur BLANC à jouer à la case [" + reponse1 +","+ reponse2+"]" );
		}
		else{
			Menu.afficher(graphe);
			System.out.println("Le joueur NOIR à jouer à la case [" + reponse1 +","+ reponse2+"]" );
		}
		
		return graphe;
		
		
	}
	
	/*
	 * Description: vérifie si il a un gagnant sur le plateau
	 * et renvoi le pion du gagnant si il y en a sinon le caractere '.'
	 * 
	 * pré-condition: s!=null
	 */
	
	private char gagnant(String s){
		
		return Plateau.verifierGagnant(s);

	}
	
	/*
	 * Description: joue une partie en commençant avec un graphe et un 
	 * pion qui commence le tour.
	 * Retourne 1 si la partie termine avec un gagnant ou -1 si
	 * la partie est interrompue
	 * 
	 * pré-condition:graphe!=null ⋀ ( pionQuiCommence='b' ⋁   pionQuiCommence='n' )
	 */
	
	public int jouerPartie(String graphe,char pionQuiCommence){
		char pionGagnant;
		char pion;
		String valeur;
		System.out.println("Allez, il est temps de jouer!\n");
		
		Menu.afficher(graphe);
		if(pionQuiCommence=='b'){
			while(true){
				
				System.out.println("Tour numéro: " + nbTour);
				nbTour++;
				/* COUP DU PION BLANC */
				pion='b';
				System.out.println("C'est au joueur BLANC de jouer");
				System.out.println("Il joue son "+ nbCoupBlanc +"e coup.");
				
				valeur=rentrerCoup(graphe,pion);
				if(valeur=="Menu")
					return -1;
				graphe=valeur;
				nbCoupBlanc++;
				pionGagnant=gagnant(graphe);
				if(pionGagnant=='b'){
						System.out.println("Bravo! Le joueur BLANC à gagner en "+nbCoupBlanc+ " coup!");
						System.out.println("La parti est fini, retour au menu...");
						return -2;
				}
			
				
				/* COUP DU PION NOIR */
				pion='n';
				System.out.println("C'est au joueur NOIR de jouer");
				System.out.println("Il joue son "+ nbCoupNoir +"e coup.");
				
				valeur=rentrerCoup(graphe,pion);
				if(valeur=="Menu")
					return -1;
				
				graphe=valeur;
				nbCoupNoir++;
				pionGagnant=gagnant(graphe);
				
				if(pionGagnant=='n'){
					System.out.println("Bravo! Le joueur BLANC à gagner en "+nbCoupNoir+ " coup!");
					System.out.println("La parti est fini, retour au menu...");
					return -2;
				}
			
			
			
			
			}
		}
		
		if(pionQuiCommence=='n'){
			while(true){
			
				System.out.println("Tour numéro: " + nbTour);
				nbTour++;
				/* COUP DU PION NOIR */
				pion='n';
				System.out.println("C'est au joueur NOIR de jouer");
				System.out.println("Il joue son "+ nbCoupNoir +"e coup.");
				
				valeur=rentrerCoup(graphe,pion);
				if(valeur=="Menu")
					return -1;
				
				graphe=valeur;
				nbCoupNoir++;
				pionGagnant=gagnant(graphe);
				
				if(pionGagnant=='n'){
					System.out.println("Bravo! Le joueur NOIR à gagner!");
					System.out.println("La parti est fini, retour au menu...");
					return -2;
				}
			
				
				System.out.println("Tour numéro :" + nbTour);
				nbTour++;
				/* COUP DU PION BLANC */
				pion='b';
				System.out.println("C'est au joueur BLANC de jouer");
				System.out.println("Il joue son "+ nbCoupBlanc +"e coup.");
				
				valeur=rentrerCoup(graphe,pion);
				if(valeur=="Menu")
					return -1;
				graphe=valeur;
				nbCoupBlanc++;
				pionGagnant=gagnant(graphe);
				if(pionGagnant=='b'){
						System.out.println("Bravo! Le joueur BLANC à gagner!");
						System.out.println("La parti est fini, retour au menu...");
						return -2;
				}
			
			
			
			
			}
		}
		return 0;
	}
	
	
	
	
}
