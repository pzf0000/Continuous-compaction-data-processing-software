#include "Data.h"
string Data::title = "";
Data::Data(string value)
{
    stringstream ss(value);

    //cout<<raw_value;
    string Date1,Date2;
    ss>>Date1>>Date2;
    Time = DateStr2Double(Date1+" "+Date2,minute,timestr);
    string tmp;
    ss>>tmp;
    double LY = GetDoubleFromStr(tmp);
    ss>>tmp;
    double LX = GetDoubleFromStr(tmp);
    ss>>tmp;
    double LZ = GetDoubleFromStr(tmp);
    ss>>tmp;
    double RY = GetDoubleFromStr(tmp);
    ss>>tmp;
    double RX = GetDoubleFromStr(tmp);
    ss>>tmp;
    double RZ = GetDoubleFromStr(tmp);
    Lx = LX,Ly = LY,Rx = RX,Ry = RY,Lz = LZ,Rz = RZ;
    Y = LY / 2 + RY / 2;
    X = LX / 2 + RX / 2;
    Z = LZ / 2 + RZ / 2;
    ss>>tmp;
    CMV = GetDoubleFromStr(tmp);
    ss>>tmp;
    RMV = GetDoubleFromStr(tmp);
    ss>>tmp;
    Speed = GetDoubleFromStr(tmp);
    ss>>tmp;
    Hz = GetDoubleFromStr(tmp);
}
bool Data::operator <(const Data &b) const
{
    return b.GetTime() < GetTime();
}
Data::Data(string value,string raw_value)
{
    stringstream ss(value);
    this->raw_value = raw_value;
    //cout<<raw_value;
    string Date1,Date2;
    ss>>Date1>>Date2;
    Time = DateStr2Double(Date1+" "+Date2,minute,timestr);
    string tmp;
    ss>>tmp;
    double LY = GetDoubleFromStr(tmp);
    ss>>tmp;
    double LX = GetDoubleFromStr(tmp);
    ss>>tmp;
    double LZ = GetDoubleFromStr(tmp);
    ss>>tmp;
    double RY = GetDoubleFromStr(tmp);
    ss>>tmp;
    double RX = GetDoubleFromStr(tmp);
    ss>>tmp;
    double RZ = GetDoubleFromStr(tmp);
    Lx = LX,Ly = LY,Rx = RX,Ry = RY,Lz = LZ,Rz = RZ;
    Y = LY / 2 + RY / 2;
    X = LX / 2 + RX / 2;
    Z = LZ / 2 + RZ / 2;
    ss>>tmp;
    CMV = GetDoubleFromStr(tmp);
    ss>>tmp;
    RMV = GetDoubleFromStr(tmp);
    ss>>tmp;
    Speed = GetDoubleFromStr(tmp);
    ss>>tmp;
    Hz = GetDoubleFromStr(tmp);
}

time_t Data::GetTime() const
{
	return Time;
}

double Data::GetSpeed()
{
	return Speed;
}

int Data::GetMinute()
{
	return minute;
}

string Data::GetTimeStr()
{
	return timestr;
}

double Data::GetCMV()
{
	return CMV;
}

double Data::GetRMV()
{
	return RMV;
}

double Data::GetHz()
{
	return Hz;
}

double Data::GetDoubleFromStr(const string &s)
{
	regex reg(".*?([0-9]{1,}\\.[0-9]{1,}).*?");
	smatch sm;
	regex_match(s,sm,reg);
	return stod(sm.str(1));
}
