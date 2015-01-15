#include <bits/stdc++.h>
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
using namespace std;
map<string,int> m;
int main()
{

  sql::Driver *driver;
  sql::Connection *con;
  sql::Statement *stmt;
  sql::ResultSet *res;

  driver = get_driver_instance();
  con = driver->connect("localhost", "root", "nitish2312");
  /* Connect to the MySQL test database */
  con->setSchema("Finance_news");

  stmt = con->createStatement();
  res = stmt->executeQuery("SELECT Headline from News_articles");
  int i=0;
  int count=0;
  int count2=0;
  while (res->next()) {
	
   	string headline= res->getString("Headline");
	m[headline]=1;
	


	}

		freopen("newsfile7.txt","r",stdin);
		freopen("newsfile8.txt","w",stdout);

		string s;
		while(getline(cin,s))
		{
			count2++;
			string curr_word="";
			for(int i=0;i<s.length();i++)
			{
				
				if(s[i]=='#'&&s[i+1]=='#')
					break;
				else
					curr_word+=s[i];
			}
			if(m[curr_word]==1)
			{}
			else
			{
				cout<<s;
				cout<<endl;
				m[curr_word]=1;	
				count++;	
			}

		}
	

	fclose(stdin);
	fclose(stdout);

	cout<<count<<" "<<count2;
        





}
