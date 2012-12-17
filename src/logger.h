/*
 * logger.h
 *
 *  Created on: 2012-12-17
 *      Author: Young <public0821@gmail.com>
 */

#ifndef LOGGER_H_
#define LOGGER_H_

#include "lib/types.h"
#include <qstring.h>
#include <qtextbrowser.h>

class Logger {
public:
	enum ELevel {
		TRACE = 1, DEBUG, INFO, WARN, ERROR1
	};

private:
	Logger();

public:
	static Logger& instance();
public:
	void bind(QTextBrowser* browser){
		m_browser = browser;
	}
public:
	void trace(const char* source_file, int line, int err_no);
	void debug(const char* source_file, int line, int err_no);
	void info(const char* source_file, int line, int err_no);
	void warn(const char* source_file, int line, int err_no);
	void error(const char* source_file, int line, int err_no);

	void trace(const char* source_file, int line, const QString& log_info);
	void debug(const char* source_file, int line, const QString& log_info);
	void info(const char* source_file, int line, const QString& log_info);
	void warn(const char* source_file, int line, const QString& log_info);
	void error(const char* source_file, int line, const QString& log_info);

private:
	void log(ELevel level, const char* source_file, int line, const QString& log_info);
private:
	QTextBrowser* m_browser;
};

#define LOG_TRACE(data) Logger::instance().trace(__FILE__, __LINE__, data )
#define LOG_DEBUG(data) Logger::instance().debug(__FILE__, __LINE__, data )
#define LOG_INFO(data) Logger::instance().info(__FILE__, __LINE__, data)
#define LOG_WARN(data) Logger::instance().warn(__FILE__, __LINE__, data )
#define LOG_ERROR(data) Logger::instance().error(__FILE__, __LINE__, data )


#endif /* LOGGER_H_ */
