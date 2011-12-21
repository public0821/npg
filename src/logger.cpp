#ifdef _DEBUG
#include "logger.h"

Logger::Logger()
{

}

Logger::~Logger()
{

}

void Logger::log(const QString& info)
{
	QMessageBox::information(NULL, "log", info);
}
#endif
