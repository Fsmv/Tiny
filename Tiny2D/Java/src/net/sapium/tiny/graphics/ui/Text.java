package net.sapium.tiny.graphics.ui;

import java.awt.Color;
import java.awt.Font;
import java.awt.FontMetrics;
import java.awt.Graphics2D;
import java.awt.image.BufferedImage;

import net.sapium.tiny.graphics.Drawable;

public class Text implements Drawable {

	private int x, y;
	private Color color;
	private String text;
	private BufferedImage image;
	private boolean needsRefresh;
	private FontMetrics fontMetrics;

	public Text(String text, int x, int y) {
		this.x = x;
		this.y = y;
		this.text = text;
		needsRefresh = true;
		color = Color.black;
		refresh(null);
	}
	
	public Text(String text){
		this.x = 0; 
		this.y = 0;
		this.text = text;
		needsRefresh = true;
		color = Color.black;
		refresh(null);
	}
	
	private void refresh(Font f){
		image = new BufferedImage(1, 1, BufferedImage.TYPE_INT_ARGB);
		
		if(f == null){
			f = image.getGraphics().getFont();
		}
		
		fontMetrics = image.getGraphics().getFontMetrics(f);

		int height = fontMetrics.getHeight();
		int width = fontMetrics.stringWidth(text);
		
		if(width == 0){
			width = 1;
		}
		
		if(height == 0){
			height = 1;
		}

		image = new BufferedImage(width, height, BufferedImage.TYPE_INT_ARGB);

		Graphics2D ig = ((Graphics2D) image.getGraphics());
		if(f != null){
			ig.setFont(f);
		}
		
		ig.setColor(color);
		
		ig.drawString(text, 0, fontMetrics.getAscent());

		needsRefresh = false;
	}

	@Override
	public void draw(Graphics2D g) {
		if (needsRefresh) {
			refresh(g.getFont());
		}

		g.drawImage(image, null, x, y);
	}

	public void setText(String text) {
		this.text = text;
		needsRefresh = true;
	}

	public void setLocation(int x, int y) {
		this.x = x;
		this.y = y;
	}

	public int getWidth() {
		return image.getWidth();
	}

	public int getHeight() {
		return image.getHeight();
	}
	
	public Color getColor() {
		return color;
	}

	public void setColor(Color color) {
		this.needsRefresh=true;
		this.color = color;
	}
	
	public String getText(){
		return text;
	}
	
	public FontMetrics getFontMetrics(){
		return fontMetrics;
	}

    public int getX() {
        return x;
    }

    public int getY() {
        return y;
    }
}
