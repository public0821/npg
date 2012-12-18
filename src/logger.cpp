/*
 * logger.cpp
 *
 *  Created on: 2012-12-17
 *      Author: Young <public0821@gmail.com>
 */

#include "logger.h"
#include "config.h"
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include "lib/os.h"
#include <qobject.h>
#include <qstring.h>

const static int MAX_LOG_LENGTH = 2048;

Logger::Logger() :
		m_browser(NULL) {
	// TODO Auto-generated constructor stub

}

Logger& Logger::instance() {
	static Logger* logger = NULL;
	if (logger == NULL) {
		logger = new Logger();
	}

	return *logger;
}

void Logger::trace(const char* source_file, int line, int err_no) {
	if (G_LOG_LEVEL > TRACE) {
		return;
	}
	char buf[2048];
	int buflen = sizeof(buf);
	if (-1 == npg_strerror(err_no, buf, buflen)) {
		log(TRACE, source_file, line, QObject::tr("get strerror failed"));
	} else {
		log(TRACE, source_file, line, QObject::tr(buf));
	}
}

void Logger::debug(const char* source_file, int line, int err_no) {
	if (G_LOG_LEVEL > DEBUG) {
		return;
	}
	char buf[2048];
	int buflen = sizeof(buf);
	if (-1 == npg_strerror(err_no, buf, buflen)) {
		log(DEBUG, source_file, line, QObject::tr("get strerror failed"));
	} else {
		log(DEBUG, source_file, line, QObject::tr(buf));
	}
}

void Logger::info(const char* source_file, int line, int err_no) {
	if (G_LOG_LEVEL > INFO) {
		return;
	}
	char buf[2048];
	int buflen = sizeof(buf);
	if (-1 == npg_strerror(err_no, buf, buflen)) {
		log(INFO, source_file, line, QObject::tr("get strerror failed"));
	} else {
		log(INFO, source_file, line, QObject::tr(buf));
	}
}

void Logger::warn(const char* source_file, int line, int err_no) {
	if (G_LOG_LEVEL > WARN) {
		return;
	}
	char buf[2048];
	int buflen = sizeof(buf);
	if (-1 == npg_strerror(err_no, buf, buflen)) {
		log(WARN, source_file, line, QObject::tr("get strerror failed"));
	} else {
		log(WARN, source_file, line, QObject::tr(buf));
	}
}

void Logger::error(const char* source_file, int line, int err_no) {
	if (G_LOG_LEVEL > ERROR1) {
		return;
	}
	char buf[2048];
	int buflen = sizeof(buf);
	if (-1 == npg_strerror(err_no, buf, buflen)) {
		log(ERROR1, source_file, line, QObject::tr("get strerror failed"));
	} else {
		log(ERROR1, source_file, line, QObject::tr(buf));
	}
}

void Logger::trace(const char* source_file, int line, const QString& log_info) {
	if (G_LOG_LEVEL > TRACE) {
		return;
	}
	log(TRACE, source_file, line, log_info);
}
void Logger::debug(const char* source_file, int line, const QString& log_info) {
	if (G_LOG_LEVEL > DEBUG) {
		return;
	}
	log(DEBUG, source_file, line, log_info);
}
void Logger::info(const char* source_file, int line, const QString& log_info) {
	if (G_LOG_LEVEL > INFO) {
		return;
	}
	log(INFO, source_file, line, log_info);
}
void Logger::warn(const char* source_file, int line, const QString& log_info) {
	if (G_LOG_LEVEL > WARN) {
		return;
	}
	log(WARN, source_file, line, log_info);
}
void Logger::error(const char* source_file, int line, const QString& log_info) {
	if (G_LOG_LEVEL > ERROR1) {
		return;
	}
	log(ERROR1, source_file, line, log_info);
}

void Logger::log(ELevel level, const char* source_file, int line, const QString& log_info) {
	time_t time_now = time(NULL);
	struct tm tm_now = *localtime(&time_now); //multithread problem

	char log_head[MAX_LOG_LENGTH];
	snprintf(log_head, sizeof(log_head), "%04d-%02d-%02d %02d:%02d:%02d", tm_now.tm_year + 1900,
			tm_now.tm_mon + 1, tm_now.tm_mday, tm_now.tm_hour, tm_now.tm_min,
			tm_now.tm_sec);

	size_t tmp_buf_len = strlen(log_head);
	switch (level) {
	case TRACE:
		strncat(log_head, " [TRACE] ", sizeof(log_head) - tmp_buf_len);
		break;
	case DEBUG:
		strncat(log_head, " [DEBUG] ", sizeof(log_head) - tmp_buf_len);
		break;
	case INFO:
		strncat(log_head, " [INFO] ", sizeof(log_head) - tmp_buf_len);
		break;
	case WARN:
		strncat(log_head, " [WARN] ", sizeof(log_head) - tmp_buf_len);
		break;
	case ERROR1:
		strncat(log_head, " [ERROR] ", sizeof(log_head) - tmp_buf_len);
		break;
	default:
		break;
	}
	log_head[sizeof(log_head) - 1] = '\0';
	tmp_buf_len = strlen(log_head);
	snprintf(log_head + tmp_buf_len, sizeof(log_head) - tmp_buf_len, "%s(%d) - ",
			source_file, line);
	log_head[sizeof(log_head) - 1] = '\0';

	//if(log_info.)
	if (m_browser != NULL) {
		m_browser->append(QString(log_head) + log_info);
	}
}
