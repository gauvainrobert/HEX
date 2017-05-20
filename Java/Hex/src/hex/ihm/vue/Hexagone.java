package hex.ihm.vue;

import java.awt.Graphics;
import java.awt.Polygon;
import java.awt.Color;
import java.awt.Point;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;

import javax.swing.JPanel;
 
public class Hexagone extends JPanel implements MouseListener{
	private Polygon hex;
	private int hex_size_px=20;
	public Hexagone(int posX, int posY, int size){
		this.hex_size_px=size;
		hex=getHex(posX,posY);
		addMouseListener(this);
	}
	
	private Polygon getHex(int posX, int posY) {
	   Polygon hex = new Polygon();
	   for (int i = 0; i < 6; i++) {
	  	 hex.addPoint((int)Math.round((posX + ((hex_size_px-1) * Math.cos((1 + i * 2) * Math.PI / 6)))),
	  			 					(int)Math.round((posY + ((hex_size_px-1) * Math.sin((1 + i * 2) * Math.PI / 6)))));
	   }
	   return hex;
	}
	
	public void paintComponent(Graphics g){
  	g.setColor(Color.BLACK);
  	g.drawPolygon(hex);
  }
  
  public void mousePressed(MouseEvent e) {}
  public void mouseReleased(MouseEvent e) {}
  public void mouseEntered(MouseEvent e) {}
  public void mouseExited(MouseEvent e) {}

  public void mouseClicked(MouseEvent e) {
  	Point p = e.getPoint();
    if(hex.contains(p)) System.out.println("hex contains point");
    else System.out.println("hex Doesn't contain point");
  }
  
}

