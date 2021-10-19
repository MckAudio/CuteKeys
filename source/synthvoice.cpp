#include "include/synthvoice.h"
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
    , m_noteOn(false)
    , m_curNoteOn(false)
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

bool SynthVoice::NoteOn(double frequency, double gainLin, unsigned int attackMs, unsigned int releaseMs, double character)
{
    if (m_initialized == false)
    {
        return false;
    }

    m_frequency = std::min(std::max(frequency, 20.0), 20000.0);
    m_gainLin = std::min(std::max(gainLin, 0.0), 1.0);
    m_character = std::min(std::max(character, -1.0), 1.0);

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

    m_noteOn = true;

    return true;
}

bool SynthVoice::NoteOff()
{
    if (m_initialized == false)
    {
        return false;
    }

    m_noteOn = false;

    return true;
}

bool SynthVoice::ProcessAdd(double *buffer, unsigned numSamples)
{
    double p = 0.0;
    unsigned phaseLen = std::floor((double) m_sampleRate / m_frequency.load());
    double gain = m_gainLin.load();

    unsigned attackSamps = m_attackSamps.load();
    unsigned releaseSamps = m_releaseSamps.load();

    bool noteOn = m_noteOn.load();

    double character = m_character.load();

    if (noteOn != m_curNoteOn)
    {
        if (noteOn)
        {
            m_noteState = ADSR_ATTACK;
            m_stateIdx = 0;
            m_phaseIdx = 0;
        } else if (m_noteState == ADSR_SUSTAIN) {
            m_noteState = ADSR_RELEASE;
            m_stateIdx = 0;
        } else {
            // Memorise current state
            double coeff = (double)m_stateIdx / (double)attackSamps;
            m_stateIdx = (unsigned) std::floor((1.0 - coeff) * (double)releaseSamps);
            m_noteState = ADSR_RELEASE;
        }
        m_curNoteOn = noteOn;
    }

    for (unsigned i = 0; i < numSamples; i++)
    {
        switch(m_noteState)
        {
        case ADSR_ATTACK:
            m_envelope = (double)m_stateIdx / (double)attackSamps;
            m_stateIdx++;
            if (m_stateIdx >= m_attackSamps)
            {
                m_stateIdx = 0;
                m_noteState = ADSR_SUSTAIN;
            }
            break;
        case ADSR_DECAY:
            m_envelope = 1.0;
            break;
        case ADSR_SUSTAIN:
            m_envelope = 1.0;
            break;
        case ADSR_RELEASE:
            m_envelope = 1.0 - (double)m_stateIdx / (double)releaseSamps;
            m_stateIdx++;
            if (m_stateIdx >= m_releaseSamps)
            {
                m_stateIdx = 0;
                m_noteState = ADSR_IDLE;
            }
            break;
        default:
            m_envelope = 0.0;
            break;
        }

        p = 2.0 * M_PI * (double)m_phaseIdx / (double)phaseLen;
        buffer[i] += m_envelope * gain * GetToneSample(p, character);
        m_phaseIdx = (m_phaseIdx + 1) % phaseLen;
    }
    return 0;
}

double SynthVoice::GetToneSample(double &phase, double &character)
{
    if (character >= 0.0) {
        return (1.0 - character) * GetSine(phase) + character * GetRect(phase);
    } else {
        return (character + 1.0) * GetSine(phase) - character * GetTri(phase);
    }
}

double SynthVoice::GetSine(double &phase)
{
    return 0.9 * std::sin(phase);
}
double SynthVoice::GetRect(double &phase)
{
    return 0.9 * phase >= M_PI ? -1.0 : 1.0;
}
double SynthVoice::GetTri(double &phase)
{
    return 0.9 * (phase - M_PI) / (2.0 * M_PI);
}
