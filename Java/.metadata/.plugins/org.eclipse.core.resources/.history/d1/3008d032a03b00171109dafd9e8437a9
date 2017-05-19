import java.util.Scanner;


public class GererErreur {

	/*
	 * Description: vérifie que valeur est compris
	 * entre le min et le max, sinon
	 * on demande une nouvelle valeur et on la retourne.
	 * 
	 */
	
	public int verifierIntervalle(int valeur,int min, int max){
	
		boolean b=false;
		while(b==false){
			if(valeur<min){
				System.out.print("La valeur est trop petite, recommencez: ");
				valeur=gererErreurInt();
			}
			else if(valeur>max){
				System.out.print("La valeur est trop grande, recommencez: ");
				valeur=gererErreurInt();
			}
			else
				b=true;
			
		}
		return valeur;
	}
	
	/*
	 * Description: vérifie qu'on rentre bien un int
	 * sinon on boucle jusqu'a ce que l'utilisateur
	 * donne une valeur correct
	 * et on retourne cette valeur
	 */
	
	public int gererErreurInt(){
		
		int chiffre = 0 ;
		boolean bsaisie = false ;
		
		do {
			Scanner sc = new Scanner(System.in);
			try { 
					chiffre = sc.nextInt(); 
					bsaisie = true ; 
			} 
			catch (java.util.InputMismatchException e) {
				System.out.print("Vous avez rentré une valeur incorrect, recommencez: ");
			}
			sc.reset() ; 
		} while(bsaisie == false) ; 
		
		
	
		
		return chiffre;
	}
	
	
	/*
	 * Description: vérifie qu'on rentre bien un char
	 * sinon on boucle jusqu'a ce que l'utilisateur
	 * donne une valeur correct, soit 'b' soit 'n'
	 * et on retourne le caractère
	 */
	
	public char gererErreurChar(char c1, char c2){
		
		String s;
		char lettre='a';
		boolean bsaisie = false ;
		
		do {
			Scanner sc = new Scanner(System.in);
			try { 
					s = sc.nextLine(); 
					lettre = s.charAt(0);
					if(lettre==c1 || lettre==c2)
						bsaisie = true ; 
					else
						System.out.print("Vous avez rentrer une valeur incorrect, recommencez: ");
			} 
			catch (java.util.InputMismatchException e) {
				System.out.print("Vous avez rentrer une valeur incorrect, recommencez: ");
			}
			sc.reset() ; 
			
		} while(bsaisie == false) ; 
		
		
	
		
		return lettre;
	}
	
	
	
}
