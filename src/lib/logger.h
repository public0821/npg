/*
 * logger.h
 *
 *  Created on: 2012-12-17
 *      Author: Young <public0821@gmail.com>
 */

#ifndef LOGGER_H_
#define LOGGER_H_

#include "types.h"
#include <string>
#include <vector>

class Logger {
public:
	enum ELevel {
		TRACE = 1, DEBUG, INFO, WARN, ERROR
	};

private:
	Logger();

public:
	static Logger& instance();

public:
	void trace(const char* source_file, int line, int err_no);
	void debug(const char* source_file, int line, const char* fmt, ...);
	void info(const char* source_file, int line, const char* fmt, ...);
	void warn(const char* source_file, int line, const char* fmt, ...);
	void error(const char* source_file, int line, const char* fmt, ...);

	void clear() {
		m_logs.clear();
	}

	std::string log_string() const;

	void trace(const char* source_file, int line, const std::string& fmt, ...);
	void debug(const char* source_file, int line, const std::string& fmt, ...);
	void info(const char* source_file, int line, const std::string& fmt, ...);
	void warn(const char* source_file, int line, const std::string& fmt, ...);
	void error(const char* source_file, int line, const std::string& fmt, ...);
	private:
	void log(ELevel level, const char* source_file, int line, const char* log_info);
	private:
	typedef std::pair<std::string, std::string> LogItem;
	std::vector<LogItem> m_logs;
};

#define LOG_TRACE(fmt, a...) Logger::instance().trace(__FILE__, __LINE__, fmt, ##a)
#define LOG_DEBUG(fmt, a...) Logger::instance().debug(__FILE__, __LINE__, fmt, ##a)
#define LOG_INFO(fmt, a...) Logger::instance().info(__FILE__, __LINE__, fmt, ##a)
#define LOG_WARN(fmt, a...) Logger::instance().warn(__FILE__, __LINE__, fmt, ##a)
#define LOG_ERROR(fmt, a...) Logger::instance().error(__FILE__, __LINE__, fmt, ##a)

#define LOG_CLEAR() Logger::instance().clear()
#define LOG_STRING() Logger::instance().log_string()

#endif /* LOGGER_H_ */
