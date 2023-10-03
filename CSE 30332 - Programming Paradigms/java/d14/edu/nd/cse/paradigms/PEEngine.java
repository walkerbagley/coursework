package edu.nd.cse.paradigms;

import java.awt.Frame;
import java.awt.Graphics;
import java.awt.Color;
import java.awt.event.*;
import java.util.ArrayList;

public class PEEngine extends Frame {
    protected PEGame game;
    protected PEScreen screen;
    protected PECentralClock clock;
    protected int width = 640;
    protected int height = 480;
    protected int titlebarHeight = 0; // varies by OS
    protected ArrayList<PEWorldObject> worldObjects = new ArrayList<PEWorldObject>();
	
    public PEEngine(PEGame game) {
        this.setSize(this.width, this.height);
        this.setResizable(false);

        this.addWindowListener(new WindowAdapter() {
            public void windowClosing(WindowEvent we){
                dispose();
                System.exit(0);
            }
        });

        this.screen = new PEScreen(this.width, this.height);
        this.screen.clear();

        this.setVisible(true);
        this.game = game;
        this.clock = new PECentralClock(this, 10);
    }

    public void add(PEWorldObject wo) {
        this.worldObjects.add(wo);
    }

    public void remove(PEWorldObject wo) {
        this.worldObjects.remove(wo);
    }

    public void tick() {
        this.game.tick();
        this.screen.clear();
        for (PEWorldObject wo : worldObjects) {
            wo.tick();
            this.screen.renderWorldObject(wo);
        }
        this.repaint();
    }

    public void update(Graphics g) {
        this.paint(g);
    }
	
    public void paint(Graphics g) {
        g.drawImage(screen.render(), 0, titlebarHeight, width, height, Color.BLACK, null);
    }
}
