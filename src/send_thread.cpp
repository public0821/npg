/*
 * SendThread.cpp
 *
 *  Created on: 2011-8-24
 *      Author: wuyangchun
 */

#include "send_thread.h"
#include "tab_sheet.h"
#include <QTime>

SendThread::SendThread(TabSheet*parent) :
		m_parent(parent), m_running(false)
{
	connect(this, SIGNAL(finished(void)), this, SLOT(onSendFinish(void)));
	connect(&m_timer, SIGNAL(timeout()), this, SLOT(onTimer()));
}

SendThread::~SendThread()
{
	// TODO Auto-generated destructor stub
}

void SendThread::start(SendType type, int count)
{
	m_type = type;
	m_count = count;
	m_error.clear();
	m_running = true;
	m_timer.start(1000); //1 second
	QThread::start();
}

void SendThread::run()
{
	m_totalSend = 0;
	m_timeConsuming = 0;

	m_error = m_parent->beforeSendData();
	if (m_error.isEmpty())
	{
		switch (m_type)
		{
		case E_TOTAL:
			sendTotal(m_count);
			break;
		case E_SPEED:
			sendPerSeconds(m_count);
			break;
		default:
			break;
		}
	}

	emit
	counter(m_totalSend, m_timeConsuming);

	m_running = false;
}

void SendThread::sendTotal(int count)
{
	for (m_totalSend = 0; m_totalSend < count; m_totalSend++)
	{
		if (!m_running)
		{
			break;
		}
		m_error = m_parent->sendData();
		if (!m_error.isEmpty())
		{
			break;
		}
	}

}

void SendThread::sendPerSeconds(int count)
{
	QTime time;
	while (true)
	{
		time.start();
		for (int i = 0; i < count; i++)
		{
			if (!m_running)
			{
				return;
			}
			m_error = m_parent->sendData();
			m_totalSend++;
			if (!m_error.isEmpty())
			{
				break;
			}
			int timeElapsed = time.elapsed();

			int moreTime = (double) 1000 / count * (i+1) - timeElapsed;
			if (moreTime > 0)
			{
				msleep(moreTime);
			}
		}
	}
}

void SendThread::onTimer()
{
	m_timeConsuming++;
	emit counter(m_totalSend, m_timeConsuming);
}

void SendThread::onSendFinish()
{
	m_timer.stop();
}
