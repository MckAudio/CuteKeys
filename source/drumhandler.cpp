#include "include/drumhandler.h"

DrumHandler::DrumHandler(QObject *parent) : QObject(parent), m_log(""), m_pad(0)
{

}

void DrumHandler::ProcessAudio(double *buffer, unsigned sampleRate, unsigned numSamples)
{

}

void DrumHandler::noteOn(unsigned drum)
{
    std::string tmp = "Pad #" + std::to_string(drum+1) + " pressed";
    m_log = QString::fromStdString(tmp);
    emit LogChanged();
    m_pad = drum + 1;
    emit PadChanged();
}

void DrumHandler::noteOff(unsigned drum)
{
    std::string tmp = "Pad #" + std::to_string(drum+1) + " released";
    m_log = QString::fromStdString(tmp);
    emit LogChanged();
    m_pad = 0;
    emit PadChanged();
}
