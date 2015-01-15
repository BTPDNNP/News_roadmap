/* Standard C++ includes */
#include <stdlib.h>
#include <iostream>
#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
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
map<pair<string,int>,int> word_freq;// universal word frequency
map<string,int> temp_freq;
map<string,int> word_in_article;
map<string,int> temp_in_article;
//map<string,int> p;
map<pair<string,int>,double> tf;
map<string,double> idf;
int article_no=0;
int total_word_count=0;
int word_count;
map<string,double> tfidf;

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
int main(void)
{
  create_grammer_map();
  
  sql::Driver *driver;
  sql::Connection *con;
  sql::Statement *stmt;
  sql::ResultSet *res;



  /* Create a connection */
  driver = get_driver_instance();
  con = driver->connect("localhost", "root", "nitish2312");
  /* Connect to the MySQL test database */
  con->setSchema("Finance_news");

  stmt = con->createStatement();
  res = stmt->executeQuery("SELECT * from News_articles");
  int i=0;
  while (res->next()) {
	//i++;
	article_no++;
	word_count=0;
	temp_freq.clear();
	temp_in_article.clear();// stores all words only once in the iterator article and updates the word_in_article map only once for multiple entries in that article
   	string headline= res->getString("Headline");
	string article= res->getString("Article");
	
	/*
few things to do here:

a) for each article,match it with the headline
b) if it doesn't match at all, replace headline with article (involves using hash maps)
c) for each article (replaced one) find some way to remove grammer from it
d) the remaining words have to be stored in a hashmap and their global counter taken
e) generate some array to find the most frequent words and sort them in some heap or priority queue
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


		// we have the current word in hash map headlineword
		if(!grammer[current_word])
			{

				headlineword[current_word]++;
				//word_freq[make_pair(current_word,article_no)]=1;// this weight has to be changed later
				temp_freq[current_word]+=1;
				word_count+=1;
				if(temp_in_article[current_word]==0)
					{
						word_in_article[current_word]++;
						word_freq[make_pair(current_word,article_no)]++;
						temp_in_article[current_word]++;
					}
			
				
			}
		// the part to avoid the redundant part is still left 
		while(headline[j]==' '&&j<headline_length)
			j++;


		
		
	}

	// now the hash map has all words from article with frequency

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
			//if(!p[current_word])
				//p[current_word]=1;

			article_value+=headlineword[current_word];// p has to be modified somehow

			
			

			// do some analytics,heuristics to analyze that the article and headline match somehow
		}
		
		
		
		// calculate the tf of that word using logarithmic method

		

		while(article[j]==' '&&j<article_length)
			j++;
		

		

	}
	if(article_value>1)
		flag=1;
	if(!flag)
	{
		article=headline;
		//stmt = con->createStatement(); put some inset statement
  		//res = stmt->executeQuery("INSERT INTO News_articles values blah blah blah");
		
	}
	
	j=0;
	article_length=article.length();
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
				
		
		
		if(!grammer[current_word])
			{
				
				//word_freq[make_pair(current_word,article_no)]=1;// this weight has to be changed later
				temp_freq[current_word]+=1;
				word_count++;


				if(temp_in_article[current_word]==0)
					{
						word_in_article[current_word]++;
						word_freq[make_pair(current_word,article_no)]++;
						temp_in_article[current_word]++;
					}
			}
		
		// calculate the tf of that word using logarithmic method

		

		while(article[j]==' '&&j<article_length)
			j++;
		

		

	}
	j=0;
	for (std::map<string,int>::iterator it=temp_freq.begin(); it!=temp_freq.end(); ++it)
	{
		tf[make_pair(it->first,article_no)]=(double)(1+log10(temp_freq[it->first]));
		//tf[make_pair((it->first),article_no)]=(double)temp_freq[(it->first)]/(double)word_count;
	}

	
	

	

  }

  for (std::map<string,int>::iterator it=word_in_article.begin(); it!=word_in_article.end(); ++it)
	{
		//tf[make_pair(it->first,article_no)]=1+log10(temp_freq[it->first]);
		idf[it->first]=log10((double)article_no/(double)(it->second));
		//tfidf[make_pair(it->)]
		tfidf[it->first]=0;
		
		
	}


    for (std::map<pair<string,int>,int>::iterator it=word_freq.begin(); it!=word_freq.end(); ++it)
	{
		//tf[make_pair(it->first,article_no)]=1+log10(temp_freq[it->first]);
		
		//tfidf.push_back(make_pair(tf[make_pair(it->first,it->second)]*idf[it->first],


		tfidf[(it->first.first)]+=(double)tf[make_pair(it->first.first,it->first.second)]*(double)(idf[it->first.first]);
		
		
	}

	freopen("/home/nitin/Desktop/News/tfidf-compute/outputname.txt","w",stdout);
	vector< pair<double,string> > sorted_list;
	int counter=0;
 for (std::map<string,double>::iterator it=tfidf.begin(); it!=tfidf.end(); ++it)
	{
		


		sorted_list.push_back(make_pair((it->second),(it->first)));
		counter++;
		
		
	}
	std::sort(sorted_list.begin(),sorted_list.end());
	for(int i=0;i<counter;i++)
	{
		
		cout<<sorted_list[i].first<<endl;
	}
	fclose(stdout);
  
  

  delete res;
  delete stmt;
  delete con;

 
  





}
