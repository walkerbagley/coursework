package edu.nd.cse.paradigms;

public class PESquare extends PEWorldObject {
    protected int size;

    public PESquare() {
        this.size = 10;
    }

    public void tick() {}

    public void setSize(int size) {
        this.size = size;
    }

    public void render(PEScreen screen) {
        for (int i = -(size / 2); i < size / 2; i++){
            for (int j = -(size / 2); j < size / 2; j++){
                screen.setPixel(this.getX() + i, this.getY() + j, this.color);
            }
        }
    }
}