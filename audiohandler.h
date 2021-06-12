#ifndef AUDIOHANDLER_H
#define AUDIOHANDLER_H

#include <atomic>
#include <QObject>
#include <rtaudio/RtAudio.h>


class SynthVoice;

class AudioHandler : public QObject
{
    Q_OBJECT
public:
    explicit AudioHandler(QObject *parent = nullptr);
    virtual ~AudioHandler();

    bool Init();
    void ProcessAudio(double *buffer, unsigned numSamples);
    unsigned GetSampleRate() { return m_sampleRate; };

    Q_PROPERTY(double gain READ GetGain WRITE SetGain NOTIFY GainChanged);
    double GetGain() { return m_gain; };
    void SetGain(double gain);

signals:
    void GainChanged();

private:
    bool OpenInterface(unsigned idx);
    double DbToLin(double db);

    bool m_initialized;
    unsigned m_sampleRate;
    unsigned m_bufferSize;

    unsigned m_numChannels;
    unsigned m_phaseIdx;
    double m_frequency;

    double m_gain;
    std::atomic<double> m_gainLin;

    RtAudio m_audio;
    std::vector<RtAudio::DeviceInfo> m_devices;

    std::vector<SynthVoice*> m_voices;

    double *m_buffer;
};

#endif // AUDIOHANDLER_H
