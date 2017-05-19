public class Test {

	
	private static void afficher(String s,int taille){
		int h=0;
		for(int j=0;j<=taille+1;j++){	/* boucle correspondant au nombre de ligne à afficher*/
			
			for(int a=0;a<j+1;a++)
				System.out.print(" ");
			
			if(j==0){
				/*  affichage de la première ligne 	*/
				for(int i=0;i<=taille;i++)
						System.out.print("W ");
						
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
				
				System.out.print("B ");
				for(int i=0;i<=taille;i++)
					System.out.print("W ");
		
			
				
			}
			
			
			
		}
		
	}
	

	
	public static void main(String[] args){       
		 	
		String s=InterfaceAvecC.creerGraphe(9);
		afficher(s,9);
	
	}
	
}
