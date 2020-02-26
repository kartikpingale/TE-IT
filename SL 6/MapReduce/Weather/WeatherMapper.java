package weather;

import java.io.IOException;
import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.io.LongWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Mapper;

public class WeatherMapper extends Mapper <LongWritable, Text, Text, IntWritable> {

	public void map(LongWritable key, Text value, Context con) throws IOException, InterruptedException {

		//get year
		String year=value.toString().substring(15,19);
		//get temperature
		int temperature=Integer.parseInt(value.toString().substring(87,91));
		
		//clean the data and write to context object
		if((temperature)!=999) {
			con.write(new Text(year), new IntWritable(temperature));
		}
	}
}