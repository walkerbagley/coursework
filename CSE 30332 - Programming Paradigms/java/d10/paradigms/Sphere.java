package paradigms;

import java.io.*;
import java.lang.*;

public class Sphere{
    double radius;

    public Sphere(double r) {
        radius = r;
    }

    public void setRadius(double r) {
        radius = r;
    }

    public double getRadius() {
        return radius;
    }

    public double getVolume() {
        return (4 * Math.PI * Math.pow(radius, 3)) / 3;
    }
    
    public double getSurfaceArea() {
        return (4 * Math.PI * Math.pow(radius, 2));
    }
    
    public String toString() {
        return String.format("Radius:        %.1f\nVolume:        %f\nSurface Area:  %f\n", radius, getVolume(), getSurfaceArea());
    }
}