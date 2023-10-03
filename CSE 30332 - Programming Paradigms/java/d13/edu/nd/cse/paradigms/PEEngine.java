package edu.nd.cse.paradigms;

import java.awt.Frame;
import java.awt.Graphics;
import java.awt.Color;
import java.awt.event.*;

public class PEEngine extends Frame {
    protected PEGame game;
    protected PEScreen screen;
    protected int width = 640;
    protected int height = 480;
    protected int titlebarHeight = 0; // varies by OS
	
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
    }
	
    public void paint(Graphics g) {
        g.drawImage(screen.render(), 0, titlebarHeight, width, height, Color.BLACK, null);
    }
}
