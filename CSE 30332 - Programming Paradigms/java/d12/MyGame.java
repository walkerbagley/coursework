import edu.nd.cse.paradigms.*;
import java.util.List;
import java.util.ArrayList;
import java.io.*;

public class MyGame extends PEGame{

	protected PEEngine engine;
	private HardCollider collider;
	private PECircle circle;
	private PESquare ob;

	public MyGame(){
	}

	public void start(){
		this.engine = new PEEngine(this);
		this.collider = new HardCollider(this.engine);
		this.circle = new PECircle();
		this.ob = new PESquare();

		this.circle.setRadius(25);
		this.circle.setColor(0xFFFFFF);
		this.circle.setCenter(this.engine.getWidth() / 2, this.engine.getHeight() / 2);
		this.engine.add(this.circle);

		this.ob.setSize(400);
		this.ob.setColor(0x8888FF);
		this.ob.setCenter(this.engine.getWidth(), this.engine.getHeight());
		this.engine.add(this.ob);
	}

	public void tick(){
	}

	public void keyPressed(int k){
		int x = this.circle.getX();
		int y = this.circle.getY();

        if (k == 40){
            y++;
        }
		else if (k == 39){
			x++;
		}
		else if (k == 38){
			y--;
		}
		else if (k == 37){
			x--;
		}
		
		this.circle.setCenter(x, y);
	}

	public void collisionDetected(List<PEWorldObject> worldObjects){
		if (engine.detectCollision(worldObjects.get(0), worldObjects.get(1))){
			collider.processCollision(worldObjects.get(0), worldObjects.get(1));
		}
	}
}