import java.util.ArrayList;

/**
 * 实现init和search方法
 * 其中search方法返回参数SearchResult的roadtime和addNextPoint需要被赋值和调用
 * @author shizhongwei
 *
 */
public class Searcher {
	//地图上所有的边
	private ArrayList<Entity_Edge> edgeList;
	
	
	/**
	 * 初始化操作,如创建索引等
	 */
	public void init(ArrayList<Entity_Edge> edgeList){
		this.edgeList = edgeList;
		
	}
	
	/**
	 * 根据起点、终点和速度计算最短路径，越快越好
	 * 如果有多条路径的时间一样，随机取一条即可
	 * @param sepoint
	 * @return
	 */
	public SearchResult search(Entity_Point start,Entity_Point b){
		
		double roadTime = 7.3345;
		SearchResult r = new SearchResult(roadTime);//计算总路径所耗时间
		
		r.addNextPoint(new Entity_Point(1, 2));
		r.addNextPoint(new Entity_Point(2,3));
		r.addNextPoint(new Entity_Point(3, 4));
		r.addNextPoint(new Entity_Point(4, 5));
		return r;
	}

}
