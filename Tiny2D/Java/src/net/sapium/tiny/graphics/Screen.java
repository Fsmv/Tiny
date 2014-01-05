package net.sapium.tiny.graphics;

import java.awt.Graphics2D;
import java.awt.event.KeyEvent;
import java.awt.event.MouseEvent;

import net.sapium.tiny.utils.Vec2D;

public abstract class Screen implements Drawable {
    protected int width, height;
    private int offsetx, offsety;

    public Screen(int width, int height) {
        this.width = width;
        this.height = height;
        this.offsetx = this.offsety = 0;
    }
    
    public void draw(Graphics2D g) {
        g.translate(-offsetx, -offsety);
        render(g);
    }
    
    /**
     * Called periodically, draw things here
     */
    public abstract void render(Graphics2D g);
    
    /**
     * Called periodically, do calculations updates here
     */
    public abstract void tick();
    
    /**
     * Translates the screen so that when it is drawn the entire thing will be translated
     * 
     * @param dx amount to translate in the x direction
     * @param dy amount to translate in the y direction
     */
    public void translate(int dx, int dy) {
        offsetx += dx;
        offsety += dy;
    }
    
    /**
     * Translates the screen so that when it is drawn the entire thing will be translated
     * 
     * @param t vector to move along
     */
    public void translate(Vec2D t) {
        translate((int)t.x, (int)t.y);
    }

    /**
     * @return the width
     */
    public int getWidth() {
        return width;
    }
    
    /**
     * @return the height
     */
    public int getHeight() {
        return height;
    }

    /**
     * @return the offsetx
     */
    protected int getOffsetx() {
        return offsetx;
    }

    /**
     * @param offsetx the offsetx to set
     */
    protected void setOffsetx(int offsetx) {
        this.offsetx = offsetx;
    }

    /**
     * @return the offsety
     */
    protected int getOffsety() {
        return offsety;
    }

    /**
     * @param offsety the offsety to set
     */
    protected void setOffsety(int offsety) {
        this.offsety = offsety;
    }
    
    /**
     * Unlike the normal keyPressed method, this is guaranteed to be called only once per key press
     */
    public void keyPressed(KeyEvent e) {
    }
    
    public void keyReleased(KeyEvent e) {
    }
    
    public void keyTyped(KeyEvent e) {
    }
    
    public void mouseClicked(MouseEvent e) {
    }
    
    public void mousePressed(MouseEvent e) {
    }

    public void mouseReleased(MouseEvent e) {
    }
    
    public void mouseMoved(MouseEvent e) {
    }
}
