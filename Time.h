#pragma once
#include <string>
class Time
{
public:
	Time(int H, int M) :H(H), M(M) {}
	
	bool operator <(const Time& time)
	{
		if (H != time.H)
			return M < time.M;
		return M < time.M;
	}
	bool operator <=(const Time& time)
	{
		if (H != time.H)
			return H < time.H;
		return M <= time.M;
	}
	
	Time operator -(const Time& time)
	{
		int newM = M - time.M;
		int newH = H - time.H;
		if (newM < 0)
		{
			--newH;
			newM += 60;
		}
		return Time(newH, newM);
	}
	
	std::string str() const
	{
		std::string res;
		res += H < 10 ? "0" + std::to_string(H): std::to_string(H);
		res += ":";
		res += M < 10 ? "0" + std::to_string(M) : std::to_string(M);
		return res;
	}

private:
	int H = 0;
	int M = 0;
};