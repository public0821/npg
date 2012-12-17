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

const static int MAX_LOG_LENGTH = 2048;

Logger::Logger() {
	// TODO Auto-generated constructor stub

}

Logger& Logger::instance() {
	static Logger* logger = NULL;
	if (logger == NULL) {
		logger = new Logger();
	}

	return *logger;
}

std::string Logger::log_string() const {
	std::string log_str;
	for (size_t i = 0; i < m_logs.size(); i++) {
		log_str += m_logs[i].first;
		log_str += " - ";
		log_str += m_logs[i].second;
		log_str += "\n";
	}
	return log_str;
}

void Logger::trace(const char* source_file, int line, const char* fmt, ...) {
	if (G_LOG_LEVEL > TRACE) {
		return;
	}
	va_list vap;
	va_start(vap, fmt);
	char log_buf[MAX_LOG_LENGTH];
	vsnprintf(log_buf, sizeof(log_buf), fmt, vap);
	log(TRACE, source_file, line, log_buf);
	va_end(vap);
}

void Logger::debug(const char* source_file, int line, const char* fmt, ...) {
	if (G_LOG_LEVEL > DEBUG) {
		return;
	}
	va_list vap;
	va_start(vap, fmt);
	char log_buf[MAX_LOG_LENGTH];
	vsnprintf(log_buf, sizeof(log_buf), fmt, vap);
	log(DEBUG, source_file, line, log_buf);
	va_end(vap);
}

void Logger::info(const char* source_file, int line, const char* fmt, ...) {
	if (G_LOG_LEVEL > INFO) {
		return;
	}
	va_list vap;
	va_start(vap, fmt);
	char log_buf[MAX_LOG_LENGTH];
	vsnprintf(log_buf, sizeof(log_buf), fmt, vap);
	log(INFO, source_file, line, log_buf);
	va_end(vap);
}

void Logger::warn(const char* source_file, int line, const char* fmt, ...) {
	if (G_LOG_LEVEL > WARN) {
		return;
	}
	va_list vap;
	va_start(vap, fmt);
	char log_buf[MAX_LOG_LENGTH];
	vsnprintf(log_buf, sizeof(log_buf), fmt, vap);
	log(WARN, source_file, line, log_buf);
	va_end(vap);
}

void Logger::error(const char* source_file, int line, const char* fmt, ...) {
	if (G_LOG_LEVEL > ERROR) {
		return;
	}
	va_list vap;
	va_start(vap, fmt);
	char log_buf[MAX_LOG_LENGTH];
	vsnprintf(log_buf, sizeof(log_buf), fmt, vap);
	log(ERROR, source_file, line, log_buf);
	va_end(vap);
}

void Logger::trace(const char* source_file, int line, const std::string& fmt, ...) {
	if (G_LOG_LEVEL > TRACE) {
		return;
	}
	va_list vap;
	va_start(vap, fmt);
	char log_buf[MAX_LOG_LENGTH];
	vsnprintf(log_buf, sizeof(log_buf), fmt.c_str(), vap);
	log(TRACE, source_file, line, log_buf);
	va_end(vap);
}
void Logger::debug(const char* source_file, int line, const std::string& fmt, ...) {
	if (G_LOG_LEVEL > DEBUG) {
		return;
	}
	va_list vap;
	va_start(vap, fmt);
	char log_buf[MAX_LOG_LENGTH];
	vsnprintf(log_buf, sizeof(log_buf), fmt.c_str(), vap);
	log(DEBUG, source_file, line, log_buf);
	va_end(vap);
}
void Logger::info(const char* source_file, int line, const std::string& fmt, ...) {
	if (G_LOG_LEVEL > INFO) {
		return;
	}
	va_list vap;
	va_start(vap, fmt);
	char log_buf[MAX_LOG_LENGTH];
	vsnprintf(log_buf, sizeof(log_buf), fmt.c_str(), vap);
	log(INFO, source_file, line, log_buf);
	va_end(vap);
}
void Logger::warn(const char* source_file, int line, const std::string& fmt, ...) {
	if (G_LOG_LEVEL > WARN) {
		return;
	}
	va_list vap;
	va_start(vap, fmt);
	char log_buf[MAX_LOG_LENGTH];
	vsnprintf(log_buf, sizeof(log_buf), fmt.c_str(), vap);
	log(WARN, source_file, line, log_buf);
	va_end(vap);
}
void Logger::error(const char* source_file, int line, const std::string& fmt, ...) {
	if (G_LOG_LEVEL > ERROR) {
		return;
	}
	va_list vap;
	va_start(vap, fmt);
	char log_buf[MAX_LOG_LENGTH];
	vsnprintf(log_buf, sizeof(log_buf), fmt.c_str(), vap);
	log(ERROR, source_file, line, log_buf);
	va_end(vap);
}

void Logger::log(ELevel level, const char* source_file, int line, const char* log_info) {
	struct tm tm_now;
	time_t time_now = time(NULL);
	localtime_r(&time_now, &tm_now);

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
	case ERROR:
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
	m_logs.push_back(std::make_pair(log_head, log_info));
}
