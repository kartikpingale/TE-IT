package weather;

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

public class WeatherDriver {

public static void main(String[] args) throws IOException, ClassNotFoundException, InterruptedException {
		
		int max=-9999, min=9999, temp;
		String str, year1 = null, year2=null;
	
		//create configuration & job objects
		Configuration con= new Configuration();
		Job job= new Job(con);
		//set mapper & reducer classes
		job.setMapperClass(WeatherMapper.class);
		job.setReducerClass(WeatherReducer.class);
		//set output data format
		job.setOutputKeyClass(Text.class);
		job.setOutputValueClass(IntWritable.class);
		//set paths
		FileInputFormat.addInputPath(job,new Path(args[0]));
		FileOutputFormat.setOutputPath(job, new Path(args[1]));
		//wait for completion
		job.waitForCompletion(true);		
		
		FileSystem fs=FileSystem.get(con);
		FileStatus[] status=fs.listStatus(new Path("hdfs://localhost:9000"+args[1]));			
		FSDataInputStream fd= fs.open(status[1].getPath());
		
		str=fd.readLine();
		while(str!=null)
		{
			String[] arr=str.split("\t");
			temp=Integer.parseInt(arr[1]);
			
			if(temp>max)
    		{
    			 max=temp;
    			 year1=arr[0];
    		}
    		if(temp<min)
    		{
    			 min=temp;
    			 year2=arr[0];
    		}
    		str=fd.readLine();
		}
		System.out.println("Max temperature is " + max + "  from year " + year1);
		System.out.println("Min temperature is " + min + "  from year " + year2);
	}
}