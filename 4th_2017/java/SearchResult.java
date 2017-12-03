import java.util.ArrayList;

/**
 * 
 * @author shizhongwei
 *
 */
public class SearchResult {
	
	private long runTime;//程序运行时间
	private double roadTime;//路径花费时间
	private ArrayList<Entity_Point> pointList = new ArrayList<Entity_Point>();//路径上的点
	

	
	public SearchResult(double roadTime) {
		this.roadTime = roadTime;
	}
	
	
	public long getRunTime() {
		return runTime;
	}


	public void setRunTime(long runTime) {
		this.runTime = runTime;
	}
	
	


	public double getRoadTime() {
		return roadTime;
	}


	public void setRoadTime(double roadTime) {
		this.roadTime = roadTime;
	}


	/**
	 * 获取完整的路径的点
	 * @return
	 * @throws Exception
	 */
	public String getRoad() throws Exception{
		StringBuffer sb = new StringBuffer();
		for(Entity_Point p:pointList){
			sb.append(p.getX()+","+p.getY()+"\t");
		}
		return sb.toString();
	}
	
	/**
	 * 添加一个新的点
	 * @param p
	 */
	public void addNextPoint(Entity_Point p){
		pointList.add(p);
	}
	
	public int getPointSize(){
		return pointList.size();
	}
	
}