#include "csoundwrapper.h"
#include <QThread>
#include <QApplication>
#include <QDebug>

// See https://medium.com/@bluepnume/learn-about-promises-before-you-start-using-async-await-eb148164a9c8#.22714eqie.

CsoundWrapper::CsoundWrapper(QObject *parent) : QObject(parent)
{
    csObject = new CsoundObject();
    cs = csObject->getCsound();
    QObject::connect(QApplication::instance(), &QApplication::aboutToQuit, csObject, &CsoundObject::stop);
    QObject::connect(csObject, SIGNAL(statusChanged(int)), this, SIGNAL(stateChanged(int)));
}

void CsoundWrapper::play(QString csd)
{

    csObject->setCsd(csd);
    csObject->start(); // start playiback in separate thread
}

//void CsoundWrapper::setControlChannel(QString channel, double value)
//{
//	//qDebug()<<"CsoundWrapper::setControlChannel  channel: "<< channel << "value: "<<value;
//    cs->SetChannel(channel.toLocal8Bit(),value);  // bad practice to access object from another thread, but let it be now...
//}

//double CsoundWrapper::getControlChannel(QString channel)
//{
//    double value = cs->GetChannel(channel.toLocal8Bit());
//	//qDebug()<<"CsoundWrapper::getControlChannel " << channel << " value: " << value;
//    return value;
//}

void CsoundWrapper::stop()
{
    csObject->stop();
}

//void CsoundWrapper::readScore(QString score)
//{
//    qDebug()<<"CsoundWrapper::readScore New event: "<<score;
//    cs->ReadScore(score.toLocal8Bit());
//}


int CsoundWrapper::compileCsd(const QString &filename) {
	return cs->CompileCsd(filename.toLocal8Bit().data());
}

int CsoundWrapper::compileCsdText(const QString &text) {
	return cs->CompileCsdText(text.toLocal8Bit().data());
}

int CsoundWrapper::compileOrc(const QString &text) {
	return cs->CompileOrc(text.toLocal8Bit().data());
}

double CsoundWrapper::evalCode(const QString &text) {
	return cs->EvalCode(text.toLocal8Bit().data());
}

double CsoundWrapper::get0dBFS() {
	return cs->Get0dBFS();
}

int CsoundWrapper::getApiVersion() {
	return cs->GetAPIVersion();
}

double CsoundWrapper::getControlChannel(const QString &name) {
	return cs->GetChannel(name.toLocal8Bit().data());
}

qint64 CsoundWrapper::getCurrentTimeSamples() { // FIXME: unknown type int64_t qint64
	return cs->GetCurrentTimeSamples();
}

QString CsoundWrapper::getEnv(const QString &name) { // not sure, if it works... test with setGlobalEnv
	return cs->GetEnv(name.toLocal8Bit());
}

int CsoundWrapper::getKsmps() {
	return cs->GetKsmps();
}

int CsoundWrapper::getNchnls() {
	return cs->GetNchnls();
}

int CsoundWrapper::getNchnlsInput() {
	return cs->GetNchnlsInput();
}

QString CsoundWrapper::getOutputName() {
	return cs->GetOutputName();
}

double CsoundWrapper::getScoreOffsetSeconds() {
	return cs->GetScoreOffsetSeconds();
}

double CsoundWrapper::getScoreTime() {
	return cs->GetScoreTime();
}

int CsoundWrapper::getSr() {
	return cs->GetSr();
}

QString CsoundWrapper::getStringChannel(const QString &name) {
	char buffer[0x100];
	cs->GetStringChannel(name.toLocal8Bit(), buffer);
	return buffer;
}

int CsoundWrapper::getVersion() {
	return cs->GetVersion();
}

bool CsoundWrapper::isPlaying() {
	return false; // ((stop_ == false) && (finished == false));OffsetSeconds// TODO:!
}

int CsoundWrapper::isScorePending() {
	return cs->IsScorePending();
}

void CsoundWrapper::message(const QString &text) {
	cs->Message(text.toLocal8Bit());
}

int CsoundWrapper::perform() {
	return cs->Perform();
}

int CsoundWrapper::readScore(const QString &text) {
   return cs->ReadScore(text.toLocal8Bit());
}

void CsoundWrapper::rewindScore() {
	cs->RewindScore();
}

int CsoundWrapper::runUtility(const QString &command, int argc, char **argv) {
	return cs->RunUtility(command.toLocal8Bit(), argc, argv);
}

 int CsoundWrapper::scoreEvent(char type, const double *pFields, long numFields) { // does not work... - unknown type const double *'
	return cs->ScoreEvent(type, pFields, numFields);
}

 void CsoundWrapper::setControlChannel(const QString &name, double value) {
	cs->SetChannel(name.toLocal8Bit(), value);
}

 int CsoundWrapper::setGlobalEnv(const QString &name, const QString &value) {
	return cs->SetGlobalEnv(name.toLocal8Bit(), value.toLocal8Bit());
}

 void CsoundWrapper::setInput(const QString &name){
	cs->SetInput(name.toLocal8Bit().data());
}

 int CsoundWrapper::setOption(const QString &name){
	return cs->SetOption((char *)name.toLocal8Bit().data());
}

 void CsoundWrapper::setOutput(const QString &name, const QString &type, const QString &format){
	cs->SetOutput((char *)name.toStdString().c_str(), (char *)type.toStdString().c_str(), (char *)format.toStdString().c_str());
}

 void CsoundWrapper::setScoreOffsetSeconds(double value){
	cs->SetScoreOffsetSeconds(value);
}

 void CsoundWrapper::setScorePending(bool value){
	cs->SetScorePending(value);
}

 void CsoundWrapper::setStringChannel(const QString &name, const QString &value){
	cs->SetChannel(name.toStdString().c_str(), (char *)value.toStdString().c_str());
}

 double CsoundWrapper::tableGet(int table_number, int index){
	return cs->TableGet(table_number, index);
}

 int CsoundWrapper::tableLength(int table_number){
	return cs->TableLength(table_number);
}

 void CsoundWrapper::tableSet(int table_number, int index, double value){
	cs->TableSet(table_number, index, value);
}



