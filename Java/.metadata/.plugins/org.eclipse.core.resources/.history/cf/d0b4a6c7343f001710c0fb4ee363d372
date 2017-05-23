/******************************************************************
* IHM                                                    		  *
* Description: Module pour jouer au jeu HEX entre deux joueurs    *
* F. ANTOINE - Univ. de Toulouse III - Paul Sabatier              *
*******************************************************************/

package hex;

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
		String difficulte="null";
		boolean ia=false;
		boolean commence_ia=false;
		String graphe=null;
		int taille=0;
		GererErreur g=new GererErreur();
		Jouer j=new Jouer(1,1,0);
		
		
		while(choix!=5){
			
			Menu m=new Menu();
			
			
			/* -1 affichage du menu */
			if(choix==-1)
				choix=m.afficherMenu();
			
			
			/* Nouvelle partie*/
			else if(choix==1){
				j=new Jouer(1,1,0);
				System.out.print("Veuillez choisir la taille du plateau (entre 2 et 20): ");
				taille=g.gererErreurInt();
				taille=g.verifierIntervalle(taille, 2,20);
				graphe= Plateau.creerGraphe(taille);
				System.out.print("Qui commence? Les blancs ou les noirs? (b/n) :");
				pion=g.gererErreurChar('b','n');
				ia=g.saisirIA();
				if(ia){
					difficulte=g.choisirDiffculte();
					commence_ia=g.commenceIA();
				}
				m.sauvegarderTemporaire(graphe,'.',0,0,ia,commence_ia,pion,difficulte.charAt(0));
				choix=j.jouerPartie(graphe,pion,ia,commence_ia,difficulte.charAt(0));
				if(choix==-2){ /* -2 signifie que la partie est fini, on efface le graphe */
					graphe=null;
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
					m.sauvegarderTemporaire(graphe,'a',0,0,true,true,'.','.');
					taille=m.recupererTaille();
					pion=m.chargerDernierPion();
					if(pion=='.'){	/*Chargement d'une partie non commencé */
						m.initialisernbCoup(j);
						System.out.print("Qui commence? Les blancs ou les noirs? (b/n) :");
						pion=g.gererErreurChar('b','n');
						choix=j.jouerPartie(graphe,pion,ia,commence_ia,'.');
					}
					else if(pion=='b'){ /*Chargement d'une partie sauvegarder dans sauvegarde.txt */
						m.nbCoup(j);
						difficulte=m.recupererDifficulteIA();
						if(m.recupererPionIA()=='b')
							choix=j.jouerPartie(graphe,'n',m.recupererJouerContreIA(),false, difficulte.charAt(0));
						else
							choix=j.jouerPartie(graphe,'n',m.recupererJouerContreIA(),true,difficulte.charAt(0));
					}
					else{
						m.nbCoup(j);
						difficulte=m.recupererDifficulteIA();
						if(m.recupererPionIA()=='n')
							choix=j.jouerPartie(graphe,'b',m.recupererJouerContreIA(),false,difficulte.charAt(0));
						else
							choix=j.jouerPartie(graphe,'b',m.recupererJouerContreIA(),true,difficulte.charAt(0));
					}
				}
				
			}
			
			/* Annuler dernier coup */
			else if(choix==4){
				graphe=m.chargerPlateauTemp();
				int taille_test=m.recupererTaille();
				int x=m.recuperDernierCoupX();				
				int y=m.recuperDernierCoupY();		
				if(x<0 || x>taille_test-1 || y<0 || y>taille_test-1 ){
					System.out.println("Impossible de supprimer coup, pas de coup joué.");
					System.out.println("retour au menu...");
					choix=-1;
				}
				/* si un coup joué par l'ia mais pas par un joueur on ne peut pas annuler le coup */
				else if(m.recupererJouerContreIA() && m.recupererIACommence() && m.nombreDeCoupJouer()<=1){
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
					
					/*graphe=Plateau.annulerDernierCoup(graphe,x,y);
					pion=m.chargerDernierPion();
					m.effacerDernierPion();
					*/
					if(m.recupererJouerContreIA()){ /*si on joue contre l'ia */
						
						if(m.recupererIACommence()){ /*si l'ia a commencé la partie */
						
							/*on recupere son dernier coup dans le fichier */
							x=m.recuperDernierCoupX();				
							y=m.recuperDernierCoupY();
							/*on annule le coup dans le graphe */
							graphe=Plateau.annulerDernierCoup(graphe,x,y);
							/*on l'efface dans le fichier*/
							m.effacerDernierPion();
							/*on recupere le dernier coup du joueur et le pion */
							x=m.recuperDernierCoupX();				
							y=m.recuperDernierCoupY();
							pion=m.chargerDernierPion();
							/* on annule le coup du joueur dans le graphe */
							graphe=Plateau.annulerDernierCoup(graphe,x,y);
							m.effacerDernierPion();
							/*le joueur joue son coup */
							if(pion=='b'){
								m.nbCoup(j);
								choix=j.jouerPartie(graphe,'b',ia,false,m.recupererDifficulteIA().charAt(0));
							}
							else{
								m.nbCoup(j);
								choix=j.jouerPartie(graphe,'n',ia,false,m.recupererDifficulteIA().charAt(0));
							}
					
						}
						else{ /*si c'est le joueur qui commence */
							x=m.recuperDernierCoupX();				
							y=m.recuperDernierCoupY();
							graphe=Plateau.annulerDernierCoup(graphe,x,y);
							pion=m.chargerDernierPion();
							m.effacerDernierPion();
							if(pion=='b'){
								m.nbCoup(j);
								choix=j.jouerPartie(graphe,'b',ia,false,'.');
							}
							else{
								m.nbCoup(j);
								choix=j.jouerPartie(graphe,'n',false,false,'.');
							}
							
						}
					}
					else{
						graphe=Plateau.annulerDernierCoup(graphe,x,y);
						pion=m.chargerDernierPion();
						m.effacerDernierPion();
						m.sauvegarderTemporaire(graphe,'x',-1,y,true,true,'.','.');
						if(pion=='b'){
							m.nbCoup(j);
							choix=j.jouerPartie(graphe,'b',false,false,'.');
						}
						else{
							m.nbCoup(j);
							choix=j.jouerPartie(graphe,'n',false,false,'.');
						}
					}
				}
			}
			
			
			/* Quitter le jeu */
			if(choix==5){
				if(graphe!=null){
					System.out.println("Voulez vous sauvegarder avant de quitter? (o/n)");
					char reponse=g.gererErreurChar('o','n');
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
