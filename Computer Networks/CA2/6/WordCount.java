import java.io.*;
import java.util.HashMap;
import java.util.HashSet;
import java.util.StringTokenizer;


import org.apache.hadoop.conf.*;
import org.apache.hadoop.conf.Configured;
import org.apache.hadoop.fs.Path;
import org.apache.hadoop.fs.FileSystem;
import org.apache.hadoop.fs.*;
import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Job;
import org.apache.hadoop.mapreduce.Mapper;
import org.apache.hadoop.mapreduce.Reducer;
import org.apache.hadoop.mapreduce.lib.input.FileInputFormat;
import org.apache.hadoop.mapreduce.lib.output.FileOutputFormat;
import java.io.BufferedOutputStream;
import java.io.FileOutputStream;
import java.io.InputStream;
import java.io.OutputStream;
import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.conf.Configured;
import org.apache.hadoop.fs.FileSystem;
import org.apache.hadoop.fs.Path;
import org.apache.hadoop.io.IOUtils;
import org.apache.hadoop.util.Tool;
import org.apache.hadoop.util.ToolRunner;
import javafx.util.Pair;

import javax.naming.Context;


public class WordCount {

    public static class TokenizerMapper
            extends Mapper<Object, Text, Text, IntWritable>{

        public static final String FS_PARAM_NAME = "fs.defaultFS";

        private HashSet<String> stopWords = new HashSet<String>();

        @Override
        public void setup(Context context) throws IOException,
                InterruptedException {

            Path inputPath = new Path("/user/sina/data/stop-words.keys");
            Configuration conf = context.getConfiguration();
            FileSystem fs = FileSystem.get(conf);
            InputStream is = fs.open(inputPath);

            try (BufferedReader br = new BufferedReader(new InputStreamReader(is))) {
                String line = "test";
                while (line != null) {
                    this.stopWords.add(line);
                    line = br.readLine();
                }
            }
        }

        private final static IntWritable one = new IntWritable(1);
        private Text word = new Text();

        public void map(Object key, Text value, Context context
        ) throws IOException, InterruptedException {
            StringTokenizer itr = new StringTokenizer(value.toString());
            while (itr.hasMoreTokens()) {
                word.set(itr.nextToken());

                boolean isNotInStopWords = !this.stopWords.contains(word.toString());
                boolean allLetters = word.toString().chars().allMatch(Character::isLetter);
                if(isNotInStopWords && allLetters) {
                    String tmp = word.toString().toLowerCase();
                    context.write(new Text(tmp), one);
                }
            }
        }
    }

    public static class IntSumReducer
            extends Reducer<Text,IntWritable,Text,IntWritable> {
        private IntWritable result = new IntWritable();
        Pair <String, Integer> mostRepeated1 = new Pair <String, Integer> ("", 0);
        Pair <String, Integer> mostRepeated2 = new Pair <String, Integer> ("", 0);

        public void reduce(Text key, Iterable<IntWritable> values,
                           Context context
        ) throws IOException, InterruptedException {

            int sum = 0;
            for (IntWritable val : values) {
                sum += val.get();
            }
            result.set(sum);
            context.write(key, result);

            if(sum > mostRepeated1.getValue()) {
                mostRepeated2 = mostRepeated1;
                mostRepeated1 = new Pair<String, Integer>(key.toString(), sum);
            } else if(sum > mostRepeated2.getValue()) {
                mostRepeated2 = new Pair<String, Integer>(key.toString(), sum);
            }

        }

        @Override
        protected void cleanup(Context context) throws IOException, InterruptedException {
            Configuration conf = context.getConfiguration();
            Path outputPath = new Path("/user/sina/result/" + conf.get("resultPath"));

            FileSystem fs = FileSystem.get(conf);

            OutputStream os;
            if (fs.exists(outputPath)) {
                os = fs.append(outputPath);
            } else {
                os = fs.create(outputPath);
            }

            try (Writer w = new OutputStreamWriter(os, "UTF-8")) {
                w.write("most repeated 1: " + mostRepeated1.getKey() + " -> " + mostRepeated1.getValue().toString());
                w.write("\n");
                w.write("most repeated 2: " + mostRepeated2.getKey() + " -> " + mostRepeated2.getValue().toString());
                w.write("\n");
            }
        }
    }

    public static void main(String[] args) throws Exception {
        Configuration conf = new Configuration();
        conf.set("resultPath", args[2]);
        Job job = Job.getInstance(conf, "word count");
        job.setJarByClass(WordCount.class);
        job.setMapperClass(TokenizerMapper.class);
        job.setCombinerClass(IntSumReducer.class);
        job.setReducerClass(IntSumReducer.class);
        job.setOutputKeyClass(Text.class);
        job.setOutputValueClass(IntWritable.class);
        job.setNumReduceTasks(Integer.parseInt(args[3]));
        FileInputFormat.addInputPath(job, new Path(args[0]));
        FileOutputFormat.setOutputPath(job, new Path(args[1]));
        System.exit(job.waitForCompletion(true) ? 0 : 1);
    }
}