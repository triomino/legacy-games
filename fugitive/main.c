#include "acllib.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<math.h>
#include "t.h"
#include "v.h"
#include "f.h"
int Setup(void)
{
	initConsole();
	set_value();
	initWindow("fugitive",0,0,window_width,window_height+add_height); 
	set_action();
	registerKeyboardEvent(KeyboardListener);
	registerMouseEvent(MouseListener);
	registerTimerEvent(TimerListener);
	set_timer();
//	beginChapter(0);
//	int a,b,c,d;
//	while (1)
//	{
//	scanf("%d %d %d %d",&a,&b,&c,&d);
//	printf("%d\n",minHamDis(you,a,b,c,d));
//	} 
	return 0;
}
void set_value(void){
	FILE* fp=fopen("saving.txt","r");
	fscanf(fp,"%*[^:]:%d",&diff);
	fscanf(fp,"%*[^:]:%d",&chapter_number);
	fscanf(fp,"%*[^:]:%d",&CompleteChap);
	for (int i=0;i<chapter_number;i++){
		fscanf(fp,"%d",&Completion[i]);
	}
	fscanf(fp,"%*[^:]:%d",&atkstnum);
	atkstbt[0]=0;
	for (int i=0;i<atkstnum;i++)
	{
		get_man_info(&atkstplcdt[i],fp,you);
		fscanf(fp,"%*[^:]:%d",&atkstet[i]);
		if (i+1<atkstnum) atkstbt[i+1]=atkstet[i];
		printf("%d %d %d\n",i,atkstbt[i],atkstet[i]);
	}
	fclose(fp);
	fp=fopen("set.txt","r");
	fscanf(fp,"%*[^:]:%d",&actions_interval);
	fscanf(fp,"%*[^:]:%d",&window_width);
	fscanf(fp,"%*[^:]:%d",&window_height);
	fscanf(fp,"%*[^:]:%d",&add_height);
//	fscanf(fp,"%*[^:]:%d",&chapter_number);
	fclose(fp);
	start=time(NULL);
//	for (int i=0;i<atkstnum;i++){
//		ACL_Image *q=&AtkStImage[i];
//		printf("%s\n",PlayerImagePath[i]);
//		loadImage(PlayerImagePath[i],q);
//		printf("%s",PlayerImagePath[i]);
//	}/
	color_set();
	printf("%s\n",people[0].name);
	printf("%d\n",people[0].wpr[1]);
	srand(start);
	population=1;
	condition=chooseChap;
}
void color_set(void){
	mycolor.bc=GREEN;
	mycolor.pc=BLACK;
	mycolor.pw=2;
	mycolor.tbkc=GREEN;
	mycolor.ts=20;
	mycolor.tc=WHITE;
	frdcolor.bc=BLUE;
	frdcolor.pc=BLACK;
	frdcolor.pw=2;
	frdcolor.tbkc=BLUE;
	frdcolor.ts=20;
	frdcolor.tc=WHITE;
	enycolor.bc=RED;
	enycolor.pc=BLACK;
	enycolor.pw=2;
	enycolor.tbkc=RED;
	enycolor.ts=20;
	enycolor.tc=WHITE;
}
void get_man_info(man *p,FILE* fp,character chrct){
	fscanf(fp,"%*[^:]:%s",&p->name);
	if (chrct!=you){
		fscanf(fp,"%*[^:]:%d",&p->x);
		fscanf(fp,"%*[^:]:%d",&p->y);
		fscanf(fp,"%*[^:]:%d",&p->amn);
		for (int i=0;i<p->amn;i++){
			fscanf(fp,"%*[^:]:%d",&p->am[i]);
			switch (p->am[i]){
				case 0:fscanf(fp,"%*[^(](%d,%d)",&p->amx[i],&p->amy[i]);
						break;
				case 1:
						break;
				case 2:fscanf(fp,"%*[^:]:%d",&p->amatkn[i]);
						fscanf(fp,"%*[^:]:");
						for (int j=0;j<p->amatkn[i];j++){
							fscanf(fp,"%d",&p->amatk[i][j]);
						}
						break;
				case 3:fscanf(fp,"%*[^(](%d,%d)",&p->amx[i],&p->amy[i]);
						fscanf(fp,"%*[^b]building %d",&p->amatko[i]);
						p->amatko[i]--;
						break;
				case 7:fscanf(fp,"%*[^:]:%d",&p->amx[i]);
						break;
			}
			fscanf(fp,"%*[^:]:%d-%d",&p->amb[i],&p->ame[i]);
			p->amb[i]--;
			p->ame[i]--;
		}
	}	
	fscanf(fp,"%*[^:]:%d",&p->sp);
	fscanf(fp,"%*[^:]:%d",&p->r);
	fscanf(fp,"%*[^:]:%d",&p->fl);
	fscanf(fp,"%*[^:]:%d",&p->gl);
	fscanf(fp,"%*[^:]:%d",&p->atk);
	fscanf(fp,"%*[^:]:%d",&p->atk_r);
	fscanf(fp,"%*[^:]:%d",&p->def);
	fscanf(fp,"%*[^:]:%d",&p->act_interval);
	fscanf(fp,"%*[^:]:%d",&p->atkint);
	fscanf(fp,"%*[^:]:%d",&p->lda_r);
	fscanf(fp,"%*[^:]:%d",&p->lda_sp);
	fscanf(fp,"%*[^:]:%d",&p->atkpn);
	for (int i=0;i<p->atkpn;i++)
	{
		fscanf(fp,"%*[^:]:%d",&p->atkp[i]);
		switch (p->atkp[i]){
			case 0:fscanf(fp,"%d %d %d",&p->atkag[i],&p->atkmr[i],&p->atkma[i]);
					break;
			case 1:fscanf(fp,"%d %d %d",&p->atkag[i],&p->atkmr[i],&p->atkma[i]);
					break;
			case 2:fscanf(fp,"%d %d %d",&p->atkdis[i],&p->atkmr[i],&p->atkma[i]);
					break;
			case 3:fscanf(fp,"%d %d %d",&p->atkdis[i],&p->atkmr[i],&p->atkma[i]);
					break;
		}
		fscanf(fp,"%d",&p->atkpfn[i]);
	}
	fscanf(fp,"%*[^:]:");
	for (int i=0;i<10;i++)
	fscanf(fp,"%d",&p->wpr[i]);
	fscanf(fp,"%*[^:]:");
	for (int i=0;i<wp_number;i++)
	fscanf(fp,"%d",&p->wpmr[i]);
	fscanf(fp,"%*[^:]:");
	for (int i=0;i<wp_number;i++)
	fscanf(fp,"%d",&p->wpma[i]);
//	if (p->wpma[3]==10&&chrct!=you){
//		fscanf(fp,"%s",p->GraphPath);
//		ACL_Image*q=&p->face;
//	    loadImage(p->GraphPath,q);
//		printf("p graphpath %s\n",p->GraphPath);
//	}
//	else if (chrct!=you){
//		ACL_Image*q=&p->face;
//		loadImage(FacePath[rand()%5],q);
//		printf("face path %s\n",FacePath[rand()%5]);
//	} 
	p->rl=0;
	p->speedup=0;
	p->backing=0;
	if (p->wpr[0]<=0)next_weapon(p);
//	if (chrct!=you) printf("%d %d %s\n",p->fl,p->amn,p->name);
//	printf("%d %d %d\n",p->atkmr[0],p->atkmr[1],p->atkmr[2]);
}
void set_timer(void){
	startTimer(0,actions_interval);
	startTimer(1,1000);//life recover and small soldier occur
	startTimer(2,400);//item eat
	startTimer(3,100);//Event
}
void set_action(void){
}
void KeyboardListener(int key, int event){
	if (condition==operate)
	if (people[0].rl>0)
	if (event==0)
	{
		int c=0;
		switch(key){
//			case 87:up_bound-=100;
//					draw();
//					break;
//			case 65:left_bound-=100;
//					draw();
//					break;
//			case 83:up_bound+=100;
//					draw();
//					break;
//			case 68:left_bound+=100;
//					draw();
//					break;
			case 87:{
				people[0].movetox=people[0].x;
				people[0].movetoy=people[0].y-people[0].sp;
				draw();
				break;
			}
			case 65:{
				people[0].movetox=people[0].x-people[0].sp;
				people[0].movetoy=people[0].y;
				draw();
				break;
			}
			case 83:{
				people[0].movetox=people[0].x;
				people[0].movetoy=people[0].y+people[0].sp;
				draw();
				break;
			}
			case 68:{
				people[0].movetox=people[0].x+people[0].sp;
				people[0].movetoy=people[0].y;
				draw();
				break;
			}
			case 69:{
					point* q=nearestAtkPt(&people[0]);
					if (q!=NULL)attackto(&people[0],q->x,q->y);
					//if enemy in atkdis atk it
					break;}
			case 70:{
				condition=pause;
				break;
			}
			case 32:{
				left_bound=people[0].x-window_width/2;
				up_bound=people[0].y-window_height/2;
				draw();
				break;
			}
			case 82:{
				if (people[0].musou==0) people[0].musou=1;
				for (int i=0;i<total_pattern;i++){
				}
				break;
			}//musou
			case 66:{
				people[0].rl=0;
				break;
			}
			default:if (key>48&&key<=48+wp_number) people[0].weapon=key-49;
			else if (key>96&&key<=96+wp_number) people[0].weapon=key-97;
			break;
		}
		left_bound=people[0].x-window_width/2;
		up_bound=people[0].y-window_height/2;
		draw();
		return;
	}
	if (condition==pause){
			if (people[0].rl>0)
	if (event==0)
	{
		int c=0;
		switch(key){
			case 87:up_bound-=100;
					draw();
					break;
			case 65:left_bound-=100;
					draw();
					break;
			case 83:up_bound+=100;
					draw();
					break;
			case 68:left_bound+=100;
					draw();
					break;
			case 32:{
				left_bound=people[0].x-window_width/2;
				up_bound=people[0].y-window_height/2;
				draw();
				break;
			}
			case 70:{
				condition=operate;
				break;
			}
		}
	}
	}
	if (condition==chooseChap){
		if (key>48&&key<=CompleteChap+49){
			condition=dialog;
			beginChapter(0);
		}
		printf("key=%d event=%d\n",key,event);
	}
	if (condition==evaluate){
		if (key==32){
			condition=chooseChap;
		}
	}
}
void MouseListener(int x,int y,int button,int event){	
	if (condition==operate){
		switch (event){
			case 0:switch (button) {
				case 1:
					if (x<=add_height&&x>=0&&y>=window_height&&y<=window_height+add_height)
					{
						//small map click
						double sh=map_height/(double)add_height;
						double sw=map_width/(double)add_height;
						int cx=x*sw;
						int cy=(y-window_height)*sh;
						left_bound=cx-window_width/2;
						up_bound=cy-window_height/2;
						draw();
					}
					else {
						attackto(&people[0],x+left_bound,y+up_bound);
					}
					break;		
				case 3:people[0].moving=1;
						people[0].movetox=x+left_bound;
						people[0].movetoy=y+up_bound;//move
				break;
			}	break;
			case 4:next_weapon(&people[0]);
					break;
			case 3:do{
					people[0].weapon=(people[0].weapon+wp_number-1)%wp_number;
					}while (people[0].wpr[people[0].weapon]==0);					
					break;
		}
	}	
	if (condition==dialog){
		if (event==0){
			if (dialogFlag==beforeChap&&imageIndex==bciPathNum){
				printf("operate\n");
				condition=operate;
				newStage(0);
				imageIndex=0;
				return;
			}
			if (dialogFlag==endChap&&imageIndex==eciPathNum){
				condition=evaluate;
				imageIndex=0;
				return;
			}
			ACL_Image *p=&picture;
//			printf("1\n");
//			printf("%s\n",bciPath[imageIndex]);
			if (dialogFlag==beforeChap) loadImage(bciPath[imageIndex++],p);
			else loadImage(eciPath[imageIndex++],p);
//			printf("hei %d\n",p->height);
//			printf("wid %d\n",p->width);
//			printf("2\n");/
			beginPaint();
			putImageScale(p,0,0,window_width,window_height+add_height);
			endPaint();
//			printf("3\n");
			freeImage(p);
//			printf("4\n");
//			printf("image index %d\n",imageIndex);
		}
	}
}
void attackto(man*p,int x,int y){
	if (p->atting==0&&entropy-p->attlt>p->atkint) 
	if (p->weapon==0){
		p->atting=1;
		if (entropy-p->attlt<p->atkint+sucint)
		p->attpat=(p->attpat+1)%p->atkpn;
		else p->attpat=0;
		p->atktox=x;
		p->atktoy=y;
	}
	else if (p->weapon==1){
			p->atting=1;
			p->atktox=x;
			p->atktoy=y;
			p->wpr[1]--;
			if (p->wpr[1]<=0) {
				p->weapon=0;
			}
		}
	else if (p->weapon==2){
		p->atting=1;
		p->atktox=x;
		p->atktoy=y;
		p->wpr[1]--;
		if (p->wpr[2]<=0){
			p->weapon=0;
		}
//		printf("%d %d to %d %d",p->x,p->y,p->atktox,p->atktoy);
	}
}
int dis2(int x,int y,int tox,int toy){
	return ((x-tox)*(x-tox)+(y-toy)*(y-toy));
}
int inbd(int x,int y,obstacle* p){
	return (x>p->l&&x<p->r&&y>p->u&&y<p->d);
}
void swap(int *a,int *b){
	int temp=*a;
	*a=*b;
	*b=temp;
}
int findmy(int y){
//	int j;
//	for (j=0;j<hor&&my[j+1]<y;j++);
//	return j;
	int l=0,r=hor-1,m;
	while (l+1<r){
		m=(l+r)>>1;
		if (my[m]<y) l=m;
		else r=m;
	}
	return l;
}
int findmx(int x){
//	int j;
//	for (j=0;j<ver&&mx[j+1]<x;j++);
//	return j;
	int l=0,r=ver-1,m;
	while (l+1<r){
		m=(l+r)>>1;
		if (mx[m]<x) l=m;
		else r=m;
	}
	return l;
}
int nocrossing(character ch,int x,int y,int tox,int toy){
	const int crossing=0;
//	printf("1 %d %d %d %d\n",x,y,tox,toy);
//	printf("b1\n");
	if (out_of_map(x,y)||out_of_map(tox,toy)) return 0;
	if (x!=tox&&y!=toy){
//		printf("b2\n");
		int dx=tox-x;
		int dy=toy-y;
		int cm=tox*y-toy*x;
		if (tox<x) swap(&tox,&x);
		if (toy<y) swap(&toy,&y); 
		int i=findmx(x);
		int j=findmx(tox);
		if (mx[j+1]==tox) j++;
		for (int t=i;t<j;t++){
			int ty=(mx[t+1]*dy+cm)/(double)dx;
//			printf("b3 %d %d\n",mx[t],ty);
			if (!algo(ch,ctx[t],ty,ctx[t+1],ty)) {
//				printf("b4 crossing %d %d %d\n",ctx[t],ctx[t+1],ty);
				return crossing;
			}
		}
		i=findmy(y);
		j=findmy(toy);
		if (toy==my[j+1]) j++;
		for (int t=i;t<j;t++){
			int tx=(my[t+1]*dx-cm)/(double)dy;
//			printf("3 %d %d\n",tx,my[t]);
//			printf("%d %d %d\n",cty[t],cty[t+1],tx);
			if (!algo(ch,tx,cty[t],tx,cty[t+1])){
//				printf("3 crossing %d %d %d\n",cty[t],cty[t+1],tx);
				return crossing;
			}
		}
	}else if (x==tox){
//		printf("b5\n");
		int j,k;
		if (y>toy) swap(&y,&toy);
		j=findmy(y);
		k=findmy(toy);
		if (my[k+1]==toy) k++;
		for (int t=j;t<k;t++){
			if (!algo(ch,x,cty[t],x,cty[t+1])){
				return crossing;
			}
		}
	}else if (y==toy){
//		printf("b6\n");
		int i,j;
		if (tox<x) swap(&tox,&x);
		i=findmx(x);
		j=findmx(tox);
		if (mx[j+1]==tox)j++;
		for (int t=i;t<j;t++){
//			printf("%d %d %d %d\n",ctx[t],y,ctx[t+1],y);
			if (!algo(ch,ctx[t],y,ctx[t+1],y)){
				return crossing;
			}
		}
	}
//	printf("b7\n");
	return !crossing;
}
void move(man*p){
	if (p->rl<=0) return;
	int x=p->movetox;
	int y=p->movetoy;
	int tox,toy;
	int d;
	if (out_of_map(x,y)) return;
	int s=spd(p);
	if ((d=nocrossingtoArdPt(p->ch,p->x,p->y,x,y))!=-1){
//		printf("1\n");
		int dx=x-p->x+_dx[d];
		int dy=y-p->y+_dy[d];
		double mo=sqrt(dx*dx+dy*dy);
		if (mo<=s) {
			p->x=x+_dx[d];
			p->y=y+_dy[d];
			p->moving=0;
		}
		else {
			p->x+=dx/mo*s;
			p->y+=dy/mo*s;
		}
	}//if nocrossing go to x+_dx[d],y+_dy[d]
	else{
//		printf("2\n");
		int d;
		int bx=findmx(p->x);
		int by=findmy(p->y);
			d=firstStepToArd(x,y,p);
//			if (p->ch==you){
//			printf("dr %d\n",d);
//			debug=1;
//			printf("x, y to near ct %d %d %d %d %d \n",p->x,p->y,ctx[bx+_dx[d]],cty[by+_dx[d]],algo(p->ch,p->x,p->y,ctx[bx+_dx[d]],cty[by+_dx[d]]));
//			debug=0;
//		}
			if (d!=-1&&algo(p->ch,p->x,p->y,ctx[bx+_dx[d]],cty[by+_dy[d]])){
//				printf("3\n");
				int tox=ctx[bx+_dx[d]];
				int toy=cty[by+_dy[d]];// if its square must go able
				int dx=tox-p->x;
				int dy=toy-p->y;
				double mo=sqrt(dx*dx+dy*dy);
				if (mo<=s){
					p->x=tox;
					p->y=toy;
				}
				else {
					p->x+=s*dx/mo;
					p->y+=s*dy/mo;
				}
			}
			else if (d!=-1){
				switch (d){
					case 0:{
						tox=ctx[bx];
						toy=my[by]+1;
						break;
					}
					case 1:{
						tox=ctx[bx];
						toy=my[by+1]-1;
						break;
					}
					case 2:{
						tox=mx[bx]+1;
						toy=cty[by];
						break;
					}
					case 3:{
						tox=mx[bx+1]-1;
						toy=cty[by];
						break;
					}
				}
//				printf("d %d x y %d %d to %d %d \n",d,p->x,p->y,tox,toy);
				if (algo(p->ch,p->x,p->y,tox,toy)){
					int dx=tox-p->x;
					int dy=toy-p->y;
					double mo=sqrt(dx*dx+dy*dy);
					if (mo<=s){
						p->x=tox;
						p->y=toy;
						attackto(p,tox,toy);
					}
					else {
						p->x+=s*dx/mo;
						p->y+=s*dy/mo;
					}
				}
			}
//			else {
////				printf("6\n");
//				d=firstStepTonearestAktGt(p);
//				if (d!=-1&&d<4){
////					printf("4 return d=%d\n",d);
////					printf("%d %d ct %d %d\n",bx,by,ctx[bx],cty[by]);
//					int tox=ctx[bx+_dx[d]];
//					int toy=cty[by+_dy[d]];// if its square must go able
//					int dx=tox-p->x;
//					int dy=toy-p->y;
//					double mo=sqrt(dx*dx+dy*dy);
//					if (mo<=s){
//						p->x=tox;
//						p->y=toy;
//					}
//					else {
//						p->x+=s*dx/mo;
//						p->y+=s*dy/mo;
//					}
//				}
//				else if (d>=4){
//					int tox,toy;
//					switch (d-4){
//						case 0:{
//							tox=ctx[bx];
//							toy=my[by]+1;
//							break;
//						}
//						case 1:{
//							tox=ctx[bx];
//							toy=my[by+1]-1;
//							break;
//						}
//						case 2:{
//							tox=mx[bx]+1;
//							toy=cty[by];
//							break;
//						}
//						case 3:{
//							tox=mx[bx+1]-1;
//							toy=cty[by];
//							break;
//						}
//					}
//					int dx=tox-p->x;
//					int dy=toy-p->y;
//					double mo=sqrt(dx*dx+dy*dy);
//					if (mo<=s){
//						p->x=tox;
//						p->y=toy;
//					}
//					else {
//						p->x+=s*dx/mo;
//						p->y+=s*dy/mo;
//					}					
//				}
//				else {
////					printf("5\n");
//					int tox=ctx[bx];
//					int toy=cty[by];
//					int dx=tox-p->x;
//					int dy=toy-p->y;
//					printf("pos %d %d\n",p->x,p->y);
//					double mo=sqrt(dx*dx+dy*dy);
//					if (mo<=s){
////						printf("%s stop here %d %d\n",p->name,tox,toy);
//						p->x=tox;
//						p->y=toy;
//					}
//					else {
//						p->x+=s*dx/mo;
//						p->y+=s*dy/mo;
//					}
//				}	
//			}
//			
//					
	}
}
int nocrossingtoArdPt(character ch,int x,int y,int tox,int toy){
	//return the direcetion go to around the point
	if (nocrossing(ch,x,y,tox,toy)) return 4;
	for (int d=0;d<4;d++){
		if (nocrossing(ch,x,y,tox+_dx[d],toy+_dy[d])){
			return d;
		}
	}
	return -1;
}

void getBlock(int x,int y,int point[]){
}
int firstStepTonearestAktGt(man *p){
	int x=p->x,y=p->y;
	if (out_of_map(x,y)) 
	{
		return -1;
	}
	int stx,sty;
	stx=findmx(x);
	sty=findmy(y);
	character oppo;
	if (p->ch==enemy) {
		oppo=friends;
	}
	else if (p->ch==you||p->ch==friends){
		oppo=enemy;
	}
	else if (p->ch==two){
		oppo=two;
	}
	if (nearDoor[stx][sty]==1){
		for (int d=0;d<4;d++){
			if (hasDoor[stx][sty][d][oppo]==1) return d+4;
		}
	}
	num=1;
	heap[1].x=stx;
	heap[1].y=sty;
	visited[stx][sty]=++angry;
	heap[1].l=0;
	int d,l,tox,toy;
	//d Euclid dis  l Hamilton dis
	while (num>0){
		x=heap[1].x;
		y=heap[1].y;
		l=heap[1].l;
//		if (&people[15]==p)
//		for (int i=1;i<=num;i++){
//			printf("i %d x %d y %d d %d l %d\n",i,heap[i].x,heap[i].y,heap[i].d,heap[i].l);
//		}
		delete_root();
		for (int dr=0;dr<4;dr++){
			tox=x+_dx[dr];
			toy=y+_dy[dr];
			if (tox>=0&&tox<ver&&toy>=0&&toy<hor)
			{
				if (visited[tox][toy]!=angry&&algo(p->ch,ctx[x],cty[y],ctx[tox],cty[toy])){
					if (nearDoor[tox][toy]==1){
						for (int dd=0;dd<4;dd++){
							if (hasDoor[tox][toy][dd][oppo]==1){
								int stepone;
								minHamDis(p->ch,ctx[tox],cty[toy],ctx[stx],cty[sty],&stepone);
//								printf("here a door %d %d center %d %d on dr %d\n",tox,toy,ctx[tox],cty[toy],dd);
//								printf("%d %d to here first step %d and oppo %d\n",ctx[stx],cty[sty],oppo_dr[stepone],stepone);
								return oppo_dr[stepone];
							}
						}
					}
					d=dis2(ctx[tox],cty[toy],ctx[stx],cty[sty]);
					add_to_heap(tox,toy,d,int_abs(ctx[x]-ctx[tox])+int_abs(cty[y]-cty[toy])+l);
					visited[tox][toy]=angry;
				}
			}
		}
	}
	return -1;
}
int firstStep(int x,int y,man *p){//first step to genius 
	if (dismode==R){
		int dr;
//		printf("what?\n");
		minHamDis(p->ch,x,y,p->x,p->y,&dr);
//		printf("no\n");
		if (dr==-1) {
//			printf("!!!!!NNNNNNOOOOOO\n");
			return -1;
		}
//		printf("dr=%d\n",dr);
		dr=oppo_dr[dr];
		if (nocrossing(p->ch,p->x,p->y,p->x+_dx[dr]*spd(p),p->y+_dy[dr]*spd(p))) 
		{
//			printf("a1\n");
			return dr;
		}
		else {
//			printf("a2\n");
			return -1;
		}
	}
	else if (dismode==E){
//		printf("a4\n");
		int min=dis2(p->x,p->y,x,y),mind=-1,tox,toy;
		for (int d=0;d<4;d++){
			tox=p->x+spd(p)*_dx[d];
			toy=p->y+spd(p)*_dy[d];
			if (min>dis2(x,y,tox,toy)&&nocrossing(p->ch,p->x,p->y,tox,toy)){
				mind=d;
				min=dis2(x,y,tox,toy);
			}
		}
		return mind;
	}
//	printf("a3\n");
	return -1;
}
int firstStepToArd(int x,int y,man *p){ 
		int mindis=INT_MAX,mindr=-1,dr;
//		if (p==&people[15])printf("fSTArd %d %d to %d %d\n",p->x,p->y,x,y);
		for (int d=0;d<4;d++){
			if (minHamDis(two,x+_dx[d],y+_dy[d],p->x,p->y,&dr)!=INT_MAX){
				if (dis2(x+_dx[d],y+_dy[d],p->x,p->y)<mindis){
					mindis=dis2(x+_dx[d],y+_dy[d],p->x,p->y);
					mindr=dr;
				}
			}
		}
		if (mindr==-1) return -1;
		else{
//			if (p==&people[15])printf("fSTArd mindr %d\n",mindr);
			return oppo_dr[mindr];
		}
}
man* danger(int x,int y,character ch){
	man*p;
	for (int i=0;i<population;i++){
		if (oppo_ch(people[i].ch,ch)){
			p=&people[i];
			if (p->rl>0)
			if (dis2(p->x,p->y,x,y)<maxatkdis2(p))
			{
				return p;
			}
		}
	}
	//for small soldier 
	for (int i=0;i<ssn;i++){
		if (oppo_ch(ss[i].ch,ch)){
			p=&ss[i];
			if (p->rl>0)
			if (dis2(p->x,p->y,x,y)<maxatkdis2(p))
			{
				return p;
			}
		}
	}
	return NULL;
}
int st_order3(int a,int b,int c){
	return (a<b&&b<c||a>b&&b>c);
}
int maxatkdis2(man*p){
	int temp=p->weapon,max=0;
	for (int i=0;i<wp_number;i++){
		p->weapon=i;
		if (max<atkdis(p)) max=atkdis(p);
	}
	p->weapon=temp;
	return max*max;
}
int order3(int a,int b,int c){
	return (a<=b&&b<=c||a>=b&&b>=c);
}
int onwall(int x,int y,obstacle *p){
	if (p->mode<=2){
		int cx=(p->l+p->r)>>1;
		int cy=(p->u+p->d)>>1;
		if (p->l==x&&(order3(p->u,y,cy-p->fll/10)||order3(cy+p->fll/10,y,p->d))) return 1;
		if (p->r==x&&(order3(p->u,y,cy-p->frl/10)||order3(cy+p->frl/10,y,p->d))) return 1;
		if (p->u==y&&(order3(p->l,x,cx-p->ful/10)||order3(cx+p->ful/10,x,p->r))) return 1;
		if (p->d==y&&(order3(p->l,x,cx-p->fdl/10)||order3(cx+p->fdl/10,x,p->r))) return 1;
	}
	else if (p->mode==3){
		if ((p->l==x||p->r==x)&&order3(p->u,y,p->d)) return 1;
		if ((p->u==y||p->d==y)&&order3(p->l,x,p->r)) return 1;
	}
	return 0;
}
int onbd(int x,int y,obstacle*p){
	if ((x==p->l||x==p->r)&&order3(p->u,y,p->d)) return 1;
	if ((y==p->u||y==p->d)&&order3(p->l,x,p->r)) return 1;
	return 0;
}
int outbd(int x,int y,obstacle* p){
	return (x<p->l||x>p->r||y<p->u||y>p->d);
}
int direction(int x,int y){
	if (x==0){
		if (y==-1) return 0;else if (y==1) return 1;
	}
	if (y==0){
		if (x==-1) return 2;else if (x==1) return 3;
	}
	return -1;
}
int algo(character ch,int x,int y,int tox,int toy){
	if (out_of_map(tox,toy)) return 0;
	int x1=findmx(x);
	int y1=findmy(y);
	int x2=findmx(tox);
	int y2=findmy(toy);
	int d=direction(x1-x2,y1-y2);
	int blank=1,through_door=0;
	if (x!=mx[x1+1]&&y!=my[y1+1]&&tox!=mx[x2+1]&&toy!=my[y2+1]){
		if (d!=-1){
//			if (debug)printf("d!=-1\n");
			if (go[x1][y1][d][ch])
			return go[x1][y1][d][ch]-1;
		}
		else {
//			if (debug)printf("d=-1,%d %d to %d %d \n",x,y,tox,toy);
//			if (debug)printf("block %d %d to %d %d\n",x1,y1,x2,y2);
			if (x1==x2&&y1==y2) return 1;
			else return 0;
		}
	}
	else blank=0;
//	if (debug) printf("here\n");
	for (int i=0;i<o_num;i++){	
		if (onwall(tox,toy,&o[i])||onwall(x,y,&o[i])) return 0;
		if (inbd(x,y,&o[i])&&outbd(tox,toy,&o[i])||inbd(tox,toy,&o[i])&&outbd(x,y,&o[i])||onbd(tox,toy,&o[i])||onbd(x,y,&o[i])){
//			printf("inbd\n ");
			if (o[i].mode==2||o[i].mode==1) //it's stronghold
			{
//				printf("inmode\n");
				int cx=(o[i].l+o[i].r)>>1;
				int cy=(o[i].u+o[i].d)>>1;
				int accept=ch==enemy&&o[i].mode==2||(ch==you||ch==friends)&&o[i].mode==1||(ch==two);
//				printf("acc=%d\n",accept);
				if (order3(x,o[i].l,tox))
				{
//					printf("order1\n");
					if (st_order3(cy-o[i].fll/10,y,cy+o[i].fll/10)) //door
						{
							through_door=1;
							if (o[i].ll<=0||accept)
							{
							return 1;
//							printf("success\n");
							}
							else 
							{
								return 0;
//								printf("failed\n");
							}
						}
					else 
					{
						if (blank&&!through_door) go[x1][y1][d][ch]=1;
						return 0;
					}
				}
				if (order3(x,o[i].r,tox)) 
				{
					if (st_order3(cy-o[i].frl/10,y,cy+o[i].frl/10)) 
						{
							through_door=1;
							if (o[i].rl<=0||accept)
							return 1;
							else return 0;
						}
					else 
					{
						if (blank&&!through_door) go[x1][y1][d][ch]=1;
						return 0;
					}
				}
				if (order3(y,o[i].u,toy)) 
				{
					through_door=1;
					if (st_order3(cx-o[i].ful/10,x,cx+o[i].ful/10)) 
						{
							if (o[i].ul<=0||accept)
							return 1;
							else return 0;
						}
					else 
					{
						if (blank&&!through_door) go[x1][y1][d][ch]=1;
						return 0;
					}
				}
				if (order3(y,o[i].d,toy)) 
				{
//					printf("indown\n");
					through_door=1;
					if (st_order3(cx-o[i].fdl/10,x,cx+o[i].fdl/10)) 
						{
							if (o[i].dl<=0||accept)
							{
								return 1;
							}
							else return 0;
						}
					else 
					{
						if (blank&&!through_door) go[x1][y1][d][ch]=1;
						return 0;
					}
				}
			}
			else {
				return 0;
			}
		}
	}
	if (blank&&!through_door) 
	{
		go[x1][y1][d][ch]=2;
//		printf("success!/n");
//		printf("%d %d %d %d\n",x,y,tox,toy);
//		printf("%d %d %d %d\n",x1,y1,x2,y2);
	}
	return 1;
}
int findAtkDoor(character ch,int x,int y,int tox,int toy,obstacle* p){
	if (out_of_map(tox,toy)) return 0;
	int x1=findmx(x);
	int y1=findmy(y);
	int x2=findmx(tox);
	int y2=findmy(toy);
	int d=direction(x1-x2,y1-y2);
	int blank=1,through_door=0;
	if (x!=mx[x1+1]&&y!=my[y1+1]&&tox!=mx[x2+1]&&toy!=my[y2+1]){
		if (d!=-1){
			if (go[x1][y1][d][ch])
			return go[x1][y1][d][ch]-1;
		}
		else {
			if (x1==x2&&y1==y2) return 1;
			else return 0;
		}
	}
	else blank=0;
	{	
		if (onwall(tox,toy,p)||onwall(x,y,p)) return 0;
		if (inbd(x,y,p)&&outbd(tox,toy,p)||inbd(tox,toy,p)&&outbd(x,y,p)||onbd(tox,toy,p)||onbd(x,y,p)){
			if (p->mode==2||p->mode==1) //it's stronghold
			{
				int cx=(p->l+p->r)>>1;
				int cy=(p->u+p->d)>>1;
				int accept=ch==enemy&&p->mode==2||ch!=enemy&&p->mode==1;
				if (order3(x,p->l,tox))
				{
					if (st_order3(cy-p->fll/10,y,cy+p->fll/10)) //door
						{
							through_door=1;
							if (p->ll<=0||accept)
							{
							return 1;
							}
							else 
							{
								return -1;
							}
						}
					else 
					{
						return 0;
					}
				}
				if (order3(x,p->r,tox)) 
				{
					if (st_order3(cy-p->frl/10,y,cy+p->frl/10)) 
						{
							through_door=1;
							if (p->rl<=0||accept)
							return 1;
							else return -2;
						}
					else 
					{
						return 0;
					}
				}
				if (order3(y,p->u,toy)) 
				{
					through_door=1;
					if (st_order3(cx-p->ful/10,x,cx+p->ful/10)) 
						{
							if (p->ul<=0||accept)
							return 1;
							else return -3;
						}
					else 
					{
						return 0;
					}
				}
				if (order3(y,p->d,toy)) 
				{
					through_door=1;
					if (st_order3(cx-p->fdl/10,x,cx+p->fdl/10)) 
						{
							if (p->dl<=0||accept)
							{
								return 1;
							}
							else return -4;
						}
					else 
					{
						return 0;
					}
				}
			}
		}
	}
	return 1;
}
int findAtkingGate(character ch,int x,int y,int tox,int toy,obstacle*p){
	int temp;
	if (x!=tox&&y!=toy){
		int dx=tox-x;
		int dy=toy-y;
		int cm=tox*y-toy*x;
		if (tox<x) swap(&tox,&x);
		if (toy<y) swap(&toy,&y); 
		int i=findmx(x);
		int j=findmx(tox);
		if (mx[j+1]==tox) j++;
		for (int t=i;t<j;t++){
			int ty=(mx[t+1]*dy+cm)/(double)dx;
			if ((temp=findAtkDoor(ch,ctx[t],ty,ctx[t+1],ty,p))<0) {
				return temp;
			}
		}
		i=findmy(y);
		j=findmy(toy);
		if (toy==my[j+1]) j++;
		for (int t=i;t<j;t++){
			int tx=(my[t+1]*dx-cm)/(double)dy;
			if ((temp=findAtkDoor(ch,tx,cty[t],tx,cty[t+1],p))<0){
				return temp;
			}
		}
	}else if (x==tox){
		int j,k;
		if (y>toy) swap(&y,&toy);
		j=findmy(y);
		k=findmy(toy);
		if (my[k+1]==toy) k++;
		for (int t=j;t<k;t++){
			if ((temp=findAtkDoor(ch,x,cty[t],x,cty[t+1],p))<0){
				return temp;
			}
		}
	}else if (y==toy){
		int i,j;
		if (tox<x) swap(&tox,&x);
		i=findmx(x);
		j=findmx(tox);
		if (mx[j+1]==tox)j++;
		for (int t=i;t<j;t++){
			if ((temp=findAtkDoor(ch,ctx[t],y,ctx[t+1],y,p))<0){
				return temp;
			}
		}
	}
	return 0;
}
void recover(man*p,int x){
	if (p->rl>0)
	if (p->rl+x<=p->fl){
		p->rl+=x;
	}
	else p->rl=p->fl;
}
void TimerListener(int TimerID){
	if (condition==operate)
	switch (TimerID){
		case 0:
			if (people[0].rl<=0) break;
			entropy++;
			now=time(NULL);
//			printf("in TL case 0 1 \n");
			actions();
//			printf("in TL case 0 2 \n");
			draw();
//			printf("in TL case 0 3\n");
			break;
		case 1:
//			printf("in TL case 1\n");
			seconds++;
			for (int i=0;i<population;i++){
				recover(&people[i],people[i].gl);
			}
			for (int i=0;i<o_num;i++){
				if (o[i].mode==1||o[i].mode==2){
					if (o[i].ll<o[i].fll&&o[i].ll>0)o[i].ll+=1;
					if (o[i].dl<o[i].fdl&&o[i].dl>0)o[i].dl+=1;
					if (o[i].ul<o[i].ful&&o[i].ul>0)o[i].ul+=1;
					if (o[i].rl<o[i].frl&&o[i].rl>0)o[i].rl+=1;
				}
			}
//			printf("%s wp %d dis %d\n",people[25].name,people[25].weapon,atkdis(&people[25]));
//			printf("ssn=%d ec=%d\n",ssn,ssfrdb[stage],ssfrda[stage],seconds);
//			printf("ssfrd_num=%d max_ssfrd[stage]=%d\n",ssfrd_num,max_ssfrd[stage]);
//			printf("arrow_hd%d arrow_tl%d\n",ar_hd,ar_tl);
//			printf("atkdis=%d\n",atkdis(&people[0]));
//			for (int i=0;i<population;i++){
//				printf("%d %d\n",i,people[i].followed);
//			}
//			int a=16;
//			printf("\npos %d %d to %d %d\n",people[a].x,people[a].y,people[a].movetox,people[a].movetoy);
//			int tempdr;
//			debug=1;
//			int tempd=minHamDis(enemy,people[a].x,people[a].y,people[a].movetox,people[a].movetoy,&tempdr);
//			debug=0;
//			printf("tempd %d tempdr %d\n,",tempd,tempdr);
//			printf("atk %d mov %d\n",people[a].atting,people[a].moving);
//			printf("atk to %d %d\n",people[a].atktox,people[a].atktoy);
//			printf("%d\n",go[30][16][2][enemy]);
			//below is small soldier occur
			printf("\n%d\n",stage);
			printf("%d %d %d \n",ssn,ssfrd_num,sseny_num);
			int temp;
			if (ssfrdb[stage]!=0&&seconds%ssfrdb[stage]==0){
				for (int i=0;i<o_num;i++){
					if (o[i].mode==1){
						if (ssfrd_num+ssfrda[stage]<=max_ssfrd[stage]){
							temp=ssfrda[stage];
						}
						else {
							temp=max_ssfrd[stage]-ssfrd_num;
						}
						for (int k=0;k<temp;k++){
							new_s((o[i].l+o[i].r)/2,(o[i].u+o[i].d)/2,friends);
						}
						if (temp>0)ssfrd_num+=temp;
					}
				}
			}
			if (ssenyb[stage]!=0&&seconds%ssenyb[stage]==0){
				for (int i=0;i<o_num;i++){
					if (o[i].mode==2){
						if (sseny_num+ssenya[stage]<=max_sseny[stage]){
							temp=ssenya[stage];
						}
						else {
							temp=max_sseny[stage]-sseny_num;
						}
						for (int k=0;k<temp;k++){
							new_s((o[i].l+o[i].r)/2,(o[i].u+o[i].d)/2,enemy);
						}
						if (temp>0)sseny_num+=temp;
					}
				}
			}
			//small soldier occur over
			//below is stage mode 
			int filled=0;
			printf("mode_num[%d]=%d\n",stage,mode_num[stage]);
			printf("%d\n",people[0].rl);
			for (int i=0;i<mode_num[stage];i++){
				switch(mode[stage][i]){
					case 0:{
//						printf("1\n");
						for (int k=0;k<moden[stage][i];k++){
							man*p=&people[modep[stage][i][k]];
							int x=modex[stage][i][k];
							int y=modey[stage][i][k];
							int r=moder[stage][i][k];
							if (dis2(p->x,p->y,x,y)<=r*r){
								filled++;
								break;
							} 
						}
						break;
					}
					case 1:{
						printf("2\n");
						for (int k=0;k<moden[stage][i];k++){
							printf("k=%d\n",k);
							int x=modex[stage][i][k];
							printf("x=%d\n",x);
							if (people[x].rl<=0&&people[x].occur_stage>=0){
								filled++;
								break;
							}
						}
						break;
					}
					case 2:{
						for (int k=0;k<moden[stage][i];k++){
							int x=modex[stage][i][k];
							int y=modey[stage][i][k];
							if (o[x].mode==y){
								filled++;
								break;
							}
						}
						break;
					}
					case 3:{
						
						break;
					}
					case 4:{
						int at_least_one_alive=0;
						for (int k=0;k<moden[stage][i];k++){
							int x=modex[stage][i][k];
							if (people[x].rl>0){
								filled++;
								at_least_one_alive=1;
								break;
							}
						}
						if (!at_least_one_alive){
							endChapter(chapter,failed);
							return ;
						}
						break;
					}
					case 5:{
						int one_building_fit=0;
						for (int k=0;k<moden[stage][i];k++){
							int x=modex[stage][i][k];
							int y=modey[stage][i][k];
							if (o[x].mode==y){
								filled++;
								one_building_fit=1;
								break;
							}
						}
						if (!one_building_fit){
							endChapter(chapter,failed);
							return ;
						}
						break;
					}//case 5 over
				}//swith over 
			}//for over
			if (filled>=mode_num[stage]){
				newStage(stage+1);
			}
			//stage mode over
			//atk stage judge
			printf("atk stage %d total %d\n",atkst,atkstnum);
			touch_time-=reduce(seconds-lastTouch);
			if (itemFullPower) lastTouch=seconds;
			if (touch_time<0) touch_time=0;
			for (int i=0;i<atkstnum;i++){
				if (st_order3(atkstbt[i],touch_time,atkstet[i]+1)){
					if (atkst!=i){
						newAtkStage(i);
					}
				}
			}
			for (int i=0;i<ssn&&ssn>0;i++){
			if (ss[i].rl<=0||people[ss[i].amx[1]].rl<=0){
				if (ss[i].ch==enemy) {
					sseny_num--;
				}
				else if (ss[i].ch==friends) 
				{
					ssfrd_num--;				
				}
				ss[i]=ss[--ssn];
				if (people[ss[i].amx[1]].followed>0) people[ss[i].amx[1]].followed--;
			}
			}
//			printf("%d\n",people[0].rl);
			//atk stage over
			printf("hhh\n");
			break;
		case 2:{
			for (int i=0;i<itnum;){
				if (dis2(people[0].x,people[0].y,item[i].x,item[i].y)<=200){
					item_eat(i);
				}
				else {
					i++;
				}
			}
			break;
		}
		case 3:{
			EventSearch();
			break;
		}
		case 4:
		case 9:{
			double_atk=0;
			break;
		}
		case 5:
		case 8:{
			double_sp=0;
			if (atkstbt[atkstnum-1]>touch_time){
				people[0].speedup=0;
			}
			break;
		}
		case 6:
		case 10:{
			double_def=0;
			break;
		}
		case 7:itemFullPower=0;break;
	}
	if (condition==chooseChap){
		beginPaint();
		clearDevice();
		setTextColor(BLACK);
		setTextBkColor(WHITE);
		setTextSize(40);
		paintText(0,0,"you can choose from chapter 1 to ");
		int temp;
		if (CompleteChap+1>chapter_number){
			temp=chapter_number;
		}
		else {
			temp=CompleteChap+1;
		}
		paintText(0,40,val_to_string(temp));
		paintText(0,80,"完成度："); 
		for (int i=0;i<chapter_number;i++){
			char s[20]="Chapter ";
			paintText(0,120+i*80,strcat(s,val_to_string(i+1)));
			paintText(0,160+i*80,val_to_string(Completion[i]));
		}
		endPaint();
	}
	if (condition==evaluate){
		beginPaint();
		clearDevice();
		setTextColor(BLACK);
		setTextBkColor(WHITE);
		setTextSize(40);
		if (result==win) paintText(0,0,"你通过了这一章");
		else paintText(0,0,"你失败了"); 
		paintText(0,40,"kill :");
		paintText(0,80,val_to_string(kill));
		paintText(0,120,"cause damage: ");
		paintText(0,160,"I don't care this");
		paintText(0,200,"事件完成度：");
		paintText(0,240,val_to_string(completionCal()));
		paintText(0,280,"空格键继续");
		endPaint();
	}
//	printf("%d %d\n",people[0].x,people[0].y);
//	printf("%d %d %d\n",entropy,ar_hd,ar_tl);
//	printf("TL over\n");
}
void EventSearch(void){
//	printf("event num=%d\n",EventNum);
	for (int i=0;i<EventNum;i++){
		if (!EventFinish[i]){
//			printf("Event %d ctd num %d\n",i,EventCdtCodeNum[i]);
			int filled=0;
			for (int j=0;j<EventCdtCodeNum[i];j++)
			switch (EventCdtCode[i][j]){
				case 0:{
//					printf("0 x %d p %d y %d\n",EventCdtx[i][j],EventCdtp[i][j],EventCdty[i][j]);
					if (order3(0,people[EventCdtp[i][j]].occur_stage,stage)
					&&order3(EventCdtx[i][j],people[EventCdtp[i][j]].rl,EventCdty[i][j])){
						filled++;
					}
					break;
				}
				case 1:{
//					printf("1 %d %d %d\n",EventCdtx[i][j],EventCdtp[i][j],EventCdty[i][j]);
					man*p=&people[EventCdtp[i][j]];
					if (dis2(p->x,p->y,EventCdtx[i][j],EventCdty[i][j])<EventCdtr[i][j]*EventCdtr[i][j]){
						filled++;
//						printf("finished\n");
					}
					break;
				}
				case 2:{
					if (o[EventCdtp[i][j]].mode==EventCdtx[i][j]){
						filled++;
					}
					break;
				}
				case 3:{
					man *p=&people[EventCdtp[i][j]];
					man *q=&people[EventCdtx[i][j]];
					if (dis2(p->x,p->y,q->x,q->y)<EventCdtr[i][j]*EventCdtr[i][j]){
						filled++;
					}
					break;
				}
			}//cdt switch over
//			printf("filled %d\n",filled);
			if (filled==EventCdtCodeNum[i]){
				EventFinish[i]=1;
				EventBegin(i);
			}
		}
	}
}
void EventBegin(int i){
	EventFinish[i]=1;
	switch (EventCode[i]){
			case 1:{
				man *p=&people[EventItem[i].people];
				EventItem[i].x=p->x;
				EventItem[i].y=p->y;
			}
			case 0:{
				item[itnum++]=EventItem[i];
//				printf("item occur %d %d\n",item[itnum-1].x,item[itnum-1].y);
				break;
			}
			case 3:{
				people[EventPeopleIndex[i]].x=people[EventPeopleOcPp[i]].x;
				people[EventPeopleIndex[i]].y=people[EventPeopleOcPp[i]].y;
			}
			case 2:{
				people[EventPeopleIndex[i]].rl=people[EventPeopleIndex[i]].fl;
				people[EventPeopleIndex[i]].occur_stage=stage;
				printf("people[EventPeopleIndex[i]].ch=%d\n",(int)people[EventPeopleIndex[i]].ch);
				break;
			}
			case 4:{
				newMessage(EventMessage[i]);
				break;
			}
			case 5:{
				break;
			}
			case 6:{
				people[EventLifePp[i]].rl=EventLifeTo[i];
				break;
			}
			case 7:{
				o[EventBd[i]].mode=EventBdMdTo[i];
				break;
			}
		}
}
void item_eat(int x){
	switch(item[x].ic){
		case 0:{
			recover(&people[0],people[0].fl/4);
			break;
		}
		case 1:{
			recover(&people[0],people[0].fl/2);
			break;
		}
		case 2:{
			double_atk++;
			startTimer(4,10000);
			break;
		}
		case 3:{
			double_sp++;
			people[0].speedup=1;
			startTimer(5,10000);
			break;
		}
		case 4:{
			double_def++;
			startTimer(6,15000);
			break;
		}
		case 5:{
			touch_time=atkstet[atkstnum-1];
			itemFullPower=1;
			startTimer(7,5000);
			break;
		}
		case 6:{
			people[0].rl=people[0].fl;
			break;
		}
		case 7:{
			double_sp++;
			people[0].speedup=1;
			startTimer(8,30000);
			break;
		}
		case 8:{
			double_atk++;
			startTimer(9,20000);
			break;
		}
		case 9:{
			double_def++;
			startTimer(10,30000);
			break;
		}
		case 10:
		case 11:
		case 12:{
			people[0].wpr[item[x].ic-10]+=item[x].wpr;
			people[0].wpma[item[x].ic-10]=item[x].ma;
			people[0].wpmr[item[x].ic-10]=item[x].mr;
			break;
		}
	}
	newMessage(itemEatString[item[x].ic]);
	item[x]=item[--itnum];
}
int reduce(int x){
	if (itemFullPower){
		return 0;
	}
	int temp;
	if (x==10&&atkst==atkstnum-1){
		return touch_time-atkstbt[atkst-1];
	}
	if (x%30==0){
		temp=(touch_time-atkstbt[atkst])/2;
		if (temp<0) return 0;
		else return temp;
	}
	if (x%10==0){
		temp=(touch_time-atkstbt[atkst])/4;
		if (temp<0) return 0;
		else return temp;
	}
	if (x%5==0){
		if (touch_time>5) return 2;
		else return touch_time;
	}
	return 1;
}

void new_s(int x,int y,character ch){
	if (ch==friends){
		ss[ssn]=ssfrd[stage];
	}
	else {
		ss[ssn]=sseny[stage];
	}
	ss[ssn].am[0]=1;
	ss[ssn].amb[0]=ss[ssn].ame[0]=enyst_num+1;//disapear
	ss[ssn].x=x;
	ss[ssn].y=y;
	ss[ssn].amn=2;
	ss[ssn].ch=ch;
	int follow=0;
	int min=INT_MAX;
	for (int i=1;i<population;i++){
		if (people[i].ch==ch&&people[i].rl>0&&people[i].followed<min){
			follow=i;
			min=people[i].followed;
		}
	}
	people[follow].followed++;
	ss[ssn].am[1]=7;
	ss[ssn].amx[1]=follow;
	ss[ssn].amb[1]=stage;
	ss[ssn].ame[1]=20;
	int temp=rand()&3;
	ss[ssn].weapon=!temp;
	ss[ssn].wpr[ss[ssn].weapon]=INT_MAX;
	if (ss[ssn].weapon==1) ss[ssn].atkint*=2;
	ss[ssn].rl=ss[ssn].fl;
	ssn++;
	//wpma & wpmr is written in set.txt
}
void actions(void){
	for (int i=0;i<population;i++){
//		printf("act people %d\n",i);
		act(&people[i]);
//		printf("act people %d over\n",i);
		d_cal(&people[i]);
//		printf("d_cal people %d over\n",i);
	}
	for (int i=0;i<ssn;i++){
//		printf("act ss %d\n",i);
		act(&ss[i]);
//		printf("act ss over %d\n",i);
		d_cal(&ss[i]);
//		printf("d_cal ss %d over\n",i);
	}
	//small soldiers
	//action over
	//arrow move
//	printf("ar & sh move\n");
	arrow_move();	
	shell_move();
//	printf("ar & sh move over\n");
	//arrow move over
}
obstacle * nearGate(man*p){
   	return NULL;
}
void act(man*p){
	if (p->rl<=0) return;
	if ((entropy&3)==0&&p->speedup){
		p->preposx=p->x;
		p->preposy=p->y;
	}
//	printf("into act \n");
	if (p->ch!=you){
		int assigned=0;
		if (p->atting!=0) assigned=1;
//		printf("into weapon consider\n");
		weapon_consider(p);
//		printf("out of weapon consider \n into findEnemy\n");
		man*q=findEnemy(p);
//		printf("out of findEnemy\n");
		int atkdisp=atkdis(p);
//		if (q!=NULL&&canTouch(p,q)){
//			printf("into atkto\n");
//			attackto(p,q->x,q->y);
//			printf("out of atkto\n");
//		}
		point*pt=nearestAtkPt(p);
		if (pt->x!=-1||pt->y!=-1){
			attackto(p,pt->x,pt->y);
			if (p->weapon==2) 
			{
				go_random(p,p->x,p->y,3);
				assigned=1;
			}
//			assigned=1;
		}
		//if can atk then atk
		if (p->atting!=0) 
		{
			assigned=1;
			p->ltas=entropy;
		}
		else if (entropy-p->ltas>=p->act_interval)
		{
			p->ltas=entropy;
			int temp;
			if (!assigned&&(temp=UnfinishedAtkPtMode(p))!=-1){
				p->moving=1;
				p->movetox=p->amx[temp];
				p->movetoy=p->amy[temp];
				assigned=1;
			}
			for (int i=0;i<p->amn&&assigned==0;i++)
				if (order3(p->amb[i],stage,p->ame[i]))
					switch(p->am[i]){
						case 0:{//protect a point
//							printf("1\n");
							man*temp;
							if (safeinbd(p)){
								go_random(p,p->x,p->y,3);
//								printf("2\n");
							}
							else if (temp=danger(p->amx[i],p->amy[i],p->ch)){
								go_random(p,temp->x,temp->y,atkdisp);
							}
							else if (q!=NULL&&dis2(q->x,q->y,p->x,p->y)<maxatkdis2(p)&&canTouch(p,q)){
									go_random(p,q->x,q->y,atkdisp+q->r);
									assigned=1;
//									printf("3\n");
							}//atk someone in root(2) max atkdis
							else if (dis2(p->amx[i],p->amy[i],p->x,p->y)>90000){
										go_random(p,p->amx[i],p->amy[i],300);
										assigned=1;
//										printf("4\n");
									}//if free go to the protect place
//							printf("5\n");
							break;
						}
						case 1:
							p->rl=0;
							break;
						case 2://attack people
								{
//									printf("mode2\n");
								int secdis=INT_MAX;
								man*q,*tempp=NULL;
								for (int j=0;j<p->amatkn[i];j++){
									q=&people[p->amatk[i][j]];
									if (q->rl<=0) continue;
									if ((dis2(q->x,q->y,p->x,p->y)<secdis)){
										tempp=q;
										secdis=dis2(q->x,q->y,p->x,p->y);
									}
								}
								if (tempp==NULL) break;
//								printf("%s %d %d go random to %d %d\n",p->name,p->x,p->y,tempp->x,tempp->y);
								go_random(p,tempp->x,tempp->y,atkdis(p)+tempp->r);
//								printf("atting %d moving %d to x %d y %d\n",p->atting,p->moving,p->movetox,p->movetoy);
								assigned=1;
//								printf("out of mode 2\n");
								}//atk targetas at any condition
							break;
						case 3://attack one place 
						{
							break;
						}
						case 4:
							break;
						case 7:{
							man *tempq=&people[p->amx[i]];
							q=findEnemy(tempq);
							if (tempq->rl>0&&dis2(tempq->x,tempq->y,p->x,p->y)>160000){
								go_random(p,tempq->x,tempq->y,30);
								assigned=1;
							}
							else if (q!=NULL&&dis2(q->x,q->y,tempq->x,tempq->y)<maxatkdis2(p)/4){
									go_random(p,q->x,q->y,atkdisp+q->r);
									assigned=1;
							}//atk someone in half max atkdis
//							else {
//								q=&people[p->amx[i]];
//								if (q!=NULL&&q->rl>0&&dis2(q->x,q->y,p->x,p->y)>900){
//									go_random(p,q->x,q->y,30);
//										assigned=1;
//								}//if free follow
//							}
							break;
						}//follow
					}
//			if (assigned==0||!canGoAround(p,p->movetox,p->movetoy)){
//				pt=nearestAtkDr(p);
//				if (pt->x!=1||pt->y!=1){
//					p->moving=1;
//					p->movetox=pt->x;
//					p->movetoy=pt->y;
//				}
//			}
//			if (assigned==0){
////				printf("6\n");
//				if (q!=NULL&&q->rl>0){ 
//					int temp;
////					printf("7\n");
//					if ((temp=dis2(p->x,p->y,q->x,q->y))<(atkdis(p)+q->r)*(atkdis(p)+q->r))
//						attackto(p,q->x,q->y);
////					printf("8\n");
//						if (!safeinbd(p)||p->wpr[1]<=0) 
//						{
////							printf("11\n");
//							go_random(p,q->x,q->y,atkdis(p)+q->r);
//						}
//						else if (safeinbd(p)) {
//							go_random(p,p->x,p->y,10);
////							printf("10\n");
//						}
//						else if (q=danger(p->x,p->y,p->ch)){
////							printf("9 \n");
//							go_random(p,q->x,q->y,atkdis(p));
//						}
//						else if (p->moving==0&&(entropy&7<2)){
////							printf("10\n");
//							go_random(p,p->x,p->y,100);
//						}
//				}
//			}//end if assigned==0
		}// end if can assign
	}
//	printf("13\n");
	if (p->atting==0){
//		printf("14\n");
		if (p->ch!=you&&p->moving==0) go_random(p,p->x,p->y,20);
		move(p);
//		printf("19\n");
	}
	if (p->atting){
		if (p->weapon==0){
			if (p->atting>=p->atkpfn[p->attpat])
			{
				p->atting=0;
				p->attlt=entropy;
			}
			else p->atting++;
		}
		else if (p->weapon==1){
			if (p->atting==1){
//				printf("15\n");
				new_arrow(p);
//				printf("16\n");
				p->wpr[1]--;
				if (p->wpr[1]<=0) next_weapon(p);
				}
//				printf("17\n");
				p->atting=0;
				p->attlt=entropy;
		}
		else if (p->weapon==2){
			if (p->atting==1){
				new_shell(p);
				p->wpr[2]--;
				if (p->wpr[2]<=0) next_weapon(p);
				p->atting=0;
				p->attlt=entropy;
			}
		}
	}
//	printf("out of act\n");
}
int UnfinishedAtkPtMode(man *p){
	int mind=INT_MAX;
	int mini=-1;
	for (int i=0;i<p->amn;i++)
	if (p->am[i]==3){
//		printf("into finishAtkPt %s %d\n",p->name,i);
		if (!finishAtkPtMode(p,i)&&dis2(p->amx[i],p->amy[i],p->x,p->y)<mind){
			mind=dis2(p->amx[i],p->amy[i],p->x,p->y);
			mini=i;
		}
	}
	return mini;
}
void new_shell(man*q){
	single_shell*p=&shell[sh_tl];
		if (maninsamesidebd(q)){
			p->through_wall=1;
		}
		else {
			p->through_wall=0;
		}
//		printf("new_shell\n");
		p->atk=atk(q);
		p->restd=atkdis(q);
		p->fulld=atkdis(q);
		p->angle=vector_angle(q->atktox-q->x,q->atktoy-q->y);
		p->sp=q->lda_sp;
//		printf("atk %d restd %d fulld%d angle %f sp %d\n",p->atk,p->restd,p->fulld,p->angle,p->sp);
		p->x=p->stx=q->x+q->r*cos(p->angle);
		p->y=p->sty=q->y+q->r*sin(p->angle);
		p->cdt=flying;
		p->ch=q->ch;
		p->people=q;
		if (sh_tl==max_sh_num) sh_tl=0;
		else sh_tl++;
}
int atk(man*p){
	int base=p->atk+p->wpma[p->weapon];
	if (p->atting){
		base+=p->atkma[p->attpat];
	}
	if (double_atk&&p==&people[0]){
		return base*2;
	}
	else {
		return base;
	}
	return base;
}
int spd(man*p){
	if (double_sp&&p==&people[0])return p->sp*2;
	else return p->sp;
}
int def(man*p){
	if (double_def&&p==&people[0])return p->def*2;
	else return p->def;
}
int finishAtkPtMode(man *p,int i){
	if (p==NULL||p->rl<=0) return 0;
			int tox=p->amx[i];
			int toy=p->amy[i];
//			printf("%s to %d %d of %s\n",p->name,tox,toy,o[p->amatko[i]].name);
			if (!samesidemanbuilding(p,&o[p->amatko[i]]))
			if (tox==o[p->amatko[i]].l&&o[p->amatko[i]].ll<=0) return 1;
			else if (tox==o[p->amatko[i]].r&&o[p->amatko[i]].rl<=0) return 1;
			else if (toy==o[p->amatko[i]].u&&o[p->amatko[i]].ul<=0) return 1;
			else if (toy==o[p->amatko[i]].d&&o[p->amatko[i]].dl<=0) return 1;
			else 
			return 0;
	return 1;
}
void go_random(man*p,int tox,int toy,int radius){
	if (radius<=0){
		p->movetox=tox;
		p->movetoy=toy;
	}
	else 
	{
		int temp2=rand()%360;
		int r=rand()%radius;
		p->movetox=tox+r*cos(temp2*pi/180);
		p->movetoy=toy+r*sin(temp2*pi/180);
	}
	p->moving=1;
}

int samesidemanbuilding(man*p,obstacle*x){
	if ((p->ch==you||p->ch==friends)&&x->mode!=2) return 1;
	if (p->ch==enemy&&x->mode!=1) return 1;
	return 0;
}
int four(obstacle *b){
	return (b->ul>0&&b->dl>0&&b->ll>0&&b->rl>0);
}
int safeinbd(man *p){
	for (int i=0;i<o_num;i++){
		if (inbd(p->x,p->y,&o[i])&&samesidemanbuilding(p,&o[i])&&four(&o[i])){
			return 1;
		}
	}	
	return 0;
}
void weapon_consider(man*p){
	if (p->atting||p->rl<=0) return;
	for (int i=0;i<o_num;i++){
		if (inbd(p->x,p->y,&o[i])){
			if (p->weapon==0&&samesidemanbuilding(p,&o[i])&&four(&o[i])){
				if (p->wpr[1]>0){
					p->weapon=1;
				}
			}
			return;
		}
	}//use arrow in bd
	int temp=p->weapon;
	if (p->wpr[0]>0&&p->weapon!=0){
		p->weapon=0;
		point *q=nearestAtkPt(p);
		if (q->x!=-1||q->y!=-1) return;
	}
	if (p->wpr[1]>0&&p->weapon!=1){
		p->weapon=1;
		point *q=nearestAtkPt(p);
		if (q->x!=-1||q->y!=-1)return ;
	}
	p->weapon=temp;
} 

int atkdis(man*p){
	int dis=p->wpmr[p->weapon];
	if (p->atting) dis+=p->atkmr[p->attpat];
	if (p->weapon==1) return dis+p->lda_r;
	if (p->weapon==0) return p->atk_r+dis;
	if (p->weapon==2) {
//		printf("%s atkdis %d \n",p->name,dis+p->lda_r);
		return dis+p->lda_r;
	}
	return dis;
}
void next_weapon(man *p){
	int x=0;
	if (p->atting==0)
	do{
		x++;
		p->weapon=p->weapon==wp_number-1?0:p->weapon+1;
	}while (p->wpr[p->weapon]<=0&&x<=wp_number);
//	if (p->weapon==2)printf("%d %d\n",p->weapon,p->wpr[p->weapon]);
}
void arrow_move(void){
	for (int i=ar_hd;i!=ar_tl;i=(i==max_ar_num?0:i+1)){
		if (arrow[i].cdt==flying){
			int tox=arrow[i].stx+(arrow[i].fulld-arrow[i].restd)*cos(arrow[i].angle);
			int toy=arrow[i].sty+(arrow[i].fulld-arrow[i].restd)*sin(arrow[i].angle);
			if (!arrow[i].through_wall&&!nocrossing(arrow[i].ch,tox,toy,arrow[i].x,arrow[i].y)){
				arrow[i].cdt=stop;
				return ;
			}
			for (int j=0;j<population;j++){
				if (oppo_ch(arrow[i].ch,people[j].ch)&&people[j].rl>0){
					if (incircle(arrow[i].x,arrow[i].y,people[j].x,people[j].y,people[j].r)
					||incircle(tox,toy,people[j].x,people[j].y,people[j].r)
					||incircle((tox+arrow[i].x)/2,(toy+arrow[i].y)/2,people[j].x,people[j].y,people[j].r)){
						arrow[i].cdt=stop;
						arrow_attack(arrow[i].people,arrow[i].atk,&people[j],0);
					}
				}
			}
			for (int j=0;j<ssn;j++){
				if (oppo_ch(arrow[i].ch,ss[j].ch)&&ss[j].rl>0){
					if (incircle(arrow[i].x,arrow[i].y,ss[j].x,ss[j].y,ss[j].r)
					||incircle(tox,toy,ss[j].x,ss[j].y,ss[j].r)
					||incircle((tox+arrow[i].x)/2,(toy+arrow[i].y)/2,ss[j].x,ss[j].y,ss[j].r)){
						arrow[i].cdt=stop;
						arrow_attack(arrow[i].people,arrow[i].atk,&ss[j],1);
					}
				}
			}
			arrow[i].x=tox;
			arrow[i].y=toy;
			arrow[i].restd-=arrow[i].sp;
			if (arrow[i].restd<=0) {
				arrow[i].cdt=stop;
			}
		}
	}
	while (arrow[ar_hd].cdt==stop&&ar_hd!=ar_tl){
		ar_hd=(ar_hd==max_ar_num?0:ar_hd+1);
	}
}
void shell_move(void){
	for (int i=sh_hd;i!=sh_tl;i=(i==max_sh_num?0:i+1)){
		if (shell[i].cdt==flying){
			int tox=shell[i].stx+(shell[i].fulld-shell[i].restd)*cos(shell[i].angle);
			int toy=shell[i].sty+(shell[i].fulld-shell[i].restd)*sin(shell[i].angle);
//			printf("%d %d tox=%d toy=%d\n",shell[i].stx,shell[i].sty,tox,toy);
			for (int j=0;j<o_num;j++){
//				printf("%d\n",j);
				if (!samesidemanbuilding(shell[i].people,&o[j])){
//					printf("%s\n",shell[i].people->name);
					int tt;
					if ((tt=findAtkDoor(shell[i].ch,shell[i].x,shell[i].y,tox,toy,&o[j]))<0){
//						printf("cause damage\n");
						bdDamage(&o[j],tt,shell[i].atk);
						shell[i].cdt=stop;
			    	}
				}
			}
//			printf("eee\n");
			if (!shell[i].through_wall&&!nocrossing(shell[i].ch,tox,toy,shell[i].x,shell[i].y)){
				shell[i].cdt=stop;
				return ;
			}
			for (int j=0;j<population;j++){
				if (oppo_ch(shell[i].ch,people[j].ch)&&people[j].rl>0){
					if (dis2(people[j].x,people[j].y,tox,toy)<(shell_radius+people[j].r)*(shell_radius+people[j].r)){
						shell[i].cdt=stop;
						shell_attack(shell[i].people,shell[i].atk/build_shell,&people[j],0);
					}
				}
			}
			for (int j=0;j<ssn;j++){
				if (oppo_ch(shell[i].ch,ss[j].ch)&&ss[j].rl>0){
					if (dis2(ss[j].x,ss[j].y,tox,toy)<(shell_radius+ss[j].r)*(shell_radius+ss[j].r)){
						shell[i].cdt=stop;
						shell_attack(shell[i].people,shell[i].atk,&ss[j],1);
					}
				}
			}
			shell[i].x=tox;
			shell[i].y=toy;
			shell[i].restd-=shell[i].sp;
			if (shell[i].restd<=0) {
				shell[i].cdt=stop;
			}
		}
	}
//	printf("xxx\n");
	while (shell[sh_hd].cdt==stop&&sh_hd!=sh_tl){
		sh_hd=(sh_hd==max_sh_num?0:sh_hd+1);
	}
//	printf("lll\n");
}
void arrow_attack(man*p,int atk,man*q,int qss){
	int dmg=atk-def(q);
	if (dmg<=0) dmg=1+(entropy&1);
	if (q->rl<=dmg){
		q->rl=0;
		pkillq(p,q,qss);
	}
	else {
		q->rl-=dmg;
		if (p->wpma[p->weapon]==-1){
			back(p,q,20);
		}
	}
}
void shell_attack(man*p,int atk,man*q,int qss){
	int dmg=atk-def(q);
	if (dmg<=0) dmg=1+(entropy&1);
	if (q->rl<=dmg){
		q->rl=0;
		pkillq(p,q,qss);
	}
	else {
		q->rl-=dmg;
	}
}
void getDamage(man*p,int x){
	if (p->rl<=x){
		p->rl=0;
	}
	else p->rl-=x;
}
void draw(void){
//		left_bound=people[0].x-window_width/2;
//		up_bound=people[0].y-window_height/2;
//	printf("draw begin\n");
	if (left_bound<0) left_bound=0;
	if (up_bound<0) up_bound=0;
	if (left_bound+window_width>map_width) 
		left_bound=map_width-window_width;
	if (up_bound+window_height>map_height) 
		up_bound=map_height-window_height;
	right_bound=left_bound+window_width;
	down_bound=up_bound+window_height;
	beginPaint();
//	printf("beginPaint\n");
	clearDevice();
	draw_obstacle();
	draw_small_soldier();
//	printf("456\n");
	draw_enemy();
//	printf("123\n");
	draw_friend();
//	printf("abc\n");
	draw_man(&people[0],&mycolor);
//	printf("def\n");
	draw_arrow();
	draw_shell();
//	draw_block();
    draw_item();
//	printf("before draw life\n");
	draw_life();
//	printf("c\n");
	draw_condition_block();
//	printf("after /draw cdt blk\n");
	endPaint();
//	printf("789\n");
}
void draw_item(void){
	setPenWidth(2);
	for (int i=0;i<itnum;i++){
		int c=item[i].ic;
		if (c<5){
			setBrushColor(MAGENTA);
			setPenColor(MAGENTA);
		}
		else if (order3(5,c,9)){
			setPenColor(RGB(255,215,0));
			setBrushColor(RGB(255,215,0));
		}
		else if (order3(10,c,12)){
			setBrushColor(GREEN);setPenColor(GREEN);
		}
		_rectangle(item[i].x-10,item[i].y-10,item[i].x+10,item[i].y+10);
	}
}
void _rectangle(int x,int y,int tox,int toy){
	rectangle(x-left_bound,y-up_bound,tox-left_bound,toy-up_bound);
}
void draw_small_soldier(void){
	for (int i=0;i<ssn;i++){
		if (ss[i].rl>0){
			if (ss[i].ch==friends)
			{
				draw_man(&ss[i],&frdcolor);
			}
			else if (ss[i].ch==enemy){
				draw_man(&ss[i],&enycolor);
			}
		}
	}
}
void draw_life(void){
	setPenColor(BLACK);
//	printf("draw life 1\n");
	for (int i=0;i<population;i++){
		if (people[i].rl>0){
			if (people[i].ch==enemy) {
				setBrushColor(RED);
			}
			else setBrushColor(GREEN);
			draw_life_bar(people[i].x,people[i].y-people[i].r-10,people[i].rl,people[i].fl,people[i].name);
		}
	}
	for (int i=0;i<ssn;i++){
		if (ss[i].rl>0){
			if (ss[i].ch==enemy){
				setBrushColor(RED);
			}
			else setBrushColor(GREEN);
			draw_life_bar(ss[i].x,ss[i].y-ss[i].r-10,ss[i].rl,ss[i].fl,ss[i].name);
		}
	}
	for (int i=0;i<o_num;i++){
		if (o[i].mode<=2){
			if (o[i].mode==1) setBrushColor(GREEN);
			else setBrushColor(RED);
			draw_life_bar((o[i].l+o[i].r)/2,o[i].u+10,o[i].ul,o[i].ful,val_to_string(o[i].ul));
			draw_life_bar((o[i].l+o[i].r)/2,o[i].d-20,o[i].dl,o[i].fdl,val_to_string(o[i].dl));
			draw_life_bar(o[i].l,(o[i].u+o[i].d)/2,o[i].ll,o[i].fll,val_to_string(o[i].ll));
			draw_life_bar(o[i].r,(o[i].d+o[i].u)/2,o[i].rl,o[i].frl,val_to_string(o[i].rl));
		}
	}
//	printf("draw life 2\n");
}
void draw_arrow(void){
	int x,y;
	for (int i=ar_hd;i!=ar_tl;i=(i==max_ar_num?0:i+1)){
		if (arrow[i].cdt==flying){
			x=arrow[i].x-left_bound;
			y=arrow[i].y-up_bound;
			if (x<0||x>window_width||y<0||y>window_height) continue;
			setPenWidth(2);
			if (arrow[i].people->wpma[1]==-1){
				setPenWidth(10);
			}
			if (arrow[i].ch==enemy)setPenColor(RED);
			else if (arrow[i].ch==friends)setPenColor(BLUE);
			else if (arrow[i].ch==you)setPenColor(GREEN);
//			printf("%d %d %d %f\n",i,x,y,arrow[i].angle);
			line(x,y,x+arr_length*cos(arrow[i].angle),y+arr_length*sin(arrow[i].angle));
		}
	}
}
void draw_shell(void){
	int x,y;
	for (int i=sh_hd;i!=sh_tl;i=(i==max_sh_num?0:i+1)){
		if (shell[i].cdt==flying){
			x=shell[i].x-left_bound;
			y=shell[i].y-up_bound;
			if (x<0||x>window_width||y<0||y>window_height) continue;
			setPenWidth(2);
			setBrushColor(BLACK);
			ellipse(x-shell_radius,y-shell_radius,x+shell_radius,y+shell_radius);
		}
	}
}
double vector_angle(int x,int y){
	if (x==0&&y==0) {	
						return 0;
					}
	if (x==0) 
	{
		return (y>0?pi/2:-pi/2);
	}
	double angle=atan(y/(double)x);
	{	
		return (x>0?angle:angle+pi);
	}
}
void draw_set_man(mds*c){
	setPenColor(c->pc);
	setBrushColor(c->bc);
	setTextColor(c->tc);
	setTextSize(c->ts);
	setTextBkColor(c->tbkc);
	setPenWidth(c->pw);
}
void draw_man(man*p,mds *c)
{
	if (p->rl<=0) return;
	int r=p->r;
	int x=p->x;
	int y=p->y;
//	printf("draw man 1 %s\n",p->name);
//	printf("draw man 2 %s\n",p->name);
	if (x+r<left_bound||x-r>right_bound||y-r>down_bound||y+r<up_bound) return;
			if (p->backing||p->speedup){
		ACL_Color cl;
		if (p->ch==enemy) cl=RGB(252,192,203);
		else if (p->ch==friends) cl=RGB(135,206,250);
		if (p->ch==you) cl=CYAN;
		setPenColor(cl);
		setBrushColor(cl);
		int x=p->preposx;
		int y=p->preposy;
		int r=p->r;
		setPenWidth(1);
		_ellipse(x-r,y-r,x+r,y+r);
		setPenWidth(r<<1);
		_line(x,y,p->x,p->y);
		if (p->backing&&((entropy&3)==0)) p->backing=0;
	}
	draw_set_man(c);
	_ellipse(x-r,y-r,x+r,y+r);
//	printf("draw man 3 %s\n",p->name);
//	if (p->ch!=you) {
//		_putImageTransparent(&p->face,x-p->r,y-p->r,2*p->r,2*p->r,WHITE);
//	}
//	else if (p->ch==you){
//		_putImageTransparent(&AtkStImage[atkst],x-p->r,y-p->r,2*p->r,2*p->r,WHITE);
//		if ((p->weapon==1||p->weapon==2)&&entropy-p->attlt<=60){
////			paintText(x-p->r/2-left_bound,y-p->r/2-up_bound,val_to_string(p->wpr[p->weapon]/(3-p->weapon)));
////		}
////		else if (p->weapon>=0&&p->weapon<wp_number&&p->wpr[p->weapon]>0)
////		{
////			paintText(x-p->r/2-left_bound,y-p->r/2-up_bound,wp_name[p->weapon]);	
////		}
//	}
//	else {
//		if ((p->weapon==1||p->weapon==2)&&entropy-p->attlt<=60){
//			paintText(x-p->r/2-left_bound,y-p->r/2-up_bound,val_to_string(p->wpr[p->weapon]/(3-p->weapon)));
//		}
//		else if (p->weapon>=0&&p->weapon<wp_number&&p->wpr[p->weapon]>0)
//		{
//			paintText(x-p->r/2-left_bound,y-p->r/2-up_bound,wp_name[p->weapon]);	
//		}
//	}
	//draw attack
	if (p->atting){
		if (p->weapon==0){
			int pat=p->atkp[p->attpat];
			switch (p->ch){
				case you:setPenColor(GREEN);
					break;
				case friends:setPenColor(BLUE);
					break;
				case enemy:setPenColor(RED);
					break;
			}
			switch(pat){
				case 0: {
//						printf("into case 0\n");
						double a1=vector_angle(p->atktox-x,p->atktoy-y);
						a1+=pi/180*p->atkag[p->attpat]*(0.5-(p->atting-1)/(double)(p->atkpfn[p->attpat]-1));
						int tox=x+cos(a1)*atkdis(p);
						int toy=y+sin(a1)*atkdis(p);
						setPenWidth(10);
						line(x-left_bound,y-up_bound,tox-left_bound,toy-up_bound);
						}
//						printf("out of case 0\n");
						break;
				case 1:{
//						printf("into case 1\n");
						double a1=vector_angle(p->atktox-x,p->atktoy-y);
						a1-=pi/180*p->atkag[p->attpat]*(0.5-(p->atting-1)/(double)(p->atkpfn[p->attpat]-1));
						int tox=x+cos(a1)*atkdis(p);
						int toy=y+sin(a1)*atkdis(p);
						setPenWidth(10);
						line(x-left_bound,y-up_bound,tox-left_bound,toy-up_bound);}
//						printf("out of case 1\n");
						break;
				case 2:{int tl=atkdis(p)-p->r;
						double a1=vector_angle(p->atktox-x,p->atktoy-y);
						int len=r+tl/(double)p->atkpfn[p->attpat]*p->atting;
						int tox=x+cos(a1)*len;
						int toy=y+sin(a1)*len;	
						setPenWidth(10);
						line(x-left_bound,y-up_bound,tox-left_bound,toy-up_bound);
						x=tox+cos(a1+5*pi/6)*20;
						y=toy+sin(a1+5*pi/6)*20;
						line(tox-left_bound,toy-up_bound,x-left_bound,y-up_bound);
						x=tox+cos(a1-5*pi/6)*20;
						y=toy+sin(a1-5*pi/6)*20;
						line(tox-left_bound,toy-up_bound,x-left_bound,y-up_bound);
					break;//0.5 yuan special effect 
				}
				case 3:{double a1=vector_angle(p->atktox-x,p->atktoy-y);
						a1-=2*pi*(0.5-(p->atting-1)/(double)(p->atkpfn[p->attpat]-1));
						int tox=x+cos(a1)*atkdis(p);
						int toy=y+sin(a1)*atkdis(p);
						setPenWidth(10);
						line(x-left_bound,y-up_bound,tox-left_bound,toy-up_bound);
					break;
				}
				} //end switch
		}//short distance attack draw over
		else if (p->weapon==1){//draw bow/ache 
//			int dx=p->atktox-p->x;
//			int dy=p->atktoy-p->y;
//			if (dx<=0&&dy<=0) {
//				int left=p->x-p->r-left_bound;
//				int right=left+p->r<<1;
//				int up=p->y-p->r-30-up_bound;
//				int down=up+2*p->r+60;
//				setPenWidth(10);
//				arc(left,up,right,down,p->x-left_bound,up,left,p->y-up_bound);
//		}
				}
	}
}
void _ellipse(int x,int y,int x2,int y2){
	ellipse(x-left_bound,y-up_bound,x2-left_bound,y2-up_bound);
}
void _putImageTransparent(ACL_Image *p,int x,int y,int wid,int hei,ACL_Color color){
	putImageTransparent(p,x-left_bound,y-up_bound,wid,hei,color);
}
void draw_block(void){
	setPenWidth(2);
	setPenColor(BLACK);
	for (int i=0;i<hor;i++)
	{
		_line(0,my[i],map_width,my[i]);
		}	
	for (int i=0;i<ver;i++)
	{
		_line(mx[i],0,mx[i],map_height);
		}
//	setPenColor(RED);
//	for (int i=0;i<hor;i++){
//		_line(0,cty[i],map_width,cty[i]);
//	}
//	for (int i=0;i<ver;i++){
//		_line(ctx[i],0,ctx[i],map_height);
//	}
	for (int i=0;i<ver-1;i++){
		for (int j=0;j<hor-1;j++){
			if (nearDoor[i][j])
			for (int d=0;d<4;d++)
			if (i+_dx[d]>=0&&i+_dx[d]<ver-1&&j+_dy[d]>=0&&j+_dy[d]<hor-1){
				if (hasDoor[i][j][d][friends]){
					setPenColor(BLUE);
					_line(ctx[i],cty[j],ctx[i+_dx[d]],cty[j+_dy[d]]);
//					printf("%d %d to %d %d friend door\n",i,j,i+_dx[d],j+_dy[d]);
				}
				else if (hasDoor[i][j][d][enemy]){
					setPenColor(RED);
					_line(ctx[i],cty[j],ctx[i+_dx[d]],cty[j+_dy[d]]);
//					printf("%d %d to %d %d eny door\n",i,j,i+_dx[d],j+_dy[d]);
				}
				else{
//					printf("line %d  %d to %d %d\n",ctx[i],cty[j],ctx[i+_dx[d]],cty[j+_dy[d]]);
					setPenColor(GREEN);
					_line(ctx[i]+3,cty[j]+3,ctx[i+_dx[d]]+3,cty[j+_dy[d]]+3);						
				}
//				printf("i %d j %d ctx %d cty %d d %d neardoor\n",i,j,ctx[i],cty[j],d);
//				for (int cc=0;cc<4;cc++){
//							printf("hasDoor[%d][%d][%d][%d]=%d\n",i,j,d,cc,hasDoor[i][j][d][cc]); 
//					}
			}
		}
	}
}
void draw_obstacle(void)
{
	for (int i=0;i<o_num;i++)
	{
		setPenWidth(10);
		setPenColor(BLACK);
		if (o[i].mode<=2){
			_line((o[i].l+o[i].r)/2-o[i].ful/10,o[i].u,(o[i].l+o[i].r)/2+o[i].ful/10,o[i].u);
			_line((o[i].l+o[i].r)/2-o[i].fdl/10,o[i].d,(o[i].l+o[i].r)/2+o[i].fdl/10,o[i].d);
			_line(o[i].l,(o[i].u+o[i].d)/2-o[i].fll/10,o[i].l,(o[i].d+o[i].u)/2+o[i].fll/10);
			_line(o[i].r,(o[i].u+o[i].d)/2-o[i].frl/10,o[i].r,(o[i].d+o[i].u)/2+o[i].frl/10);
		}
		setPenWidth(2);
		setBrushColor(RGB(o[i].R,o[i].G,o[i].B));
		rectangle(o[i].l-left_bound,o[i].u-up_bound,o[i].r-left_bound,o[i].d-up_bound);
		setTextBkColor(RGB(o[i].R,o[i].G,o[i].B));
		setTextSize(30);
		paintText(o[i].l-left_bound,o[i].u-up_bound,o[i].name);
	}
}
void _line(int x,int y,int tox,int toy){
	line(x-left_bound,y-up_bound,tox-left_bound,toy-up_bound);
}
void draw_friend(void){
	for (int i=0;i<population;i++){
		if (people[i].ch==friends)
		draw_man(&people[i],&frdcolor);
	}
}
void draw_enemy(void){
	for (int i=0;i<population;i++){
		if (people[i].ch==enemy)
		draw_man(&people[i],&enycolor);
	}
}
void draw_life_bar(int x,int y,int rest_life,int full_life,char *s){
	if (full_life==0) return;
	if (rest_life>full_life) rest_life=full_life;
	if (rest_life<=0) return;
	int length=30+(full_life-100)/20;
	if (length>300){
		length=300;
	}
	int left=x-length/2-left_bound;
	if (left>=0&&left<=window_width&&y>=up_bound&&y<=down_bound)
	{
		setTextSize(20);
		setPenWidth(2);
		setTextColor(BLACK);
		setTextBkColor(WHITE);
		paintText(left+10,y-up_bound-30,s);
		rectangle(left,y-up_bound,x+(rest_life/(double)full_life-0.5)*length-left_bound,y+5-up_bound);
	}
}
void draw_life_bar2(int x,int y,int rest_life,int full_life,char *s){
	if (full_life==0) return;
	if (rest_life>full_life) rest_life=full_life;
	if (rest_life<=0) return;
	int len=strlen(s);
	int length=80;
	int left=x-length/2;
	if (left<=0) left=0;
	else if (left+length>=window_width) left=window_width-length;
	if (left+len*10>=window_width) left=window_width-len*10;
	paintText(left,y,s);
	rectangle(left,y+15,left+rest_life/(double)full_life*length,y+20);
}
int out_of_screen(int x,int y){
	return (x<left_bound||x>right_bound||y<up_bound||y>down_bound);
}
void draw_condition_block(void){
	if (people[0].rl<=0||people[0].fl<=0) return;
	setBrushColor(WHITE);
	if (people[0].fl/people[0].rl>10&&(seconds&1==1))setPenColor(RED);
	else setPenColor(BLACK);
	setPenWidth(2);
	rectangle(0,window_height,window_width,window_height+add_height);
	setTextBkColor(WHITE);
	setTextColor(BLACK);
	setTextSize(30);
	//time
	paintText(window_width-200,window_height+20,val_to_string(now-start));
	rectangle(0,window_height,add_height,window_height+add_height);
	//small map
	double sw=add_height/(double) map_width;
	double sh=add_height/(double) map_height;
	int left=left_bound*sw;
	int up=up_bound*sh;
	int right=right_bound*sw;
	int down=down_bound*sh;
	int x,y,r;
	for (int i=0;i<o_num;i++){
		up=o[i].u*sh;
		left=o[i].l*sw;
		right=(o[i].r)*sw;
		down=o[i].d*sh;
		setBrushColor(RGB(o[i].R,o[i].G,o[i].B));
		rectangle(left,window_height+up,right,window_height+down);
	}
	for (int i=0;i<population;i++){
		if (people[i].rl>0){
			if (people[i].ch==enemy){
				setPenColor(RED);
				setBrushColor(RED);
			}
			else if (people[i].ch==friends){
				setPenColor(BLUE);
				setBrushColor(BLUE);
			}
			else if (people[i].ch==you){
				setPenColor(GREEN);
				setBrushColor(GREEN);
			}
			x=people[i].x*sw;
			y=people[i].y*sh;
			r=people[i].r*sw;
			if (r<=1) r=2;
			if (r>5) r=5;
			ellipse(x-r,window_height+y-r,x+r,window_height+y+r);	
		}
	}
	int x1=left_bound*sw;
	int y1=up_bound*sh+window_height;
	int x2=right_bound*sw;
	int y2=down_bound*sh+window_height;
	setPenColor(BLACK);
	line(x1,y1,x1,y2);
	line(x1,y1,x2,y1);
	line(x2,y1,x2,y2);
	line(x1,y2,x2,y2);
	//pos
//	paintText(add_height+20,window_height+20,val_to_string(people[0].x));
//	paintText(add_height+20,window_height+60,val_to_string(people[0].y));
	//player condition
//	printf("%s \n",strcat(atkstring,val_to_string(people[0].atk)));
//	printf("%s \n",strcat(defstring,val_to_string(people[0].def)));
	char s1[20]="atk:";
	char s2[20]="def:";
	char s3[20]="spd:";
	paintText(add_height+20,window_height+20,strcat(s1,val_to_string(atk(&people[0]))));
	paintText(add_height+20,window_height+60,strcat(s2,val_to_string(def(&people[0]))));
	paintText(add_height+20,window_height+100,strcat(s3,val_to_string(spd(&people[0]))));
	//power bank
	x1=0;
	x2=window_width;
	y1=window_height-20;
	y2=window_height-10;
//	printf("draw cdt blk 1\n");
	double rat=window_width/(double)atkstet[atkstnum-2];
//	printf("draw cdt blk 2\n");
	setBrushColor(RGB(128,128,128));
	x2=touch_time*rat;
	setBrushColor(YELLOW);
//	printf("draw cdt blk 2\n");
	if (touch_time>atkstet[atkstnum-2]&&((entropy&7)<=2))
	setBrushColor(RED);
	rectangle(x1,y1,x2,y2);
	setPenColor(BLACK);
	for (int i=0;i<atkstnum-1;i++)
	{
		line(atkstet[i]*rat,y1,rat*atkstet[i],y2);
	}
//		printf("draw cdt blk 6\n");
	y1+=10;y2+=10;
	rat=window_width/(double)people[0].fl;
	x2=people[0].rl*rat;
	setBrushColor(RGB(0,255,255));
	rectangle(x1,y1,x2,y2);
	//draw people life bar on screen
	int cx=(left_bound+right_bound)>>1;
	int cy=(up_bound+down_bound)>>1;
	int hsw=(right_bound-left_bound)>>1;
	int hsh=(down_bound-up_bound)>>1;
	int dx,dy,ddy,ddx;
	setTextColor(BLACK);
	setTextSize(15);
	setTextBkColor(WHITE);
	setBrushColor(BLUE);
	setPenColor(BLACK);
//		printf("draw cdt blk 7\n");
	for (int i=0;i<population;i++){
		man*p=&people[i];
		if (oppo_ch(people[i].ch,enemy)&&out_of_screen(p->x,p->y)&&p->rl>0){
			dx=p->x-cx;
			dy=p->y-cy;
//			printf("%d %d\n",dx,dy);
//				printf("draw cdt blk friends %s\n",p->name);
			if (p->x<left_bound){
				
				if (st_order3(-hsh,ddy=dy/(double)dx*hsw,hsh)){
					char *s=malloc(30);
					s[0]=p->name[0];
					s[1]=p->name[1];
					s[2]=':';
					s[3]=0;
					strcat(s,val_to_string(sqrt(dis2(p->x,p->y,cx,cy))));
					draw_life_bar2(0,hsh-ddy,p->rl,p->fl,s);
					continue;
				}
				
			}
			if (p->x>right_bound){
//				printf("dcb 10\n");
				if (st_order3(-hsh,ddy=dy/(double)dx*hsw,hsh)){
					char *s=malloc(30);
					s[0]=p->name[0];
					s[1]=p->name[1];
					s[2]=':';
					s[3]=0;
//					printf("%s\n",s);
					strcat(s,val_to_string(sqrt(dis2(p->x,p->y,cx,cy))));
					draw_life_bar2(window_width,ddy+hsh,p->rl,p->fl,s);
					continue;
				}
//				printf("dcb 10\n");
			}
			if (p->y<up_bound){
				if (st_order3(-hsw,ddx=dx/(double)dy*hsh,hsw)){
					char *s=malloc(30);
					s[0]=p->name[0];
					s[1]=p->name[1];
					s[2]=':';
					s[3]=0;
					strcat(s,val_to_string(sqrt(dis2(p->x,p->y,cx,cy))));
					draw_life_bar2(hsw-ddx,0,p->rl,p->fl,s);
					continue;
				}
			}
			if (p->y>down_bound){
				if (st_order3(-hsw,ddx=dx/(double)dy*hsh,hsw)){
					char *s=malloc(30);
					s[0]=p->name[0];
					s[1]=p->name[1];
					s[2]=':';
					s[3]=0;
					strcat(s,val_to_string(sqrt(dis2(p->x,p->y,cx,cy))));
					draw_life_bar2(hsw+ddx,window_height-40,p->rl,p->fl,s);
					continue;
				}
			}
		}
	}
//	paintText(0,0,val_to_string(touch_time));
//	setTextSize(20);
//	paintText("")
	//message&words
//	printf("draw cdt blk 3\n");
	setTextSize(20);
	int temp;
	if (mn>0){
		if ((temp=mn-7)<0) temp=0; 
		for (int i=temp;i<mn;i++)paintText(add_height+200,window_height+20*(i-temp),message[i]);
	}
	//draw weapon
	setTextSize(30);
	setTextColor(BLACK);
	man*p=&people[0];
	if ((p->weapon==1||p->weapon==2)&&entropy-p->attlt<=60){
			paintText(add_height+800,window_height+20,val_to_string(p->wpr[p->weapon]/(3-p->weapon)));
		}
		else if (p->weapon>=0&&p->weapon<wp_number&&p->wpr[p->weapon]>0)
		{
			paintText(add_height+800,window_height+20,wp_name[p->weapon]);	
		}
	//draw mark
	setPenColor(BLACK);
//		printf("draw cdt blk 4\n");
//	printf("mkn%d\n",mkn);
	for (int i=0;i<mkn;){
//		printf("mk %d x %d y %d t %d\n",i,mk[i].x,mk[i].y,mkt[i]);
		if (mkt[i]<=120){
			mkt[i]++;
			double sw=add_height/(double) map_width;
			double sh=add_height/(double) map_height;
			int ctx=mk[i].x*sw;
			int cty=window_height+mk[i].y*sh;
			r=1+(entropy&15)/4;
			line(ctx-r,cty-r,ctx+r,cty+r);
			line(ctx-r,cty+r,ctx+r,cty-r);
			i++;
		}
		else {
			mk[i]=mk[--mkn];
			mkt[i]=mkt[mkn];
		}
	}
//		printf("draw cdt blk 5\n");
	//draw mark over
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
void beginChapter(int bc){
	seconds=0;
	chapter=bc;
	population=1;
	o_num=0;
	kill=0;
	ssn=ssfrd_num=sseny_num=0;
	int a,b,c,d;
	printf("bc %d\n",bc);
	FILE* fp=fopen("set.txt","r");
	do{
	fscanf(fp,"%*[^C]Chapter %d",&c);
	} while (c-1<bc);
	fscanf(fp,"%*[^:]:%d",&map_width);
	fscanf(fp,"%*[^:]:%d",&map_height);
	fscanf(fp,"%*[^:]:%d",&initial_posx);
	fscanf(fp,"%*[^:]:%d",&initial_posy);
	fscanf(fp,"%*[^:]:%d",&o_num);
	printf("o_num=%d",o_num);
	for (int i=0;i<o_num;i++)
	{
		fscanf(fp,"%*[^:]:%s",&o[i].name);
		fscanf(fp,"%*[^:]:(%d,%d)-(%d,%d)",&o[i].u,&o[i].l,&o[i].d,&o[i].r);
		fscanf(fp,"%*[^:]:%d",&o[i].mode);
		if (o[i].mode<=2) fscanf(fp,"%*[^:]:%d %d %d %d",&o[i].ful,&o[i].fll,&o[i].fdl,&o[i].frl);
		o[i].ul=o[i].ful;o[i].ll=o[i].fll;o[i].dl=o[i].fdl;o[i].rl=o[i].frl;
		fscanf(fp,"%*[^R]RGB(%d,%d,%d)",&o[i].R,&o[i].G,&o[i].B);
		int cx=(o[i].l+o[i].r)>>1;
		int cy=(o[i].u+o[i].d)>>1;
		door_pos[i][0].x=cx;
		door_pos[i][0].y=o[i].d;
		door_pos[i][1].x=cx;
		door_pos[i][1].y=o[i].u;
		door_pos[i][2].x=o[i].r;
		door_pos[i][2].y=cy;
		door_pos[i][3].x=o[i].l;
		door_pos[i][3].y=cy;
	}
	printf("o_num=%d\n",o_num);
	//stage number
	fscanf(fp,"%*[^:]:%d",&enyst_num);
	printf("enyst_num=%d\n",enyst_num);
	for (int i=0;i<enyst_num;i++){
		fscanf(fp,"%*[^:]:%d\n",&mbstn[i]);
		for (int j=0;j<mbstn[i];j++){
			fscanf(fp,"%s",mbst[i][j]);
		}
		fscanf(fp,"%*[^:]:%d",&markn[i]);
		for (int j=0;j<markn[i];j++){
			fscanf(fp,"%d %d",&markx[i][j],&marky[i][j]);
		}
		fscanf(fp,"%*[^:]:%d",&frd_num);
		printf("stage %d frd_num=%d",i,frd_num);
		for (int j=0;j<frd_num;j++)
		{
			get_man_info(&people[population],fp,friends);
			printf("frd %d %s\n",population,people[population].name);
			people[population].ch=friends;
			people[population].cam=0;
			people[population].occur_stage=i;
			people[population].followed=0;
			people[population].rl=0;
			people[population++].attlt=-1;
		}
		fscanf(fp,"%*[^:]:%d",&eny_num);
		printf("eny_num=%d\n",eny_num);
		printf("o_num=%d\n",o_num);
		for (int j=0;j<eny_num;j++){
				get_man_info(&people[population],fp,enemy);
				printf("eny %d name %s\n",j,people[population].name);
				people[population].ch=enemy;
				people[population].cam=0;
				people[population].occur_stage=i;
				people[population].followed=0;
				people[population].rl=0;
				people[population++].attlt=-1;
		}
		fscanf(fp,"%*[^:]:%d/%d %*[^:]:%d",&ssfrda[i],&ssfrdb[i],&max_ssfrd[i]);
		get_man_info(&ssfrd[i],fp,friends);
		ssfrd[i].ch=friends;
		ssfrd[i].occur_stage=i;
		ssfrd[i].attlt=-1;
		fscanf(fp,"%*[^:]:%d/%d %*[^:]:%d",&ssenya[i],&ssenyb[i],&max_sseny[i]);
		get_man_info(&sseny[i],fp,enemy);
		sseny[i].ch=enemy;
		sseny[i].occur_stage=i;
		sseny[i].attlt=-1;
		fscanf(fp,"%*[^:]:%d",&mode_num[i]);
		printf("stage %d mode_num=%d\n",i,mode_num[i]);
		//stage i the j-th mode
		for (int j=0;j<mode_num[i];j++){
			fscanf(fp,"%d",&mode[i][j]);
//			printf("i=%d j=%d o_num=%d\n",i,j,o_num);
			switch (mode[i][j]){
				case 1:
				case 4:
					printf("1&4\n");
					fscanf(fp,"%d",&moden[i][j]);
					for (int k=0;k<moden[i][j];k++){
						fscanf(fp,"%d",&modex[i][j][k]);
					}
					printf("14o_num%d\n",o_num);
					break;
				case 2:
				case 5:
					fscanf(fp,"%d",&moden[i][j]);
					for (int k=0;k<moden[i][j];k++){
						fscanf(fp,"%d %d",&modex[i][j][k],&modey[i][j][k]);
						modex[i][j][k]--;
					}
//					printf("25o_num%d\n",o_num);
					break;
				case 3:
					fscanf(fp,"%d",&modex[i][j][0]);
//					printf("3o_num%d\n",o_num);
					break;
				case 0:
					fscanf(fp,"%d",&moden[i][j]);
					for (int k=0;k<moden[i][j];k++){
						fscanf(fp,"%d %d %d %d",&modep[i][j][k],&modex[i][j][k],&modey[i][j][k],&moder[i][j][k]);
					}
//					printf("0o_num%d\n",o_num);
					break;
			}
		}
	}//end for i 
	//stage read over
	fscanf(fp,"%*[^:]:%d",&EventNum);
	printf("EventNum=%d\n",EventNum);
	for (int i=0;i<EventNum;i++){
		fscanf(fp,"%*[^:]:%d",&EventCdtCodeNum[i]);
		EventFinish[i]=0;
		printf("Event %d EventCdtCodeNum=%d\n",i,EventCdtCodeNum[i]);
		for (int j=0;j<EventCdtCodeNum[i];j++)
		{
			fscanf(fp,"%*[^:]:%d",&EventCdtCode[i][j]);
			printf("Cdt :%d\n",EventCdtCode[i][j]);
			fscanf(fp,"%d %d %d %d",&EventCdtp[i][j],&EventCdtx[i][j],&EventCdty[i][j],&EventCdtr[i][j]);
		}
		fscanf(fp,"%*[^:]:%d",&EventCode[i]);
		printf("Event code %d\n",EventCode[i]);
		switch (EventCode[i]){
			case 0:{
				fscanf(fp,"%d %d %d %d %d %d",&EventItem[i].ic,
				&EventItem[i].x,&EventItem[i].y,&EventItem[i].wpr,&EventItem[i].ma,&EventItem[i].mr);
				printf("%d %d %d %d %d %d",EventItem[i].ic,
				EventItem[i].x,EventItem[i].y,EventItem[i].wpr,EventItem[i].ma,EventItem[i].mr);
				break;
			}
			case 1:{
				fscanf(fp,"%d %d %d %d %d",&EventItem[i].ic,
				&EventItem[i].people,&EventItem[i].wpr,&EventItem[i].ma,&EventItem[i].mr);
				printf("%d %d %d %d %d",EventItem[i].ic,
				EventItem[i].people,EventItem[i].wpr,EventItem[i].ma,EventItem[i].mr);
				break;
			}
			case 2:{
				get_man_info(&people[population],fp,friends);
				int temp;
				fscanf(fp,"%*[^:]:%d %d %d",&EventPeople[i].x,&EventPeople[i].y,&temp);
				people[population].ch=temp;
				people[population].followed=0;
				people[population].rl=0;
				EventPeopleIndex[i]=population;
				people[population].occur_stage=-1;
				people[population].occur=0;
				people[population++].attlt=-1;
				break;
			}
			case 3:{
				get_man_info(&people[population],fp,friends);
				int temp;
				fscanf(fp,"%*[^:]:%d %d",&EventPeopleOcPp[i],&temp);
				printf("%s\n",people[population].name);
				people[population].ch=temp;
				people[population].occur_stage=-1;
				people[population].followed=0;
				people[population].rl=0;
				people[population].occur=0;
				EventPeopleIndex[i]=population;
				people[population++].attlt=-1;
				break;
			}
			case 4:{
				fscanf(fp,"%s",EventMessage[i]);
				printf("%s",EventMessage[i]); 
				break;
			}
			case 5:{
				break;
			}
			case 6:{
				fscanf(fp,"%d %d",&EventLifePp[i],&EventLifeTo[i]);
				break;
			}
			case 7:{
				fscanf(fp,"%d %d",&EventBd[i],&EventBdMdTo[i]);
				break;
			}
		} //switch event code
	}//for i
	//event read over
//	printf("00o_num=%d\n",o_num);
	fscanf(fp,"%*[^:]:%d",&bciPathNum);
	for (int i=0;i<bciPathNum;i++){
		fscanf(fp,"%s",bciPath[i]);
		printf("%d %s\n",i,bciPath[i]);
	}
	fscanf(fp,"%*[^:]:%d",&eciPathNum);
	for (int i=0;i<eciPathNum;i++){
		fscanf(fp,"%s",eciPath[i]);
		printf("%d %s\n",i,eciPath[i]);
	}
	fclose(fp);
	people[0]=atkstplcdt[0];
	people[0].x=initial_posx;
	people[0].y=initial_posy;
	people[0].moving=0;
	people[0].atting=0;
	people[0].rl=people[0].fl;
	people[0].ch=you;
	touch_time=double_atk=double_sp=double_def=itemFullPower=0;
	mkn=0;
	ar_hd=ar_tl=0;
	sh_hd=sh_tl=0;
//	printf("sds o_num=%d\n",o_num);
	map_cut();
//	printf("sdeaf o_num=%d\n",o_num);
	for (int i=0;i<ver-1;i++){
		ctx[i]=(mx[i]+mx[i+1])>>1;
//		printf("ctx %d %d \n",i,ctx[i]);
	}	
	for (int i=0;i<hor-1;i++){
		cty[i]=(my[i]+my[i+1])>>1;
//		printf("cty %d %d \n",i,cty[i]);
	}
	neardoor_set();
	entropy=0;
	for (int i=0;i<ver;i++) {
		for (int j=0;j<hor;j++) visited[i][j]=0;
	}
	for (int i=0;i<ver;i++){
		for (int j=0;j<hor;j++){
			for (int d=0;d<4;d++)
			for (int ch=0;ch<4;ch++)
			go[i][j][d][ch]=0;
		}
	}
	ssfrd_num=sseny_num=0;
	ssn=0;
	itnum=0;
	left_bound=people[0].x-window_width/2;
	up_bound=people[0].y-window_height/2;
	printf("5\n");
	printf("o_num=%d\n",o_num);
//	draw();
	mn=dmn=0;
	newAtkStage(0);
	condition=dialog;
	imageIndex=0;
	dialogFlag=beforeChap;
	printf("load successfully\n");
}
void neardoor_set(void){
	for (int i=0;i<ver-1;i++){
		for (int j=0;j<hor-1;j++){
			int x=ctx[i];
			int y=cty[j];
			nearDoor[i][j]=0;
			for (int d=0;d<4;d++)
			if (i+_dx[d]>=0&&i+_dx[d]<ver-1&&j+_dy[d]>=0&&j+_dy[d]<hor-1){
				int tox=ctx[i+_dx[d]];
				int toy=cty[j+_dy[d]];
//				printf("near door set %d %d to %d %d\n",i,j,i+_dx[d],j+_dy[d]);
//				printf("near door set center %d %d to %d %d\n",x,y,tox,toy);
				if (algo(enemy,x,y,tox,toy)&&!algo(friends,x,y,tox,toy)){
					nearDoor[i][j]=1;
					hasDoor[i][j][d][enemy]=1;
					hasDoor[i][j][d][two]=1;
					hasDoor[i][j][d][friends]=0;
					hasDoor[i][j][d][you]=0;
//					printf("%d %d to %d %d has eny door\n",x,y,tox,toy);
				}//its a enemy door
				else if (algo(friends,x,y,tox,toy)&&!algo(enemy,x,y,tox,toy)){
					nearDoor[i][j]=1;
					hasDoor[i][j][d][enemy]=0;
					hasDoor[i][j][d][two]=1;
					hasDoor[i][j][d][friends]=1;
					hasDoor[i][j][d][you]=1;
//					printf("%d %d to %d %d has frd door\n",x,y,tox,toy);
				}
//					printf("%d %d %d %d algo(frd):%d\n",x,y,tox,toy,algo(friends,x,y,tox,toy));
//					printf("%d %d %d %d algo(eny):%d\n",x,y,tox,toy,algo(enemy,x,y,tox,toy));
			}
		}
	}
//	for (int i=0;i<ver-1;i++){
//		for (int j=0;j<hor-1;j++){
//			printf("%d ",nearDoor[i][j]);
//		}
//		printf("\n");
//	}
}
void newAtkStage(int st){
	printf("new atkst=%d total=%d\n",st,atkstnum);
	printf("people[0].speedup=%d\n",people[0].speedup);
	atkst=st;
	man temp=people[0];
	people[0]=atkstplcdt[st];
	people[0].rl=temp.rl;
	people[0].weapon=temp.weapon;
	for (int i=0;i<wp_number;i++){
		people[0].wpr[i]=temp.wpr[i];
		people[0].wpma[i]=temp.wpma[i];
		people[0].wpmr[i]=temp.wpmr[i];
	}
	people[0].x=temp.x;
	people[0].y=temp.y;
	people[0].moving=temp.moving;
	people[0].movetox=temp.movetox;
	people[0].movetoy=temp.movetoy;
	people[0].atting=temp.atting;
	people[0].atktox=temp.atktox;
	people[0].atktoy=temp.atktoy;
	if (st>=atkstnum-1){
		people[0].speedup=1;
		people[0].preposx=people[0].x;
		people[0].preposy=people[0].y;
	}
}
void endChapter(int ec,game_result temp){
	printf("end chapter %d\n",chapter);
	result=temp;
	int x=completionCal();
	if (x>Completion[chapter]){
		Completion[chapter]=x;
	}
	if (temp==win) 
	{
		printf("win\n");
		condition=dialog;
		dialogFlag=endChap;
		if (ec==CompleteChap) CompleteChap++;
	}
	else 
	{
		printf("failed at stage%d\n",stage);
		condition=evaluate;
	}
	//save
	FILE* fp=fopen("saving.txt","w");
	fprintf(fp,"difficulty:%d\n",diff);
	fprintf(fp,"total chapter:%d\n",chapter_number);
	fprintf(fp,"CompleteChap:%d\n",CompleteChap);
	for (int i=0;i<chapter_number;i++){
		fprintf(fp,"%d\n",Completion[i]);
	}
	fprintf(fp,"atkstnum:%d\n",atkstnum);
	for (int i=0;i<atkstnum;i++){
		putManInfo(&atkstplcdt[i],fp);
		fprintf(fp,"\natkst et:%d\n",atkstet[i]);
	}
	fclose(fp);
}
void putManInfo(man *p,FILE*fp){
	fprintf(fp,"name:%s\n",p->name);
	if (p->ch!=you){
		fprintf(fp,"posx:%d\n",p->x);
		fprintf(fp,"posy:%d\n",p->y);
		fprintf(fp,"actionmode:%d\n",p->amn);
		for (int i=0;i<p->amn;i++){
			fprintf(fp,"actionmode %d :%d\n",i,p->am[i]);
			switch (p->am[i]){
				case 0:fprintf(fp,"protect(%d,%d)\n",p->amx[i],p->amy[i]);
						break;
				case 1:
						break;
				case 2:fprintf(fp,"atk num:%d  ",p->amatkn[i]);
						fprintf(fp,"people:");
						for (int j=0;j<p->amatkn[i];j++){
							fprintf(fp," %d ",p->amatk[i][j]);
						}
						printf("\n");
						break;
				case 3:fprintf(fp,"atk to (%d,%d)",p->amx[i],p->amy[i]);
						fprintf(fp,"of building %d",p->amatko[i]);
						printf("\n");
						break;
				case 7:fprintf(fp,"follow :%d\n",p->amx[i]);
						break;
			}
			fprintf(fp,"being to end:%d-%d\n",p->amb[i],p->ame[i]);
		}
	}	
	fprintf(fp,"sp:%d\n",p->sp);
	fprintf(fp,"radius:%d\n",p->r);
	fprintf(fp,"full life:%d\n",p->fl);
	fprintf(fp,"recover sp:%d\n",p->gl);
	fprintf(fp,"atk:%d\n",p->atk);
	fprintf(fp,"akt r:%d\n",p->atk_r);
	fprintf(fp,"def:%d\n",p->def);
	fprintf(fp,"act interval:%d\n",p->act_interval);
	fprintf(fp,"atk interval:%d\n",p->atkint);
	fprintf(fp,"long dis atk r:%d\n",p->lda_r);
	fprintf(fp,"long dis atk sp:%d\n",p->lda_sp);
	fprintf(fp,"atk pattern number:%d\n",p->atkpn);
	for (int i=0;i<p->atkpn;i++)
	{
		fprintf(fp,"atkpattern :%d ",p->atkp[i]);
		switch (p->atkp[i]){
			case 0:fprintf(fp,"%d %d %d",p->atkag[i],p->atkmr[i],p->atkma[i]);
					break;
			case 1:fprintf(fp,"%d %d %d",p->atkag[i],p->atkmr[i],p->atkma[i]);
					break;
			case 2:fprintf(fp,"%d %d %d",p->atkdis[i],p->atkmr[i],p->atkma[i]);
					break;
			case 3:fprintf(fp,"%d %d %d",p->atkdis[i],p->atkmr[i],p->atkma[i]);
					break;
		}
		fprintf(fp," %d\n",p->atkpfn[i]);
	}
	fprintf(fp,"wpr:");
	for (int i=0;i<10;i++)
	fprintf(fp,"%d ",p->wpr[i]);
	fprintf(fp,"\n");
	fprintf(fp,"wpma:");
	for (int i=0;i<wp_number;i++)
	fprintf(fp,"%d ",p->wpmr[i]);
	fprintf(fp,"\n");
	fprintf(fp,"wpmr:");
	for (int i=0;i<wp_number;i++)
	fprintf(fp,"%d ",p->wpma[i]);
	fprintf(fp,"\n");
}
int completionCal(void){
	int finish=0;
	for (int i=0;i<EventNum;i++){
		if (EventFinish[i]){
			finish++;
		}
	}
	return (stage/(double)enyst_num+finish/(double)EventNum)*50;
}
void newStage(int ns){
	printf("into stage %d\n",ns);
	stage=ns;
	for (int i=0;i<population;i++){
		if (people[i].occur_stage==ns&&people[i].rl<=0){
			people[i].rl=people[i].fl;
			people[i].occur=1;
		}
	}
	for (int i=0;i<mbstn[ns];i++){
		newMessage(mbst[ns][i]);
	}
	for (int i=0;i<markn[ns];i++){
		newMark(markx[ns][i],marky[ns][i]);
	}
	if (stage>=enyst_num){
		endChapter(chapter,win);
	}
}
void newMark(int x,int y){
	mk[mkn].x=x;
	mk[mkn].y=y;
	mkt[mkn]=0;
	mkn++;
}
int maninsamesidebd(man*p){
	for (int i=0;i<o_num;i++){
		if (samesidemanbuilding(p,&o[i])&&inbd(p->x,p->y,&o[i])){
			return 1;
		}
	}
	return 0;
}
void new_arrow(man*q){
		single_arrow*p=&arrow[ar_tl];
		if (maninsamesidebd(q)){
			p->through_wall=1;
		}
		else {
			p->through_wall=0;
		}
		p->atk=q->atk/2;
		p->restd=atkdis(q);
		p->fulld=atkdis(q);
		p->angle=vector_angle(q->atktox-q->x,q->atktoy-q->y);
		p->sp=q->lda_sp;
		p->x=p->stx=q->x+q->r*cos(p->angle);
		p->y=p->sty=q->y+q->r*sin(p->angle);
		p->cdt=flying;
		p->ch=q->ch;
		p->people=q;
		if (ar_tl==max_ar_num) ar_tl=0;
		else ar_tl++;
//		printf("%d %d %d\n",p->sp,p->dx,p->dy);
}
int oppo_ch(character a,character b){
	if (a==friends||a==you) return (b==enemy);
	else if (a==enemy) return (b==friends||b==you);
}
man* findEnemy(man*p){
	if (p->rl<=0) return NULL;
	man* minp=NULL;
//	if (p->weapon==0){
//		int dis=INT_MAX,dr,seddis=INT_MAX;
//		int temp;
//		for (int i=0;i<population;i++){
//			man *q=&people[i];
//			if (oppo_ch(p->ch,q->ch)&&q->rl>0){
//				if (dis>(temp=minHamDis(p->ch,p->x,p->y,q->x,q->y,&dr))
//				||(dis==temp)&&(dis2(p->x,p->y,q->x,q->y)<seddis)){
//					dis=temp;
//					seddis=dis2(p->x,p->y,q->x,q->y);
//					minp=q;
//				}
//			}
//		}
//	}
//	else if (p->weapon==1){
		int dis=INT_MAX;
		for (int i=0;i<population;i++){
			if (oppo_ch(people[i].ch,p->ch)&&people[i].rl>0){
				if (dis>dis2(people[i].x,people[i].y,p->x,p->y)){
					dis=dis2(people[i].x,people[i].y,p->x,p->y);
					minp=&people[i];						
				}
			}			
		}
		for (int i=0;i<ssn;i++){
			if (oppo_ch(ss[i].ch,p->ch)&&ss[i].rl>0){
				if (dis>dis2(ss[i].x,ss[i].y,p->x,p->y)){
					dis=dis2(ss[i].x,ss[i].y,p->x,p->y);
					minp=&ss[i];						
				}
			}
		}
//	}
	return minp;
}
void map_cut(void){
	hor=ver=2;
	mx[0]=my[0]=0;
	mx[1]=map_width;
	my[1]=map_height;
//	printf("adfas o_num=%d\n",o_num);
	for (int i=0;i<o_num;i++){
//		printf("i=%d o_num=%d\n",i,o_num);
		if (o[i].mode<=2){
			int cx=(o[i].l+o[i].r)/2;
			int cy=(o[i].u+o[i].d)/2;
			ver=order_insert(o[i].l,mx,ver);
			ver=order_insert(cx-o[i].ful/10,mx,ver);
			ver=order_insert(cx+o[i].ful/10,mx,ver);
			ver=order_insert(cx-o[i].fdl/10,mx,ver);
			ver=order_insert(cx+o[i].fdl/10,mx,ver);
			ver=order_insert(o[i].r,mx,ver);
			hor=order_insert(o[i].u,my,hor);
			hor=order_insert(cy-o[i].fll/10,my,hor);
			hor=order_insert(cy+o[i].fll/10,my,hor);
			hor=order_insert(cy-o[i].frl/10,my,hor);
			hor=order_insert(cy+o[i].frl/10,my,hor);
			hor=order_insert(o[i].d,my,hor);
		}
		else if (o[i].mode==3){
			ver=order_insert(o[i].l,mx,ver);
			ver=order_insert(o[i].r,mx,ver);
			hor=order_insert(o[i].u,my,hor);
			hor=order_insert(o[i].d,my,hor);
		}
	}
//	printf("ddd o_num=%d\n",o_num);
}
int order_insert(int x,int a[],int n){
	int i;
//	printf("%d %d\n",x,n);
	for (i=0;i<n;i++)
	if (a[i]==x) return n;
	for (i=n-1;a[i]>x;a[i+1]=a[i],i--);
	a[i+1]=x;
	return n+1;
}
int out_of_map(int x,int y){
	return (x<=0||x>=map_width||y<=0||y>=map_height);
}
int minHamDis(character ch,int x,int y,int tox,int toy,int *direction)//min hamilton distance 
{
	if (out_of_map(x,y)||out_of_map(tox,toy)) 
	{
		*direction=-1;
		return -1;
	}
//	for (int i=0;i<ver;i++){
//		printf("%d \n",mx[i]);
//	}
//	for (int i=0;i<hor;i++){
//		printf("%d\n",my[i]);
//	}
	int stx,sty,edx,edy;
	stx=findmx(x);
	sty=findmy(y);
	edx=findmx(tox);
	edy=findmy(toy);
	heap[1].x=stx;
	heap[1].y=sty;
	visited[stx][sty]=++angry;
//	if (debug){
//		printf("minHD pos %d %d to %d %d\n",x,y,tox,toy);
//		printf("minHD block %d %d to %d %d\n",stx,sty,edx,edy);
//	}
//	printf("///////////////////////////////////\n");
	heap[1].l=0;
	num=1;
	int l,d=dis2(ctx[stx],cty[sty],ctx[edx],cty[edy]);
	//d Euclid dis  l Hamilton dis
	if (d==0) 
	{
		*direction=-1;
		return 0;
	}
	while (num>0){
		x=heap[1].x;
		y=heap[1].y;
		l=heap[1].l;
//		if (debug){
//			printf("min HD %d\n",num);
//			for (int i=1;i<=num;i++){
//				printf("min HD %d %d %d %d\n",heap[i].x,heap[i].y,heap[i].d,heap[i].l);
//			}
//			printf("min HD extend:%d %d ct %d %d\n",x,y,ctx[x],cty[y]);
//		}
//		for (int i=1;i<=num;i++){
//			if (i*2<=num&&heap[i].d>heap[i*2].d) printf("no\n");
//			if (i*2+1<=num&&heap[i].d>heap[i*2+1].d) printf("no\n");
//		}
		delete_root();
		for (int dr=0;dr<4;dr++){
			tox=x+_dx[dr];
			toy=y+_dy[dr];
//			printf("min HD to:%d %d ctx%d cty %d\n",tox,toy,ctx[tox],cty[toy]);
			if (tox>=0&&tox<ver&&toy>=0&&toy<hor)
			{
				if (visited[tox][toy]!=angry&&algo(ch,ctx[x],cty[y],ctx[tox],cty[toy])){
					d=dis2(ctx[tox],cty[toy],ctx[edx],cty[edy]);
//					printf("min HD to %d %d is in\n",tox,toy);
					if (d==0) 
					{
//						printf("min HD arrive last step dr %d\n",dr);
						*direction=dr;
						return int_abs(ctx[x]-ctx[tox])+int_abs(cty[y]-cty[toy])+l;
					}
					add_to_heap(tox,toy,d,int_abs(ctx[x]-ctx[tox])+int_abs(cty[y]-cty[toy])+l);
					visited[tox][toy]=angry;
				}
				else {
//					printf("min HD %d %d\n",visited[tox][toy]!=angry,algo(ch,ctx[x],cty[y],ctx[tox],cty[toy]));
				}
			}
			else {
//				if (debug){
//					printf("min HD tox toy out\n");
				}
//			}
		}
	}
	*direction=-1;
	return INT_MAX;
}//direction is the last step 
int int_abs(int x){
	return x<0?-x:x;
}
void add_to_heap(int x,int y,int d,int l){
	int i=++num;
	int j;
	while ((j=(i>>1))>0&&d<heap[j].d||d==heap[j].d&&l<heap[j].l){
		heap[i]=heap[j];
		i=j;
	}
	heap[i].x=x;
	heap[i].y=y;
	heap[i].l=l;
	heap[i].d=d;
}
void swap_heap_element(heap_element *a,heap_element *b){
	heap_element temp=*a;
	*a=*b;
	*b=temp;
}
void delete_root(void){
//	if (num==0) return;
	int i=1,j;
	swap_heap_element(&heap[1],&heap[num]);
	heap[num--].d=INT_MAX;
	while ((j=(i<<1))<=num){
		if (heSmall(j,j+1)&&heSmall(j,i)){
			swap_heap_element(&heap[i],&heap[j]);
			i=j;
		}
		else if (heSmall(j+1,j)&&heSmall(j+1,i)){
			swap_heap_element(&heap[i],&heap[j+1]);
			i=j+1;
		}
		else return;
	}
}
int heSmall(int i,int j){
	return (heap[i].d<heap[j].d||heap[i].d==heap[j].d&&heap[i].l<heap[j].l||
	heap[i].d==heap[j].d&&heap[i].l==heap[j].l&&i<j);
}
void d_cal(man *p){
	if (p->atting==0||p->rl<=0) return;
		if (p->weapon==0){
			int x=p->x;
			int y=p->y;
			int r=p->r;
//			printf("here\n");
			int pat=p->atkp[p->attpat];
			switch(pat){
				case 0: {double a1=vector_angle(p->atktox-x,p->atktoy-y);
						if ((p->atkpfn[p->attpat]-1)<=0) {
							printf("0 bug\n");
							return;
						} 
						a1+=pi/180*p->atkag[p->attpat]*(0.5-(p->atting-1)/(double)(p->atkpfn[p->attpat]-1));
						int tox=x+cos(a1)*atkdis(p);
						int toy=y+sin(a1)*atkdis(p);
						for (int i=0;i<population;i++){
							man*q=&people[i];
							if (oppo_ch(q->ch,p->ch)&&q->rl>0)
							if (p->damaged[i]!=p->attlt)
							if (lineCrossCircle(x,y,tox,toy,q->x,q->y,q->r)){
								p->damaged[i]=p->attlt;
								touch(p,q,0);
							}
						}
						for (int i=0;i<ssn;i++){
							man*q=&ss[i];
							if (oppo_ch(q->ch,p->ch)&&q->rl>0)
							if (lineCrossCircle(x,y,tox,toy,q->x,q->y,q->r)){
								touch(p,q,1);
							}
						}
						for (int i=0;i<o_num;i++)
						if (!samesidemanbuilding(p,&o[i])){
							{
								bdDamage(&o[i],findAtkingGate(p->ch,x,y,tox,toy,&o[i]),atk(p)/build_shell);
							}
						}
						}
						break;
				case 1:{double a1=vector_angle(p->atktox-x,p->atktoy-y);
						if ((p->atkpfn[p->attpat]-1)<=0) {
							printf("1 bug\n");
							return;
						} 
						a1-=pi/180*p->atkag[p->attpat]*(0.5-(p->atting-1)/(double)(p->atkpfn[p->attpat]-1));
						int tox=x+cos(a1)*atkdis(p);
						int toy=y+sin(a1)*atkdis(p);
						for (int i=0;i<population;i++){
							man*q=&people[i];
							if (oppo_ch(q->ch,p->ch)&&q->rl>0)
							if (p->damaged[i]!=p->attlt)
							if (lineCrossCircle(x,y,tox,toy,q->x,q->y,q->r)){
								p->damaged[i]=p->attlt;
								touch(p,q,0);
							}
						}
						for (int i=0;i<ssn;i++){
							man*q=&ss[i];
							if (oppo_ch(q->ch,p->ch)&&q->rl>0)
							if (lineCrossCircle(x,y,tox,toy,q->x,q->y,q->r)){
								touch(p,q,1);
							}
						}
						for (int i=0;i<o_num;i++)
						if (!samesidemanbuilding(p,&o[i])){
								bdDamage(&o[i],findAtkingGate(p->ch,x,y,tox,toy,&o[i]),atk(p)/build_shell);
						}
						break;}
				case 2:{int tl=atkdis(p)-r;
						double a1=vector_angle(p->atktox-x,p->atktoy-y);
						if ((p->atkpfn[p->attpat])<=0) {
							printf("2 bug\n");
							return;
						} 
						int len=r+tl/(double)p->atkpfn[p->attpat]*p->atting;
						int tox=x+cos(a1)*len;
						int toy=y+sin(a1)*len;
						for (int i=0;i<population;i++)
							{
								man*q=&people[i];
								if (q->rl>0&&oppo_ch(people[i].ch,p->ch))
								if (p->damaged[i]!=p->attlt)
								if (lineCrossCircle(x,y,tox,toy,q->x,q->y,q->r)){
									p->damaged[i]=p->attlt;
									touch(p,q,0);
									back(p,q,p->atkdis[p->attpat]);
								}
							}
						for (int i=0;i<ssn;i++)
							{
								man*q=&ss[i];
								if (q->rl>0&&oppo_ch(q->ch,p->ch))
								if (lineCrossCircle(x,y,tox,toy,q->x,q->y,q->r)){
									touch(p,q,1);
									back(p,q,p->atkdis[p->attpat]);
								}
							}
						for (int i=0;i<o_num;i++)
						if (!samesidemanbuilding(p,&o[i])){
								bdDamage(&o[i],findAtkingGate(p->ch,x,y,tox,toy,&o[i]),atk(p)/build_shell);
						}
					break;
				}
				case 3:{double a1=vector_angle(p->atktox-x,p->atktoy-y);
						if ((p->atkpfn[p->attpat]-1)<=0) {
							printf("3 bug\n");
							return;
						} 
						a1-=2*pi*(0.5-(p->atting-1)/(double)(p->atkpfn[p->attpat]-1));
						int tox=x+cos(a1)*atkdis(p);
						int toy=y+sin(a1)*atkdis(p);
						for (int i=0;i<population;i++)
							{
								man*q=&people[i];
								if (q->rl>0&&oppo_ch(people[i].ch,p->ch))
								if (p->damaged[i]!=p->attlt)
								if (lineCrossCircle(x,y,tox,toy,q->x,q->y,q->r)){
									p->damaged[i]=p->attlt;
									touch(p,q,0);
									back(p,q,p->atkdis[p->attpat]);
								}
							}
						for (int i=0;i<ssn;i++)
							{
								man*q=&ss[i];
								if (q->rl>0&&oppo_ch(q->ch,p->ch))
								if (lineCrossCircle(x,y,tox,toy,q->x,q->y,q->r)){
									touch(p,q,1);
									back(p,q,p->atkdis[p->attpat]);
								}
							}
						for (int i=0;i<o_num;i++)
						if (!samesidemanbuilding(p,&o[i])){
								bdDamage(&o[i],findAtkingGate(p->ch,x,y,tox,toy,&o[i]),atk(p)/build_shell);
						}
					break;
				}
			}		//end switch short dis damage calculate 
		}//end if weapon==0
//		printf("out d_cal over\n");
}
int lineCrossCircle(int x,int y,int tox,int toy,int cx,int cy,int r){
	int fx,fy;
	int pd=sqrt(dis2(tox,toy,x,y));
	if (pd<=0) pd=1;
	if (pd>10) pd=10;
	for (int i=0;i<=pd;i++){
		fx=(tox*i+(pd-i)*x)/(double)pd;
		fy=(toy*i+(pd-i)*y)/(double)pd;
		if (incircle(fx,fy,cx,cy,r)) return 1;
	}
	return 0;
}
void bdDamage(obstacle *p,int door,int dmg){
	if (p==NULL) return;
	if (dmg<=0) dmg=1+(entropy&1);
	int broke=0;
	switch (door){
		case -1:
			if (p->ll<=dmg) 
				{
					p->ll=0;
					broke=1;
				}
			else p->ll-=dmg;
			break;
		case -2:
			if (p->rl<=dmg) {
				p->rl=0;
					broke=1;
				}
			else p->rl-=dmg;
			break;
		case -3:
			if (p->ul<=dmg) 
			{
				p->ul=0;
					broke=1;
				}
			else p->ul-=dmg;
			break;
		case -4:
			if (p->dl<=dmg) {
				p->dl=0;
				broke=1;
				}
			else p->dl-=dmg;
			break;
	}
	if (broke){
		int len=strlen(p->name);
		char ss[30];
		for (int i=0;i<=len;i++) ss[i]=p->name[i];
		newMessage(strcat(ss,door_broken_string[door+4]));
		for (int i=0;i<o_num;i++)
		if (&o[i]==p){
			newMark(door_pos[i][door+4].x,door_pos[i][door+4].y);
		}
		neardoor_set();
	}
	if (p->ll==0&&p->rl==0&&p->ul<=0&&p->dl<=0&&p->mode<=2){
		p->mode=3-p->mode;
		p->ll=p->fll/2;
		p->rl=p->frl/2;
		p->dl=p->fdl/2;
		p->ul=p->ful/2;
		char ss[30];
		int len=strlen(p->name);
		for (int i=0;i<=len;i++) ss[i]=p->name[i];
		if (p->mode==2)newMessage(strcat(ss,lost_string));
		else if (p->mode==1) 
		{
			newMessage(strcat(ss,occupy_string));
			if (p->frl+p->ful+p->fdl+p->fll>3000)newRandomItem(0,(p->l+p->r)>>1,(p->u+p->d)>>1,NULL,0);
			else if (p->frl+p->ful+p->fdl+p->fll>2000)newRandomItem(0,(p->l+p->r)>>1,(p->u+p->d)>>1,NULL,4);
			else if (p->frl+p->ful+p->fdl+p->fll>1000)newRandomItem(0,(p->l+p->r)>>1,(p->u+p->d)>>1,NULL,10);
			else if (p->frl+p->ful+p->fdl+p->fll>500)newRandomItem(0,(p->l+p->r)>>1,(p->u+p->d)>>1,NULL,20);
			else if (p->frl+p->ful+p->fdl+p->fll>100)newRandomItem(0,(p->l+p->r)>>1,(p->u+p->d)>>1,NULL,1000);
		}
	}
}
void newRandomItem(int code,int x,int y,man*q,int z){
	int temp;
	if (z==0){
		temp=rand()%5+5;
		newItem(temp,code,x,y,q);
	}
	else {
		temp=rand()%z;
		if (temp==0){
			temp=rand()%5+5;
			newItem(temp,code,x,y,q);
		}
		else {
			temp=rand()%5;
			newItem(temp,code,x,y,q);
		}
	}
}//0 at x y;1 at manp pos; 
void newItem(int itemcode,int flag,int x,int y,man*p){
	if (flag==1){
		x=p->x;
		y=p->y;
	}
	item[itnum].ic=itemcode;
	item[itnum].x=x;
	item[itnum++].y=y;
}
int incircle(int x,int y,int cx,int cy,int r){
//	printf("%d %d %d %d %d\n",x,y,cx,cy,r);
	return (dis2(x,y,cx,cy)<r*r); 
}
void touch(man *p,man *q,int qss){
	if (q->rl<=0) return;
	int real_dmg=atk(p)-def(q);
	if (real_dmg<0) real_dmg=1+(entropy&1);
	if (q->rl<=real_dmg){
		q->rl=0;
		pkillq(p,q,qss);
	}
	else 
	{
		q->rl-=real_dmg;
		if (p->wpma[p->weapon]==-1)back(p,q,25);
	}
	if (p->ch==you){
		int temp;
		if (qss) temp=1;
		else if ((temp=real_dmg)>20) temp=20;
		touch_time+=temp;
		if (touch_time>atkstet[atkstnum-1]) {
			touch_time=atkstet[atkstnum-1];
			p->rl++;
			if (p->rl>p->fl) p->rl=p->fl;
		}
		lastTouch=seconds;
	}
//	printf("%s touch %s\n",p->name,q->name);
//	char s[30];
//	printf("%s loses %d hp\n",q->name,real_dmg);
//	new_massage(s); 
}
void pkillq(man*p,man *q,int qss){ 
	if (qss){
		for (int i=0;i<ssn&&ssn>0;i++){
			if (ss[i].rl<=0){
				if (ss[i].ch==enemy) {
					sseny_num--;
				}
				else if (ss[i].ch==friends) 
				{
					ssfrd_num--;				
				}
				ss[i]=ss[--ssn];
				if (people[ss[i].amx[1]].followed>0) people[ss[i].amx[1]].followed--;
			}
		}
	}
	else 
	{
		if (q->ch==friends){
			char ss[30];
			for (int i=0;i<=strlen(q->name);i++) ss[i]=q->name[i];
			newMessage(strcat(ss,defeated_string));
		}
		else if (q->ch==enemy){
			char ss[30];
			int len=strlen(p->name);
			for (int i=0;i<len;i++) ss[i]=p->name[i];
			for (int i=len;i<=len+strlen(defeat_string);i++) ss[i]=defeat_string[i-len];
			newMessage(strcat(ss,q->name));
		}
		newMark(q->x,q->y);
	}
	if (p->ch==you) {
		kill++;
	}
	int x=100;
	x-=q->fl/20;
	x-=q->atk+q->def+q->sp;
	x+=q->act_interval*10;
	if (x<100){
		if (x<0) x=0;
		newRandomItem(1,0,0,q,x);
	}
}
void newMessage(char *q){
	strcpy(message[mn++],q);
	ltdm=seconds;
}
int back(man *p,man *q,int dis){
	int dx=q->x-p->x;
	int dy=q->y-p->y;
	double mo=sqrt(dx*dx+dy*dy);
	if (mo<0.1) {
		dx=0;
		dy=1;
		mo=1;
	}
	double ddx=dx/mo;
	double ddy=dy/mo;
	int m,l=0,r=dis+1;
	while (l+1<r){
		m=(l+r)>>1;
		if (nocrossing(q->ch,q->x,q->y,q->x+ddx*m,q->y+ddy*m)){
			l=m;
		}
		else r=m;
	}
	
	if (l>0){
		q->backing=1;
		q->preposx=q->x;
		q->preposy=q->y;
		q->x+=ddx*l;
		q->y+=ddy*l;
	}
	printf("%s force %s back %d in %d\n",p->name,q->name,l,dis);
	return l;
}
point* nearestAtkDr(man *p){//within atk range
	if (p!=NULL&&p->rl>0){
		point*q=malloc(sizeof(point));
		int mind=INT_MAX;
		q->x=-1;
		q->y=-1;
		for (int i=0;i<o_num;i++){
			if (!samesidemanbuilding(p,&o[i])){
				int cy=(o[i].u+o[i].d)/2;
				int cx=(o[i].l+o[i].r)/2;
				if (canGoAround(p,cx,o[i].u)&&o[i].ul>0&&mind>dis2(cx,o[i].u,p->x,p->y)){
					mind=dis2(cx,o[i].u,p->x,p->y);
					q->x=cx;
					q->y=o[i].ul;
				}
				if (canGoAround(p,cx,o[i].d)&&o[i].dl>0&&mind>dis2(cx,o[i].d,p->x,p->y)){
					mind=dis2(cx,o[i].d,p->x,p->y);
					q->x=cx;
					q->y=o[i].dl;
				}
				if (canGoAround(p,o[i].l,cy)&&o[i].ll>0&&mind>dis2(o[i].l,cy,p->x,p->y)){
					mind=dis2(o[i].l,cy,p->x,p->y);
					q->x=o[i].l;
					q->y=cy;
				}
				if (canGoAround(p,o[i].r,cy)&&o[i].rl>0&&mind>dis2(o[i].r,cy,p->x,p->y)){
					mind=dis2(o[i].r,cy,p->x,p->y);
					q->x=o[i].r;
					q->y=cy;
				}
			}
		}
		return q;
	}
	else return NULL;
}
int canGoAround(man*p,int x,int y){
	int dr;
	for (int d=0;d<4;d++){
		if (minHamDis(p->ch,p->x,p->y,x+_dx[d],y+_dy[d],&dr)!=INT_MAX){
			return 1;
		}
	}
	return 0;
}
point* nearestAtkPt(man *p){//within atk range
	if (p!=NULL&&p->rl>0){
		point*q=malloc(sizeof(point));
		int mind=INT_MAX,mini=-1;
		man *t;
		for (int i=0;i<population;i++){
			t=&people[i];
			if (t->rl>0&&canTouch(p,t)&&mind>dis2(t->x,t->y,p->x,p->y)){
				mind=dis2(t->x,t->y,p->x,p->y);
				mini=i;
//				printf("fl\n");
			}
		}
		if (mini!=-1){
			q->x=people[mini].x;
			q->y=people[mini].y;
			return q;
		}
		for (int i=0;i<ssn;i++){
			t=&ss[i];
			if (t->rl>0&&canTouch(p,t)&&mind>dis2(t->x,t->y,p->x,p->y)){
				mind=dis2(t->x,t->y,p->x,p->y);
				mini=i;
			}
		}//end for 
		if (mini!=-1){
			q->x=ss[mini].x;
			q->y=ss[mini].y;
			return q;
		}
		//below is cdt that no eny in atk range but eny bd in range
		if (p->weapon==0)
		for (int i=0;i<o_num;i++){
			if (!samesidemanbuilding(p,&o[i])){
				int cy=(o[i].u+o[i].d)/2;
				int cx=(o[i].l+o[i].r)/2;
				if (dis2(cx,o[i].u,p->x,p->y)<atkdis(p)*atkdis(p)&&o[i].ul>0){
					q->x=cx;
					q->y=o[i].u;
					return q;
				}
				if (dis2(cx,o[i].d,p->x,p->y)<atkdis(p)*atkdis(p)&&o[i].dl>0){
					q->x=cx;
					q->y=o[i].d;
					return q;
				}
				if (dis2(o[i].l,cy,p->x,p->y)<atkdis(p)*atkdis(p)&&o[i].ll>0){
					q->x=o[i].l;
					q->y=cy;
					return q;
				}
				if (dis2(o[i].r,cy,p->x,p->y)<atkdis(p)*atkdis(p)&&o[i].rl>0){
					q->x=o[i].r;
					q->y=cy;
					return q;
				}
			}
		}
		else if (p->weapon==2){
			for (int i=0;i<o_num;i++)
			if (!samesidemanbuilding(p,&o[i])){
				int cx=(o[i].l+o[i].r)>>1;
				int cy=(o[i].u+o[i].d)>>1;
				int atkdisp=atkdis(p);
				if (o[i].ul>0)
				if (ShellMoveAble(p->ch,p->x,p->y,cx,o[i].u)&&incircle(cx,o[i].u,p->x,p->y,atkdisp)){
					q->x=cx;
					q->y=o[i].u;
					return q;
				}
				if (o[i].dl>0&&incircle(cx,o[i].d,p->x,p->y,atkdisp))
				if (ShellMoveAble(p->ch,p->x,p->y,cx,o[i].d)){
					q->x=cx;
					q->y=o[i].d;
					return q;
				}
				if (o[i].ll>0&&incircle(o[i].l,cy,p->x,p->y,atkdisp))
				if (ShellMoveAble(p->ch,p->x,p->y,o[i].l,cy)){
					q->x=o[i].l;
					q->y=cy;
					return q;
				}
				if (o[i].rl>0&&incircle(o[i].r,cy,p->x,p->y,atkdisp))
				if (ShellMoveAble(p->ch,p->x,p->y,o[i].r,cy)){
					q->x=o[i].r;
					q->y=cy;
					return q;
				}
			}
		}
		if (p->wpr[0]>0&&p->atting==0) p->weapon=0;
		q->x=-1;
		q->y=-1;
		if (p->ch==you){
			q->x=rand()%(map_width+1);
			q->y=rand()%(map_height+1);
		}
		return q;
	}
	else return NULL;
}
int ShellMoveAble(character ch,int x,int y,int tox,int toy){
	if (!nocrossing(two,x,y,tox,toy)) return 0; 
	double angle=vector_angle(y-toy,tox-x);
	double dx=shell_radius*cos(angle)/2;
	double dy=shell_radius*sin(angle)/2;
	int x1=x+dx;
	int y1=y+dy;
	int tox1=tox+dx;
	int toy1=toy+dy;
	if (!nocrossing(two,x1,y1,tox1,toy1)) return 0;
	x1=x-dx;
	y1=y-dy;
	tox1=tox-dx;
	toy1=toy-dy;
	if (!nocrossing(two,x1,y1,tox1,toy1)) return 0;
//	printf("Shell Move Able\n%d %d %d %d\n",x,y,tox,toy);
	return 1;
}
int canTouch(man*p,man*t){
	if (p&&t)
	if (oppo_ch(p->ch,t->ch)){
		if (dis2(t->x,t->y,p->x,p->y)<(atkdis(p)+t->r)*(atkdis(p)+t->r)){
			if (p->weapon==0){
					return 1;
			}
			else if (p->weapon==1){
				if (safeinbd(p)||nocrossing(p->ch,p->x,p->y,t->x,t->y)){
					return 1;
				}
			}
		if (p->weapon==2&&finishAllAtkPtMode(p)&&nocrossing(p->ch,p->x,p->y,t->x,t->y))
			return 1;
		}
		else return 0;
	}
	return 0;
}
int finishAllAtkPtMode(man*p){
	for (int i=0;i<p->amn;i++){
		if (order3(p->amb[i],stage,p->ame[i])&&p->am[i]==3){
			if (!finishAtkPtMode(p,i)){
				return 0;
			}
		}
	}
	return 1;
}
int nocrossingArtoPt(character ch,int x,int y,int tox,int toy){
	for (int d=0;d<4;d++){
		if (nocrossing(ch,tox+3*_dx[d],toy+3*_dy[d],x,y)) return 1;
	}
	return 0;
}

