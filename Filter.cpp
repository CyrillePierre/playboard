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

#include "config.h"
#include "Filter.h"

Filter::Filter()
{
	bool m_estate = false;
	ALsizei m_order = 0;
	ALfloat m_incline = 0;
}

bool Filter::getEstate()
{
	return m_estate;
}

void Filter::setEstate(bool estate)
{
	m_estate = estate;
}

void Filter::setValue(ALfloat order, ALfloat incline)
{
	if (0 <= order && order <= 1)
	{
		m_order = order;
	}
	if (1 <= incline && incline <= 20)
	{
		m_incline = incline;
	}
}

void Filter::generate(ALint *data, ALfloat freq, ALsizei dataSize)
{
	if (m_estate == DISABLE)
		return;

	ALint *tamp;
	ALsizei samplePeriod = SAMPLE_FREQ / freq;
	ALsizei sampleOrder = floor(m_order * samplePeriod);
	ALdouble sum;
	ALfloat *coef;
	ALfloat allCoef = 0;

	if (sampleOrder < 1) sampleOrder = 1;  //juste histoire d'éviter d'avoir des erreurs :p

	tamp = new ALint[dataSize];
	coef = new ALfloat[sampleOrder];

	for (ALsizei i = 0; i < sampleOrder; i++)
	{
		/*calcul des coefficients réducteurs (plus les samples précédantes/suivantes
			sont éloignées du sample actuel, plus ils tendent vers 0)*/
		coef[i] = exp(-i * m_incline / sampleOrder);

		//calcul de la somme de tout les coefs
		allCoef += coef[i];
	}

	for (ALsizei i = 0; i < dataSize; i++)
	{
		sum = 0;

		for (ALsizei j = 0; j < sampleOrder; j++)
		{
			//adoucissement du signal par persistance des samples précédentes
			if ((i - j) >= 0)
				sum += data[i - j] * coef[j];

			//adoucissement du signal par anticipation des samples suivantes
			if (((i + j) < dataSize) && (j != 0))
				sum += data[i + j] * coef[j];
		}

		sum /= 2 * allCoef;  //correction de l'amplitude max
		tamp[i] = floor(sum);
	}

	for (ALsizei i = 0; i < dataSize; i++)
		data[i] = tamp[i];    //transfert du data de sortie dans le data d'entré

	delete[] tamp;
	delete[] coef;
}