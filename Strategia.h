int cCompare(int side1, int place1, int side2, int place2);
int fazis2_alul();
double sarokChkSum(int num);
double sarokPosChkSum(int num);
void fazis1();
void fazis2();
void fazis3();
void fazis4();
void fazis5();
int fazis6();
void fazis7();
int run();

/*int fazis2()
{
	int i,j,k,l,m,n;
	char cmd1[8], cmd2[8];
	// kereszt 4 oldala
	for(i=1; i!=5; i++)
	{
		// 1. eset, ha a feher egy oldal kozepen bal oldalt van
		for(j=0; j!=4; j++)
		{
			if(getCube()Color[i][4].r == 1.0 && getCube()Color[i][4].g == 1.0 && getCube()Color[i][4].b == 1.0)
			{
				switch(i)
				{
					case 1: sprintf(cmd1, "4j"); sprintf(cmd2, "4b"); break;
					case 2: sprintf(cmd1, "1j"); sprintf(cmd2, "1b"); break;
					case 3: sprintf(cmd1, "2j"); sprintf(cmd2, "2b"); break;
					case 4: sprintf(cmd1, "3j"); sprintf(cmd2, "3b"); break;

				}
				cTransform(cmd1);
				cTransform("6j");
				cTransform(cmd2);

				return fazis2_alul();
			}
		}
	}
	return 0;
}

*/
// azt az esetet oldja meg, amikor a masodik fazisban egy feher
// alul van, felette egy szin. kiporgeti arra a helyre 6. lapot
// ahol az 5. indexen a megfelelo szin van, es 2-t felporget
/*int fazis2_alul()
{
	int k,l,m,n;
	// ha minden igaz, most alul van egy feherunk, a 6. oldalon
	for(k=1; k!=5; k++)
	{
		switch(k)
		{
			case 1: l=8; break;
			case 2: l=6; break;
			case 3: l=2; break;
			case 4: l=4; break;
		}
		if((float)getCube()Color[6][l].r==1.0 && (float)getCube()Color[6][l].g==1.0 && (float)getCube()Color[6][l].b==1.0)
		{
			// k lapon kell forgatni
			for(m=0; m!=4; m++)
			{
				int oldal = k+m;
				if(oldal > 4) oldal-=4;
				if(cCompare(oldal, 8, oldal, 5))
				{
					n = oldal + (oldal-1);
					cTransformN(n);
					cTransformN(n);
					return 1;
				} else cTransform("6j");
			}
			return 0;
		}
	}
	return 0;
}*/
