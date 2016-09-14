

#ifndef CSOUNDOBJECT_H
#define CSOUNDOBJECT_H

#include <QObject>

#ifdef Q_OS_ANDROID
	#include "AndroidCsound.hpp"
#else
	#include <csound.hpp>
#endif

//#include <csound.h>
class CsoundObject : public QObject
{
	Q_OBJECT
public:
	explicit CsoundObject(QObject *parent = 0);

signals:

public slots:
	Q_INVOKABLE void setChannel(QString channel, double value); // do I need Q_INVOKABLE, if it is a slot...
	Q_INVOKABLE double getChannel(QString channel);
	Q_INVOKABLE void play();
	Q_INVOKABLE void stop();
	Q_INVOKABLE void scoreEvent(QString event);

private:
#ifdef Q_OS_ANDROID
	AndroidCsound  *cs ;
#else
	Csound  *cs;
#endif
	QString csd; // resolve later
	bool stopNow;
};

#endif // CSOUNDOBJECT_H
