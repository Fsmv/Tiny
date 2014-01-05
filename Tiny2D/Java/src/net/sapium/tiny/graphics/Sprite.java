package net.sapium.tiny.graphics;

import java.awt.Graphics2D;
import java.awt.image.BufferedImage;
import java.io.IOException;

import javax.imageio.ImageIO;

import org.apache.log4j.Logger;

public class Sprite {

    BufferedImage image;
    
    public Sprite(String filepath){
        try {
            image = ImageIO.read(Sprite.class.getResourceAsStream(filepath));
        } catch (IOException e) {
            Logger.getLogger(Sprite.class).error("Could not read image", e);
        }
    }
    
    public Sprite(BufferedImage image){
        this.image = image;
    }
    
    public void draw(Graphics2D g, int x, int y) {
        g.drawImage(image, x, y, null);
    }
    
    public int getWidth(){
        return image.getWidth();
    }
    
    public int getHeight(){
        return image.getHeight();
    }
    
    public void setImage(BufferedImage image){
        this.image = image;
    }
}
