/* ========================================================================== */
generating arbitrary timed waveforms on multiple user gpios simultaneously;
uses DMA and interrupts are not disabled
/* ========================================================================== */

    #include <stdio.h>

    #include <pigpio.h>

    #define LED 4

    gpioPulse_t pulse[2]; /* only need two pulses for a square wave */

    int main(int argc, char *argv[])
    {
       int secs=60, us = 1000000;

       if (argc>1) us   = atoi(argv[1]); /* square wave micros */
       if (argc>2) secs = atoi(argv[2]); /* program run seconds */

       if (us<2) us = 2; /* minimum of 2 micros per pulse */

       if ((secs<1) || (secs>3600)) secs = 3600;

       if (gpioInitialise()<0) return 1;

       gpioSetMode(LED, PI_OUTPUT);

       pulse[0].gpioOn = (1<<LED); /* high */
       pulse[0].gpioOff = 0;
       pulse[0].usDelay = us;

       pulse[1].gpioOn = 0;
       pulse[1].gpioOff = (1<<LED); /* low */
       pulse[1].usDelay = us;

       gpioWaveClear();

       gpioWaveAddGeneric(2, pulse);

       gpioWaveTxStart(PI_WAVE_MODE_REPEAT);

       sleep(secs);

       gpioWaveTxStop();

       gpioTerminate();
    }
