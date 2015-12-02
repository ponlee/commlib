/**********************************
 * File: DateHelper.h
 * Author: ponlee
 * Version: 1.0
 * Date:  2014-04
 * Desc: 基本日期操作封装类
***********************************/
#ifndef _C_DATE_H__
#define _C_DATE_H__

#include <vector>
#include <ctime>
#include <string>

class CDateHelper
{
public:
	static void BreakDate(unsigned long date, int &year, int &month, int &day)
	{
		if (date == 0)
		{
			time_t now = time(NULL);
			struct tm tmnow;
			localtime_r(&now, &tmnow);
			year = 1900 + tmnow.tm_year;
			month = 1 + tmnow.tm_mon;
			day = tmnow.tm_mday;
		}
		else
		{
			year = date / 10000;
			month = date / 100 % 100;
			day = date % 100;
		}
	}

	static unsigned long GetDate(int year, int month, int day)
	{
		return year * 10000 + month * 100 + day;
	}

	static unsigned long GetDateNow()
	{
		time_t now = time(NULL);
		struct tm tmnow;
		localtime_r(&now, &tmnow);
		return GetDate(1900 + tmnow.tm_year, 1 + tmnow.tm_mon, tmnow.tm_mday);
	}
	
	static unsigned long DateToSecond(int year, int month, int day)
	{
		struct tm t;
		memset(&t, 0, sizeof(t));
		t.tm_year = year - 1900;
		t.tm_mon = month - 1;
		t.tm_mday = day;
		return mktime(&t);
	}
	
	static unsigned long DateToSecond(unsigned long date)
	{
		int y, m, d;
		BreakDate(date, y, m, d);
		return DateToSecond(y, m, d);
	}

	static void SecondToDate(unsigned long seconds, int &year, int &month, int &day)
	{
		struct tm t;
		if (!localtime_r((time_t *)&seconds, &t))
		{
			year = month = day = 0;
		}
		else
		{
			year = t.tm_year + 1900;
			month = t.tm_mon + 1;
			day = t.tm_mday;
		}
	}
	
	static unsigned long SecondToDate(unsigned long seconds)
	{
		int y, m, d;
		SecondToDate(seconds, y, m, d);
		return GetDate(y, m, d);
	}
	
	/*************************************************
	** @Description:		计算一个时间范围
	** @Input:	
	**		from, to		开始和结束时间，格式为yyyymmdd，如20071220
	** @Output:		  
			vectDates		从from到to的所有时间，格式为yyyymmdd
	** @Return:
				 0			正确
				 -1 		输入有误
	** @Others: 
				from, to可以互换位置。
				from, to = 0表示当前日期。
				输出的vectDates中已经把当前日期转化为0。
	*************************************************/
	static int GetDateRange(unsigned long from, unsigned long to, std::vector<unsigned long> &vectDates)
	{
		int year_from, month_from, day_from, year_to, month_to, day_to;
		
		BreakDate(from, year_from, month_from, day_from);
		BreakDate(to, year_to, month_to, day_to);
		if ((year_from < 2007 || year_from > 2050)
			|| (month_from < 1 || month_from > 12)
			|| (day_from < 0 || day_from > 31)
			|| (year_to < 2007 || year_to > 2050)
			|| (month_to < 1 || month_to > 12)
			|| (day_to < 0 || day_to > 31))
		{
			return -1;
		}
		
		unsigned long time_from, time_to;
		time_from = DateToSecond(year_from, month_from, day_from);
		time_to = DateToSecond(year_to, month_to, day_to);

		/* 如果from晚于to则互换位置 */
		if (time_from > time_to)
		{
			unsigned long tmp = time_to;
			time_to = time_from;
			time_from = tmp;
		}

		/* 转化成秒数计算，然后转化成年月日 */
		for (; time_from <= time_to; time_from += 3600 * 24)
		{
			unsigned long one_date = SecondToDate(time_from);

			/* 如果是当前日期则转化成0 */
			//if (one_date == date_now)
			//	one_date = 0;
			vectDates.push_back(one_date);
		}

		return 0;
	}

	/*************************************************
	** @Description:	  给定一个时间，计算指定天数前的日期
	** @Input:	
			baseDate		 指定要逆推的时间，格式为yyyymmdd，如20071220
			month			 month个月之前
			day 			  day个日之前
	** @Output:		  
	** @Return:
			baseDate逆推month月day天之后的时间,格式为yyyymmdd
	** @Others: 
			baseDate = 0表示当前日期。
	*************************************************/
	static unsigned long GetDateAgo(unsigned int month, unsigned int day, unsigned long baseDate = 0)
	{
		int y, m, d;
		BreakDate(baseDate, y, m, d);
		if ((y < 2007 || y > 2050)
			|| (m < 1 || m > 12)
			|| (d < 0 || d > 31))
		{
			return 0;
		}

		/* 先考虑month个月之前 */
		y -= month / 12;
		m -= month % 12;
		if (m <= 0)
		{
			y--;
			m += 12;
		}
		
		unsigned long seconds = DateToSecond(y, m, d);

		/* 再考虑day天之前 */
		seconds -= day * 3600 * 24;

		return SecondToDate(seconds);
	}

	/*************************************************
	** @Desc:	  给定一个时间，计算指定天数后的日期
	** @Input:	
			baseDate		 指定要顺推的时间，格式为yyyymmdd，如20071220
			month			 month个月之前
			day 			  day个日之前
	** @Output:		  
	** @Return:
			baseDate顺推month月day天之后的时间,格式为yyyymmdd
	** @Others: 
			baseDate = 0表示当前日期。
	*************************************************/
	static unsigned long GetDateFuture(unsigned int month, unsigned int day, unsigned long baseDate = 0)
	{
		int y, m, d;
		BreakDate(baseDate, y, m, d);
		if ((y < 2007 || y > 2050)
			|| (m < 1 || m > 12)
			|| (d < 0 || d > 31))
		{
			return 0;
		}

		/* 先考虑month个月之后 */
		y += month / 12;
		m += month % 12;
		if (m > 12)
		{
			y++;
			m -= 12;
		}
		
		unsigned long seconds = DateToSecond(y, m, d);
		
		/* 再考虑day天之后 */
		seconds += day * 3600 * 24;

		return SecondToDate(seconds);
	}

	static unsigned long GetDateCount(unsigned long from, unsigned long to)
	{
		int year_from, month_from, day_from, year_to, month_to, day_to;
		
		BreakDate(from, year_from, month_from, day_from);
		BreakDate(to, year_to, month_to, day_to);
		
		unsigned long time_from, time_to;
		time_from = DateToSecond(year_from, month_from, day_from);
		time_to = DateToSecond(year_to, month_to, day_to);
		if (time_from > time_to)
		{
			unsigned long tmp = time_to;
			time_to = time_from;
			time_from = tmp;
		}

		return (time_to - time_from) / (3600 * 24);
	}
	/***************************************************************
	** @Desc:获得当前日期，由format指定格式:"%Y-%m-%d"/"%Y-%m-%d %H:%M%S"
	** @Return:
	**	   特定格式的当前日期的字符串
	***************************************************************/
	static const string CurrentDate( const string& format ) 
	{
		time_t     now = time(0); 
		struct tm  tstruct;
		char       buf[80];
		tstruct = *localtime(&now);
		strftime(buf, sizeof(buf), format.c_str(), &tstruct);
		return buf;
	}
	
	static time_t StrToTime(const string& timeStr )
	{
		struct tm tm_time;
		strptime(timeStr.c_str(), "%Y-%m-%d %H:%M:%S", &tm_time);
		return mktime(&tm_time);
	}
};

#endif

