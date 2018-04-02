#ifndef READCVS_H
#define READCVS_H
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
#include "data.h"
#include <QDebug>
using namespace std;

void readcsv(ifstream& input,void (*f)(int,int,void *t),void *w,vector<Data> &Datavec);

void ReplaceTime(string &s,const map<string,string> &MonthMap);

void InitMonthMap(map<string,string> &MonthMap);

void findcol(ifstream& input);

bool iseffecol(const string &x);

void AddDataToVec(const string &s,const string &raw_value,vector<Data> &Datavec);

#endif // READCVS_H
