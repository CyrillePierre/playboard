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

#ifndef OSC_H_INCLUDED
#define OSC_H_INCLUDED

typedef double (*waveformFunction) (ALsizei period, ALsizei phase);

class Osc
{
    public:

        Osc::Osc();
        void setValue(ALenum waveform, ALint amplitude, ALfloat tone);
		void generateData(ALint *data, ALfloat freq, ALsizei dataSize);
		ALint getAmp();


    private:

		waveformFunction getWaveformFunction(ALenum waveshape);
		static double waveformSine(ALsizei period, ALsizei phase);
		static double waveformSquare(ALsizei period, ALsizei phase);
		static double waveformSawtooth(ALsizei period, ALsizei phase);
		static double waveformTriangle(ALsizei period, ALsizei phase);
		static double waveformWhitenoise(ALsizei period, ALsizei phase);

		ALenum m_waveform;
		ALint m_amplitude;
		ALsizei m_lastPhase;
		ALsizei m_phase;
		ALfloat m_tone;
};

#endif // OSC_H_INCLUDED
