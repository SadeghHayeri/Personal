import java.io.*;
import java.net.HttpURLConnection;
import java.net.URL;

public class Crawler {

    static String getHTML(String urlToRead) throws Exception {
        StringBuilder result = new StringBuilder();
        URL url = new URL(urlToRead);
        HttpURLConnection conn = (HttpURLConnection) url.openConnection();
        conn.setRequestMethod("GET");
        BufferedReader rd = new BufferedReader(new InputStreamReader(conn.getInputStream()));
        String line;
        while ((line = rd.readLine()) != null) {
            result.append(line);
        }
        rd.close();
        return result.toString();
    }

    public static void main(String[] args) throws Exception {
        StringBuilder finalText = new StringBuilder();

        try (BufferedReader br = new BufferedReader(new FileReader(args[0]))) {
            String line = br.readLine();
            while (line != null && finalText.length() <= 10000000) {
                try {
                    String url = "https://en.wikipedia.org/wiki/" + line + "?action=raw";
                    String out = getHTML(url);
                    String result = out.split("==References==")[0];
                    finalText.append(result);
                    System.out.println(finalText.length());
                    line = br.readLine();
                } catch (Exception e) {}
            }

            try (Writer writer = new BufferedWriter(new OutputStreamWriter(
                    new FileOutputStream("raw.data"), "utf-8"))) {
                for (int i = 0; i < 26; i++)
                    writer.write(finalText.toString());
            }

            String[] hdfArgs = new String[2];
            hdfArgs[0] = "raw.data";
            hdfArgs[1] = "/user/data/raw.data";
            HdfsWriter.main(hdfArgs);
        }
    }
}