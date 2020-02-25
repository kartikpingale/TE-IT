package wordcount;

import java.io.IOException;
import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.io.LongWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Mapper;

public class WCMapper extends Mapper <LongWritable, Text, Text, IntWritable> {
	
	public void map(LongWritable key, Text value, Context con) throws IOException, InterruptedException {

		//text to string
		String info=value.toString();
		//split string into words
		String parts[]=info.split(", ");
		
		//object having value 1
		IntWritable one=new IntWritable(1);
		
		//traverse the words and write to context object
		for(String x:parts)
		{
			Text t=new Text(x);
			con.write(t, one);
		}	
	}
}