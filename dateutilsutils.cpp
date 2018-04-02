#include "dateutils.h"

int DaysPerMonth[2][12] =
{
	{
		31, 28, 31, 30, 31, 30,
		31, 31, 30, 31, 30, 31
	},
	{
		31, 29, 31, 30, 31, 30,
		31, 31, 30, 31, 30, 31
	}
};

int isLeapYear(int year)//判断是否为闰年 是：返回1 不是：返回0
{
	if ((year % 4   == 0)
	        && ((year % 100 != 0)
	            ||  (year % 400 == 0))) return 1;
	else return 0;
}

double datetime_encodeDate(int year, int month, int day)

{
	int i, j;
	i = isLeapYear(year);
	if ((year >= 1)
	        && (year <= 9999)
	        && (month >= 1)
	        && (month <= 12)
	        && (day >= 1)
	        && (day <= DaysPerMonth[i][month-1]))
	{
		for (j = 0; j < month-1; j++) day += DaysPerMonth[i][j];
		i = year - 1;
		return i*365 + i/4 - i/100 + i/400 + day - StartData;
	}
	else return -StartData;
}

// seconds per day
double datetime_encodeTime(int hour, int minute, int second,int ms)

{
	int s;
	if ((hour >= 0)
	        && (minute >= 0)
	        && (second >= 0))
	{
		s = (hour * 3600 + minute * 60 + second);
		return (s + ms/1000.)/SecsPerDay;
	}
	else return 0.0;
}

void d1totime(double d1,int &year,int &month,int &day)
{
	int intd1 = d1;
	intd1 += StartData;
	int i;
	for(i = 1990 ; i < 2100 ; i++)
		if(i*365 + i/4 - i/100 + i/400 - intd1 >= 0)
			break;
	year = i;
	int isleapyear = isLeapYear(year);
	i -= 1;
	day = intd1 - (i*365 + i/4 - i/100 + i/400);
	int j;
	int sum = 0;
	for(j = 0 ; j < 12 ; j++)
	{
		sum += DaysPerMonth[isleapyear][j];
		if(sum >= day)
			break;
	}
	sum = 0;
	for(int k = 0 ; k < j ; k++)
	{
		sum += DaysPerMonth[isleapyear][k];
	}
	day = day - sum;
	month = j+1;
}

void d2totime(double d2,int &hour,int &minute,int &second,int &ms)
{
	d2 *= SecsPerDay;
	ms = (d2 - (int)d2)*1000;
	int tmp = (int)d2;
	second = tmp % 60;
	tmp /= 60;
	minute = tmp % 60;
	tmp /= 60;
	hour = tmp %= 24;
	//cout<<h<<" "<<min<<" "<<sec<<" "<<ms<<endl;
}

time_t DateStr2Double(string s, int &minute_,string &timestr)
{
	regex reg(".*?([0-9]{1,})-([0-9]{1,})-([0-9]{1,}).*?([0-9]{1,}):([0-9]{1,}):([0-9]{1,})\\.([0-9]{1,}).*?");
	smatch sm;
	regex_match(s,sm,reg);
	stringstream ss(sm.str(1) + " " + sm.str(2) + " " + sm.str(3) + " "+sm.str(4) + " "+sm.str(5) + " " + sm.str(6) + " " + sm.str(7));
	int year,month,day,hour,minute,second,ms;
	timestr = sm.str(1) + "-" + sm.str(2) + "-" + sm.str(3) + " " + sm.str(4) + ":" + sm.str(5) + ":" + sm.str(6);
	ss>>year>>month>>day>>hour>>minute>>second>>ms;
	minute_ = minute;
	return calc_sec1970(year,month,day,hour,minute,second);
}

string DoubletoDateStr(double d)
{
	return "#";
}

time_t calc_sec1970(int Y, int M, int D, int h, int m, int s)
{
	int i = 0;
	int sec = 0;
	int days[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

	/* 年计算 */
	for(i = 1970; i < Y; i++)
	{
		if(isLeapYear(i))
			sec += 366 * 24 * 60 * 60;
		else
			sec += 365 * 24 * 60 * 60;
	}

	/* 月计算 */
	for(i = 1; i < M; i++)
	{
		sec += days[i] * 24 * 60 * 60;
		if(i == 2 && isLeapYear(Y))
		{
			sec += 24 * 60 * 60;
		}
	}

	/* 天计算 */
	sec += (D - 1) * 24 * 60 * 60;

	/* 时分秒计算 */
	sec += h * 60 * 60 + m * 60 + s;

	return sec - 8*3600;
}
