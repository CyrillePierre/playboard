/*Copyright (C) 2010 BOILARD Sylvain & PIERRE Cyrille

This file is part of PlayBoard.

PlayBoard is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

PlayBoard is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.*/

#include <AL/al.h>
#include <AL/alc.h>

#ifndef CONFIG_H_INCLUDED
#define CONFIG_H_INCLUDED

#define NULL  0
#define PI    3.141592653589793238

#define ENABLE    1
#define DISABLE   0

#define SAMPLE_FREQ     44100
#define BUFFER_FREQ     50
#define DATA_SIZE       SAMPLE_FREQ / BUFFER_FREQ
#define AMPLITUDE_MAX   32767

#define ADSR_TMP_MAX   5   //pour chaque phase de la courbe (en secondes)
#define ADSR_SIZE      SAMPLE_FREQ * ADSR_TMP_MAX

#define WAVEFORM_SINE         0x100
#define WAVEFORM_SQUARE       0x101
#define WAVEFORM_SAWTOOTH     0x102
#define WAVEFORM_TRIANGLE     0x103
#define WAVEFORM_WHITENOISE   0x104

#endif
