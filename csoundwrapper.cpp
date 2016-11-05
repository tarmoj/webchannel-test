#include "csoundwrapper.h"
#include <QThread>
#include <QApplication>
#include <QDebug>

// See https://medium.com/@bluepnume/learn-about-promises-before-you-start-using-async-await-eb148164a9c8#.22714eqie.

CsoundWrapper::CsoundWrapper(QObject *parent) : QObject(parent)
{
    csObject = new CsoundObject();
    cs = csObject->getCsound();
	csound = cs->GetCsound(); // pointer to C API csound object - closer to CsoundQt usag
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

int CsoundWrapper::compileCsd(const QString &filename) {
    return csoundCompileCsd(csound, filename.toLocal8Bit().data());
}

int CsoundWrapper::compileCsdText(const QString &text) {
	return csoundCompileCsdText(csound, text.toLocal8Bit());
}

int CsoundWrapper::compileOrc(const QString &text) {
	return csoundCompileOrc(csound, text.toLocal8Bit());
}

double CsoundWrapper::evalCode(const QString &text) {
	return csoundEvalCode(csound, text.toLocal8Bit());
}

double CsoundWrapper::get0dBFS() {
	return csoundGet0dBFS(csound); //cs->Get0dBFS();
}

int CsoundWrapper::getApiVersion() {
	return csoundGetAPIVersion();
}

double CsoundWrapper::getControlChannel(const QString &name) {
	int result = 0;
	double value = csoundGetControlChannel(csound, name.toLocal8Bit(), &result);
	return value;
}

qint64 CsoundWrapper::getCurrentTimeSamples() { // FIXME: unknown type int64_t qint64
	return csoundGetCurrentTimeSamples(csound);
}

QString CsoundWrapper::getEnv(const QString &name) { // not sure, if it works... test with setGlobalEnv
	return csoundGetEnv(csound,name.toLocal8Bit());
}

int CsoundWrapper::getKsmps() {
	return csoundGetKsmps(csound);
}

int CsoundWrapper::getNchnls() {
	return csoundGetNchnls(csound);
}

int CsoundWrapper::getNchnlsInput() {
	return csoundGetNchnlsInput(csound);
}

QString CsoundWrapper::getOutputName() {
	return QString(csoundGetOutputName(csound));
}

double CsoundWrapper::getScoreOffsetSeconds() {
	return csoundGetScoreOffsetSeconds(csound);
}

double CsoundWrapper::getScoreTime() {
	return csoundGetScoreTime(csound);
}

int CsoundWrapper::getSr() {
	return csoundGetSr(csound);
}

QString CsoundWrapper::getStringChannel(const QString &name) {
	char buffer[0x100];
	csoundGetStringChannel(csound,name.toLocal8Bit(), buffer);
	return QString(buffer);
}

int CsoundWrapper::getVersion() {
	return csoundGetVersion();
}

bool CsoundWrapper::isPlaying() {
	return false; // ((stop_ == false) && (finished == false));OffsetSeconds// TODO:!
}

int CsoundWrapper::isScorePending() {
	return csoundIsScorePending(csound);
}

void CsoundWrapper::message(const QString &text) {
	csoundMessage(csound, text.toLocal8Bit());
}

int CsoundWrapper::perform() {
	return csoundPerform(csound);
}

int CsoundWrapper::readScore(const QString &text) {
   return csoundReadScore(csound, text.toLocal8Bit());
}

void CsoundWrapper::rewindScore() {
	csoundRewindScore(csound);
}

int CsoundWrapper::runUtility(const QString &command, int argc, char **argv) {
	return csoundRunUtility(csound, command.toLocal8Bit(), argc, argv); // probably does not work from JS due char **
}

 int CsoundWrapper::scoreEvent(char type, const double *pFields, long numFields) { // does not work... - unknown type const double *'
	return csoundScoreEvent(csound,type, pFields, numFields);
}

 void CsoundWrapper::setControlChannel(const QString &name, double value) {
	csoundSetControlChannel(csound,name.toLocal8Bit(), value);
}

 int CsoundWrapper::setGlobalEnv(const QString &name, const QString &value) {
	return csoundSetGlobalEnv(name.toLocal8Bit(), value.toLocal8Bit());
}

 void CsoundWrapper::setInput(const QString &name){
    csoundSetInput(csound, name.toLocal8Bit().data());
}

 int CsoundWrapper::setOption(const QString &name){
    return csoundSetOption(csound, name.toLocal8Bit().data());
}

 void CsoundWrapper::setOutput(const QString &name, const QString &type, const QString &format){
    csoundSetOutput(csound, name.toLocal8Bit().data(), type.toLocal8Bit().data(), format.toLocal8Bit().data()); // csound version problem?
}

 void CsoundWrapper::setScoreOffsetSeconds(double value){
	csoundSetScoreOffsetSeconds(csound, value);
}

 void CsoundWrapper::setScorePending(bool value){
	csoundSetScorePending(csound,(int) value);
}

 void CsoundWrapper::setStringChannel(const QString &name, const QString &value){
	csoundSetStringChannel(csound,  name.toLocal8Bit(), value.toLocal8Bit().data());
}

 double CsoundWrapper::tableGet(int table_number, int index){
	return csoundTableGet(csound, table_number, index);
}

 int CsoundWrapper::tableLength(int table_number){
	return csoundTableLength(csound, table_number);
}

 void CsoundWrapper::tableSet(int table_number, int index, double value){
	csoundTableSet(csound, table_number, index, value);
}



