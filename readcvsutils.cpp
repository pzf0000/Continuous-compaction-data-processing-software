#include "readcvsutils.h"

map<int,string> mp;
string effecolstr[] = {"Time","Left Y","Left X","Left Z","Right Y","Right X","Right Z","CMV","RMV","Speed","Frequency (Hz)"};
int badData = 0;
void AddDataToVec(const string &s,const string &raw_value,vector<Data> &Datavec)
{
	try
	{
        Data tmpData(s,raw_value);
		if(Datavec.size() != 0)
		{
			if(tmpData.GetTime() < Datavec[Datavec.size() - 1].GetTime())
			{
				badData++;
				return;
			}
		}
		Datavec.push_back(tmpData);
	}
	catch(...)
	{
		badData++;
	}
}

bool iseffecol(const string &x)
{
	for(auto &s : effecolstr)
		if(s == x)
			return true;
	return false;
}

void findcol(ifstream& input)
{
	string value;
	string tmp;
	int col = 0;
    getline(input,value);
    Data::title = value;
	stringstream ss(value);
	while(ss.good())
	{
		getline(ss,tmp,',');
		if(iseffecol(tmp))
			mp[col] = tmp;
		col++;
	}
}

void InitMonthMap(map<string,string> &MonthMap)
{
	MonthMap["一月"] = "01";
	MonthMap["二月"] = "02";
	MonthMap["三月"] = "03";
	MonthMap["四月"] = "04";
	MonthMap["五月"] = "05";
	MonthMap["六月"] = "06";
	MonthMap["七月"] = "07";
	MonthMap["八月"] = "08";
	MonthMap["九月"] = "09";
	MonthMap["十月"] = "10";
	MonthMap["十一月"] = "11";
	MonthMap["十二月"] = "12";
}

void ReplaceTime(string &s,const map<string,string> &MonthMap)
{
	for(auto i = MonthMap.begin() ; i != MonthMap.end() ; i++)
	{
		string Month = i->first;
		auto it = s.find(Month);
		if(it != string::npos)
		{
			s.replace(it,Month.length(),i->second);
			break;
		}
	}
}

void readcsv(ifstream& input,void (*f)(int,int,void *),void *w,vector<Data> &Datavec)
{

	string value;
	string tmp;
	map<string,string> MonthMap;
	InitMonthMap(MonthMap);
	int n = 0;
	while(input.good())
	{
		f(++n,Datavec.size(),w);
		getline(input,value);
        string raw_value = value;
        //cout<<value<<endl;
		stringstream ss(value);
		int col = 0;
		stringstream tss;
		while(ss.good())
		{
			getline(ss,tmp,',');
			if(!mp.count(col))
			{
				col++;
				continue;
			}
			if(tmp == "\"N/A\"")
			{
				goto end;
			}
			if(mp[col] == "Time")
				ReplaceTime(tmp,MonthMap);
			tss<<tmp<<" ";
			col++;
		}
		qDebug("#");
        AddDataToVec(tss.str(),raw_value,Datavec);
end:
		;
	}
	f(n,Datavec.size(),w);
}
