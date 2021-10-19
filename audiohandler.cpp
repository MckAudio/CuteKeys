#include "audiohandler.h"
#include "synthvoice.h"
#include "drumhandler.h"
#include <cmath>

int process(void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames, double streamTime, RtAudioStreamStatus status, void *userData)
{
    AudioHandler *audioHandler = (AudioHandler *)userData;

    double *buffer = (double *)outputBuffer;

    audioHandler->ProcessAudio(buffer, nBufferFrames);

    return 0;
}

AudioHandler::AudioHandler(QObject *parent)
    : QObject(parent)
    , m_initialized(false)
    , m_sampleRate(48000)
    , m_bufferSize(512)
    , m_numChannels(1)
    , m_phaseIdx(0)
    , m_frequency(440.0)
    , m_gain(-6.0)
    , m_gainLin(0.1)
    , m_attack(100)
    , m_release(1000)
    , m_character(0.0)
    , m_buffer(nullptr)
{
}

AudioHandler::~AudioHandler()
{
    if (m_initialized)
    {
        if (m_audio.isStreamRunning())
        {
            try {
                m_audio.stopStream();
            }  catch (RtAudioError &e) {
                e.printMessage();
            }
        }

        if (m_audio.isStreamOpen())
        {
            m_audio.closeStream();
        }

        m_initialized = false;
    }

    if (m_buffer != nullptr)
    {
        free(m_buffer);
        m_buffer = nullptr;
    }
}

bool AudioHandler::Init(DrumHandler *drumHandler)
{
    if (m_initialized)
    {
        return false;
    }

    m_drumHandler = drumHandler;

    unsigned deviceCount = m_audio.getDeviceCount();
    m_devices.clear();
    m_devices.resize(deviceCount);

    for (unsigned i = 0; i < deviceCount; i++)
    {
        m_devices[i] = m_audio.getDeviceInfo(i);
    }

    unsigned outIdx = m_audio.getDefaultOutputDevice();
    m_voices.resize(4);

    m_buffer = (double *) malloc(m_bufferSize * sizeof(double));
    memset(m_buffer, 0, m_bufferSize * sizeof(double));

    m_initialized = OpenInterface(outIdx);

    for(auto &v : m_voices)
    {
        v.first = -1;
        v.second = new SynthVoice();
        v.second->Init(m_sampleRate, m_bufferSize);
    }
    return m_initialized;
}

void AudioHandler::ProcessAudio(double *buffer, unsigned int numSamples)
{
    if (m_initialized == false)
    {
        return;
    }

    double p = 0.0;

    memset(m_buffer, 0, m_bufferSize * sizeof(double));

    for (auto &v : m_voices)
    {
        v.second->ProcessAdd(m_buffer, m_bufferSize);
    }

    if (m_numChannels == 0)
    {
        memcpy(buffer, m_buffer, numSamples);
    } else {
        for (unsigned i = 0; i < std::min(numSamples, m_bufferSize); i++)
        {
            buffer[i*2] = m_buffer[i];
            buffer[i*2+1] = m_buffer[i];
        }
    }

    if (m_drumHandler != nullptr)
    {
        m_drumHandler->ProcessAudio(buffer, m_sampleRate, numSamples);
    }
}

void AudioHandler::SetGain(double gain)
{
    m_gain = std::max(std::min(gain, 0.0), -200.0);
    m_gainLin = DbToLin(m_gain);

    emit GainChanged();
}
void AudioHandler::SetAttack(unsigned int attack)
{
    m_attack = attack;
    emit AttackChanged();
}
void AudioHandler::SetRelease(unsigned int release)
{
    m_release = release;
    emit ReleaseChanged();
}
void AudioHandler::SetCharacter(double character)
{
    m_character = std::max(std::min(character, 1.0), -1.0);
    emit CharacterChanged();
}

void AudioHandler::noteOn(unsigned note)
{
    note = std::min(note, (unsigned) 7);
    for (auto &v : m_voices)
    {
        if (v.second->IsIdle())
        {
            if (v.second->NoteOn(frequencies[note], m_gainLin.load(), m_attack.load(), m_release.load(), m_character.load())) {
                v.first = note;
                break;
            }
        }
    }
}

void AudioHandler::noteOff(unsigned note)
{
    for (auto &v : m_voices)
    {
        if (v.first >= 0 && v.first == (int)note)
        {
            v.second->NoteOff();
            v.first = -1;
            break;
        }
    }
}

bool AudioHandler::OpenInterface(unsigned int idx)
{
    if (idx >= m_devices.size())
    {
        return false;
    }

    RtAudio::StreamParameters param;
    param.deviceId = idx;
    param.firstChannel = 0;
    param.nChannels = m_devices[idx].outputChannels > 2 ? 2 : m_devices[idx].outputChannels;
    m_numChannels = param.nChannels;
    m_sampleRate = m_devices[idx].sampleRates[0];

    try {
        m_audio.openStream(&param, NULL, RTAUDIO_FLOAT64, m_sampleRate, &m_bufferSize, &process, this);
        m_audio.startStream();
    }  catch (RtAudioError &e) {
        e.printMessage();
        return false;
    }

    return true;
}

double AudioHandler::DbToLin(double db)
{
    return db <= -200.0 ? 0.0 : std::pow(10.0, std::min(0.0, db) / 20.0);
}
