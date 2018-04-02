#ifndef Data_H
#define Data_H
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <set>
#include <map>
#include <vector>
#include <regex>
#include <vector>
#include <ctime>
#include <ctime>
#include "dateutils.h"
using namespace std;

class Data
{
		time_t Time;
		int minute;

		double CMV,RMV;
		double Speed;
		double Hz;
		string timestr;
	public :
		double X,Y,Z,Lx,Ly,Rx,Ry,Lz,Rz;
        static string title;
        string raw_value;
        Data(string value,string raw_value);
        Data(string value);
        time_t GetTime() const;
        double GetSpeed();
		int GetMinute();
		double GetCMV();
		double GetRMV();
		double GetHz();
		string GetTimeStr();
        bool operator < (const Data& b) const;
	private :
		double GetDoubleFromStr(const string &s);
};

#endif // Data_H
