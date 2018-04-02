#ifndef DATEUTILS_H
#define DATEUTILS_H
#include <iostream>
#include <cstdio>
#include <ctime>
#include <vector>
#include <string>
#include <cstring>
#include <array>
#include <sstream>
#include <iterator>
#include <iomanip>
#include <regex>
using namespace std;
const int StartData = 726468; //1990 1 1

const double SecsPerDay = 86400.L;

extern int DaysPerMonth[2][12];    // days per month
/*{{31, 28, 31, 30, 31, 30,               // normal years
  31, 31, 30, 31, 30, 31},
 {31, 29, 31, 30, 31, 30,               // leap years
  31, 31, 30, 31, 30, 31}};*/

int isLeapYear(int year);

double datetime_encodeDate(int year, int month, int day);

double datetime_encodeTime(int hour, int minute, int second,int ms);

void d1totime(double d1,int &year,int &month,int &day);

void d2totime(double d2,int &hour,int &minute,int &second,int &ms);

time_t DateStr2Double(string s, int &minute_, string &timestr);

string Double2DateStr(double d);

time_t calc_sec1970(int Y, int M, int D, int h, int m, int s);

#endif // DATEUTILS_H
