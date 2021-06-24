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

    Q_PROPERTY(unsigned attack READ GetAttack WRITE SetAttack NOTIFY AttackChanged);
    unsigned GetAttack() { return m_attack.load(); };
    void SetAttack(unsigned attack);

    Q_PROPERTY(unsigned release READ GetRelease WRITE SetRelease NOTIFY ReleaseChanged);
    unsigned GetRelease() { return m_release.load(); };
    void SetRelease(unsigned release);

    Q_PROPERTY(double character READ GetCharacter WRITE SetCharacter NOTIFY CharacterChanged);
    double GetCharacter() { return m_character.load(); };
    void SetCharacter(double character);

    const double frequencies[8] = {
        261.63,
        293.66,
        329.63,
        349.23,
        392.00,
        440.00,
        493.88,
        523.25
    };
signals:
    void GainChanged();
    void AttackChanged();
    void ReleaseChanged();
    void CharacterChanged();

public slots:
    void noteOn(unsigned note);
    void noteOff(unsigned note);

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

    std::atomic<unsigned> m_attack;
    std::atomic<unsigned> m_release;
    std::atomic<double> m_character;

    RtAudio m_audio;
    std::vector<RtAudio::DeviceInfo> m_devices;

    std::vector<std::pair<int, SynthVoice*>> m_voices;
    double *m_buffer;
};

#endif // AUDIOHANDLER_H
