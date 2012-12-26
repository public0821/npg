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

//	bool isRunning() const
//	{
//		return m_running;
//	}
signals:
//	void error(const QString&);
	void counter(int, int);
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

	ESendType m_type;
	int m_count;

	int m_total_send;
	int m_time_consuming;
	QTimer m_timer;
};
#endif /* SENDTHREAD_H_ */
