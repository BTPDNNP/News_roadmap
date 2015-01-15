/* Standard C++ includes */
#include <stdlib.h>
#include <iostream>
#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <mysql_connection.h>
#include <cppconn/prepared_statement.h>
#include <map>
#include <vector>
#include <fstream>
#include <cstdio>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <cstdlib>
#include <cmath>
#include<fstream>
/* Libraries come to end */

using namespace std;

/* declaration of various variables */
map<string,int> headlineword;
map<string,int> grammer;
map<pair<string,int>,int> word_freq;
int article_no=0;
int total_word_count=0;
int word_count;


/* decleration ends */


void create_grammer_map()
{
 // fstream f1;
	
 freopen("grammer.txt","r",stdin);
 char a[110]; 
 while(scanf("%s",a)!=EOF)
 {
	if(a[0]>='a'&&a[0]<='z')
		grammer[a]++;
	else if(a[0]>='A'&&a[0]<='Z')
		{
			a[0]='a'+int(a[0]-'A');
			grammer[a]++;
			
		}
	

 }
 fclose(stdin);
	

}
int headline_count=0;
int main(void)
{
	
  create_grammer_map();
  
  sql::Driver *driver;
  sql::Connection *con;
  sql::Statement *stmt;
  sql::ResultSet *res;
  sql::PreparedStatement  *prep_stmt;
  driver = get_driver_instance();
  con = driver->connect("localhost", "root", "nitish2312");
  /* Connect to the MySQL test database */
  con->setSchema("finance_news_copy2");
  stmt = con->createStatement();
  res = stmt->executeQuery("SELECT * from News_articles");
  int i=0;
  int page_cnt=0;
  while (res->next()) {
	page_cnt++;
	article_no++;
	word_count=0;
   	string headline = res->getString("Headline");
	string article = res->getString("Article");
	string filename = res->getString("End_time");
	ofstream outfile;
      
	string f="";
	for(int i=0;i<10;i++)
		f+=filename[i];
        f+=".txt";
        outfile.open(f.c_str(),ios::app);
	/*
		To do 
		1) Map of words from title
		2) Map of words from Url
		3) If not co-related, Replace Url with headline
	`	4) after this, merge a single day document into one and write a system call to write it into a file
		5) mallet

	*/
	string final= headline;
        outfile<<final<<endl;
        
	
	//system(("echo abc  >> /home/nitin/Desktop/News/test3/"+f+".txt").c_str());
	

  }
  delete res;
  delete stmt;
  delete con;
}
