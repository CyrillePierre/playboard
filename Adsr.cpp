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

#include "config.h"
#include "Adsr.h"

Adsr::Adsr()
{
	m_estate = DISABLE;
	m_attack = 0;
	m_decay = 0;
	m_sustain = 1;
	m_release = 0;
	m_lastLevel = 0;
	m_lastPhase = 0;
}

bool Adsr::getEstate()
{
	return m_estate;
}

void Adsr::setEstate(bool estate)
{
	m_estate = estate;
}


void Adsr::setValue(ALsizei attack, ALsizei decay, ALfloat sustain, ALsizei release)
{
	if (attack >= 0 && attack <= ADSR_SIZE)
		m_attack = attack;
	if (decay >= 0 && decay <= ADSR_SIZE)
		m_decay = decay;
	if (sustain >= 0 && sustain <= 1)
		m_sustain = sustain;
	if (release >= 0 && release <= ADSR_SIZE)
		m_release = release;
}

void Adsr::generate(ALint *data, bool estateKey, ALsizei dataSize)
{
	if (m_estate == DISABLE)
		return;

	ALdouble level;
	ALsizei phase;
	bool resetPhase = false, incrPhase = true;

	level = m_lastLevel;
	phase = m_lastPhase;

	for (ALsizei i = 0; i <= dataSize; i++)
	{
		if (incrPhase) phase = m_lastPhase + i;

		if (phase < m_attack)      //phase d'attaque
			level = (double) phase / m_attack;

		else if (m_attack <= phase && phase < (m_decay + m_attack))  //phase de descente
			level = 1 + (m_sustain - 1) * ((double) phase - m_attack) / m_decay;

		else if (estateKey == true)
		{
			incrPhase = false;
			level = m_sustain;  //phase de maintien
		}

		else if (estateKey == false)
		{
			incrPhase = true;

			if ((m_attack + m_decay) <= phase && phase < (m_attack + m_decay + m_release))  // phase de descente
				level = m_sustain -(m_sustain) * ((double) phase - (m_attack + m_decay)) / m_release;

			else     //là c'est la fin
				level = NULL;
		}

		data[i] *= level;
	}
	
	m_lastPhase = phase;
}