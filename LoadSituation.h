
double getColorDimension(char c, char *dim);

void LoadSituation()
{
	// TODO

	/*char c;
	int index=1;
	int side=1;
	char *str;
	struct cubeColorType cct[7][10];
	FILE *fd = fopen(".\\RubikKocka.txt", "r");
	if(!fd) return;

	while(!feof(fd))
	{
		c = fgetc(fd);
		if(c=='\r') continue;
		else if(c=='\n')
		{
			side++;
			if(side==7) 
			{
				fclose(fd);
				return;
			}
			index=1;

			
		} else
		{
			cubeColor[side][index].r = getColorDimension(c, "red");
			cubeColor[side][index].g = getColorDimension(c, "green");
			cubeColor[side][index].b = getColorDimension(c, "blue");
			index++;
		}
	}
	
	fclose(fd);*/
}

double getColorDimension(char c, char *dim)
{
	if(c=='p')
	{
		if(strcmp(dim, "red") == 0) return 1.0; 
		if(strcmp(dim, "green") == 0) return 0.0; 
		if(strcmp(dim, "blue") == 0) return 0.0; 
	} else if(c=='k')
	{
		if(strcmp(dim, "red") == 0) return 0.0; 
		if(strcmp(dim, "green") == 0) return 0.0; 
		if(strcmp(dim, "blue") == 0) return 1.0; 
	} else if(c=='f')
	{
		if(strcmp(dim, "red") == 0) return 1.0; 
		if(strcmp(dim, "green") == 0) return 1.0; 
		if(strcmp(dim, "blue") == 0) return 1.0; 
	} else if(c=='z')
	{
		if(strcmp(dim, "red") == 0) return 0.0; 
		if(strcmp(dim, "green") == 0) return 1.0; 
		if(strcmp(dim, "blue") == 0) return 0.0; 
	}  else if(c=='n')
	{
		if(strcmp(dim, "red") == 0) return 1.0; 
		if(strcmp(dim, "green") == 0) return 0.5; 
		if(strcmp(dim, "blue") == 0) return 0.0; 
	} else if(c=='s')
	{
		if(strcmp(dim, "red") == 0) return 1.0; 
		if(strcmp(dim, "green") == 0) return 1.0; 
		if(strcmp(dim, "blue") == 0) return 0.0; 
	}

	return 0.0;
}

