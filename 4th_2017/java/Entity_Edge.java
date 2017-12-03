/**
 * 每一条边的实体
 * 
 * @author shizhongwei
 *
 */
public class Entity_Edge {

	private int speed;
	
	private Entity_Point a;
	
	private Entity_Point b;

	public Entity_Edge(Entity_Point a, Entity_Point b, int speed) {
		this.a = a;
		this.b = b;
		this.speed = speed;
	}

	public int getSpeed() {
		return speed;
	}

	public void setSpeed(int speed) {
		this.speed = speed;
	}

	public Entity_Point getA() {
		return a;
	}

	public void setA(Entity_Point a) {
		this.a = a;
	}

	public Entity_Point getB() {
		return b;
	}

	public void setB(Entity_Point b) {
		this.b = b;
	}
	
	

}
