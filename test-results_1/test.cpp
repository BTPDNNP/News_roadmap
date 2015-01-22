#include <bits/stdc++.h>
using namespace std;
#define e 2.7182818284
map <string,string> m;
map <pair<string,int>,double> m2;
map <pair<string,int>,double> m_univ;
map <string,int> match;
double percent_match(string s1,string s2)
{
	int i=0;
	int j=0;
	int len1=s1.length();
	int len2=s2.length();
	int word=0;
	int match1=0;
	while(i<len1)
	{
		string curr_word="";
		while(s1[i]!=' '&&i<len1)
		{
			curr_word+=s1[i];
			i++;
		}
		i++;
		
		match[curr_word]++;
		word++;
		
	}
	
	while(j<len2)
	{
		string curr_word="";
		while(s2[j]!=' '&&j<len2)
		{
			curr_word+=s2[j];
			j++;
		}
		j++;
		
		if(match[curr_word])
			match1++,match[curr_word]--;
			
			
			word++;
		
		
		
		
	}
	
	match.clear();
	return (double)match1/(double)word;
	
}
int main()
{
	
	double stock_val_diff;
	string current_folder;
	
	for(int f=1;f<=10;f++)
	{
		string name = "";
		name += char(f + '0') ;
		current_folder = "/home/nitin/Desktop/test-results_1/"+ name;
		string input_file = current_folder + "/1";
		if(freopen(input_file.c_str(),"r",stdin)) cout<<"success"<<endl;
		
		cout<<current_folder<<endl;
		cout<< input_file<<endl;
		stock_val_diff=0;
		cin>>stock_val_diff;
		fclose(stdin);
		cout<<stock_val_diff;
        // here we have got the stock fall or rise value so far
        
	
	
	
		
		string mapping_headlines;
		string map_file = current_folder + "/output_csv/Topics_Words.csv";
		cout<<map_file<<endl;
		freopen(map_file.c_str(),"r",stdin);
		string s;
		getline(cin,s);
		for(int i=0;i<10;i++)
		{
			getline(cin,s);
			string val="";
			int j=0;
			
			while(s[j]!=',')
				{val+=s[j];j++;}
				
			j++;
		    
			string topics = s.substr(j);
			m[val]=topics;
			cout<<val<<endl;
			cout<<topics<<endl;
			

			//m2[topics]= stock_val_diff/10;
		}
		// m2 is for initial value storage for all current topics in hand
		fclose(stdin);
		string map_file2 = current_folder + "/output_csv/TopicsInDocs.csv";
		freopen(map_file2.c_str(),"r",stdin);
		getline(cin,s);
		string temp_array[7];
		
		for(int i=0;i<7;i++)
		{
			getline(cin,s);
			int j=0;
			
			while(s[j]!=',')
				j++;
			j++;
			s= s.substr(j);
			temp_array[i]=s;
		}
		std::sort(temp_array,temp_array+7);
		
		for(int i=6;i>=0;i--)
		{
			s=temp_array[i];
			
			int j=0;
			
			while(s[j]!=',')
			{
				j++;
			}
			//j++;
			int len=s.length();
			while(j<len)
			{
				j++;
				
				if(j==len)
					break;
				string mapnum="";
				while(s[j]!=',')
				{
					mapnum+=s[j];
					j++;
					
				}
				j++;
				string mapval="";
				while(s[j]!=',')
				{
					mapval+=s[j];
					j++;
				}
				double f_val= atof(mapval.c_str());
				
				m2[make_pair(m[mapnum],6-i)]= f_val*stock_val_diff/(double)(6-i+1);
				// f_val*stock_val_diff*(e^-6-i)
				
			}
			
		}
		fclose(stdin);
	
		//open the file mapping days to topics with their percentage values that will be put in the temporary map m2
		
	
		
		map<pair<string,int>,double >:: iterator it1;
		map<pair<string,int>,double>::iterator it;

		for(it1=m2.begin();it1!=m2.end();it1++)
		{
			int d=it1->first.second;
			double v=it1->second;
			string p = it1->first.first;
			
			for(it=m_univ.begin();it!=m_univ.end();it++)
			{
				string past_topic = it->first.first;
				int day= it->first.second;
				double val = it-> second;
				
				if(day==d)
				{
					double perc=percent_match(past_topic,p);
					
					m2[make_pair(p,d)]+=m_univ[make_pair(past_topic,d)]*perc;
					
					
				}
				
				
				
				
			}
		}
		
		
		for(it1=m2.begin();it1!=m2.end();it1++)
		{
			m_univ[make_pair(it1->first.first,it1->first.second)]=it1->second;
		}
		m.clear();
		m2.clear();
		
		
	}
	
	map<pair<string,int>,double> ::iterator it3;
	
	for(it3=m_univ.begin();it3!=m_univ.end();it3++)
	{
		cout<<it3->first.first<<" affects market with "<<it3->second<<" after "<<it3->first.second<<" days "<<endl; 
	}
	
}
