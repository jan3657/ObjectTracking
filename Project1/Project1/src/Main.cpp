#include <iostream>
#include "Log.cpp"

int main()
{
	Log log;
	log.SetLevel(log.LogLevelInfo);
	log.Warn("Hello!");
	log.Error("Hello!");
	log.Info("Hello!");
	std::cin.get();
}