package wordcount;

import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.fs.Path;
import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.lib.input.FileInputFormat;
import org.apache.hadoop.mapreduce.Job;
import org.apache.hadoop.mapreduce.lib.output.FileOutputFormat;

public class Driver {

	public static void main(String[] args) throws Exception {
		
		//create configuration object
		Configuration config=new Configuration();
		
		//create job object
		@SuppressWarnings("deprecation")
		Job j=new Job(config);
		
		//set mapper and reducer classes
		j.setMapperClass(WCMapper.class);
		j.setReducerClass(WCReducer.class);
		
		//set output data type
		j.setOutputKeyClass(Text.class);
		j.setOutputValueClass(IntWritable.class);
		
		//set input and output paths
		FileInputFormat.addInputPath(j, new Path(args[0]));
		FileOutputFormat.setOutputPath(j, new Path(args[1]));
		
		//wait for completion of job
		j.waitForCompletion(true);
	}
}