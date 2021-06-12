#include "audiohandler.h"
#include "synthvoice.h"
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
    , m_buffer(nullptr)
{
    emit GainChanged();
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

bool AudioHandler::Init()
{
    if (m_initialized)
    {
        return false;
    }

    unsigned deviceCount = m_audio.getDeviceCount();
    m_devices.clear();
    m_devices.resize(deviceCount);

    for (unsigned i = 0; i < deviceCount; i++)
    {
        m_devices[i] = m_audio.getDeviceInfo(i);
    }

    unsigned outIdx = m_audio.getDefaultOutputDevice();
    m_voices.resize(4);

    m_initialized = OpenInterface(outIdx);

    m_buffer = (double *) malloc(m_bufferSize * sizeof(double));
    memset(m_buffer, 0, m_bufferSize * sizeof(double));

    for(auto &v : m_voices)
    {
        v = new SynthVoice();
        v->Init(m_sampleRate, m_bufferSize);
    }
    return m_initialized;
}

void AudioHandler::ProcessAudio(double *buffer, unsigned int numSamples)
{

    double p = 0.0;

    memset(m_buffer, 0, m_bufferSize * sizeof(double));

    for (auto &v : m_voices)
    {
        v->ProcessAdd(m_buffer, m_bufferSize);
    }

    if (m_numChannels == 0)
    {
        memcpy(buffer, m_buffer, numSamples);
    } else {
        for (unsigned i = 0; i < std::min(numSamples, m_bufferSize); i++)
        {
            buffer[i*2] = buffer[i];
            buffer[i*2+1] = buffer[i];
        }
    }
}

void AudioHandler::SetGain(double gain)
{
    m_gain = std::max(std::min(gain, 0.0), -200.0);
    m_gainLin = DbToLin(m_gain);

    emit GainChanged();
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
