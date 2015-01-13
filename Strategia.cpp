#include "RubikCube.h"

int run()
{
	int iter=0;
	fazis1();
	while(findPattern(MINTA_FAZIS2) == -1) 
	{
		fazis2();
		iter++;
		if(iter > 5) return 0;
	}
	iter=0;
	while(findPattern(MINTA_FAZIS3) == -1)
	{
		fazis3();
		iter++;
		if(iter >5) return 0;
	}

	iter=0;
	while(findPattern(MINTA_FAZIS4) == -1)
	{
		fazis4();
		iter++;
		if(iter>5) return 0;
	}

	iter=0;
	while(findPattern(MINTA_FAZIS5) == -1)
	{
		fazis5();
		iter++;
		if(iter>5) return 0;
	}

	fazis6(); // megbizhato, nem tesszuk whileba
	fazis7();

	if(findPattern(MINTA_FAZIS5) == -1) return 0;

	return 1;

}


void fazis1()
{
	setInfo("Fazis 1");

	// feher felforgatasa
	int i;
	CubeModel* cube = getCube();
	for(i=1; i!=7; i++)
	{
		if((int)cube->GetCellColor(i, 5).Red == 1 &&
			(int)cube->GetCellColor(i, 5).Green == 1 &&
			(int)cube->GetCellColor(i, 5).Blue == 1)
		{
			setInfo("belepve");
			switch(i)
			{
			case 1: cTransform("7j"); break;
			case 2: cTransform("8j"); break;
			case 3: cTransform("7b"); break;
			case 4: cTransform("8b"); break;
			case 5: break;
			case 6: 
				cTransform("8b");
				cTransform("8b");
				break;	
			}
			return;
		} else 
		{
			//char buff[1024];
			//sprintf(buff, "%s [%d|%2.2f:%2.2f:%2.2f]", msginfo, i, cube->GetCellColor(i, 5).Red, cube->GetCellColor(i, 5).Green, cube->GetCellColor(i, 5).Blue);
		}
	}



}


void fazis2()
{
	int j,i,k;
	for(j=0; j!=4; j++)
	{
		if(fazis2_alul()) continue;
		for(i=0; i!=rulesLen();  i++)
		{
			if(rules[i].group == FEHERET_ALULRA)
			{
				if(checkPattern(i)) 
				{	
					applySolution(i, 0);
					int k;
					for(k=0; k!=4; k++)
					{
						if(fazis2_alul()) break;
						cTransform("6j");
					}
				}
			}
		}
	}

	for(i=0; i!=rulesLen(); i++)
	{
		if(rules[i].group == MINTA_FAZIS2) 
			if(!checkPattern(i)) setWarning("HIBA: hibas szabalyrendszer a 2. fazis kirakasa kozben!");
	}
}

void fazis3()
{
	int find;
	int i,j,old,m;
	int find2;
	if(findPattern(MINTA_FAZIS2) == -1) 
	{
		setInfo("Nincs kesz a masodik fazis!");
		return;
	}
	// 3. fazis

	if(1)
	{
		for(old=0; old!=4; old++)
		{
			find2 = findPattern(SAROKFEHER_LE);
			if(find2!=-1)
				applySolution(find2, 0);


			// nem negyet fordulunk hanem otot, hogy a kulso
			// for ciklusra is maradjon iteracionkent egy 
			// elforgatas. neki is kell, mert van olyan sarokfeher_le
			// amit csak akkor tud megoldani, ha jo helyre van forgatva
			for(j=0; j!=5; j++)
			{
				find = findPattern(FEHER_LENT_POZICIOBAN);
				if(find != -1) 
					applySolution(find, 0);

				cTransform("6j");
			}
		}
	}
}

void fazis4()
{
	int find;
	int iteration;
	for(iteration=0; iteration!=15; iteration++)
	{

		if(findPattern(MINTA_FAZIS3) == -1)
		{
			setInfo("Nincs harmadik fazisban!");
			return;
		}
		//int h;
		//h=0;
		//while(findPattern(MINTA_FAZIS4) == -1)
		if(1)
		{
			find = findPattern(NAGYT_KIST);
			if(find!=-1) 
			{
				if(rules[find].elofeltetel[0] != RESCUE) 
				{
					setH(0);
					applySolution(find, 0);
				} else 
				{
					incrementH();
					cTransform("6j");
					if(getH()>4) {	// nincs mit tenni.
						applySolution(find, 0);
						setH(0);
					}

				}
			}
			else 
			{
				cTransform("6j");
			}
		}

		if(findPattern(MINTA_FAZIS4) == -1)
			setInfo("nincs meg a negyedik fazis");
		else
			setInfo("megvan a negyedik fazis");
	}

}


void  fazis5()
{
	int s;
	int i,j;

	if(findPattern(MINTA_FAZIS5) != -1) return;		// nem kell csinalni semmit sem
	for(j=0; j!=10; j++)
	{
		for(i=0; i!=10; i++)
		{
			s = findPattern(ALSO1);
			if(s!=-1)
			{
				applySolution(s, 0);
				if(findPattern(MINTA_FAZIS5) != -1)
				{
					return; // kesz van az 5. fazis
				}
			}
		}
		cTransform("6j");
	}

}


int fazis6()
{
	int i;
	int kesz;
	int fix;
	int iter=0;
	int find;

	kesz=1;
	for(i=1; i!=5; i++)
		if(sarokChkSum(i) != sarokPosChkSum(i)) 
			kesz = 0;
	if(kesz) 
		return 1;

	while(1)
	{
		iter++;

		//fixpont keresese
		fix = -1;
		for(i=1; i!=5; i++)
			if((double)sarokChkSum(i) == (double)sarokPosChkSum(i)) fix = i;


		switch(fix) 
		{
		case 1: find = findPattern(SARKOK1);break;
		case 2: find = findPattern(SARKOK2);break;
		case 3: find = findPattern(SARKOK3);break;
		case 4: find = findPattern(SARKOK4);break;
		default: find = findPattern(SARKOK1);break;
		}

		//sprintf(msginfo, "fixpont: %d alkalmazzuk: %d (2: %f es %f)", fix, find, sarokChkSum(2), sarokPosChkSum(2));

		applySolution(find, 0);

		// kilepes vizsgalata
		kesz=1;
		for(i=1; i!=5; i++)
			if((double)sarokChkSum(i) != (double)sarokPosChkSum(i)) 
			{
				kesz = 0;
			}
			if(kesz)  {
				return 1;
			}
	}



	return 1;
}


void fazis7()
{
	int find;

	while(findPattern(KIRAKOTT) == -1)
	{
		find = findPattern(FINISH);
		if(find == -1) find = findPattern(FINISH_RESC);
		if(find != -1)
			applySolution(find, 0);
	} 

	setInfo("ki van rakva");

}

double sarokChkSum(int num)
{
	CubeModel* cube = getCube();
	double retval;
	double ar, ag, ab, br, bg, bb, cr, cg, cb;
	if(num==1)
	{
		ar = cube->GetCellColor(1, 7).Red; ag = cube->GetCellColor(1, 7).Green; ab = cube->GetCellColor(1, 7).Blue;
		br = cube->GetCellColor(4, 7).Red; bg = cube->GetCellColor(4, 7).Green; bb = cube->GetCellColor(4, 7).Blue;
		cr = cube->GetCellColor(6, 7).Red; cg = cube->GetCellColor(6, 7).Green; cb = cube->GetCellColor(6, 7).Blue;
	}

	if(num==2)
	{
		ar = cube->GetCellColor(2, 7).Red; ag = cube->GetCellColor(2, 7).Green; ab = cube->GetCellColor(2, 7).Blue;
		br = cube->GetCellColor(1, 9).Red; bg = cube->GetCellColor(1, 9).Green; bb = cube->GetCellColor(1, 9).Blue;
		cr = cube->GetCellColor(6, 9).Red; cg = cube->GetCellColor(6, 9).Green; cb = cube->GetCellColor(6, 9).Blue;
	}
	if(num==3)
	{
		ar = cube->GetCellColor(2, 9).Red; ag = cube->GetCellColor(2, 9).Green; ab = cube->GetCellColor(2, 9).Blue;
		br = cube->GetCellColor(6, 3).Red; bg = cube->GetCellColor(6, 3).Green; bb = cube->GetCellColor(6, 3).Blue;
		cr = cube->GetCellColor(3, 9).Red; cg = cube->GetCellColor(3, 9).Green; cb = cube->GetCellColor(3, 9).Blue;
	}
	if(num==4)
	{
		ar = cube->GetCellColor(3, 7).Red; ag = cube->GetCellColor(3, 7).Green; ab = cube->GetCellColor(3, 7).Blue;
		br = cube->GetCellColor(4, 9).Red; bg = cube->GetCellColor(4, 9).Green; bb = cube->GetCellColor(4, 9).Blue;
		cr = cube->GetCellColor(6, 1).Red; cg = cube->GetCellColor(6, 1).Green; cb = cube->GetCellColor(6, 1).Blue;
	}

	//retval = 0.0001*ar + 0.001*ag + 0.01*ab + 0.1*br + 1.0*bg + 10.0*bb + 100.0*cr + 1000.0*cg + 10000.0*cb;

	double c[3];
	c[0] = 100.0*ar + 10.0*ag + 1.0*ab;
	c[1] = 100.0*br + 10.0*bg + 1.0*bb;
	c[2] = 100.0*cr + 10.0*cg + 1.0*cb;

	int i;
	int minIndex=0;
	int maxIndex=0;
	for(i=0; i!=3; i++)
		if(c[i] < c[minIndex]) minIndex = i;

	for(i=0; i!=3; i++)
		if(c[i] > c[maxIndex]) maxIndex = i;
	int kozepso = 3 - (maxIndex+minIndex);


	return c[minIndex]*100.0 + c[kozepso]*10.0 + c[maxIndex]*1.0;


}


double sarokPosChkSum(int num)
{
	CubeModel* cube = getCube();
	double retval;
	double ar, ag, ab, br, bg, bb, cr, cg, cb;
	if(num==1)
	{
		ar = cube->GetCellColor(1, 5).Red; ag = cube->GetCellColor(1, 5).Green; ab = cube->GetCellColor(1, 5).Blue;
		br = cube->GetCellColor(4, 5).Red; bg = cube->GetCellColor(4, 5).Green; bb = cube->GetCellColor(4, 5).Blue;
		cr = cube->GetCellColor(6, 5).Red; cg = cube->GetCellColor(6, 5).Green; cb = cube->GetCellColor(6, 5).Blue;
	}

	if(num==2)
	{
		ar = cube->GetCellColor(2, 5).Red; ag = cube->GetCellColor(2, 5).Green; ab = cube->GetCellColor(2, 5).Blue;
		br = cube->GetCellColor(1, 5).Red; bg = cube->GetCellColor(1, 5).Green; bb = cube->GetCellColor(1, 5).Blue;
		cr = cube->GetCellColor(6, 5).Red; cg = cube->GetCellColor(6, 5).Green; cb = cube->GetCellColor(6, 5).Blue;
	}
	if(num==3)
	{
		ar = cube->GetCellColor(2, 5).Red; ag = cube->GetCellColor(2, 5).Green; ab = cube->GetCellColor(2, 5).Blue;
		br = cube->GetCellColor(6, 5).Red; bg = cube->GetCellColor(6, 5).Green; bb = cube->GetCellColor(6, 5).Blue;
		cr = cube->GetCellColor(3, 5).Red; cg = cube->GetCellColor(3, 5).Green; cb = cube->GetCellColor(3, 5).Blue;
	}
	if(num==4)
	{
		ar = cube->GetCellColor(3, 5).Red; ag = cube->GetCellColor(3, 5).Green; ab = cube->GetCellColor(3, 5).Blue;
		br = cube->GetCellColor(4, 5).Red; bg = cube->GetCellColor(4, 5).Green; bb = cube->GetCellColor(4, 5).Blue;
		cr = cube->GetCellColor(6, 5).Red; cg = cube->GetCellColor(6, 5).Green; cb = cube->GetCellColor(6, 5).Blue;
	}

	double c[3];
	c[0] = 100.0*ar + 10.0*ag + 1.0*ab;
	c[1] = 100.0*br + 10.0*bg + 1.0*bb;
	c[2] = 100.0*cr + 10.0*cg + 1.0*cb;

	int i;
	int minIndex=0;
	int maxIndex=0;
	for(i=0; i!=3; i++)
		if(c[i] < c[minIndex]) minIndex = i;

	for(i=0; i!=3; i++)
		if(c[i] > c[maxIndex]) maxIndex = i;
	int kozepso = 3 - (maxIndex+minIndex);


	return c[minIndex]*100.0 + c[kozepso]*10.0 + c[maxIndex]*1.0;
	//return (double)c[0];

}



int fazis2_alul()
{
	int i=0;
	for(i=0; i!=rulesLen(); i++)
	{
		if(rules[i].group == MINTA_KORONA_FELPORGET)
		{
			if(checkPattern(i))
			{
				char buff[256];
				sprintf(buff, "%d igaz", i);
				setWarning(buff);
				applySolution(i,0);
				return 1; // kov. iteracio
			} else setWarning("");
		}
	}
	return 0; // nem csinaltunk semmit
}

int cCompare(int side1, int place1, int side2, int place2)
{
	CubeModel* cube = getCube();
	if((cube->GetCellColor(side1, place1).Red == cube->GetCellColor(side2, place2).Red) &&
		(cube->GetCellColor(side1, place1).Green == cube->GetCellColor(side2, place2).Green) &&
		(cube->GetCellColor(side1, place1).Blue == cube->GetCellColor(side2, place2).Blue))
	{
		return 1;
	} else return 0;
}

