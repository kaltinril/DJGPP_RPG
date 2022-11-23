void open_mod(char *filename)
{
    /* initialize audio library */
    AInitialize();

    /* open audio device */
    info.nDeviceId = AUDIO_DEVICE_MAPPER;
    info.wFormat = AUDIO_FORMAT_16BITS | AUDIO_FORMAT_STEREO;
    info.nSampleRate = 44100;
    AOpenAudio(&info);

    /* load module and waveform file */
    ALoadModuleFile(filename, &lpModule, 0);
    //ALoadWaveFile("test.wav", &lpWave, 0);

    /* open voices for module and waveform */
    AOpenVoices(lpModule->nTracks + 1);
}


void play_mod(int vn)
{
    APlayModule(lpModule);
    ASetModuleVolume(vn);
}

void check_mod(int yngoing)
{
 AGetModuleStatus(&stopped);
 if (stopped && yngoing==1){play_mod(vol);}
}

void kill_mod()
{
 AStopModule();
 ACloseVoices();
 AFreeModuleFile(lpModule);
}

void kill_wav()
{
 AStopVoice(hVoice);
 ADestroyAudioVoice(hVoice);
 AFreeWaveFile(lpWave);
}
void close_audio()
{
 ACloseAudio();
}
void close_all()
{
 kill_mod();
 kill_wav();
 close_audio();
}
