package net.sapium.tiny;

import java.applet.Applet;

import net.sapium.tiny.screens.PlayScreen;

public class Main extends Applet {
    private static final long serialVersionUID = 1L;

    private static Game game;

    public static void main(String[] args) {
        game = new Game();
        game.createWindow();
        
        game.setCurrentScreen(new PlayScreen());
        game.start();
    }

    @Override
    public void init() {
        game = new Game();
        game.setCurrentScreen(new PlayScreen());
        
        add(game.getDrawComponent());
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
