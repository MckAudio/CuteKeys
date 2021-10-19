#ifndef SYNTHVOICE_H
#define SYNTHVOICE_H

#include <atomic>
#include <cmath>

class SynthVoice
{
public:
    enum {
        ADSR_ATTACK = 0,
        ADSR_DECAY,
        ADSR_SUSTAIN,
        ADSR_RELEASE,
        ADSR_IDLE,
        ADSR_LENGTH
    };

    //double M_PI = 2.0 * std::asin(1.0);

    SynthVoice();
    ~SynthVoice();
    bool Init(unsigned sampleRate, unsigned bufferSize);
    bool IsIdle() { return m_noteState == ADSR_IDLE; };

    bool NoteOn(double frequency, double gainLin, unsigned attackMs = 100, unsigned releaseMs = 1000, double character = 0.0);
    bool NoteOff();

    bool ProcessAdd(double *buffer, unsigned numSamples);


private:
    double GetToneSample(double &phase, double &character);
    double GetSine(double &phase);
    double GetRect(double &phase);
    double GetTri(double &phase);
    bool m_initialized;
    unsigned m_sampleRate;
    unsigned m_bufferSize;

    std::atomic<double> m_frequency;
    std::atomic<double> m_gainLin;
    unsigned m_attackMs;
    std::atomic<unsigned> m_attackSamps;
    unsigned m_releaseMs;
    std::atomic<unsigned> m_releaseSamps;

    double m_envelope;

    std::atomic<double> m_character;

    char m_noteState; // 0 - Attack, 1 - Decay, 2 - Sustain, 3 - Release, 4 - None
    std::atomic<bool> m_noteOn;
    bool m_curNoteOn;
    unsigned m_stateIdx;

    // Tone Generator
    unsigned m_phaseIdx;
};

#endif // SYNTHVOICE_H
