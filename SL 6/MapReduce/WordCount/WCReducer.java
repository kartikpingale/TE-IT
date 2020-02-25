package wordcount;

import java.io.IOException;
import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Reducer;

public class WCReducer extends Reducer <Text, IntWritable, Text, IntWritable> {

	public void reduce(Text w, Iterable<IntWritable> values, Context con) throws IOException, InterruptedException {
		
		int sum=0;
		
		//traverse through values and calculate word count
		while(values.iterator().hasNext())
		{
			sum+=1;
			values.iterator().next();
		}
		
		//create object with value sum
		IntWritable p=new IntWritable(sum);
		
		//write to context object
		con.write(w, p);
	}
}