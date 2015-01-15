/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

package newsandimages;
import java.net.URL;
import java.sql.*;
import de.l3s.boilerpipe.extractors.ArticleExtractor;
import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.sql.Timestamp;
import java.util.Date;
import java.util.concurrent.TimeUnit;
/**
 *
 * @author Mohit
 */
public class Newsandimages {

    public static Connection conn=null;
                    public static Statement st=null;
                    public static ResultSet rs=null; 
   
                    public static void main(String[] args) throws ClassNotFoundException, SQLException, IOException, InterruptedException 
                    {   Integer i1=0;    
        
                         Class.forName("com.mysql.jdbc.Driver");        
                         conn=DriverManager.getConnection("jdbc:mysql://127.0.0.1:3306/news?useUnicode=true&characterEncoding=UTF-8","root","");        
                         st=conn.createStatement();    
                        
                        System.out.println("Connected");
        
                         BufferedReader br = null;
 
                    while(i1!=1)
       {
                        try {
 
                                String sCurrentLine;
 
                                br = new BufferedReader(new FileReader("C://xampp//newsfile.txt"));
                              
                                while ((sCurrentLine = br.readLine()) != null ) 
                                {  
                                    
                                            //System.out.println(sCurrentLine);
                                      String[] array = sCurrentLine.split("##");
                                        int flag=0;
                                
                                         try
                                         {
                                             
                                             
                                             
                                              String p="SELECT headline from newsphoto ";
                                             System.out.println("Query was: "+p);
                                              ResultSet rs = st.executeQuery(p);
                                              System.out.println("1");
                                              String temp="";
                                              temp=array[0].replace("?", "");
                                               
                                               while(rs.next())
                                                {
                                                    if(temp.equals(rs.getString(1)))
                                                    { flag=1;
                                                    }
                                                               
                                                }

                                             
                                             
                                             
                                             String article_text="";
                                             
                                                if(flag==0)
                                               {
                                                 final URL url = new URL(array[1]);
                                                 System.out.println("2");
                                  
                                                    
                                                  article_text = ArticleExtractor.INSTANCE.getText(url);
                                               
                                                
                                          System.out.println("3");
                                         //String p="INSERT INTO news (headline,url,date,article,processed) VALUES( '"+array[0]+"','"+array[1]+"','"+array[2]+"','"+article_text+"','n'";
                                         //stmt.executeUpdate(p);
                                                // System.out.println(array[0]+" "+array[1]+" "+array[2]+article_text+" "+"n");
                                                
                                               
                                                String sql = "insert into newsphoto (headline, url,date,article,processed,normaldate,headlineid)" +
                                                                 " VALUES (?, ?, ?, ?, ?, ?, ?)";
                                                PreparedStatement preparedStatement = conn.prepareStatement(sql);
                                                   preparedStatement.setString(1, temp);
                                                   preparedStatement.setString(2, array[1]);
                                                   preparedStatement.setString(3, array[2]);
                                                   preparedStatement.setString(4, article_text);
                                                   preparedStatement.setString(5, "n");
                                                   preparedStatement.setString(6, array[3]);
                                                   preparedStatement.setString(7, array[4]);
                                                   preparedStatement.execute(); 
                                                   System.out.println("Inserted records into the table...");

                                        
                                         
                                            }
                                         }
                                         catch(Exception e)
                                         {
                                            //System.out.println("time out ");
                                             e.printStackTrace();
                                         }
                               
                                    }
                                
                                
                                
                                System.out.println("Sleeping");
             Thread.sleep(3600000);
             System.out.println("Wake up");
 
                        } 
                        catch (IOException e) 
                        {
			e.printStackTrace();
                        }
        
                   
       
        
       }
                        
             
             
        
            
        
        
       
       
        // TODO code application logic here
            }
    
            }