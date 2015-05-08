void switchChars(char* x, char *y, int n)
{
    //printf("x adr: %p y adr: %p\n", x, y);
	const size_t ALIGNMENT = sizeof(void*);

	size_t alignedX = ((size_t)x + ALIGNMENT-1) & ~(ALIGNMENT-1);
	size_t alignedY = ((size_t)y + ALIGNMENT-1) & ~(ALIGNMENT-1);
	if((alignedX - (size_t)x) == (alignedY - (size_t)y))
	{
		//printf("aligned addresses\n");
		int i=0;
		for (; i<(n/ALIGNMENT); i+=ALIGNMENT)
		{
			size_t* px = (size_t*)(x+i);
			size_t* py = (size_t*)(y+i);
			size_t temp = *px;
			*px = *py;
			*py = temp;
		}
		i *= ALIGNMENT;
		for (; i<n; ++i)
		{
			char temp = x[i];
			x[i] = y[i];
			y[i] = temp;
		}
	}
	else
	{
		//printf("misaligned addresses\n");
		char temp;
		for (int i=0; i<n; ++i)
		{
			temp = x[i];
			x[i] = y[i];
			y[i] = temp;
		}
	}
}