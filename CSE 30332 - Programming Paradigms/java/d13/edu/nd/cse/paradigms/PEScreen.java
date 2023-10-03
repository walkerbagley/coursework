package edu.nd.cse.paradigms;

import java.awt.image.BufferedImage;

public class PEScreen {
    private int width, height;
    private int bg;
	
    private BufferedImage image;
    private int[][] pixels;
	
    public PEScreen(int width, int height) {
        this.width = width;
        this.height = height;
		
        this.bg = 0x22CC11; // default background color is green
		
        this.pixels = new int[this.width][this.height];
        this.image = new BufferedImage(this.width, this.height, BufferedImage.TYPE_INT_RGB);
        this.clear();
    }
	
    public void setPixel(int px, int py, int color) {
        if (inBounds(px, py)){
            this.pixels[px][py] = color;
        }
    }
	
    public void clear() {
        for (int i = 0; i < this.width; i++){
            for (int j = 0; j < this.height; j++){
                setPixel(i, j, this.bg);
            }
        }
    }
	
    public boolean inBounds(int px, int py) {
        if (px < 0 || px >= this.width || py < 0 || py >= this.height){
            return false;
        }
        return true;
    }
	
    public BufferedImage render() {
        for (int i = 0; i < this.width; i++){
            for (int j = 0; j < this.height; j++){
                this.image.setRGB(i, j, this.pixels[i][j]);
            }
        }
        return this.image;
    }
}
