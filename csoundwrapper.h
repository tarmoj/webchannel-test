#ifndef CSOUNDWRAPPER_H
#define CSOUNDWRAPPER_H

#include <QObject>
#include <QDebug>
#include "csoundobject.h"
//#include <csound.h>


class CsoundWrapper : public QObject
{
    Q_OBJECT
public:
    explicit CsoundWrapper(QObject *parent = 0);
    Q_INVOKABLE void play(QString csd);
	//Q_INVOKABLE void setControlChannel(QString channel, double value);
	//Q_INVOKABLE double getControlChannel(QString channelName);
    Q_INVOKABLE void stop();
   // Q_INVOKABLE void readScore(QString score);
    Q_INVOKABLE void test(QString message) {qDebug()<<"TEST "<<message;}

	//
	Q_INVOKABLE int compileCsd(const QString &filename);
	Q_INVOKABLE int compileCsdText(const QString &text);
	Q_INVOKABLE int compileOrc(const QString &text);
	Q_INVOKABLE double evalCode(const QString &text);
	Q_INVOKABLE double get0dBFS();
	Q_INVOKABLE int getApiVersion();
	Q_INVOKABLE double getControlChannel(const QString &name);
	Q_INVOKABLE qint64 getCurrentTimeSamples();
	Q_INVOKABLE QString getEnv(const QString &name);
	Q_INVOKABLE int getKsmps();
	Q_INVOKABLE int getNchnls();
	Q_INVOKABLE int getNchnlsInput();
	Q_INVOKABLE QString getOutputName();
	Q_INVOKABLE double getScoreOffsetSeconds();
	Q_INVOKABLE double getScoreTime();
	Q_INVOKABLE int getSr();
	Q_INVOKABLE QString getStringChannel(const QString &name);
	Q_INVOKABLE int getVersion();
	Q_INVOKABLE bool isPlaying();
	Q_INVOKABLE int isScorePending();
	Q_INVOKABLE void message(const QString &text);
	Q_INVOKABLE int perform();
	Q_INVOKABLE int readScore(const QString &text);
	Q_INVOKABLE void rewindScore();

	Q_INVOKABLE int runUtility(const QString &command, int argc, char **argv);
	Q_INVOKABLE int scoreEvent(char type, const double *pFields, long numFields);
	Q_INVOKABLE void setControlChannel(const QString &name, double value);
	Q_INVOKABLE int setGlobalEnv(const QString &name, const QString &value);
	Q_INVOKABLE void setInput(const QString &name);
	Q_INVOKABLE int setOption(const QString &name);
	Q_INVOKABLE void setOutput(const QString &name, const QString &type, const QString &format);
	Q_INVOKABLE void setScoreOffsetSeconds(double value);
	Q_INVOKABLE void setScorePending(bool value);
	Q_INVOKABLE void setStringChannel(const QString &name, const QString &value);
	Q_INVOKABLE double tableGet(int table_number, int index);
	Q_INVOKABLE int tableLength(int table_number);
	Q_INVOKABLE void tableSet(int table_number, int index, double value);


signals:
    void stateChanged(int state);
private:
    CsoundObject * csObject;
    Csound * cs;
	CSOUND * csound;

};

#endif // CSOUNDWRAPPER_H
