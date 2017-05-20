package hex.ihm.vue;

import hex.ihm.vue.Fenetre;
import hex.ihm.vue.Hexagone;


public class Test {
	
	public static void main(String[] args) {
		Fenetre fen= new Fenetre("Hex");
		Hexagone pan=new Hexagone(0,0,10);
		fen.setContentPane(pan);
	}

}
