package net.sapium.tiny;

import java.awt.Canvas;
import java.awt.Color;
import java.awt.Component;
import java.awt.Dimension;
import java.awt.Frame;
import java.awt.Graphics2D;
import java.awt.event.WindowEvent;
import java.awt.event.WindowListener;
import java.awt.image.BufferStrategy;
import java.io.IOException;

import javax.imageio.ImageIO;

import net.sapium.tiny.graphics.Screen;
import net.sapium.tiny.utils.InputHandler;

import org.apache.log4j.ConsoleAppender;
import org.apache.log4j.FileAppender;
import org.apache.log4j.Level;
import org.apache.log4j.Logger;
import org.apache.log4j.PatternLayout;

public class Game implements Runnable {
    private String title = "Game";
    private int width = 720;
    private int height = 480;
    private int fps = 60;
    private int tps = 60;
    private Color background;
    private boolean printFPS = true;
    private boolean limitFPS = true;
    private boolean limitTPS = true;

    private String icon = "";
    private String logfile = "output.log";
    
    private Canvas canvas;
    
    private Logger logger = Logger.getLogger(Game.class);
    private Thread thread;
    private boolean running = false;
    private Screen currentScreen;
    
    public Game() {
        canvas = new Canvas();
        canvas.setPreferredSize(new Dimension(width, height));
    }
    
    public Game(String title, int width, int height) {
        this.title = title;
        this.width = width;
        this.height = height;
        
        canvas = new Canvas();
        canvas.setPreferredSize(new Dimension(width, height));
    }

    /**
     * Draws to the screen
     */
    private void render() {
        BufferStrategy bs = canvas.getBufferStrategy();
        if(bs == null){
            canvas.createBufferStrategy(2);
            return;
        }
        
        Graphics2D g = (Graphics2D) bs.getDrawGraphics();
        
        g.clearRect(0, 0, width, height);
        
        currentScreen.draw(g);
        
        g.dispose();
        bs.show();
    }

    /**
     * Processes game updates
     */
    private void tick() {
        currentScreen.tick();
    }

    /**
     * Calls tick, then render at the specified rates
     */
    @Override
    public void run() {
        double unprocessedTicks = 0.0;
        double nsPerTick = 1000000000.0/tps;
        
        double unrenderedFrames = 0.0;
        double nsPerFrame = 1000000000.0/fps;

        long lastTime = System.nanoTime();
        
        long lastFpsTime = System.currentTimeMillis();
        int frameCount = 0;
        int tickCount = 0;
        
        while(running){
            long now = System.nanoTime();
            unprocessedTicks += (now - lastTime) / nsPerTick;
            unrenderedFrames += (now - lastTime) / nsPerFrame;
            lastTime = now;
            
            if(unprocessedTicks >= 1.0 || !limitTPS){
                tick();
                unprocessedTicks -= 1.0;
                tickCount++;
            }
            
            if(unrenderedFrames >= 1.0 || !limitFPS){
                render();
                unrenderedFrames -= 1.0;
                frameCount++;
            }
            
            if(printFPS && System.currentTimeMillis() - lastFpsTime > 1000){
                System.out.println(frameCount + " fps; " + tickCount + " tps");
                frameCount = 0;
                tickCount = 0;
                lastFpsTime = System.currentTimeMillis();
            }
        }
    }
    
    /**
     * Set the window title
     * 
     * must be set before init() is called
     * 
     * Default: "Game"
     * 
     * @param title the window title
     */
    public void setTitle(String title) {
        this.title = title;
    }
    
    /**
     * Set the location of the window icon
     * 
     * must be called before createWindow()
     * 
     * if null don't set an icon
     * 
     * Default: /icon.png
     * 
     * @param path location of the icon image
     */
    public void setIcon(String path) {
        this.icon = path;
    }
    
    /**
     * Sets the frames per second to limit rendering to
     * 
     * if <= 0 unlimited
     * 
     * Default: 60
     * 
     * @param fps the fps to set
     */
    public void setFps(int fps) {
        this.fps = fps;
        
        if(fps <= 0)
            this.limitFPS = false;
        else
            this.limitFPS = true;
    }
    
    /**
     * Sets the number of updates per second to limit to
     * 
     * if <= 0 unlimited
     * 
     * Default: 60
     * 
     * @param tps the tps to set
     */
    public void setTPS(int tps) {
       this.tps = tps;
       
       if(tps <= 0) 
           this.limitTPS = false;
       else
           this.limitTPS = true;
    }

    /**
     * Sets the background color to use when clearing the screen
     * 
     * @param background set the background color to draw
     */
    public void setBackgroundColor(Color background) {
        this.background = background;
        canvas.setBackground(background);
    }

    /**
     * Sets whether or not the engine should print the current fps
     * 
     * Default: true
     * 
     * @param printFPS if true print the fps and tps on stdout
     */
    public void setPrintFPS(boolean printFPS) {
        this.printFPS = printFPS;
    }

    /**
     * Sets the screen to draw
     * 
     * @param s the screen to draw
     */
    public void setCurrentScreen(Screen s){
        currentScreen = s;
    }
    
    /**
     * Set the file Log4J should append to
     * 
     * must be called before init
     * 
     * if null, only log to the console (unnecessary if you're running in an applet)
     * 
     * @param logfile filename to use
     */
    public void setLogfile(String logfile) {
        this.logfile = logfile;
    }
    
    /**
     * @return The component all of the rendering is done onto (add this to your window or applet)
     */
    public Component getDrawComponent() {
        return canvas;
    }
    
    /**
     * Sets log4J to print to the console and to the logfile if set
     * 
     * if running in an applet it does not write to a logfile due to security restrictions
     */
    private void initLog4J() {
        logger.setLevel(Level.INFO);
        
        Logger.getRootLogger().addAppender(new ConsoleAppender(new PatternLayout("%d %-5p [%c] - %m%n")));
        try {
            if(logfile != null)
                Logger.getRootLogger().addAppender(new FileAppender(new PatternLayout("%d %-5p [%c] - %m%n"), logfile));
        } catch (IOException e) {
            logger.error("Could not write log file", e);
        } catch (SecurityException e) {
            logger.debug("Could not create log file. Running in an applet.");
        }
    }
    
    /**
     * Creates a window and initializes the game
     */
    public void createWindow() {
        Frame window = new Frame(this.title);
        
        final Game game = this;
        window.addWindowListener(new WindowListener() {
            @Override
            public void windowClosing(WindowEvent e) {
                game.stop();
                System.exit(0);
            }
            @Override
            public void windowOpened(WindowEvent e) {}
            @Override
            public void windowClosed(WindowEvent e) {}
            @Override
            public void windowIconified(WindowEvent e) {}
            @Override
            public void windowDeiconified(WindowEvent e) {}
            @Override
            public void windowActivated(WindowEvent e) {}
            @Override
            public void windowDeactivated(WindowEvent e) {}
        });
        
        initLog4J();
        
        this.init();
        window.add(canvas);
        
        if(icon != null && icon != "") {
            try {
                window.setIconImage(ImageIO.read(Game.class.getResourceAsStream(icon)));
            } catch (IOException e) {
                logger.error("Could not load icon image", e);
            }
        }

        window.setLocationRelativeTo(null);
        window.setResizable(false);
        window.pack();
        window.setVisible(true);
    }
    
    /**
     * Initializes the game
     */
    public void init() {
        initLog4J();
        
        InputHandler ih = new InputHandler();
        canvas.addKeyListener(ih);
        canvas.addMouseListener(ih);
        canvas.addMouseMotionListener(ih);
        
        logger.debug("init");
        canvas.setBackground(background);
        thread = new Thread(this);
    }

    /**
     * Starts running the game
     */
    public void start() {
        logger.debug("start");
        running = true;
        thread.start();
    }

    /**
     * Stops the game
     */
    public void stop() {
        logger.debug("stop");
        running = false;
    }
}
