/******************************************************************
* Plateau                                                  		  *
* Description: Appelle des fonctions c                            *
* F. ANTOINE - Univ. de Toulouse III - Paul Sabatier              *
*******************************************************************/

package hex;

import java.io.File;

public class Plateau {
	
	static{
		
		String path = new File("src/libPlateau.so").getAbsolutePath();
        System.load(path);
	}
	
	public static native String creerGraphe(int n);
	public static native String rentrerCoup(String s,char c,int x,int y);
	public static native char verifierGagnant(String s);
	public static native String annulerDernierCoup(String s, int x, int y);
	public static native char verifierCase(String s,int x,int y);
	
	
	
}
