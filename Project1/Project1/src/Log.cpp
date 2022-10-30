#include <iostream>

class Log
{
public:
	int LogLevelError = 0;
	int LogLevelWarning = 1;
	int LogLevelInfo = 2;
private:
	int m_LogLevel = LogLevelInfo;

public:
	void SetLevel(int level)
	{
		m_LogLevel = level;
	}

	void Warn(const char* message)
	{
		if (m_LogLevel >= LogLevelError)
			std::cout << "[WARNING]: " << message << std::endl;
	}

	void Error(const char* message)
	{
		if (m_LogLevel >= LogLevelWarning)
			std::cout << "[ERROR]: " << message << std::endl;
	}

	void Info(const char* message)
	{
		if (m_LogLevel >= LogLevelInfo)
			std::cout << "[INFO]: " << message << std::endl;
	}


};