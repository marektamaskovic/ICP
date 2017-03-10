#ifndef CORE
#define CORE

static int position[] = {0,0,0,0};

int getPosition(void){
	for (int i = 0; i < 4; i++)
	{
		if (position[i] == 0)
			return i;
	}

	return -1;
}

#endif