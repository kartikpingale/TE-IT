package accesslog;

import java.io.IOException;
import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Reducer;

public class LogReducer extends Reducer <Text,IntWritable,Text,IntWritable> {
	
	public void reduce (Text t, Iterable<IntWritable> values, Context con) throws IOException, InterruptedException {
		
		int sum=0;
		
		//find sum of occurrences
		while(values.iterator().hasNext())
		{
			sum+=1;
			values.iterator().next();
		}
		
		//write ip address and sum to context object
		con.write(t, new IntWritable(sum));
	}
}