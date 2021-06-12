#include "synthvoice.h"
#include <algorithm>
#include <cmath>

SynthVoice::SynthVoice()
    : m_initialized(false)
    , m_sampleRate(0)
    , m_bufferSize(0)
    , m_frequency(400.0)
    , m_gainLin(0.1)
    , m_attackMs(0)
    , m_attackSamps(1)
    , m_releaseMs(0)
    , m_releaseSamps(1)
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
        m_attackSamps = std::max((unsigned) 1, (unsigned)std::round((double)m_attackMs / 1000.0 * (double)m_sampleRate));
    }
    if (releaseMs != m_releaseMs)
    {
        m_releaseMs = std::min(std::max(releaseMs, (unsigned)0), (unsigned)8000);
        m_releaseSamps = std::max((unsigned) 1, (unsigned)std::round((double)m_releaseMs / 1000.0 * (double)m_sampleRate));
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
        m_noteState = ADSR_RELEASE;
    }

    return true;
}

bool SynthVoice::ProcessAdd(double *buffer, unsigned numSamples)
{
    double p = 0.0;
    unsigned phaseLen = std::floor((double) m_sampleRate / m_frequency.load());
    double gain = m_gainLin.load();
    char state = m_noteState.load();

    unsigned attackSamps = m_attackSamps.load();
    unsigned releaseSamps = m_releaseSamps.load();

    unsigned phaseIdx = m_phaseIdx.load();
    unsigned stateIdx = m_stateIdx.load();


    for (unsigned i = 0; i < numSamples; i++)
    {
        switch(state)
        {
        case ADSR_ATTACK:
            m_envelope = (double)stateIdx / (double)attackSamps;
            stateIdx++;
            if (stateIdx >= m_attackSamps)
            {
                stateIdx = 0;
                state = ADSR_SUSTAIN;
            }
            break;
        case ADSR_DECAY:
            m_envelope = 1.0;
            break;
        case ADSR_SUSTAIN:
            m_envelope = 1.0;
            break;
        case ADSR_RELEASE:
            m_envelope = 1.0 - (double)stateIdx / (double)releaseSamps;
            stateIdx++;
            if (stateIdx >= m_releaseSamps)
            {
                stateIdx = 0;
                state= ADSR_IDLE;
            }
            break;
        default:
            m_envelope = 0.0;
            break;
        }

        p = 2.0 * M_PI * (double)phaseIdx / (double)phaseLen;
        buffer[i] += m_envelope * gain * std::sin(p);
        phaseIdx = (phaseIdx + 1) % phaseLen;
    }

    m_noteState = state;
    m_phaseIdx = phaseIdx;
    m_stateIdx = stateIdx;
    return 0;
}
