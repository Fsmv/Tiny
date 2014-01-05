package net.sapium.tiny.utils;

public abstract class Vec2D {
    public static class Double extends Vec2D {
        public Double(double x, double y) {
            this.x = x;
            this.y = y;
        }
        
        public double getx(){
            return x;
        }
        
        public double gety(){
            return y;
        }
    }
    
    public static class Short extends Vec2D {
        public Short(short x, short y) {
            this.x = x;
            this.y = y;
        }
        
        public short getx(){
            return (short) x;
        }
        
        public short gety(){
            return (short) y;
        }
    }
    
    public double x, y;

    public Vec2D() {
        x = y = 0;
    }

    public Vec2D(Vec2D v) {
        this.x = v.x;
        this.y = v.y;
    }

    public void add(Vec2D b) {
        this.x += b.x;
        this.y += b.y;
    }

    public void sub(Vec2D b) {
        this.x -= b.x;
        this.y -= b.y;
    }

    public void mult(double c) {
        this.x *= c;
        this.y *= c;
    }

    public void div(double c) {
        this.x /= c;
        this.y /= c;
    }

    public double dot(Vec2D b) {
        return this.x * b.x + this.y * b.y;
    }
}
