import edu.nd.cse.paradigms.*;
import java.util.List;
import java.util.ArrayList;

public class MyGame extends PEGame{

	protected PEEngine engine;
	private PECircle circle;

	public MyGame(){
	}

	public void start(){
		this.engine = new PEEngine(this);
		this.circle = new PECircle();

		this.circle.setRadius(25);
		this.circle.setColor(0xFFFFFF);
		this.circle.setCenter(50, 50);
		this.engine.add(this.circle);
	}

	public void tick(){
	}

	public void keyPressed(int k){
		int x = this.circle.getX();
		int y = this.circle.getY();

        if (k == 40){
            y++;
        }
		
		this.circle.setCenter(x, y);
	}

	public void collisionDetected(List<PEWorldObject> worldObjects){
	}
}