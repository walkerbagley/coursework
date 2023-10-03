import edu.nd.cse.paradigms.*;

class MyGame extends PEGame {
    private PEEngine engine;

    public void start() {
        engine = new PEEngine(this);
    }
}

public class EngineTest {
    public static void main(String[] args) {
        MyGame game = new MyGame();
        game.start();
    }
}

