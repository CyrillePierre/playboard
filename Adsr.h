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

#ifndef ADSR_H_INCLUDED
#define ADSR_H_INCLUDED

class Adsr
{
    public:

		Adsr::Adsr();
		bool getEstate();
		void setEstate(bool estate);
		void setValue(ALsizei attack, ALsizei decay, ALfloat sustain, ALsizei release);
		void generate(ALint *data, bool estateKey, ALsizei dataSize);

    private:

		bool m_estate;       //indique si l'effet est activé ou pas
		ALsizei m_attack;        //temps de la phase de montée du volume
		ALsizei m_decay;         //temps de la phase de descente
		ALfloat m_sustain;       //valeur du volume pendant le maintien de la touche
		ALsizei m_release;       //temps de la phase de descente du volume quand la touche est relachée
		ALdouble m_lastLevel;
		ALsizei m_lastPhase;
};

#endif // ADSR_H_INCLUDED
