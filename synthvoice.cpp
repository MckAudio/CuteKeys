#include "synthvoice.h"
#include <algorithm>
#include <cmath>

SynthVoice::SynthVoice()
    : m_initialized(false)
    , m_sampleRate(0)
    , m_bufferSize(0)
    , m_frequency(400.0)
    , m_gainLin(0.1)
    , m_attackMs(100)
    , m_attackSamps(0)
    , m_releaseMs(1000)
    , m_releaseSamps(0)
    , m_envelope(1.0)
    , m_character(0.0)
    , m_noteState(ADSR_IDLE)
    , m_stateIdx(0)
    , m_phaseIdx(0)
{

}

SynthVoice::~SynthVoice()
{
    m_initialized = false;
}

bool SynthVoice::Init(unsigned int sampleRate, unsigned int bufferSize)
{
    if (m_initialized)
    {
        return false;
    }
    m_sampleRate = sampleRate;
    m_bufferSize = bufferSize;

    m_initialized = true;
    return true;
}

bool SynthVoice::NoteOn(double frequency, double gainLin, unsigned int attackMs, unsigned int releaseMs)
{
    if (m_initialized == false)
    {
        return false;
    }

    m_frequency = std::min(std::max(frequency, 20.0), 20000.0);
    m_gainLin = std::min(std::max(gainLin, 0.0), 1.0);

    if (attackMs != m_attackMs)
    {
        m_attackMs = std::min(std::max(attackMs, (unsigned)0), (unsigned)8000);
        m_attackSamps = (double)m_attackMs * 1000.0 / (double)m_sampleRate;
    }
    if (releaseMs != m_releaseMs)
    {
        m_releaseMs = std::min(std::max(releaseMs, (unsigned)0), (unsigned)8000);
        m_releaseSamps = (double)m_releaseMs * 1000.0 / (double)m_sampleRate;
    }

    m_noteState = ADSR_ATTACK;
    m_stateIdx = 0;
    m_phaseIdx = 0;

    return true;
}

bool SynthVoice::NoteOff()
{
    if (m_initialized == false)
    {
        return false;
    }

    if (m_noteState.load() <= ADSR_SUSTAIN)
    {
        m_noteState = ADSR_SUSTAIN;
    }

    return true;
}

bool SynthVoice::ProcessAdd(double *buffer, unsigned numSamples)
{
    double p = 0.0;
    unsigned phaseLen = std::floor((double) m_sampleRate / m_frequency.load());
    double masterGain = m_gainLin.load();
    double gain = 0.0;
    char state = m_noteState.load();

    unsigned attackSamps = m_attackSamps.load();
    unsigned releaseSamps = m_releaseSamps.load();


    for (unsigned i = 0; i < numSamples; i++)
    {
        switch(state)
        {
        case ADSR_ATTACK:
            gain = (double)m_stateIdx / (double)attackSamps;
            m_stateIdx++;
            if (m_stateIdx >= m_attackSamps)
            {
                m_stateIdx = 0;
                state = ADSR_SUSTAIN;
            }
            break;
        case ADSR_DECAY:
            gain = 1.0;
            break;
        case ADSR_SUSTAIN:
            gain = 1.0;
            break;
        case ADSR_RELEASE:
            gain = 1.0 - (double)m_stateIdx / (double)releaseSamps;
            m_stateIdx++;
            if (m_stateIdx >= m_releaseSamps)
            {
                m_stateIdx = 0;
                state= ADSR_IDLE;
            }
            break;
        default:
            gain = 0.0;
            break;
        }

        p = 2.0 * M_PI * (double)m_phaseIdx / (double)phaseLen;
        buffer[i] += gain * masterGain * std::sin(p);
        m_phaseIdx = (m_phaseIdx + 1) % phaseLen;
    }

    m_noteState = state;

    return 0;
}
