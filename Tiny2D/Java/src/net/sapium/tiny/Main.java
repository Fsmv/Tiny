package net.sapium.tiny;

import java.applet.Applet;

public class Main extends Applet {
    private static final long serialVersionUID = 1L;

    private static Game game;

    public static void main(String[] args) {
        game = new Game();
        game.createWindow();
        game.start();
    }

    @Override
    public void init() {
        game = new Game();
        
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
