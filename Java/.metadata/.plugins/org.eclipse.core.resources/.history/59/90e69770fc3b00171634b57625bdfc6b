/******************************************************************
* Menu                                                   		  *
* Description: Module pour jouer au jeu HEX entre deux joueurs    *
* F. ANTOINE - Univ. de Toulouse III - Paul Sabatier              *
*******************************************************************/


public class IHM {

	
	
	/**
	 * 
	 * Description: Permet de jouer au jeu complet,
	 * gère nouvelle partie, sauvegarde, chargement,
	 * annuler dernier coup, choix taille plateau etc...
	 * 
	 */
	
	private static void jouerHex(){
		
		int choix=-1;
		char pion='b';
		String graphe="null";
		int taille=0;
		GererErreur g=new GererErreur();
		Jouer j=new Jouer(1,1,1);
		
		
		while(choix!=5){
			
			Menu m=new Menu();
			
			
			/* -1 affichage du menu */
			if(choix==-1)
				choix=m.afficherMenu();
			
			
			/* Nouvelle partie*/
			else if(choix==1){
				System.out.print("Veuillez choisir la taille du plateau (entre 2 et 20): ");
				taille=g.gererErreurInt();
				taille=g.verifierIntervalle(taille, 2,20);
				graphe= Plateau.creerGraphe(taille);
				m.sauvegarderTemporaire(graphe,'.',0,0);
				System.out.print("Qui commence? Les blancs ou les noirs? (b/n) :");
				pion=g.gererErreurChar('b','n');
				choix=j.jouerPartie(graphe,pion);
				if(choix==-2){ /* -2 signifie que la partie est fini, on efface le graphe */
					graphe="null";
					choix=-1;
				}
			}
			
			/* Sauvegarder partie */
			else if(choix==2){
				
				/*Empêche de sauvegarder si aucune partie n'est lancée */
				if(taille==0){
					System.out.println("Impossible de sauvegarder, pas de partie en cours");
					System.out.println("retour à la partie...");
					choix=-1;
				
				}
				/*Empêche de sauvegarder si la dernière partie est terminé */
				else if(j.gagnant(m.chargerPlateauTemp())!='.'){ 
					System.out.println("Impossible de sauvegarder, la partie est fini");
					System.out.println("retour au menu");
					choix=-1;
					
				}
				
				
				else{
					m.sauvegarder();
					System.out.println("La partie en cours a été sauvegarder");
					System.out.println("retour au menu...");
					choix=-1;
				}
			}
			
			/* Charger partie */
			else if(choix==3){
				graphe=m.charger();
				pion=m.chargerDernierPion();
				if(graphe=="null"){ /*Aucune partie chargée */
					System.out.println("Impossible de charger, pas de partie en cours sauvegarder");
					System.out.println("retour au menu...");
					choix=-1;
				}
				else{
					m.sauvegarderTemporaire(graphe,'a',0,0);
					taille=m.recupererTaille();
					pion=m.chargerDernierPion();
					if(pion=='.'){	/*Chargement d'une partie non commencé */
						m.initialisernbCoup(j);
						System.out.print("Qui commence? Les blancs ou les noirs? (b/n) :");
						pion=g.gererErreurChar('b','n');
						choix=j.jouerPartie(graphe,pion);
					}
					else if(pion=='b'){ /*Chargement d'une partie sauvegarder d'en sauvegarde.txt */
						m.nbCoup(j);
						choix=j.jouerPartie(graphe,'n');
					}
					else{
						m.nbCoup(j);
						choix=j.jouerPartie(graphe,'b');
					}
				}
				
			}
			
			/* Annuler dernier coup */
			else if(choix==4){
				int taille_test=m.recupererTaille();
				int x=m.recuperDernierCoupX();				
				int y=m.recuperDernierCoupY();				
				if(x<0 || x>taille_test-1 || y<0 || y>taille_test-1){
					System.out.println("Impossible de supprimer coup, pas de coup joué.");
					System.out.println("retour au menu...");
					choix=-1;
				}
				else if(j.gagnant(m.chargerPlateauTemp())!='.'){ 
					System.out.println("Impossible d'annuler le dernier coup, la partie est fini");
					System.out.println("retour au menu");
					choix=-1;
					
				}
				else{
					graphe=Plateau.annulerDernierCoup(graphe,x,y);
					pion=m.chargerDernierPion();
					if(pion=='b'){
						m.nbCoup(j);
						choix=j.jouerPartie(graphe,'n');
					}
					else{
						m.nbCoup(j);
						choix=j.jouerPartie(graphe,'b');
					}
				}
			}
			
			
			/* Quitter le jeu */
			if(choix==5){
				
				if(graphe!="null"){
					System.out.println("Voulez vous sauvegarder avant de quitter? (o/n)");
					char reponse=g.gererErreurChar('b','n');
					if(reponse=='o')
						m.sauvegarder();
					System.out.println("Merci d'avoir joué avec nous. A bientôt!");
				}
				else
					System.out.println("Merci d'avoir joué avec nous. A bientôt!");
				
			}
			
		}
		
		
		
		
		
	}
	
	
	
	
	
	public static void main(String[] args){       
		
		jouerHex();
			
		}
}
