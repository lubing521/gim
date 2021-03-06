#include "ef_utility.h"
#include <sstream>
#include <sys/epoll.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

namespace ef{

	std::string itostr(int64 i){
		std::stringstream os;
		os << i;
		return os.str();
	}

	int64 htonll(int64 ll){
		int64 ret = ll;
		char* p = (char*)&ret;
		for(int i = 0; i < 4; ++i){
			char c = p[i];
			p[i] =  p[7 - i];
			p[7 - i] = c;
		}
		return	ret;
	}

	int32 tv_cmp(struct timeval t1, struct timeval t2){
		if(t1.tv_sec < t2.tv_sec){
			return	-1;
		}else	if(t1.tv_sec > t2.tv_sec){
			return	1;
		}else{
			if(t1.tv_usec < t2.tv_usec){
				return	-1;
			}else	if(t1.tv_usec > t2.tv_usec){
				return	1;
			}else{
				return	0;
			}
		}
	}

	struct timeval tv_diff(struct timeval t1, struct timeval t2){
		struct	timeval	ret;

		ret.tv_sec = t1.tv_sec - t2.tv_sec;

		if(t1.tv_usec < t2.tv_usec){
			ret.tv_sec -= 1;
			t1.tv_usec += 1000000;
		}

		ret.tv_usec = t1.tv_usec - t2.tv_usec;

		return	ret;
	}


	int64 gettime_ms(){
		struct timeval tp;
		gettimeofday(&tp, NULL);
		return tp.tv_sec * 1000 + tp.tv_usec / 1000;
	}

	int split(const std::string& str, std::vector<std::string>& ret_, 
		std::string sep)
	{
	    if (str.empty())
	    {
		return 0;
	    }

	    std::string tmp;
	    std::string::size_type pos_begin = str.find_first_not_of(sep);
	    std::string::size_type comma_pos = 0;

	    while (pos_begin != std::string::npos)
	    {
		comma_pos = str.find(sep, pos_begin);
		if (comma_pos != std::string::npos)
		{
		    tmp = str.substr(pos_begin, comma_pos - pos_begin);
		    pos_begin = comma_pos + sep.length();
		}
		else
		{
		    tmp = str.substr(pos_begin);
		    pos_begin = comma_pos;
		}

		if (!tmp.empty())
		{
		    ret_.push_back(tmp);
		    tmp.clear();
		}
	    }
	    return 0;
	}

	int32 sleep_ms (int32 msec)
	{
		int32  ret = 0; 
		struct epoll_event ev[1];
		int32 fd = epoll_create(1);
		ret = epoll_wait(fd, ev, 1, msec);
		close(fd);
		if(ret < 0){
			printf("sleep_ms err:%s\n", strerror(errno));
		}

		return ret;
	}
};

