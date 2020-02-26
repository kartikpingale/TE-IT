package accesslog;

import java.io.IOException;
import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.fs.FSDataInputStream;
import org.apache.hadoop.fs.FileStatus;
import org.apache.hadoop.fs.FileSystem;
import org.apache.hadoop.fs.Path;
import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Job;
import org.apache.hadoop.mapreduce.lib.input.FileInputFormat;
import org.apache.hadoop.mapreduce.lib.output.FileOutputFormat;

public class LogDriver {

	@SuppressWarnings("deprecation")
	public static void main(String[] args) throws IOException, ClassNotFoundException, InterruptedException {

		//create configuration and job objects
		Configuration conf=new Configuration();
		Job j=new Job(conf);
		
		//set mapper and reducer classes
		j.setMapperClass(LogMapper.class);
		j.setReducerClass(LogReducer.class);
		
		//set output data types
		j.setOutputKeyClass(Text.class);
		j.setOutputValueClass(IntWritable.class);
		
		//set input and output paths
		FileInputFormat.addInputPath(j, new Path(args[0]));
		FileOutputFormat.setOutputPath(j, new Path(args[1]));
		
		//wait for job completion
		j.waitForCompletion(true);
		
		//file system object
		FileSystem fs=FileSystem.get(conf);
		FileStatus[] status=fs.listStatus(new Path("hdfs://localhost:9000"+args[1]));
		FSDataInputStream fd=fs.open(status[1].getPath());
		
		String str=fd.readLine();
		String ip="";
		int max=0;
		
		while(str!=null)
		{
			//split the record
			String parts[]=str.split("	");
			//find most occurred IP
			if(max<Integer.parseInt(parts[1])) {
				
				max=Integer.parseInt(parts[1]);
				ip=parts[0];
			}		
    		str=fd.readLine();
    	}
		
		//print results
		System.out.println("IP address: " + ip);
		System.out.println("No. of occurrences: " + max);
	}
}