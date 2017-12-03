import java.io.BufferedReader;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.Writer;
import java.text.DecimalFormat;
import java.util.ArrayList;
import java.util.List;

/**
 * 
 * @author shizhongwei
 * 
 */
public class MainFrame {
	//边的列表
	public static ArrayList<Entity_Edge> EDGE_LIST = new ArrayList<Entity_Edge>();
	//起点和终点的列表
	public static ArrayList<Entity_Point> SPOINT_LIST = new ArrayList<Entity_Point>();
	public static ArrayList<Entity_Point> EPOINT_LIST = new ArrayList<Entity_Point>();
	
	/**
	 * 主入口
	 * 
	 * @param args
	 *  args[0] 输入文件
	 *  args[1] 输出文件
	 * @throws IOException
	 */
	public static void main(String[] args) throws Exception {
		String inputFile = null;
		String outputFile  = null; 
		if(args == null || args.length !=2)
			System.exit(0);
		inputFile = args[0];
		outputFile =  args[1];
		
		//读取文件，初始化地图和起点、终点列表
		initEntity(inputFile,outputFile);
		
		Searcher searcher = new Searcher();
		long startTime = System.nanoTime();
		searcher.init(EDGE_LIST);
		long endTime = System.nanoTime();
		
		List<SearchResult> checkResult = process(searcher);
		//打印结果文件
		genResultFile((endTime-startTime)/1000,outputFile,checkResult);
	}
	
	/**
	 * 初始化两个全局变量
	 * @param ifile
	 * @param ofile
	 * @throws IOException
	 */
	private static void initEntity(String ifile,String ofile) throws IOException {
		//long startTime = System.nanoTime();
		List<String> infoList = readFileByLines(ifile);
		
		int edgeNum = Integer.parseInt(infoList.get(0));
		for(int i=1;i<(edgeNum+1);i++){
			String[] info = infoList.get(i).split("\t");
			String[] p1 = info[0].split(",");
			String[] p2 = info[1].split(",");
			EDGE_LIST.add(new Entity_Edge(new Entity_Point(Integer.parseInt(p1[0]), Integer.parseInt(p1[1])), new Entity_Point(Integer.parseInt(p2[0]), Integer.parseInt(p2[1])), Integer.parseInt(info[2])));
		}
		
		for(int i=edgeNum+2;i<infoList.size();i++){
			String[] info = infoList.get(i).split("\t");
			String[] p1 = info[0].split(",");
			String[] p2 = info[1].split(",");
			SPOINT_LIST.add(new Entity_Point(Integer.parseInt(p1[0]),Integer.parseInt(p1[1])));
			EPOINT_LIST.add(new Entity_Point(Integer.parseInt(p2[0]),Integer.parseInt(p2[1])));
		}
		//long endTime = System.nanoTime();
		//System.out.println("读取数据文件耗时"+(endTime-startTime)/1000000000+"秒,地图共有"+EDGE_LIST.size()+"个边，共有"+SPOINT_LIST.size()+"对起始点");
	}
	
	/**
	 * 查询主方法
	 * @param searcher
	 * @return
	 * @throws IOException
	 */
	private static List<SearchResult> process(Searcher searcher) throws IOException {
		List<SearchResult> resList = new ArrayList<SearchResult>();
		for (int i=0;i<SPOINT_LIST.size();i++) {
			long startTime = System.nanoTime();
			SearchResult r = searcher.search(SPOINT_LIST.get(i),EPOINT_LIST.get(i));
			long endTime = System.nanoTime();
			r.setRunTime((endTime-startTime)/1000);
			resList.add(r);
		}
		return resList;
	}
	
	/**
	 * 校验结果
	 * @param checkResult
	 * @return
	 * @throws IOException
	 */
	private static void genResultFile(long time,String ofile,List<SearchResult> checkResultList)
			throws Exception {
		StringBuffer sb = new StringBuffer();
		sb.append(checkResultList.size()).append("\n");
		for(SearchResult cr:checkResultList){
			time +=cr.getRunTime();
			sb.append(formatDouble(cr.getRoadTime())).append("\t").append(cr.getPointSize()).append("\t").append(cr.getRoad()).append("\n");
		}
		sb.append(String.valueOf(time));
		WriteFile(ofile, sb);
	}
	
	/**
	 * 浮点数保留6位小数
	 * @return
	 */
	private static String formatDouble(double d){
		return new DecimalFormat("0.000000").format(d); 
	}
	
	
	

	/**
	 * 按照行读取文件
	 * 
	 * @param filePath
	 * @return
	 * @throws IOException
	 */
	private static List<String> readFileByLines(String filePath)
			throws IOException {
		ArrayList<String> lines = new ArrayList<String>();

		BufferedReader br = new BufferedReader(new FileReader(filePath));
		try {
			String line=null;
			while ((line = br.readLine()) != null) {
				if(line != null && !line.trim().equals(""))
				lines.add(line);
			}
		} finally {
			br.close();
		}

		return lines;
	}

	/**
	 * 写文件，覆盖的形式
	 * @param oFile
	 * @param sb
	 * @throws IOException
	 */
	private static void WriteFile(String oFile, StringBuffer sb) throws IOException {
		Writer w = null;
		try {
			w = new FileWriter(oFile, false);
			w.write(sb.toString());
		} finally {
			if (w != null)
				w.close();
		}
	}
	
}
