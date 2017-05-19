/**
 * Description: Module permettant la gestion de l'intelligence artificielle afin de pouvoir jouer contre
 * la machine au jeu HEX.
 * 
 * G. ROBERT - Univ. de Toulouse III - Paul Sabatier
 */

package hex;
import java.io.File;

public class IA {
		
	static{
			
		String path = new File("src/libIA.so").getAbsolutePath();
		System.load(path);
	}
	/**
	 * Descrition: fonction qui permet à l'ordinateur de jouer un coup facile
	 * @param s ≠ NULL
	 * @param p=NOIR ⋁ p=BLANC
	 * @return Retourne un tableau de 2 entiers, le premier représente une coordonnée en x et l'autre en y.
	 */
	public static native int[] jouerCoupFacile(String s,char p);
	public static native int[] jouerCoupMoyen(String s,char p);
	public static native int[] jouerCoupDifficile(String s,char p);
	public static native int[] jouerCoupImpossible(String s,char p);
	
	
}
