#include "acllib.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<math.h>
#define exploding 0
#define flying 1
#define out 2
#define exploded 3
#define hit 4
#define falling 5
#define walking 6
#define invade 7
int screen_width,screen_height;
int plane_patten_number;
char plane_patten_file[200][50];
int plane_speed_low;
int plane_speed_range;
double angle=0; 
double dangle=0;
int exploded_plane=0;
int entropy=0;
int total=0;
int out_plane_number=0;
int effective_shell_number=0;
int finish=0;
int ubosn=10;
int shell_number=0;
int shell_speed;
int shell_radius;
int draw_interval;
int plane_move_interval;
int plane_occur_interval;
int game_start_interval;
int shell_move_interval;
int points_stage;
int speed_uping=0;
int multiply;
int pause=0;
int soldier_number=0;
int walking_speed;
int falling_speed;
int exploded_soldier=0;
int points=0;
int life;
int available_soldier=0;
struct a_single_shell{
	int x;
	int y;
	int speed;
	int radius;
	int condition;
	int dx;
	int dy;
	int time;
	ACL_Image image;
	ACL_Image *p;
} shell[10000];
struct a_single_plane{
	int height;
	int crossing_speed;
	int distance;
	int color;
	char* s;
	int time;
	ACL_Image image;
	ACL_Image *p;
	int condition;
	int soldier_release;
} planes[1000];
struct a_single_soldier{
	int x;
	int y;
	ACL_Image image;
	ACL_Image *p;
	int dy;
	int dx;
	int condition;
	int time;
} soldier[1000];
int total_life=0;
int plane_number=0;
int soldier_move_interval;
int stage=1;
void parameter_set()
{
	FILE* fp=fopen("parameter.txt","r");
	if (fp==NULL)
	{
		printf("File parameter.txt open failed.");
		getchar();
		return;
	}
	fscanf(fp,"width:%d\n",&screen_width);
	fscanf(fp,"height:%d\n",&screen_height);
	fscanf(fp,"plane_patten_number:%d\n",&plane_patten_number);
	for (int i=0;i<plane_patten_number;i++)
	{
		fscanf(fp,"%s\n",plane_patten_file[i]);
	}
	fscanf(fp,"lower bound of plane speed:%d\n",&plane_speed_low);
	fscanf(fp,"plane speed range:%d\n",&plane_speed_range);
	fscanf(fp,"total plane:%d\n",&total);
	fscanf(fp,"shell speed:%d\n",&shell_speed);
	fscanf(fp,"shell radius:%d\n",&shell_radius);
	multiply=shell_speed*shell_radius;
	fscanf(fp,"shell number upper bound at every moment:%d\n",&ubosn);
	fscanf(fp,"flexible of your cannon:%lf\n",&dangle);
	fscanf(fp,"draw_interval:%d\n",&draw_interval);
	fscanf(fp,"plane_move_interval:%d\n",&plane_move_interval);
	fscanf(fp,"plane_occur_interval:%d\n",&plane_occur_interval);
	fscanf(fp,"game_start_interval:%d\n",&game_start_interval);
	fscanf(fp,"shell_move_interval:%d\n",&shell_move_interval);
	fscanf(fp,"soldier falling speed:%d\n",&falling_speed);
	fscanf(fp,"soldier walking speed:%d\n",&walking_speed);
	fscanf(fp,"life at beginning:%d\n",&life);
	total_life=life;
	soldier_move_interval=plane_move_interval;
	fclose(fp);
}
void timer_set()
{
	startTimer(0,draw_interval);
	startTimer(2,plane_move_interval);
	startTimer(3,game_start_interval);
	startTimer(4,soldier_move_interval);
}
void timer_cancel()
{
	for (int i=0;i<1000;i++) cancelTimer(i); 
}
int Setup()
{
	parameter_set();
	initWindow("barrage",100,100,screen_width,screen_height);
	initConsole();
	time_t t;
	time(&t);
	srand(t);
	void MouseListener(int x,int y,int button,int event);
	void KeyboardListener(int key,int event);
	void TimerListener(int timer_ID);
	beginPaint();
	registerMouseEvent(MouseListener);
	registerKeyboardEvent(KeyboardListener);
	timer_set();
	registerTimerEvent(TimerListener);
	endPaint();
	return 0;
}
char *val_to_string(int points)
{
	int len=0;
	int flag=0;
	char *temp=malloc(20),*s=malloc(20);
	if (points<0)
	{
		flag=-1;
		points=-points;
	}
	while (points)
	{
		temp[len++]=points%10+48;
		points/=10;
	}
	if (flag==-1) temp[len++]='-';
	for (int i=0;i<len;i++)
	s[i]=temp[len-i-1];
	if (len==0) s[len++]='0';
	s[len]=0;
	return s;
}
void new_soldier(int x,int y)
{
	soldier[soldier_number].x=x;
	soldier[soldier_number].y=y;
	soldier[soldier_number].dx=walking_speed;
	soldier[soldier_number].dy=falling_speed;
	soldier[soldier_number].condition=falling;
	soldier[soldier_number].p=&(soldier[soldier_number].image);
	soldier[soldier_number].time=0;
	loadImage("graph\\soldier.jpg",soldier[soldier_number].p);
	printf("new soldier %d at %d %d\n",soldier_number,soldier[soldier_number].x,soldier[soldier_number].y);
	printf("speed %d %d\n",walking_speed,falling_speed);
	soldier_number++;
	available_soldier++;
}
void plane_move()
{
	for (int i=0;i<plane_number;i++)
	if (planes[i].condition==flying)
	{	
		planes[i].distance+=planes[i].crossing_speed;
		if (planes[i].distance>screen_width+100) 
		{
			planes[i].condition=out;
			out_plane_number++;
		}
		if (planes[i].height<screen_height-200&&planes[i].soldier_release==0)
		{
			int temp=rand();
		//	printf("%d\n",temp);
			temp&=0x3f;
			if (temp==0)
			{
				planes[i].soldier_release=1;
				new_soldier(planes[i].distance,planes[i].height);
			}
		}
	}
}
void draw_plane()
{
	for(int i=0;i<plane_number;i++)
	switch (planes[i].condition)
		{
			case flying:
				putImageTransparent(planes[i].p,planes[i].distance,planes[i].height,100,90,WHITE);
				break;
			case exploding:
				putImageTransparent(planes[i].p,planes[i].distance,planes[i].height,100,90,WHITE);
				if (planes[i].time++>=10) planes[i].condition=exploded;
				break;
		}
}
void draw_armstrong()
{
	int x0=screen_width/2;
	int y0=screen_height-70;
//	printf("%d %d\n",x0,y0);
	double dx=10*cos(angle);
	double dy=10*sin(angle);
	int xld=x0-dx;
	int yld=y0-dy;
	int xrd=x0+dx;
	int yrd=y0+dy;
	x0+=28*sin(angle);
	y0-=28*cos(angle);
	int xlu=x0-dx;
	int ylu=y0-dy;
	int xru=x0+dx;
	int yru=y0+dy;
	setPenColor(BLACK);
	line(xld,yld,xlu,ylu);
	line(xlu,ylu,xru,yru);
	line(xru,yru,xrd,yrd);
	line(xrd,yrd,xld,yld);
//	printf("%d %d\n",xld,yld);
//	printf("%d %d\n",xlu,ylu);
//	printf("%d %d\n",xru,yru);
//	printf("%d %d\n",xrd,yrd);
}
void draw_cross()
{
	for (int i=0;i<1000;i+=100)
		for (int j=0;j<1000;j+=100)
		{
			int x=i/100;
			int y=j/100;
			char *s=malloc(20);
			s[0]='(';
			s[1]=x+48;
			s[2]=',';
			s[3]=y+48;
			s[4]=')';
			s[5]=0;
			setTextColor(BLACK);
			paintText(i,j,s);
		}
}
void draw_time_block(int entropy)
{
	setTextSize(20);
	char temp[20],s[20];
	int len=0;
	while (entropy>0)
	{
		temp[len++]=48+entropy%10;
		entropy/=10;
	}
	for (int i=0;i<len-1;i++)
	{
		s[i]=temp[len-i-1];
	}
	if (len==1) {
		s[0]='0';
	}else len--;
	s[len++]='.';
	s[len++]=temp[0];
	s[len++]='s';
	s[len]=0;
	paintText(screen_width/4,screen_height-50,s);
//	printf("%s\n",s);
}
void draw_point_block()
{
	setTextSize(30);
	char *title=malloc(20);
	strcpy(title,"points:");
	char *s=strcat(title,val_to_string(points));
	paintText(screen_width/4*3,screen_height-50,s);
}
void game_finished()
{
	beginPaint();
	finish=1;
	clearDevice();
	ACL_Image temp;
	ACL_Image *p=&temp;
	loadImage("graph\\game_finished.jpg",p);
	putImageTransparent(p,0,0,screen_width,screen_height,WHITE);
	setTextSize(50);
	char*s=malloc(50);
	strcpy(s,"Total shells:");
	s=strcat(s,val_to_string(shell_number));
	paintText(0,0,s);
	strcpy(s,"Plane points:");
	s=strcat(s,val_to_string(exploded_plane));
	s=strcat(s,"*10  ");
	paintText(0,75,s);
	strcpy(s,"Soldier points:");
	s=strcat(s,val_to_string(exploded_soldier));
	paintText(0,150,s);
	strcpy(s,"life point:");
	s=strcat(s,val_to_string(life-total_life));
	s=strcat(s,"*10");
	paintText(0,225,s);
	strcpy(s,"Total points:");
	s=strcat(s,val_to_string(points));
	paintText(0,300,s);
	paintText(0,375,"R: retry ");
	endPaint();
	return ;
}
void draw_shells()
{
	for (int i=0;i<shell_number;i++)
	{
		int x=shell[i].x;
		int y=shell[i].y;
		int r=shell[i].radius;	
		switch (shell[i].condition)
		{	
			case flying:
				putImageTransparent(shell[i].p,x-r,y-r,2*r,2*r,WHITE);
				break;
			case exploding:
				setTextSize(30);
				paintText(x,y,"HIT");
				if (shell[i].time++>=10) shell[i].condition=exploded;
				break;
		}
	}
} 
void draw_left_shell_number()
{
	setTextSize(20);
	char *s=val_to_string(ubosn-effective_shell_number);
	paintText(screen_width/2-10,screen_height-30,s);
}
void speed_up()
{
	if (rand()&1==1)
	{
		plane_speed_low+=rand()%3;
	}
	if (rand()&1==1)
	{
		plane_speed_range+=rand()&3;
	}
	plane_occur_interval-=plane_occur_interval/4;
	if (plane_occur_interval==0) plane_occur_interval=10;
	speed_uping=1;
	cancelTimer(1);
	startTimer(1,plane_occur_interval);
	static int pedal=0;
	points_stage+=++pedal;
}
void draw_speed_uping()
{
	setTextSize(30);
	paintText(screen_width/2,screen_height/2,"Speed Up!");
	static int time=0;
	if (time++==20)
	{
		time=0;
		speed_uping=0;
	}
}
void draw_soldier()
{
	for (int i=0;i<soldier_number;i++)
	{
		if (soldier[i].condition!=out&&soldier[i].condition!=invade)
		{
			putImageTransparent(soldier[i].p,soldier[i].x,soldier[i].y,32,32,WHITE);
		}
		if (soldier[i].condition==hit)
		{
			if (soldier[i].time++>30)
			{
				soldier[i].condition=out;
			}
		}
	}
}
void draw_life_block()
{
	char *s=malloc(20);
	strcpy(s,"life:");
	s=strcat(s,val_to_string(life));
	setTextSize(30);
	paintText(screen_width/3,screen_height-50,s);
}
void draw()
{
	beginPaint();
//	printf("draw\n");
//	printf("%d %d\n",plane_speed_range,plane_speed_low);
	clearDevice();
	draw_plane();
	draw_armstrong();
	draw_time_block(entropy*draw_interval/100);
	draw_point_block();
	draw_life_block();
	draw_shells();
	draw_left_shell_number();
	draw_soldier();
	if (speed_uping) draw_speed_uping();
//	printf("%d %d\n",getWidth(),getHeight());
//	draw_cross();
	endPaint();
	entropy++;
	if (entropy>stage*5000/draw_interval) 
	{
		speed_up();
		stage++;
		printf("entropy=%d draw_interval=%d stage=%d\n   ",entropy,draw_interval,stage);
	}
	if (out_plane_number+exploded_plane>=total&&available_soldier==0) 
	{
		game_finished(); 
	}
}
char *random_string()
{	
	int len=rand()%20;
	char *s=malloc(len);
	for (int i=0;i<len;i++)
	{
		s[i]=rand()%26+97;
	}
	return s;
}
void new_plane()
{
	if (plane_number>=total) return;
	planes[plane_number].height=rand()%(screen_height-100);
	planes[plane_number].distance=0;
	planes[plane_number].s=random_string();
	planes[plane_number].color=rand()%8;
	planes[plane_number].p=&(planes[plane_number].image);
	planes[plane_number].condition=flying;
	planes[plane_number].time=0;
	int temprand=rand()%plane_patten_number;
	loadImage(plane_patten_file[temprand],planes[plane_number].p);
	planes[plane_number].soldier_release=0;
	planes[plane_number++].crossing_speed=rand()%plane_speed_range+plane_speed_low;
}
void new_plane_switch_change()
{
		startTimer(1,plane_occur_interval);
		cancelTimer(3);
}
void MouseListener(int x,int y,int button,int event)
{
}
void new_shell()
{
	if (effective_shell_number>=ubosn) 
	{	
		return;
	}
	startTimer(shell_number+5,shell_move_interval);
	effective_shell_number++;
	shell[shell_number].x=screen_width/2;
	shell[shell_number].y=screen_height-70;
	shell[shell_number].speed=shell_speed;
	shell[shell_number].radius=shell_radius;
	shell[shell_number].dx=shell[shell_number].speed*sin(angle);
	shell[shell_number].dy=-shell[shell_number].speed*cos(angle);
	shell[shell_number].time=0;
	shell[shell_number].p=&(shell[shell_number].image);
	loadImage("graph\\shell.jpg",shell[shell_number].p);
	shell[shell_number++].condition=flying;
}
void biggershell()
{
	int x=shell_radius+4;
	if (x<=0) return;
	int y=multiply/x;
	if (y>1)
	{
		shell_radius=x;
		shell_speed=y;
	}
}
void smallershell()
{
	int x=shell_radius-4;
	if (x<=0) return;
	int y=multiply/x;
	if (y>0)
	{
		shell_radius=x;
		shell_speed=y;
	}
}
void retry()
{
	points=0;
	finish=0;
	plane_number=0;
	shell_number=0;
	effective_shell_number=0;
	life=total_life;
	soldier_number=0;
	exploded_plane=0;
	out_plane_number=0;
	available_soldier=0;
	exploded_soldier=0;
	entropy=0;
	stage=1;
	angle=0;
	parameter_set();
	timer_cancel();
	timer_set();
}
void KeyboardListener(int key,int event)
{
	//printf("%d %d\n",key,event);
	if (event==0)
	switch (key)
	{
		case 37:angle-=dangle;break;
		case 39:angle+=dangle;break;
		case 38:biggershell();break;
		case 40:smallershell();break;
		case 32:new_shell();break;//boom
		case 70:
		case 102:pause=1-pause;printf("pause\n");break;
		case 82:
		case 114:retry();break;
	}
	
}
int d(int x,int y,int xp,int yp)
{
	return (x-xp)*(x-xp)+(y-yp)*(y-yp);
}
int lay(int x,int y,int r,int xp,int yp,int dx,int dy)
{
	r*=r;
	if (d(x,y,xp,yp)<r||d(x,y,xp,yp+dy)<r||d(x,y,xp+dx,yp)<r||d(x,y,xp+dx,yp+dy)<r)
	return 1;
	if (x>xp&&x<xp+dx&&y>yp&&y<yp+dy)
	return 1;
	return 0;
}
int shell_condition(int x,int y,int r)
{
	if (x<-r||x>screen_width+r||y<-r||y>screen_height+r)
	return out;
	int xp,yp;
	int flag=flying;
	for (int i=0;i<plane_number;i++)
	if (planes[i].condition==flying)
	{
		xp=planes[i].distance;
		yp=planes[i].height;
		if (lay(x,y,r-4,xp,yp,100,90))
		{
			planes[i].condition=exploding;
			freeImage(planes[i].p);
			loadImage("graph\\plane_lost.jpg",planes[i].p);
			flag=exploding;
			exploded_plane++;
			points+=10;
		}
	}
	for (int i=0;i<soldier_number;i++)
	{
		if (soldier[i].condition==falling||soldier[i].condition==walking)
		{
			if (lay(x,y,r,soldier[i].x,soldier[i].y,32,32))
			{
				soldier[i].condition=hit;
				freeImage(soldier[i].p);
				loadImage("graph\\underdog.jpg",soldier[i].p);
				flag=exploding;
				exploded_soldier++;
				available_soldier--;
				points++;
			}
		}
	}
	return flag;
}
void shell_move(int shell_ID)
{
	if (shell[shell_ID].condition!=flying) return;
	shell[shell_ID].x+=shell[shell_ID].dx;
	shell[shell_ID].y+=shell[shell_ID].dy;
	if (shell[shell_ID].condition==flying)
	{
		shell[shell_ID].condition=shell_condition(shell[shell_ID].x,shell[shell_ID].y,shell[shell_ID].radius);
		if (shell[shell_ID].condition!=flying) 
		{
			effective_shell_number--;
			cancelTimer(shell_ID+5);
		}
	}
}
void game_over()
{
	beginPaint();
	finish=1;
	ACL_Image image;
	ACL_Image *p=&image;
	loadImage("graph\\soldier.jpg",p);
	putImageTransparent(p,0,0,screen_width,screen_height,WHITE);
	setTextSize(50);
	char*s=malloc(50);
	strcpy(s,"Total shells:");
	s=strcat(s,val_to_string(shell_number));
	paintText(0,0,s);
	strcpy(s,"Plane points:");
	s=strcat(s,val_to_string(exploded_plane));
	s=strcat(s,"*10  ");
	paintText(0,75,s);
	strcpy(s,"Soldier points:");
	s=strcat(s,val_to_string(exploded_soldier));
	paintText(0,150,s);
	strcpy(s,"life point:");
	s=strcat(s,val_to_string(life-total_life));
	s=strcat(s,"*10");
	paintText(0,225,s);
	strcpy(s,"Total points:");
	s=strcat(s,val_to_string(points));
	paintText(0,300,s);
	paintText(0,375,"R: retry ");
	endPaint();
}
void soldier_invade()
{
	life--;
	if (life<=0) game_over();
	points-=10;
	if (points<0) points=0;
	available_soldier--;
}
void soldier_move()
{
	for (int i=0;i<soldier_number;i++)
	{
		if (soldier[i].condition==falling)
		{
			soldier[i].y+=soldier[i].dy;
			if (soldier[i].y>screen_height-50)
			{
				soldier[i].condition=walking;
				soldier[i].y=screen_height-50;
			}
		}
		else 
		if (soldier[i].condition==walking)
		{
			if (soldier[i].x>screen_width/2+4)
			{
				soldier[i].x-=soldier[i].dx;
			}
			else 
			if (soldier[i].x<screen_width/2-30)
			{
				soldier[i].x+=soldier[i].dx;
			}
			else 
			if (soldier[i].x<screen_width/2+5&&soldier[i].x>screen_width/2-32)
			{
				soldier[i].condition=invade;
				soldier_invade();
			}
		}
	}
}
void TimerListener(int timer_ID)
{
	if (finish) return;
	if (pause) 
	{
			return;
	}
	switch (timer_ID)
	{
		case 0:draw();break;
		case 1:new_plane();break;
		case 2:plane_move();break;
		case 3:new_plane_switch_change();break;
		case 4:soldier_move();break;
		default :shell_move(timer_ID-5);
	}
}

