# Project overview

A place to gather my thoughts.

## Video sensor
Photo diode connected to the mcu

```
3.3v -- photodiode + 220K resistor -- gnd
                   |
              MCU Input
```

## Audio sensor
Keep as simple as possible, preferably able to be handled by a digital input

Current version tries to place audio signal ( -+ 1v ) on top of ~ 1.8v ( VCC/2 )

```
Current version (will change)

3.3v -- 220K R --------+ 220K R -------+ gnd
                       |               |
Audio in - 10uF E cap -+- 0.01uF cap --+
                       |
                  mcu input
```

## Theory of operation
Device has two (or more?) modes.
A button or switch needs to be used to select mode

### Video vs Audio (VvA)
Tries to figure out the delay between video and audio
- Listen for trigger on either A or V
- Mark time of received trigger, and disable further input for that trigger
- Listen for trigger on second channel, transmit time between A and V over serial
- Needs to have a reset button
- Needs a timeout

 if sensors can be made to output High and Low (low-pass filter?) instead of oscillating with the input the triggers could be handled by an ISR. else we need to rely on AnalogInput with threshold.

### Frame dropped (FC)
Checks if frames are dropped by measuring the time between two HIGH signals from the V sensor. To make this work we need to play a video with alternating black and white frames.
- Check for trigger on V
- Notes time of trigger
- Check for next trigger on V
- Outputs delta over serial (if stable then we can reduce serial spam to only report dropped frames)

Setting framerate could happen automagically by measuring the average delay on the first 10/20/30 frames (assumption is that frames will only rarely drop)

## Pseudo code
```

```

## Hardware
The case is a project box,
[http://www.gmelectronic.com/plastic-box-kp28-z-37-p622-477](http://www.gmelectronic.com/plastic-box-kp28-z-37-p622-477)

Neutrik chassis mount usb

ikea desk light

Telejack

## Future
Add a handheld device that outputs light + audio tone to measure the latency of the complete chain from input to output.
Use audio tone input as marker and wait for video to arrive.
