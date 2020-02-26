package weather;

import java.io.IOException;
import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Reducer;

public class WeatherReducer extends Reducer <Text, IntWritable, Text, IntWritable> {

     public void reduce(Text word, Iterable<IntWritable> values, Context con) throws IOException, InterruptedException {

    	 int min=9999, max=0;

    	 //find min & max temp
    	 for(IntWritable temp:values)
    	 {
    		 if((temp.get())<min)
    		 {
    			 min=temp.get();
    		 }
    		 if((temp.get())>max)
    		 {
    			 max=temp.get();
    		 }
    	 }
    	 //write to context object
    	 con.write(word, new IntWritable(max));
    	 con.write(word, new IntWritable(min));
     }
}