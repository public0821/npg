/*
 * SendThread.cpp
 *
 *  Created on: 2011-8-24
 *      Author: Young <public0821@gmail.com>
 */

#include "send_thread.h"
#include "widget/tab_sheet.h"
#include <QTime>

SendThread::SendThread(TabSheet*parent) :
		m_parent(parent), m_running(false)
{
	connect(this, SIGNAL(finished(void)), this, SLOT(onSendFinish(void)));
	connect(&m_timer, SIGNAL(timeout()), this, SLOT(onTimer()));
}

SendThread::~SendThread()
{
}

void SendThread::start(ESendType type, int count)
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
	m_total_send = 0;
	m_time_consuming = 0;

	m_error = m_parent->beforeSendData();
	if (m_error.isEmpty())
	{
		switch (m_type)
		{
		case E_SEND_TYPE_TOTAL:
			sendTotal(m_count);
			break;
		case E_SEND_TYPE_SPEED:
			sendPerSeconds(m_count);
			break;
		default:
			break;
		}
	}

	emit
	counter(m_total_send, m_time_consuming);

	m_running = false;
}

void SendThread::sendTotal(int count)
{
	for (m_total_send = 0; m_total_send < count; m_total_send++)
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
			m_total_send++;
			if (!m_error.isEmpty())
			{
				break;
			}
			int time_elapsed = time.elapsed();
			const int MILLISECOND_SECOND = 1000;
			int more_time = (double) MILLISECOND_SECOND / count * (i+1) - time_elapsed;
			if (more_time > 0)
			{
				msleep(more_time);
			}
		}
	}
}

void SendThread::onTimer()
{
	m_time_consuming++;
	emit counter(m_total_send, m_time_consuming);
}

void SendThread::onSendFinish()
{
	m_timer.stop();
}
