import edu.nd.cse.paradigms.*;

class CoolSquare extends PESquare {
    private int x_rate = 1;
    private int y_rate = 1;

    public void tick() {
        this.x += this.x_rate;
        this.y += this.y_rate;
    }
}

class MyGame extends PEGame {
    private PEEngine engine;
    private CoolSquare cs;

    public void start() {
        engine = new PEEngine(this);
        cs = new CoolSquare();
        cs.setCenter(10, 10);
        cs.setColor(0x000044);
        cs.setSize(100);
        engine.add(cs);
    }

    public void tick() { }

}

public class EngineTest {
    public static void main(String[] args) {
        MyGame game = new MyGame();
        game.start();
    }
}