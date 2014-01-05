package net.sapium.tiny.screens;

import java.awt.Color;
import java.awt.Graphics2D;
import java.awt.event.KeyEvent;
import java.awt.event.MouseEvent;

import net.sapium.tiny.graphics.Screen;
import net.sapium.tiny.utils.InputHandler;

public class PlayScreen extends Screen {

    public static final int WIDTH = 1000;
    public static final int HEIGHT = 1000;
    
    public PlayScreen() {
        super(HEIGHT, WIDTH);
        
        //qwerty
        InputHandler.registerAction("up", KeyEvent.VK_W);
        InputHandler.registerAction("left", KeyEvent.VK_A);
        InputHandler.registerAction("down", KeyEvent.VK_S);
        InputHandler.registerAction("right", KeyEvent.VK_D);
        
        //dvorak
        InputHandler.registerAction("up", KeyEvent.VK_COMMA);
        InputHandler.registerAction("left", KeyEvent.VK_A);
        InputHandler.registerAction("down", KeyEvent.VK_O);
        InputHandler.registerAction("right", KeyEvent.VK_E);
        
        InputHandler.registerAction("drag", InputHandler.VK_MOUSE_2);
        
        InputHandler.registerScreen(this);
    }

    @Override
    public void render(Graphics2D g) {
        g.setColor(Color.CYAN);
        g.fillRect(0, 0, width, height);
        g.setColor(Color.BLACK);
        g.drawLine(0, 0, width, height);
        g.drawRect(750, 15, 25, 25);
    }

    @Override
    public void tick() {
        if(InputHandler.isDown("up")){
            this.translate(0, -3);
        }else if(InputHandler.isDown("down")){
            this.translate(0, 3);
        }
        
        if(InputHandler.isDown("left")){
            this.translate(-3, 0);
        }else if(InputHandler.isDown("right")){
            this.translate(3, 0);
        }
    }
    
    @Override
    public void mouseMoved(MouseEvent e) {
        if(InputHandler.isDown("drag")){
            this.translate(InputHandler.getChangeInMouse());
        }
    }
    
    @Override
    public void mousePressed(MouseEvent e){
        if(InputHandler.isDown("drag")){
            InputHandler.setMouseMoveable(false);
        }
    }
    
    @Override
    public void mouseReleased(MouseEvent e){
        if(!InputHandler.isDown("drag")){
            InputHandler.setMouseMoveable(true);
        }
    }
}
