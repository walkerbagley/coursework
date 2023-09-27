import edu.nd.cse.paradigms.*;

public class HardCollider extends Collider{
    protected PEEngine engine;

    public HardCollider(PEEngine engine){
        this.engine = engine;
    }

    public void processCollision(PEWorldObject wo1, PEWorldObject wo2){
        // I wasn't sure whether I should remove the circle on collision or just reset it the the center of the map, so I went with the center so the user could keep "playing"
        // this.engine.remove(wo1);
        wo1.setCenter(this.engine.getWidth() / 2, this.engine.getHeight() / 2);
    }
}
