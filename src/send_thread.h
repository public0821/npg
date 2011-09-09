/*
 * SendThread.h
 *
 *  Created on: 2011-8-24
 *      Author: wuyangchun
 */

#ifndef SENDTHREAD_H_
#define SENDTHREAD_H_

#include <qthread.h>
#include <qtimer.h>

enum SendType
{
	E_SPEED = 1, E_TOTAL
};

class TabSheet;
class SendThread: public QThread
{
Q_OBJECT
public:
	SendThread(TabSheet*parent);
	virtual ~SendThread();
public:
	void stop()
	{
		m_running = false;
	}
	void start(SendType type, int count);

	const QString& getError() const
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
	QString m_error;

	SendType m_type;
	int m_count;

	int m_totalSend;
	int m_timeConsuming;
	QTimer m_timer;
};
#endif /* SENDTHREAD_H_ */
