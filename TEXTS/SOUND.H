    AUDIOINFO info;
    LPAUDIOMODULE lpModule;
    LPAUDIOWAVE lpWave;
    HAC hVoice;
    BOOL stopped;
int vol=64;

void open_mod(char *);
void play_mod();
void check_mod(int);


void open_wav(char *);
void play_wav(int);
void check_wav(int);

void kill_mod();
void kill_wav();
void close_audio();
void close_all();
