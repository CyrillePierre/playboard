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

#include <math.h>
#include <stdlib.h>
#include <time.h>

#include "config.h"
#include "Osc.h"


Osc::Osc()    //initialisation des variables à la création de l'objet
{
    m_waveform = 0;
    m_amplitude = 0;
    m_lastPhase = 0;
    m_phase = 0;
    m_tone = 0;
}

//permet d'éditer la valeur des paramètres de l'objet en fonction des valeurs de l'interface
void Osc::setValue(ALenum waveform, ALint amplitude, ALfloat tone)
{
    m_waveform = waveform;

	if (amplitude <= AMPLITUDE_MAX && amplitude >= NULL)
		m_amplitude = amplitude;

    m_tone = tone;
}

//permet de créer une data à partir de sa fréquence et son type d'onde
void Osc::generateData(ALint *data, ALfloat freq, ALsizei dataSize)
{
	waveformFunction function;
	ALsizei numSamplePeriod;

	function = getWaveformFunction(m_waveform);      //la fonction dépendra du type d'onde choisie
	if (function == NULL)
		return;

    //temps de la période en sample
	numSamplePeriod = floor(SAMPLE_FREQ / (freq + m_tone));

	for (ALsizei i = 0; i < dataSize; i++)
	{
	    //crée un compteur qui a pour période la taille de la première période
	    m_phase = (i + m_lastPhase) % numSamplePeriod;

	    //création de la data
	    data[i] = floor(m_amplitude * function(numSamplePeriod, m_phase));
	}

	m_lastPhase = m_phase + 1;
}

ALint Osc::getAmp()
{
	return m_amplitude;
}

//permet de récuperer l'adresse des fonctions qui fabrique l'onde
waveformFunction Osc::getWaveformFunction(ALenum waveshape)
{
	switch (waveshape)
	{
	case WAVEFORM_SINE:
		return &waveformSine;
	case WAVEFORM_SQUARE:
		return &waveformSquare;
	case WAVEFORM_SAWTOOTH:
		return &waveformSawtooth;
	case WAVEFORM_TRIANGLE:
		return &waveformTriangle;
	case WAVEFORM_WHITENOISE:
		return &waveformWhitenoise;
	}
	return NULL;
}

//Calcul d'un signal sinusoïdal
double Osc::waveformSine(ALsizei period, ALsizei phase)
{
    return sin(2 * PI * phase / period);
}

//Calcul d'un signal carré
double Osc::waveformSquare(ALsizei period, ALsizei phase)
{
    return (phase < (period / 2)) ? 1 : -1;
}

//Calcul d'un signal en dent de scie
double Osc::waveformSawtooth(ALsizei period, ALsizei phase)
{
    return 2 * ((double) phase / period) - 1;
}

//Calcul d'un signal triangle
double Osc::waveformTriangle(ALsizei period, ALsizei phase)
{
	if (phase < (period / 2))
		return 4 * ((double) phase / period) - 1;
	else return 4 * ((period / 2) - (double) phase) / period + 1;
}

//Calcul d'un signal aléatoire
double Osc::waveformWhitenoise(ALsizei period, ALsizei phase)
{
	return (2 * (double) rand() / RAND_MAX) - 1;
}
