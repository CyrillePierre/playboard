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


/*----Preprocessor commands----*/

//Including OpenAL headers.


#include "config.h"

#include <stdlib.h>
#include <time.h>

#include "Osc.h"
#include "Adsr.h"
#include "Filter.h"

static ALCdevice *device;
static ALCcontext *context;

bool alInit(const ALCchar* devicename = NULL, const ALCint* attrlist = NULL)
{
	//Opens an OpenAL device and checks if succeeded.
	//If not, returns -1 and quits the program.
	device = alcOpenDevice(devicename);
	if (!device)
		return NULL;

	//Creates an OpenAL context in the previously-opened device and checks if succeeded.
	//If not, returns -1 and quits the program.
	context = alcCreateContext(device, attrlist);
	if(!context)
		return NULL;

	//Activates the previously-created context and checks if succeeded.
	//If not, returns -1 and quits the program.
	if (!alcMakeContextCurrent(context))
		return NULL;
	return 1;
}

void alExit()
{
	//De-activates the context.
	alcMakeContextCurrent(NULL);

	//Destroys the context.
	alcDestroyContext(context);

	//Closes the device.
	alcCloseDevice(device);
}


int main()
{
	/*----Memory initialization----*/

	//Declaring two buffer and one audio source IDs.
	ALuint buffer[2];
	ALuint source;
	ALint nbQueu, nbProc;

	//Declaring data array (TEST)
	ALint plob[DATA_SIZE];
	//ALint data[DATA_SIZE];

	int ik = 0;

	srand(time(NULL));

	/*----Initializating OpenAL----*/

	if (alInit() == NULL)
		return -1;

	//Creating one source and two buffers, then stocking their IDs, and checks if succeeded.
	//If not, returns -1 and quit the program.
	alGenSources(1, &source);
	alGenBuffers(2, buffer);
	if (alGetError() != AL_NO_ERROR)
		return -1;

	/*Osc OscB;
	OscB.setValue(WAVEFORM_SQUARE, 20000, 0);
	OscB.generateData(data, 660, DATA_SIZE);

    ALint ampM = OscA.getAmp() + OscB.getAmp();

    if (ampM > 32767)
    {
        for (int i=0;i<DATA_SIZE;i++)
            plob[i] = ((double) (plob[i] + data[i]) / ampM) * 32767;
    }
	else
	{
        for (int i=0;i<DATA_SIZE;i++)
            plob[i] = plob[i] + data[i];
	}*/

	Osc OscA;
	Adsr Adsr;
	Filter FilterA;

	OscA.setValue(WAVEFORM_SQUARE, 10000, 0);
	FilterA.setValue(0.3, 5);
	Adsr.setValue(800, 600, 0.5, 8000);

	FilterA.setEstate(DISABLE);
	Adsr.setEstate(DISABLE);


	OscA.generateData(plob, 1200, DATA_SIZE);
	FilterA.generate(plob, 440, DATA_SIZE);
	Adsr.generate(plob, true, DATA_SIZE);


    for(int i = 0; i < 50; i++)
    {
        alSourceUnqueueBuffers(source, 1, &(buffer[0]));
        OscA.generateData(plob, 880, DATA_SIZE);
        alBufferData(buffer[0], AL_FORMAT_MONO16, plob, sizeof(plob), SAMPLE_FREQ);
        alSourceQueueBuffers(source, 1, &(buffer[0]));

        if (ik == 0) alSourcePlay(source);

        ik = 1;

        alSourceUnqueueBuffers(source, 1, &(buffer[1]));
        OscA.generateData(plob, 1200, DATA_SIZE);
        alBufferData(buffer[1], AL_FORMAT_MONO16, plob, sizeof(plob), SAMPLE_FREQ);
        alSourceQueueBuffers(source, 1, &(buffer[1]));
    }

    alGetSourcei(source, AL_BUFFERS_QUEUED, &nbQueu);

    while(1)
    {
        alGetSourcei(source, AL_BUFFERS_PROCESSED, &nbProc);
        if (nbQueu == nbProc) break;
    }


	/*----Releasing OpenAL----*/

	//Destroys buffers and source.
	alDeleteBuffers(2, buffer);
	alDeleteSources(1, &source);

	alExit();

	//Returns 0 if the program properly ends.
	return 0;
}
