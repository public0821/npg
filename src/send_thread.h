/*
 * SendThread.h
 *
 *  Created on: 2011-8-24
 *      Author: Young <public0821@gmail.com>
 */

#ifndef SENDTHREAD_H_
#define SENDTHREAD_H_

#include <qthread.h>
#include <qtimer.h>

enum ESendType
{
	E_SEND_TYPE_SPEED = 1, E_SEND_TYPE_TOTAL
};

class TabSheet;
class SendThread: public QThread
{
Q_OBJECT
public:
	SendThread(TabSheet*parent);
	~SendThread();
public:
	void stop()
	{
		m_running = false;
	}
	void start(ESendType type, int count);

	const QString& error() const
	{
		return m_error;
	}
	;
//	bool isRunning() const
//	{
//		return m_running;
//	}
signals:
//	void error(const QString&);
	void counter(int, time_t);
private slots:
	void onTimer();
	void onSendFinish();
private:
	void run();
	void sendTotal(int count);
	void sendPerSeconds(int count);
private:
	TabSheet* m_parent;
	volatile bool m_running;
	QString m_error;

	ESendType m_type;
	int m_count;

	int m_total_send;
	time_t m_time_consuming;
	QTimer m_timer;
};
#endif /* SENDTHREAD_H_ */
