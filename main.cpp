#include "MSC.h"
#include <cstdlib>
#include <stdlib.h>
#include <time.h>
#include <string>

using namespace std;
using namespace MSC;

int T1=0,T2=0;
Rectangle rect[4];
Rectangle rectN[4];
Rectangle RECT[24][12];
bool line[25][12];
int l=30;
int score=0;
string Score;
Text ScoreT;
Text GameT[2];
int shape;
int shapeN;
int spin;
bool game=1;
bool IfPause=0;
Text IfPauseT;
Rectangle GameOver;
int  t;
float tx[4],ty[4];
int Tx[4],Ty[4];

void TetrisN()
{
	for (int i=0;i<4;i++)
	{
		rectN[i].setSize(l-3, l-3);
		rectN[i].setFill(0xffffffff);
		rectN[i].setBorderWidth(3);
		rectN[i].setBorderColor(0xccccccff);
		rectN[i].setZIndex(2);
	}
	if (shapeN==1)
	{
		for (int i=0;i<4;i++)
			rectN[i].put(790+i*l,70);
	}
	else if (shapeN>=2&&shapeN<=4)
	{
		rectN[0].put(820,70);
		for (int i=1;i<4;i++)
			rectN[i].put(820+(i-1)*l,100);
		if (shapeN==3)
			rectN[0].move(l,0);
		else if (shapeN==4)
			rectN[0].move(2*l,0);
	}
	else if (shapeN>=5&&shapeN<=7)
	{
		for (int i=0;i<2;i++)
			rectN[i].put(820+i*l,70);
		for (int i=2;i<4;i++)
			rectN[i].put(820+(i-2)*l,100);
		if (shapeN==6)
			for (int i=0;i<2;i++)
				rectN[i].move(l,0);
		else if (shapeN==7)
			for (int i=2;i<4;i++)
				rectN[i].move(l,0);
	}
}

void Tetris()
{

 	shape=shapeN;
	spin=0;

	for (int i=0;i<4;i++)
	{
		rect[i].setSize(l-3, l-3);
		rect[i].setFill(0xffffffff);
		rect[i].setBorderWidth(3);
		rect[i].setBorderColor(0xccccccff);
		rect[i].setZIndex(2);
	}
	if (shape==1)
	{
		for (int i=0;i<4;i++)
			rect[i].put(440+i*l,40);
	}
	else if (shape>=2&&shape<=4)
	{
		rect[0].put(470,40);
		for (int i=1;i<4;i++)
			rect[i].put(470+(i-1)*l,70);
		if (shape==3)
			rect[0].move(l,0);
		else if (shape==4)
			rect[0].move(2*l,0);
	}
	else if (shape>=5&&shape<=7)
	{
		for (int i=0;i<2;i++)
			rect[i].put(470+i*l,40);
		for (int i=2;i<4;i++)
			rect[i].put(470+(i-2)*l,70);
		if (shape==6)
			for (int i=0;i<2;i++)
				rect[i].move(l,0);
		else if (shape==7)
			for (int i=2;i<4;i++)
				rect[i].move(l,0);
	}
}

void Rotate()
{
	if (spin==0)
	{
		if (shape==1)
		{
			rect[0].move(l,-2*l);
			rect[1].move(0,-l);
			rect[2].move(-l,0);
			rect[3].move(-2*l,l);
		}
		else if (shape==2)
		{
			rect[0].move(l,-l);
			rect[1].move(l,-l);
			rect[2].move(-l,0);
			rect[3].move(-l,0);
		}
		else if (shape==3)
		{
			rect[0].move(0,0);
			rect[1].move(0,0);
			rect[2].move(0,0);
			rect[3].move(-l,l);
		}
		else if (shape==4)
		{
			rect[0].move(-l,0);
			rect[1].move(2*l,-l);
			rect[2].move(l,0);
			rect[3].move(0,l);
		}
		else if (shape==6)
		{
			rect[0].move(0,-l);
			rect[1].move(-l,0);
			rect[2].move(2*l,-l);
			rect[3].move(l,0);
		}
		else if (shape==7)
		{
			rect[0].move(2*l,-l);
			rect[1].move(0,0);
			rect[2].move(l,-l);
			rect[3].move(-l,0);
		}
	}
	else if (spin==1)
	{
		if (shape==1)
		{
			rect[0].move(-l,2*l);
			rect[1].move(0,l);
			rect[2].move(l,0);
			rect[3].move(2*l,-l);
		}
		else if (shape==2)
		{
			rect[0].move(-2*l,l);
			rect[1].move(-l,0);
			rect[2].move(l,-l);
			rect[3].move(0,0);
		}
		else if (shape==3)
		{
			rect[0].move(-l,l);
			rect[1].move(l,0);
			rect[2].move(l,0);
			rect[3].move(0,0);
		}
		else if (shape==4)
		{
			rect[0].move(0,0);
			rect[1].move(0,0);
			rect[2].move(l,-l);
			rect[3].move(-l,-l);
		}
		else if (shape==6)
		{
			rect[0].move(0,l);
			rect[1].move(l,0);
			rect[2].move(-2*l,l);
			rect[3].move(-l,0);
		}
		else if (shape==7)
		{
			rect[0].move(-2*l,l);
			rect[1].move(0,0);
			rect[2].move(-l,l);
			rect[3].move(l,0);
		}
	}
	else if (spin==2)
	{
		if (shape==1)
		{
			rect[0].move(l,-2*l);
			rect[1].move(0,-l);
			rect[2].move(-l,0);
			rect[3].move(-2*l,l);
		}
		else if (shape==2)
		{
			rect[0].move(l,0);
			rect[1].move(l,0);
			rect[2].move(-l,l);
			rect[3].move(-l,l);
		}
		else if (shape==3)
		{
			rect[0].move(l,-l);
			rect[1].move(0,0);
			rect[2].move(0,0);
			rect[3].move(0,0);
		}
		else if (shape==4)
		{
			rect[0].move(0,-l);
			rect[1].move(-l,0);
			rect[2].move(-2*l,l);
			rect[3].move(l,0);
		}
		else if (shape==6)
		{
			rect[0].move(0,-l);
			rect[1].move(-l,0);
			rect[2].move(2*l,-l);
			rect[3].move(l,0);
		}
		else if (shape==7)
		{
			rect[0].move(2*l,-l);
			rect[1].move(0,0);
			rect[2].move(l,-l);
			rect[3].move(-l,0);
		}
	}
	else if (spin==3)
	{
		if (shape==1)
		{
			rect[0].move(-l,2*l);
			rect[1].move(0,l);
			rect[2].move(l,0);
			rect[3].move(2*l,-l);
		}
		else if (shape==2)
		{
			rect[0].move(0,0);
			rect[1].move(-l,l);
			rect[2].move(l,0);
			rect[3].move(2*l,-l);
		}
		else if (shape==3)
		{
			rect[0].move(0,0);
			rect[1].move(-l,0);
			rect[2].move(-l,0);
			rect[3].move(l,-l);
		}
		else if (shape==4)
		{
			rect[0].move(l,l);
			rect[1].move(-l,l);
			rect[2].move(0,0);
			rect[3].move(0,0);
		}
		else if (shape==6)
		{
			rect[0].move(0,l);
			rect[1].move(l,0);
			rect[2].move(-2*l,l);
			rect[3].move(-l,0);
		}
		else if (shape==7)
		{
			rect[0].move(-2*l,l);
			rect[1].move(0,0);
			rect[2].move(-l,l);
			rect[3].move(l,0);
		}
		else if(shape==8)
		{
			rect[0].move(l,-2*l);
			rect[1].move(0,-l);
			rect[2].move(-l,0);
			rect[3].move(-2*l,l);
		}
	}
	spin=(spin+1)%4;
}
void gameover()
{
	GameOver.setSize(800, 400);
	GameOver.setFill(0xffffff88);
	GameOver.setBorderWidth(20);
	GameOver.setBorderColor(0x00000ff);
	GameOver.setZIndex(3);
	GameOver.put(100,100);

	GameT[0].setZIndex(4);
	GameT[1].setZIndex(4);
	ScoreT.setZIndex(4);
	GameT[0].setFontSize(80);
	GameT[0].setColor(0x000000ff);
	GameT[0].setBold();
	GameT[0].put(270,150);
	GameT[1].setFontSize(80);
	GameT[1].setColor(0x000000ff);
	GameT[1].setBold();
	GameT[1].put(220,250);
	GameT[0].setText(" Game  Over ");
	GameT[1].setText("Your Final Score");
	ScoreT.setColor(0x000000ff);
	ScoreT.setFontSize(80);
	ScoreT.put(470,350);

}

void gameInit()
{
	for (int i=0;i<12;i++)
		line[24][i]=1;

	for (int k=0;k<12;k++)
	{
		for (int j=0;j<24;j++)
		{
			RECT[j][k].setSize(27, 27);
			RECT[j][k].setFill(0x434343ff);
			RECT[j][k].setBorderWidth(3);
			RECT[j][k].setBorderColor(0xccccccff);
			RECT[j][k].put(k*30+320,j*30+40);
			RECT[j][k].setZIndex(1);
		}
	}
	ScoreT.setFontSize(50);
	ScoreT.setColor(0xffffffff);
	ScoreT.setBold();
	ScoreT.put(150,50);

	IfPauseT.setFontSize(50);
	IfPauseT.setColor(0xffffffff);
	IfPauseT.setBold();
	IfPauseT.put(100,200);

	shapeN=rand()%7+1;
}

bool New=1,GoDown=0,Begin=0;

void gamming(int ms)
{
	if (game)
	{
	if (New)
	{
		New=0;
		Tetris();
		shapeN=rand()%7+1;
		TetrisN();
		GoDown=1;
		Begin=1;
	}
	for (int i=0;i<4;i++)
	{
		tx[i]=rect[i].getX();
		ty[i]=rect[i].getY();
		Tx[i]=(int(tx[i])-320)/l;
		Ty[i]=(int(ty[i])-40)/l;
	}


	bool flag=0;

	for (int i=0;i<4;i++)
	{
		if (line[Ty[i]+1][Tx[i]]==1)
		{
			if (t%30==0)
				flag=1;
			break;
		}
	}

		if (flag)
		{

			for (int i=0;i<4;i++)
			{
					RECT[Ty[i]][Tx[i]].setFill(0xffffffff);
					line[Ty[i]][Tx[i]]=1;
			}
			GoDown=0;
			New=1;
		}

		for (int i=0;i<24;i++)
		{
			int s=0;
			for (int j=0;j<12;j++)
				s=s+line[i][j];
			if (s==12)
			{
				for (int I=i;I>=1;I--)
				{
					for (int j=0;j<12;j++)
					{
						line[I][j]=line[I-1][j];
						if (line[I][j]==1)
							RECT[I][j].setFill(0xffffffff);
						else
							RECT[I][j].setFill(0x434343ff);
					}
				}
				for (int j=0;j<12;j++)
				{
					line[0][j]=0;
					RECT[0][j].setFill(0x434343ff);
				}
				score++;
			}
		}
	int speed;
	if (score<100)
		speed=30;
	else if (score<200)
		speed=20;
	else if (score<300)
		speed=10;

		Score=to_string(score);
		ScoreT.setText(Score);


	for (int j=0;j<12;j++)
	{
		if (line[0][j]==1)
		{
			game=0;
			gameover();
			break;
		}
	}
	if(t%speed==0&&GoDown&&!IfPause)
	{
		for (int i=0;i<4;i++)
		{
			rect[i].move(0,l);
		}
	}

		if (t==30*30*30*30)
		t=-1;
		t++;
	}


}

void doEvent(Event event)
{
	for (int i=0;i<4;i++)
	{
		tx[i]=rect[i].getX();
		ty[i]=rect[i].getY();
		Tx[i]=(int(tx[i])-320)/l;
		Ty[i]=(int(ty[i])-40)/l;
	}

	bool GoLeft=1,GoRight=1;
	for (int i=0;i<4;i++)
	{
		if (line[Ty[i]][Tx[i]-1]==1)
		{
			GoLeft=0;
			break;
		}
	}
	for (int i=0;i<4;i++)
	{
		if (tx[i]-350<0)
		{
			GoLeft=0;
			break;
		}
	}

	for (int i=0;i<4;i++)
	{
		if (tx[i]-620>0)
		{
			GoRight=0;
			break;
		}
	}
	for (int i=0;i<4;i++)
	{
		if (line[Ty[i]][Tx[i]+1]==1)
		{
			GoRight=0;
			break;
		}
	}

	switch(event.type)
	{
		case Event::KeyPressed:
		if (event.key.code == Key::Left&&GoLeft)
		{
			for (int i=0;i<4;i++)
			{
				rect[i].move(-l,0);
			}
		}
		else if (event.key.code == Key::Right&&GoRight)
		{
			for (int i=0;i<4;i++)
			{
				rect[i].move(l,0);
			}
		}
		else if (event.key.code == Key::Up)
		{
			Rotate();
			bool CantRotate[2]={0,0};
			for (int i=0;i<4;i++)
			{
				tx[i]=rect[i].getX();
				ty[i]=rect[i].getY();
				Tx[i]=(int(tx[i])-320)/l;
				Ty[i]=(int(ty[i])-40)/l;
			}
			for (int i=0;i<4;i++)
			{
				if (tx[i]-320<0)
				{
					CantRotate[0]=1;
					break;
				}
				else if (tx[i]-650>0)
				{
					CantRotate[1]=1;
					break;
				}
			}
			if (CantRotate[0])
			{
				for (int i=0;i<4;i++)
				{
					rect[i].move(l,0);
				}
			}
			else if (CantRotate[1])
			{
				for (int i=0;i<4;i++)
				{
					if (shape==1||shape==8)
						rect[i].move(-2*l,0);
					else rect[i].move(-l,0);
				}
			}

		}
		bool NoDown=0;
		for (int i=0;i<4;i++)
		{
			if (line[Ty[i]+1][Tx[i]]==1)
			{
				NoDown=1;
			}
		}
		if (event.key.code == Key::Down&&!NoDown)
		{
			for (int i=0;i<4;i++)
			{
				rect[i].move(0,l);
			}
		}
		if (event.key.code == Key::P)
		{

			IfPause=!IfPause;
			if (!IfPause)
				IfPauseT.setText("");
			if (IfPause)
			{
				IfPauseT.setText("Pause");
			}
		}
		break;
	}
}

int main()
{
	MSCinit();

	createWindow(1000, 800, "I Wanna Play Tetris!");
    setBackground(0x000000ff);

	srand((unsigned)time(NULL));

	gameInit();
	gameLoop(gamming, doEvent);

	return 0;
}
