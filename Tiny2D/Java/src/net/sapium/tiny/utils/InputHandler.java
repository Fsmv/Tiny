package net.sapium.tiny.utils;

import java.awt.AWTException;
import java.awt.Robot;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.awt.event.MouseMotionListener;
import java.util.HashMap;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;
import java.util.concurrent.ConcurrentHashMap;

import net.sapium.tiny.graphics.Screen;
import net.sapium.tiny.utils.Vec2D;

import org.apache.log4j.Logger;

public class InputHandler implements KeyListener, MouseListener, MouseMotionListener {

    public static final int VK_MOUSE_1 = 7894561;
    public static final int VK_MOUSE_2 = 7894562;
    public static final int VK_MOUSE_WHEEL = 7894563;

    public static Map<String, List<Integer>> actions;
    public static Map<Integer, Boolean> keymap;
    public static List<Screen> screens;

    private static int mousex = 0;
    private static int mousey = 0;
    private static int dx = 0;
    private static int dy = 0;
    private static int sx = 0;
    private static int sy = 0;
    private static boolean letMouseMove = true;
    private static Robot robot;

    private static Logger logger = Logger.getLogger(InputHandler.class);

    public InputHandler() {
        screens = new LinkedList<Screen>();

        try {
            robot = new Robot();
        } catch (AWTException e) {
            logger.error("Could not capture mouse", e);
        }

        clearActions();
    }
    
    public static void registerAction(String action, int keyCode) {
        if(!actions.containsKey(action)) {
            actions.put(action, new LinkedList<Integer>());
        }

        actions.get(action).add(keyCode);
        registerButton(keyCode);
    }
    
    public static void clearActions() {
        actions = new HashMap<String, List<Integer>>();
        keymap = new ConcurrentHashMap<Integer, Boolean>(307);
        
        registerButton(VK_MOUSE_1);
        registerButton(VK_MOUSE_2);
        registerButton(VK_MOUSE_WHEEL);
    }

    private static void registerButton(int keyCode) {
        keymap.put(keyCode, false);
    }

    public static void registerScreen(Screen screen) {
        synchronized(screens) {
            screens.add(screen);
        }
    }

    public static void deregisterScreen(Screen screen) {
        synchronized(screens) {
            screens.remove(screen);
        }
    }

    public static boolean isDown(String action) {
        List<Integer> keys = actions.get(action);
        if(keys == null) {
            logger.error("Key not registered; returned false");
            return false;
        }
        
        boolean result = false;
        
        Iterator<Integer> it = keys.iterator();
        while(it.hasNext() && !result) {
            result = keymap.get(it.next()) || result;
        }
        
        return result;
    }

    public static void setMouseMoveable(boolean letMouseMove) {
        InputHandler.letMouseMove = letMouseMove;
    }

    public static Vec2D getChangeInMouse() {
        return new Vec2D.Double(dx, dy);
    }

    public static Vec2D getMousePos() {
        return new Vec2D.Double(mousex, mousey);
    }

    private void handleMouseMotion(MouseEvent arg0) {
        dx = arg0.getX() - mousex;
        dy = arg0.getY() - mousey;

        if (letMouseMove) {
            mousex = arg0.getX();
            mousey = arg0.getY();

            sx = arg0.getXOnScreen();
            sy = arg0.getYOnScreen();
        } else {
            if (robot != null) {
                robot.mouseMove(sx, sy);
            } else {
                logger.warn("Robot is not available");
                letMouseMove = true;
            }
        }
        
        synchronized(screens) {
            Iterator<Screen> it = screens.iterator();
            while (it.hasNext()) {
                it.next().mouseMoved(arg0);
            }
        }
    }

    @Override
    public void mouseMoved(MouseEvent arg0) {
        handleMouseMotion(arg0);
    }

    @Override
    public void mouseDragged(MouseEvent arg0) {
        handleMouseMotion(arg0);
    }

    @Override
    public void mousePressed(MouseEvent arg0) {
        switch (arg0.getButton()) {
        case MouseEvent.BUTTON1:
            keymap.put(VK_MOUSE_1, true);
            break;
        case MouseEvent.BUTTON3:
            keymap.put(VK_MOUSE_2, true);
            break;
        case MouseEvent.BUTTON2:
            keymap.put(VK_MOUSE_WHEEL, true);
            break;
        default:
            if (arg0.getButton() != MouseEvent.NOBUTTON) {
                if (keymap.containsKey(arg0.getButton())) {
                    keymap.put(arg0.getButton(), true);
                }
            }
        }
        
        synchronized(screens) {
            Iterator<Screen> it = screens.iterator();
            while (it.hasNext()) {
                it.next().mousePressed(arg0);
            }
        }
    }

    @Override
    public void mouseReleased(MouseEvent arg0) {
        switch (arg0.getButton()) {
        case MouseEvent.BUTTON1:
            keymap.put(VK_MOUSE_1, false);
            break;
        case MouseEvent.BUTTON3:
            keymap.put(VK_MOUSE_2, false);
            break;
        case MouseEvent.BUTTON2:
            keymap.put(VK_MOUSE_WHEEL, false);
            break;
        default:
            if (arg0.getButton() != MouseEvent.NOBUTTON) {
                if (keymap.containsKey(arg0.getButton())) {
                    keymap.put(arg0.getButton(), false);
                }
            }
        }

        synchronized(screens) {
            Iterator<Screen> it = screens.iterator();
            while (it.hasNext()) {
                it.next().mouseReleased(arg0);
            }
        }
    }

    @Override
    public void keyPressed(KeyEvent arg0) {
        if (keymap.containsKey(arg0.getKeyCode())) {
            keymap.put(arg0.getKeyCode(), true);
        }
        
        synchronized(screens) {
            Iterator<Screen> it = screens.iterator();
            while (it.hasNext()) {
                it.next().keyPressed(arg0);
            }
        }
    }

    @Override
    public void keyReleased(KeyEvent arg0) {
        if (keymap.containsKey(arg0.getKeyCode())) {
            keymap.put(arg0.getKeyCode(), false);
        }

        synchronized(screens) {
            Iterator<Screen> it = screens.iterator();
            while (it.hasNext()) {
                it.next().keyReleased(arg0);
            }
        }
    }

    @Override
    public void keyTyped(KeyEvent arg0) {
        synchronized(screens) {
            Iterator<Screen> it = screens.iterator();
            while (it.hasNext()) {
                it.next().keyTyped(arg0);
            }
        }
    }

    @Override
    public void mouseClicked(MouseEvent arg0) {
        synchronized(screens) {
            Iterator<Screen> it = screens.iterator();
            while (it.hasNext()) {
                it.next().mouseClicked(arg0);
            }
        }
    }

    @Override
    public void mouseEntered(MouseEvent arg0) {
    }

    @Override
    public void mouseExited(MouseEvent arg0) {
    }
}
