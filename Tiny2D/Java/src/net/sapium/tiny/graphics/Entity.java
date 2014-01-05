package net.sapium.tiny.graphics;

import java.awt.Graphics2D;
import java.awt.image.BufferedImage;
import java.io.IOException;
import java.util.ArrayList;

import javax.imageio.ImageIO;

import net.sapium.tiny.utils.Vec2D;

import org.apache.log4j.Logger;

public class Entity implements Drawable {

    private double x, y;
    private double dx, dy;
    private double angle;
    private int width, height;
    private ArrayList<Animation> animations;
    private int currentAnimation;
    
    /**
     * Constructs an entity with no animation
     * 
     * @param filename path to the sprite
     */
    public Entity(String filename) {
        animations = new ArrayList<Animation>();
        
        BufferedImage image;
        try {
            image = ImageIO.read(Entity.class.getResourceAsStream(filename));
            
            animations.add(new Animation(image, 1, image.getWidth(), image.getHeight()));
            this.width = image.getWidth();
            this.height = image.getHeight();
        } catch (IOException e) {
            Logger.getLogger(Entity.class).error("Failed to load image", e);
        }
        
        x = y = 0;
        dx = dy = 0;
        angle = 0;
    }
    
    /**
     * Construct a new Entity object
     * 
     * @param filename path to the sprite sheet
     * @param numFrames number of frames in each animation row in the sprite sheet
     * @param width width of each frame
     * @param height height of each frame
     */
    public Entity(String filename, int[] numFrames, int width, int height) {
        animations = new ArrayList<Animation>();
        
        BufferedImage image;
        try {
            image = ImageIO.read(Entity.class.getResourceAsStream(filename));
            
            for(int i=0; i<numFrames.length; i++){
                animations.add(new Animation(image.getSubimage(0, i*height, image.getWidth(), height), 
                                             numFrames[i], width, height));
            }
        } catch (IOException e) {
            Logger.getLogger(Entity.class).error("Failed to load image", e);
        }
        
        this.width = width;
        this.height = height;
        
        x = y = 0;
        dx = dy = 0;
    }
    
    @Override
    public void draw(Graphics2D g) {
        g.rotate(angle, this.getX() + this.getWidth()/2, this.getY() + this.getHeight()/2);
        animations.get(currentAnimation).draw(g, (int) x, (int) y);
        g.rotate(-angle, this.getX() + this.getWidth()/2, this.getY() + this.getHeight()/2);
    }

    public void tick() {
        x += dx;
        y += dy;
        
        animations.get(currentAnimation).tick();
    }
    
    public void play(){
        animations.get(currentAnimation).play();
    }
    
    public void pause() {
        animations.get(currentAnimation).pause();
    }
    
    public void restart() {
        animations.get(currentAnimation).restart();
    }
    
    public void setCurrentAnimation(int animation){
        animations.get(currentAnimation).pause();
        animations.get(currentAnimation).restart();
        
        currentAnimation = animation % animations.size();
    }
    
    public double getRotation() {
        return angle;
    }
    
    public void setRotation(double angle) {
        this.angle = angle;
    }

    public double getX() {
        return x;
    }

    public void setX(double x) {
        this.x = x;
    }

    public double getY() {
        return y;
    }

    public void setY(double y) {
        this.y = y;
    }
    
    public int getWidth() {
        return width;
    }

    public int getHeight() {
        return height;
    }

    public void setPos(Vec2D v){
        this.x = v.x;
        this.y = v.y;
    }

    public void setVelocity(Vec2D v) {
        this.dx = v.x;
        this.dy = v.y;
    }

    public Vec2D getVelocity() {
        return new Vec2D.Double(dx, dy);
    }
}
