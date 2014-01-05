package net.sapium.tiny;

import java.applet.Applet;

import net.sapium.tiny.utils.InputHandler;

import org.apache.log4j.Level;
import org.apache.log4j.Logger;

public class Main extends Applet {
    private static final long serialVersionUID = 1L;

    public static final String logfile = "output.log";

    private static Logger logger;
    private static Game game;

    public static void main(String[] args) {
        game = new Game();
        game.createWindow();
    }

    @Override
    public void init() {
        logger.setLevel(Level.ALL);

        game = new Game();
        
        InputHandler ih = new InputHandler();
        game.addKeyListener(ih);
        game.addMouseListener(ih);
        game.addMouseMotionListener(ih);
        
        this.add(game);
        game.init();
        
        this.requestFocus();
    }

    @Override
    public void start() {
        game.start();
    }

    @Override
    public void stop() {
        game.stop();
    }
}
