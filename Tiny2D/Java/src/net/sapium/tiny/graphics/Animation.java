package net.sapium.tiny.graphics;

import java.awt.Graphics2D;
import java.awt.image.BufferedImage;
import java.util.ArrayList;

public class Animation {
    
    public static final int FPS = 10;

    private ArrayList<Sprite> frames;
    private int currentFrame;
    private boolean isPlaying;
    private long lastTick;

    /**
     * Constructs a new Animation object
     * 
     * @param image
     *            row of animation frames
     * @param numframes
     *            number of frames in the row
     * @param width
     *            width of each frame
     * @param height
     *            height of each frame
     */
    public Animation(BufferedImage image, int numframes, int width, int height) {
        frames = new ArrayList<Sprite>();
        currentFrame = 0;
        isPlaying = false;

        for (int i = 0; i < numframes; i++) {
            frames.add(new Sprite(image.getSubimage(i * width, 0, width, height)));
        }
    }

    public void draw(Graphics2D g, int x, int y) {
        frames.get(currentFrame).draw(g, x, y);
    }

    public void nextFrame() {
        currentFrame = (currentFrame + 1) % frames.size();
    }

    public void setCurrentFrame(int frame) {
        currentFrame = frame % frames.size();
    }

    public void play() {
        isPlaying = true;
        lastTick = System.nanoTime();
    }

    public void pause() {
        isPlaying = false;
    }
    
    public void restart() {
        lastTick = System.nanoTime();
        currentFrame = 0;
    }

    public boolean isPlaying() {
        return isPlaying;
    }

    public void tick() {
        if(System.nanoTime() - lastTick > 1000000000/FPS){
            lastTick = System.nanoTime();
            nextFrame();
        }
    }
}
