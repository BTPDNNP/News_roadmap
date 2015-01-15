/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

package Try1;

/**
 *
 * @author Aniket
 */
 
import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.HashMap;
 
public class ReadCVS {
 
  public static void main(String[] args) {
 
	ReadCVS obj = new ReadCVS();
	obj.run();
 
  }
 
  public static HashMap<String, String> run() {
 
	String csvFile = "C://source_info.csv";
	BufferedReader br = null;
	String line = "";
	String cvsSplitBy = ";";
        HashMap<String,String> hm=new HashMap<>();
 
	try {
 
		br = new BufferedReader(new FileReader(csvFile));
		while ((line = br.readLine()) != null) 
                {                    
		        // use comma as separator
			String[] country = line.split(cvsSplitBy);
                        hm.put(country[0],country[1]);
			//System.out.println(country[0]+"   "+country[1]); 
		}
 
	} catch (FileNotFoundException e) {
		e.printStackTrace();
	} catch (IOException e) {
		e.printStackTrace();
	} finally {
		if (br != null) {
			try {
				br.close();
			} catch (IOException e) {
				e.printStackTrace();
			}
		}
	}
 
	System.out.println("Done");
        return hm;
  }
 
}