/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

//package Try1;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.sql.Timestamp;
import java.util.Date;
import java.util.HashMap;
import java.util.concurrent.TimeUnit;

/**
 *
 * @author Aniket
 */
public class Headlines 
{
     public static Connection conn=null;
     public static Statement st=null;
     public static ResultSet rs=null; 
     //public static HashMap<String,String> hm=null;
     public static void main(String[] args) throws ClassNotFoundException, SQLException, IOException, InterruptedException 
    {
       Integer i1=0;    
       String fname="/home/nitin/Desktop/News/newsfile.txt";
       File f1=new File(fname);
      
       if(f1.exists())
           f1.delete();
       
       while(i1!=1)
       {
           try{
             BufferedWriter bw=new BufferedWriter(new FileWriter(f1));
             Date date= new java.util.Date();
             Timestamp t1=new Timestamp(date.getTime());                 //current time
         
             Long l=t1.getTime()-TimeUnit.MINUTES.toMillis(30);   //25 minutes earlier time in milli
             Long l1=t1.getTime();

             Date dt=new Date(l);        
             Date dt1=new Date(l1);
            //time stamp curr-30 min
             Timestamp t2=new Timestamp(dt.getTime());
             Timestamp t3=new Timestamp(dt1.getTime());
             
             
            // String s1="select DISTINCT(newsHeadline),start_time_stamp,end_time_stamp,URL,source_id from local_information_repository, source_info where start_time_stamp >='"+t2.toString()+"'  AND start_time_stamp <= '"+t3.toString()+"' AND source_info.category='business' AND  local_information_repository.source_id=source_info.id ";

 //String s1="select DISTINCT(newsHeadline),start_time_stamp,URL,source_id from local_information_repository where start_time_stamp >='"+t2.toString()+"'  AND start_time_stamp <= '"+t3.toString()+"'";
String s1="select DISTINCT(newsHeadline) from local_information_repository";
             System.out.println("\n\n");
             System.out.println("Current Timestamp:"+t1);
             System.out.println("Fetched Timestamp:"+t2);
             System.out.println("Query Fired : "+s1);
             System.out.println("\n\n"); 
             
             Class.forName("com.mysql.jdbc.Driver");        
             conn=DriverManager.getConnection("jdbc:mysql://192.168.111.105:3306/newsdata?useUnicode=true&characterEncoding=UTF-8","bazir","bishnoi");
             st=conn.createStatement();
             System.out.println("Connected");
             ResultSet rs = st.executeQuery(s1);            
                                       
             while(rs.next())
             {
                 System.out.println("nitin");
                 String url=rs.getString("URL");
                 int i=url.length();
                 if(url.charAt(i-1)=='m' && url.charAt(i-2)=='o' && url.charAt(i-3)=='c' && url.charAt(i-4)=='.')
                 {
                     
                 }
                 else if(rs.getString("URL")==null || rs.getString("URL").endsWith(".com") || rs.getString("URL").startsWith("http://t.co"))
                 {
                 }
                 else if(rs.getString("URL").startsWith("http://"))
                 {
                     bw.write(rs.getString(1)+"##"+rs.getString("URL")+"##"+(rs.getTimestamp(2).getTime()/1000L)+"##"+rs.getTimestamp(2)+"##"+rs.getString(5));
                     bw.newLine(); 
                     
                 }else
                 {                     
                      String temp1;
                      
                     if(rs.getString("URL").startsWith("/"))
                     {
                         temp1=url.substring(1,url.length()-1);
                     }
                     else 
                     {
                         temp1=url;
                     }
                             
                     
                     
                     String ty=Integer.toString(rs.getInt("source_id"));
                     //System.out.println("source_id : "+ty );
                     String temp=run(ty);
                     temp=temp.concat(temp1);
                     bw.write(rs.getString(1)+"##"+temp+"##"+((rs.getTimestamp(2).getTime())/1000L)+"##"+rs.getTimestamp(2)+"##"+rs.getString(5));
                     bw.newLine();
                     //System.out.println("with / only");
                     
                 }
             }
             bw.close();
           }catch(Exception e)
           {
               e.printStackTrace();
           }             
             System.out.println("Sleeping");
             Thread.sleep(3600000);
             System.out.println("Wake up");
             
             if(f1.exists())
                 f1.delete();
        }
        
    }
     
       public static String run(String source_id) {
        String tr=null;  
	String csvFile = "/home/nitin/Desktop/News/source_info.csv";
	BufferedReader br = null;
	String line = "";
	String cvsSplitBy = ";";
        source_id="\""+source_id+"\"";
        //HashMap<String,String> hm=new HashMap<>();
 
	try {
 
		br = new BufferedReader(new FileReader(csvFile));
		while ((line = br.readLine()) != null) 
                {                    
		        // use comma as separator
			String[] country = line.split(cvsSplitBy);
                       // System.out.println("1:"+country[0]+"country[1]"+country[1]);
                        //hm.put(country[0],country[1]);
			if(source_id.equals(country[0]))
                        {  //System.out.println("Matched");
                            
                            tr=country[1];
                            tr=tr.substring(1,tr.length()-2);
                          //  System.out.println("tr:"+tr);
                            break;
                            
                            
                        }
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
 
	//System.out.println("Done");
        return tr;
//        return hm;
  }

}    
