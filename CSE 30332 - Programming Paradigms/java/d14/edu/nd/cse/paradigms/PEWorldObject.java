package edu.nd.cse.paradigms;

import java.lang.Object;

abstract public class PEWorldObject extends Object{
    protected int color;
    protected int x;
    protected int y;

    public PEWorldObject() {
        this.color = 0xFFFFFF;
        this.x = 0;
        this.y = 0;
    }

    public void setCenter(int x, int y) {
        this.x = x;
        this.y = y;
    }

    public void setColor(int color) {
        this.color = color;
    }

    public int getX() {
        return this.x;
    }

    public int getY() {
        return this.y;
    }

    public abstract void tick();
    public abstract void render(PEScreen screen);
}