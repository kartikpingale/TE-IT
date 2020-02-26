package accesslog;

import java.io.IOException;
import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.io.LongWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Mapper;

public class LogMapper extends Mapper <LongWritable,Text,Text,IntWritable> {
	
	public void map(LongWritable key, Text value, Context con) throws IOException, InterruptedException {
		
		//text to string
		String logs=value.toString();
		//split fields in a record
		String logrecord[]=logs.split(" ");
		//write ip address to context object
		con.write(new Text(logrecord[0]),new IntWritable(1));
	}
}