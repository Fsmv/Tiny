package net.sapium.tiny.graphics.ui;

import java.awt.Color;
import java.awt.FontMetrics;
import java.awt.Graphics2D;
import java.awt.event.KeyEvent;

import net.sapium.tiny.graphics.Drawable;

public class TextBox implements Drawable {
	public static final int padding = 3;
	public static final int blinkDelay = 400;
	public static final char passchar = '\u25CF';
	
	private Text text;
	private Text passText;
	private int caretPos;
	private int x, y;
	private int width, height;
	
	private boolean isPassword;
	private boolean drawCaret = true;
	private boolean caretBlink = true;
	private long lastBlinkTime;
	
	public TextBox(){
		text = new Text("");
		passText = new Text("");
		caretPos = 0;
		x = 0;
		y = 0;
		width = 100;
		height = 21;
		
		lastBlinkTime = System.currentTimeMillis();
		isPassword = false;
	}
	
	public TextBox(int x, int y){
		text = new Text("");
		passText = new Text("");
		caretPos = 0;
		this.x = x;
		this.y = y;
		width = 100;
		height = 21;
		
		lastBlinkTime = System.currentTimeMillis();
		isPassword = false;
	}
	
	public TextBox(boolean isPassword) {
		text = new Text("");
		passText = new Text("");
		caretPos = 0;
		x = 0;
		y = 0;
		width = 100;
		height = 21;
		
		lastBlinkTime = System.currentTimeMillis();
		this.isPassword = isPassword;
	}
	
	public TextBox(int x, int y, boolean isPassword) {
		text = new Text("");
		passText = new Text("");
		caretPos = 0;
		this.x = x;
		this.y = y;
		width = 100;
		height = 21;
		
		lastBlinkTime = System.currentTimeMillis();
		this.isPassword = isPassword;
	}
	
	public TextBox(String text){
		this.text = new Text(text);
		String passString = "";
		for(int i = 0; i<text.length(); i++){
			passString += TextBox.passchar;
		}
		passText = new Text(passString);
		caretPos = 0;
		x = 0;
		y = 0;
		width = 100;
		height = 21;
		
		lastBlinkTime = System.currentTimeMillis();
		isPassword = false;
	}
	
	public TextBox(String text, int x, int y){
		this.text = new Text(text);
		String passString = "";
		for(int i = 0; i<text.length(); i++){
			passString += TextBox.passchar;
		}
		passText = new Text(passString);
		caretPos = 0;
		this.x = x;
		this.y = y;
		width = 100;
		height = 21;
		
		lastBlinkTime = System.currentTimeMillis();
		isPassword = false;
	}
	
	public TextBox(String text, int x, int y, boolean isPassword){
		this.text = new Text(text);
		String passString = "";
		for(int i = 0; i<text.length(); i++){
			passString += TextBox.passchar;
		}
		passText = new Text(passString);
		caretPos = 0;
		this.x = x;
		this.y = y;
		width = 100;
		height = 21;
		
		lastBlinkTime = System.currentTimeMillis();
		this.isPassword = isPassword;
	}

	public int getWidth() {
		return width;
	}

	public void setWidth(int width) {
		this.width = width;
	}

	public int getHeight() {
		return height;
	}

	public void setHeight(int height) {
		this.height = height;
	}

	public int getX() {
		return x;
	}

	public int getY() {
		return y;
	}

	public void setLocation(int x, int y) {
		this.x = x;
		this.y = y;
	}
	
	public String getText() {
		return text.getText();
	}

	public boolean isDrawingCaret() {
		return drawCaret;
	}

	public void setDrawCaret(boolean drawCaret) {
		this.drawCaret = drawCaret;
	}

	@Override
	public void draw(Graphics2D g) {
		g.setColor(Color.WHITE);
		g.fillRect(x, y, width, height);
		
		g.setColor(Color.BLACK);
		g.drawRect(x, y, width, height);
		
		
		if(isPassword){
			passText.setLocation(x + padding, y + padding);
			passText.draw(g);
		}else{
			text.setLocation(x + padding, y + padding);
			text.draw(g);
		}
		
		if(caretBlink && drawCaret){
			int caretx;
			if(isPassword){
				caretx = x + padding + g.getFontMetrics().stringWidth(passText.getText().substring(0, caretPos));
			}else{
				caretx = x + padding + g.getFontMetrics().stringWidth(text.getText().substring(0, caretPos));
			}
			g.drawLine(caretx, y + padding, caretx, y + height - padding);
		}
	}
	
	public void tick() {
		if(caretBlink){
			if(System.currentTimeMillis() - lastBlinkTime > blinkDelay){
				caretBlink = !caretBlink;
				lastBlinkTime = System.currentTimeMillis();
			}
		}else{
			if(System.currentTimeMillis() - lastBlinkTime > blinkDelay){
				caretBlink = !caretBlink;
				lastBlinkTime = System.currentTimeMillis();
			}
		}
	}
	
	public boolean contains(int x, int y) {
		return (x > this.x && x < this.width + this.x && y > this.y && y < this.height + this.y);
	}
	
	public void mouseClicked(int x, int y) {
		if(!contains(x, y)){
			return;
		}
		
		int textLeft = this.x + padding;
		x = x - textLeft;
		
		String currStr;
		if(isPassword){
			currStr = passText.getText();
		}else{
			currStr = text.getText();
		}
		
		if(currStr == ""){
			return;
		}
		
		FontMetrics mets = text.getFontMetrics();
		
		int sta = 0;
		int mid = currStr.length()/2;
		int end = currStr.length(); 
		
		while(true){
			int distToLeft;
			if(mid > 0){
				distToLeft = Math.abs(x - mets.stringWidth(currStr.substring(0, mid - 1)));
			}else{
				distToLeft = Integer.MAX_VALUE;
			}
			
			int distToMid = Math.abs(x - mets.stringWidth(currStr.substring(0, mid)));
			
			int distToRight;
			if(mid < currStr.length()){
				distToRight = Math.abs(x - mets.stringWidth(currStr.substring(0, mid + 1)));
			}else{
				distToRight = Integer.MAX_VALUE;
			}
			
			if(distToLeft < distToMid && distToLeft < distToRight){
				end = mid;
				mid = (end + sta)/2;
			}else if(distToRight < distToMid && distToRight < distToLeft){
				sta = mid;
				mid = (int) Math.ceil((end + sta)/2.0);
			}else{
				caretPos = mid;
				break;
			}
		}
	}
	
	public void keyReleased(KeyEvent e) {
		System.out.println("typed! " + e.getKeyChar());
		if(e.getKeyCode() == KeyEvent.VK_BACK_SPACE) {
			String oldText = text.getText();

			if(oldText.substring(0, caretPos).length() > 0){
				if(isPassword){
					passText.setText(passText.getText().substring(1));
				}
				
				String newText = oldText.substring(0, caretPos - 1) + oldText.substring(caretPos, oldText.length());
				text.setText(newText);
				caretPos--;
			}
		}else if(e.getKeyCode() == KeyEvent.VK_DELETE){
			String oldText = text.getText();

			if(oldText.substring(caretPos).length() > 0){
				if(isPassword){
					passText.setText(passText.getText().substring(1));
				}
				
				String newText = oldText.substring(0, caretPos) + oldText.substring(caretPos + 1, oldText.length());
				text.setText(newText);
			}
		}else if(e.getKeyCode() == KeyEvent.VK_LEFT){
			if(caretPos > 0){
				caretPos--;
			}
		}else if(e.getKeyCode() == KeyEvent.VK_RIGHT){
			if(caretPos < text.getText().length()){
				caretPos++;
			}
		}else if(e.getKeyChar() != KeyEvent.CHAR_UNDEFINED){
			if(isPassword){
				passText.setText(passText.getText() + passchar);
			}
			
			String oldText = text.getText();
			String newText = oldText.substring(0, caretPos) + e.getKeyChar() + oldText.substring(caretPos, oldText.length());
			text.setText(newText);
			caretPos++;
		}
	}
}
