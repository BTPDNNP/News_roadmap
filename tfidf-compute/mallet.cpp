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
  int count=0;
  create_grammer_map();
  sql::Driver *driver;
  sql::Connection *con;
  sql::Statement *stmt;
  sql::ResultSet *res;
  sql::PreparedStatement  *prep_stmt;
  /* Create a connection */
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
	string date = res->getString("End_time");
	
	/*
		To do 
		1) Map of words from title
		2) Map of words from Url
		3) If not co-related, Replace Url with headline
	`	4) after this, merge a single day document into one and write a system call to write it into a file
		5) mallet
	*/
	int headline_length=headline.length();
	int j=0;
	while(j<headline_length)
	{
		string current_word="";
		while(headline[j]!=' '&&j<headline_length)
		{
			if(headline[j]>='a'&&headline[j]<='z')
				current_word+=headline[j];
			else if(headline[j]>='A'&&headline[j]<='Z')
				{
					headline[j]='a'+int(headline[j]-'A');
					current_word+=headline[j];
				}
			else if(headline[j]>='0'&&headline[j]<='9')
					current_word+=headline[j];
			j++;
		}
		if(!grammer[current_word])
			{
				headlineword[current_word]++;	
			}
		while(headline[j]==' '&&j<headline_length)
			j++;
	}
	int article_length=article.length();
	j=0;
	int article_value=0;
	int flag=0; // assuming that headling and article do not match
	while(j<article_length)
	{
		string current_word="";
		while(article[j]!=' '&&j<article_length)
		{
			if(article[j]>='a'&&article[j]<='z')
				current_word+=article[j];
			else if(article[j]>='A'&&article[j]<='Z')
				{
					article[j]='a'+int(article[j]-'A');
					current_word+=article[j];
				}
			j++;
		}
		if(headlineword[current_word])
		{
			article_value+=headlineword[current_word];	
		}
		while(article[j]==' '&&j<article_length)
			j++;
	}
	if(article_value<2)
	    flag=1;

	if(flag)
	{
		article=headline;
		prep_stmt = con->prepareStatement("UPDATE News_articles SET Article=? where Headline=?");
		prep_stmt->setString(1, headline);
		prep_stmt->setString(2, headline);
		prep_stmt->execute();
		delete prep_stmt;
		cout<<"Successfully added "<<headline<<" to "<<headline<<endl; 	
		cout<<count<<endl;
		count++;
	}
  }
  delete res;
  delete stmt;
  delete con;
}
