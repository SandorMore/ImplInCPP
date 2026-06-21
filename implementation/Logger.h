#pragma once

#include <string>
#include <memory>

class Logger 
{
public:
	void Log(const std::string& message) const;
private:
	Logger();
	~Logger();

	class Impl;
	std::unique_ptr<Impl> impl;
};