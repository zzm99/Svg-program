#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

string allin;
int count_left;

class letter
{
public:
	int x;
	int y;
	int layor;
	int flag; 
	int w;
	string s1;
	string s2;
};


class REC1
{
public:
	int x;
	int y;
	int w;
	string s1; 
	string s2;
	string s3;
	string ss3;
	string s4;
	string s5;
	string s6;
	string s7;
	string s8;
	
	REC1()
	{
		s1 = "<rect x=\"";
		s2 = "\" y=\"";
		s3 = "\" width=\"";
		ss3 = "\" height=\"30\" stroke=\"rgb(250,205,173)\" fill=\"rgb(247,68,97)\" fill-opacity=\"0.7\" stroke-opacity=\"0.7\" stroke-width=\"2\"/>";	
		s4 = "<text x=\"";
		s5 = "\" y=\"";
		s6 = "\" fill=\"rgb(35,31,33)\" text-anchor=\"middle\">";
		s8 = "</text>";
	}
};

class REC2
{
public:
	int x;
	int y;
	int w;
	string s1; 
	string s2;
	string s3;
	string ss3;
	string s4;
	string ss4;
	string s5;
	string s6;
	string s7;
	string s8;
	string s9;
	string s10;
	
	REC2()
	{
		s1 = "<rect x=\"";
		s2 = "\" y=\"";
		s3 = "\" width=\"";
		ss3 = "\" height=\"30\" stroke=\"rgb(250,205,173)\" fill=\"rgb(247,68,97)\" fill-opacity=\"0.7\" stroke-opacity=\"0.7\" stroke-width=\"2\"/>";
		s4 = "\" width=\"";
		ss4 = "\" height=\"30\" stroke=\"rgb(250,205,173)\" fill=\"transparent\" fill-opacity=\"0.7\" stroke-opacity=\"0.7\" stroke-width=\"2\"/>";
		s5 = "<text x=\"";
		s6 = "\" y=\"";
		s7 = "\" fill=\"rgb(35,31,33)\" text-anchor=\"middle\">";
		s9 = "</text>";
	}
};

class LINE
{
public:
	int x1;
	int x2;
	int y1;
	int y2;
	string s1; 
	string s2;
	string s3;
	string s4;
	string s5;
	
	LINE()
	{
		s1 = "<line x1=\"";
		s2 = "\" x2=\"";
		s3 = "\" y1=\"";
		s4 = "\" y2=\"";
		s5 = "\" stroke=\"rgb(250,205,173)\" fill=\"transparent\" fill-opacity=\"0.8\" stroke-opacity=\"0.8\" stroke-width=\"3\"/>";
	}
};


vector<REC1> comRec;
vector<REC2> uncomRec;
vector<LINE> comLine;
vector<letter> temletter;

void  ccin()
{
	for(int i=0; i<allin.size(); i++)
	{
		if(allin[i] == '(')
			count_left++;
		if(allin[i] == ')')
			count_left--;
		if(allin[i] != '(' && allin[i] != ')' && allin[i] != ' ')
		{   
			string tem_s;
			while(allin[i] != '(' && allin[i] != ')' && allin[i] != ' ')
			{
				tem_s = tem_s+allin[i];
				i++;	
			} 
			while(allin[i] == ' ')
			{
				i++;
			}
			if(allin[i] == '(')
			{
				letter temrec1;
				temrec1.layor = count_left;
				temrec1.flag = 0;
				temrec1.s1 = tem_s;
				temletter.push_back(temrec1);
				count_left++;
			}
			else if(allin[i] != '(' && allin[i] != ')' && allin[i] != ' ')
			{
				string tem_s2;
				while(allin[i] != '(' && allin[i] != ')' && allin[i] != ' ')
				{
					tem_s2 = tem_s2+allin[i];
					i++;	
				} 
				while(allin[i] == ' ')
				{
					i++;
				}
				letter temrec1;
				temrec1.layor = count_left;
				temrec1.flag = 1;
				temrec1.s1 = tem_s;
				temrec1.s2 = tem_s2;
				temletter.push_back(temrec1);
				count_left--;
			}
		}
	}

}

void match()
{

	int over_flag = 10;
	for(int i=0; i<temletter.size(); i++)
	{
		if(temletter[i].flag == 1)
		{
			int len1 = temletter[i].s1.size();
			int len2 = temletter[i].s2.size();
			int maxlen = len1>len2? len1:len2;
			
			REC2 a;
			a.s8 = temletter[i].s1;
			a.s10 = temletter[i].s2;
			a.x = over_flag;
			a.y = 10+(temletter[i].layor-1)*80;
			a.w = 10+maxlen*12;
			temletter[i].w = a.w;
			temletter[i].x = a.x;
			temletter[i].y = a.y;
			uncomRec.push_back(a);
			over_flag += maxlen*12;
			over_flag += 25;
		}
	}
	for(int i=temletter.size()-2; i>=0; i--)
	{
		if(temletter[i].flag == 0)
		{
			int rem_x = 0;
			int rem_count = 0;
			for(int j=i; j<temletter.size(); j++)
			{
				if(temletter[j].layor == temletter[i].layor+1 && temletter[j].flag == 1)
				{
					rem_x += temletter[j].x;
					rem_count++;
					temletter[j].flag = 0;
				}
			}
			temletter[i].x = rem_x/rem_count;
			temletter[i].y = 10+(temletter[i].layor-1)*80;
			temletter[i].flag = 1;
			REC1 a;
			a.w = 12*temletter[i].s1.size()+10;
			a.s7 = temletter[i].s1;
			a.x = temletter[i].x;
			a.y = temletter[i].y;
			temletter[i].w = a.w;
			comRec.push_back(a);
		}
	}
	for(int i = 1; i<temletter.size(); i++)
	{
		int j=i-1;
		for( ; j>=0; j--)
		{
			if(temletter[j].layor == temletter[i].layor-1)
				break;
		}
		LINE a;
		a.x1 = temletter[j].x+temletter[j].w/2;
		a.y1 = temletter[j].y+30;
		a.x2 = temletter[i].x+temletter[i].w/2;
		a.y2 = temletter[i].y;
		comLine.push_back(a);
	}
}


int main()
{	
	ifstream in("du.txt");
	getline(in, allin);
	in.close();
	if(allin.empty())
	{
		cout << "¶ÁÈ¡×Ö·û´®Ê§°Ü" << endl;
		return 0;
	}
	ccin();
	match();
	int max_layor = 0;
	for(int i=0; i<temletter.size(); i++)
	{
		if(temletter[i].layor > max_layor)
			max_layor = temletter[i].layor;
	}
	max_layor *= 85;
	ofstream outfile;
	outfile.open("ss.html");
	outfile << "<svg width=\"2000\" height=\"1500\" xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\">" << endl;
	outfile << "<rect x=\"0\" y=\"0\" width=\"1500\" height=\"1000\" fill=\"#D1BA74\" fill-opacity = \"0.1\" />" << endl;  
	for(int i=0; i<comRec.size(); i++)
	{
		outfile << comRec[i].s1 << comRec[i].x << comRec[i].s2 << comRec[i].y << comRec[i].s3  << comRec[i].w << comRec[i].ss3 << endl;
		outfile << comRec[i].s4 << comRec[i].x+comRec[i].w/2 << comRec[i].s5 << comRec[i].y+20 << comRec[i].s6 << comRec[i].s7 << comRec[i].s8 << endl;
	}
	for(int i=0; i<uncomRec.size(); i++)
	{
		outfile << uncomRec[i].s1 << uncomRec[i].x << uncomRec[i].s2 << uncomRec[i].y << uncomRec[i].s3 << uncomRec[i].w << uncomRec[i].ss3 << endl;
		outfile << uncomRec[i].s1 << uncomRec[i].x << uncomRec[i].s2 << uncomRec[i].y + 30 << uncomRec[i].s4 << uncomRec[i].w << uncomRec[i].ss4 << endl;
		outfile << uncomRec[i].s5 << uncomRec[i].x+uncomRec[i].w/2 << uncomRec[i].s6 << uncomRec[i].y+20 << uncomRec[i].s7 << uncomRec[i].s8 << uncomRec[i].s9 << endl;
		outfile << uncomRec[i].s5 << uncomRec[i].x+uncomRec[i].w/2 << uncomRec[i].s6 << uncomRec[i].y+50 << uncomRec[i].s7 << uncomRec[i].s10 << uncomRec[i].s9 << endl;
	}
	for(int i=0; i<comLine.size(); i++)
	{
		outfile << comLine[i].s1 << comLine[i].x1 << comLine[i].s2 << comLine[i].x2;
		outfile << comLine[i].s3 << comLine[i].y1 << comLine[i].s4 << comLine[i].y2 << comLine[i].s5 << endl;
	}
	outfile << "<linearGradient id=\"gr-simple\" x1=\"0\" y1=\"0\" x2=\"100%\" y2=\"100%\"> <stop stop-color=\"hsl(50, 100%, 70%)\" offset=\"10%\"/>" << endl;
	outfile << "<stop stop-color=\"hsl(320, 100%, 50%)\" offset=\"90%\"/> </linearGradient>" << endl;
    outfile << "<text font-family=\"microsoft yahei\" font-size=\"40\" y=\"" << max_layor;
	outfile << "\" x=\"500\" fill=\"url(#gr-simple)\">" << endl;
    outfile << "18342138 zzm<animate attributeName=\"x\" from=\"500\" to=\"100\" begin=\"0s\" dur=\"10s\" repeatCount=\"indefinite\" /></text>" << endl;
	outfile << "</svg>" << endl;
	outfile.close();
	cout << "success" << endl;
	return 0;
}
