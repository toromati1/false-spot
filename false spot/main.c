#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <unistd.h>

/* 0 = MAIN (como un juego), 1 = BGM (como Spotify) */
#define PORT_TYPE 1

#define FORMAT_S16_STEREO 1
#define GRAIN 256
#define SAMPLE_RATE 48000
#define SECONDS 10

int sceUserServiceInitialize(void *params);
int sceUserServiceGetInitialUser(int *userId);
int sceAudioOutInit(void);
int sceAudioOutOpen(int userId, int type, int index, unsigned len,
                    unsigned freq, unsigned param);
int sceAudioOutOutput(int handle, const void *ptr);
int sceAudioOutClose(int handle);

int main(void) {
    int userId = 0xFF;
    int handle;
    int16_t buf[GRAIN * 2];
    double phase = 0.0;
    double step = 2.0 * M_PI * 440.0 / SAMPLE_RATE;
    int vueltas = SAMPLE_RATE * SECONDS / GRAIN;

    sceUserServiceInitialize(NULL);
    if (sceUserServiceGetInitialUser(&userId) != 0) {
        userId = 0xFF;
    }

    int r = sceAudioOutInit();
    printf("sceAudioOutInit: 0x%x\n", r);

    handle = sceAudioOutOpen(userId, PORT_TYPE, 0, GRAIN, SAMPLE_RATE,
                             FORMAT_S16_STEREO);
    printf("sceAudioOutOpen (tipo %d): 0x%x\n", PORT_TYPE, handle);
    if (handle < 0) {
        return 1;
    }

    for (int i = 0; i < vueltas; i++) {
        for (int j = 0; j < GRAIN; j++) {
            int16_t m = (int16_t)(sin(phase) * 3000);
            buf[j * 2] = m;
            buf[j * 2 + 1] = m;
            phase += step;
        }
        int w = sceAudioOutOutput(handle, buf);
        if (w < 0) {
            printf("sceAudioOutOutput fallo: 0x%x\n", w);
            break;
        }
    }

    sceAudioOutClose(handle);
    printf("listo\n");
    return 0;
}
