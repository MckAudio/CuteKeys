#ifndef DRUMHANDLER_H
#define DRUMHANDLER_H

#include <QObject>
#include <QString>
#include <string>

class DrumHandler : public QObject
{
    Q_OBJECT
public:
    explicit DrumHandler(QObject *parent = nullptr);

    void ProcessAudio(double *buffer, unsigned sampleRate, unsigned numSamples);

    Q_PROPERTY(QString log READ GetLog NOTIFY LogChanged);
    QString GetLog() { return m_log; };

    Q_PROPERTY(double pad READ GetPad NOTIFY PadChanged);
    double GetPad() { return (double)m_pad; };

signals:
    void LogChanged();
    void PadChanged();
    /*
    void FmFrequencyChanged();
    void FmAmountChanged();
    void FreqencyChanged();
    void CharacterChanged();
    */
public slots:
    void noteOn(unsigned drum);
    void noteOff(unsigned drum);

private:
    QString m_log;
    unsigned m_pad;
};

#endif // DRUMHANDLER_H
