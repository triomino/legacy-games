// value define
int window_width;
int window_height;
int add_height;
int diff;//difficult degree
int hor,ver,mx[300],my[300],ctx[300],cty[300];//for map_cut use
int nearDoor[300][300],hasDoor[300][300][4][5];
//time
int seconds=0;
//minHamiltonDistance
int visited[300][300],go[300][300][4][5]; //1 go 2 no 0 uncertain
int num;
int angry;
heap_element heap[90000];
//chapter related
int chapter_number;
int CompleteChap;
int Completion[10];
int chapter;
int stage;
//stage mode
int mode_num[MaxStageNumber];//number of modes of one stage
int moden[MaxStageNumber][30],mode[MaxStageNumber][31];//stage i j th mode elements num &mode-code
int modex[MaxStageNumber][30][10],modey[MaxStageNumber][30][10];
int modep[MaxStageNumber][30][10],moder[MaxStageNumber][30][10];
int modeto[MaxStageNumber][30];//if can not finish, go to
//weapon
int wp_number=10;
int ar_hd=0,ar_tl=0;
int sh_hd=0,sh_tl=0;
const int max_ar_num=10000;
const int max_sh_num=10000;
single_arrow arrow[10004];
single_shell shell[10004];
const int arr_length=10;
const int shell_radius=10;
int sucint=5;//succession attack max interval
//small soldier
int ssfrda[MaxStageNumber],ssfrdb[MaxStageNumber],ssenya[MaxStageNumber],ssenyb[MaxStageNumber];
int max_ssfrd[MaxStageNumber],ssn,max_sseny[MaxStageNumber],ssfrd_num,sseny_num;
man ss[500],ssfrd[MaxStageNumber],sseny[MaxStageNumber];//copy
const int max_ss=500;
//pos related
int map_width;
int map_height;
int initial_posx;
int initial_posy;
//man
man people[310];
int population,frd_num;
const int max_population=300;
int enyst_num,eny_num;//enemy stage number
//attack pattern
int total_pattern=4;
//attack pattern frame number
//attack stage
int atkstnum,atkst,atkstbt[10],atkstet[10];
man atkstplcdt[10];
int lastTouch,touch_time;
//screen
int up_bound;
int down_bound;
int left_bound;
int right_bound;
//building
int o_num;
obstacle o[100];
int build_shell=10;//man weapon damage to wall should be divided by this
point door_pos[100][4];
//parameters
int actions_interval;
//color set
mds mycolor,frdcolor,enycolor;
//const strings
char wp_name[3][10]={"枪","弓","炮"}; 
char atkstring[20]="atk:";
char defstring[20]="def:";
char defeated_string[20]=" 败退! "; 
char defeat_string[20]=" 击退 ";
char door_broken_string[4][30]={" 南侧入口被破坏!"," 北侧入口被破坏!"," 东侧入口被破坏!"," 西侧入口被破坏!"}; 
char lost_string[30]=" 被敌军攻占!";
char occupy_string[30]=" 被我军攻占!"; 
char itemEatString[20][20]={
	"life+",
	"life++",
	"atk*2",
	"spd*2",
	"def*2",
	"Full Power!",
	"life++++",
	"spd*2",
	"atk*2",
	"def*2",
	"这是啥?",
	"箭",
	"炮弹"	 
};
char FacePath[20][30]={
	"graph\\001.jpg",
	"graph\\002.jpg",
	"graph\\003.jpg",
	"graph\\004.jpg",
	"graph\\005.jpg",
	"graph\\006.jpg",
	"graph\\007.jpg",
	"graph\\008.jpg",
	"graph\\009.jpg",
};
const char PlayerImagePath[10][20]={
	"graph\\AtkSt1.jpg",
	"graph\\AtkSt2.jpg",
	"graph\\AtkSt3.jpg",
	"graph\\AtkSt4.jpg",
};
//other
int _dx[5]={0,0,-1,1,0};
int _dy[5]={-1,1,0,0,0};
int oppo_dr[4]={1,0,3,2};
int entropy=0; //it's time of the universe
double pi=3.14159265358979323846262;
long start,now;
//debug
int debug=0;
//message&words
int mn,dmn,ltdm;
char message[1000][30];
int mbstn[MaxStageNumber];//message before a stage
char mbst[MaxStageNumber][10][30];
//mark
int markn[MaxStageNumber],markx[MaxStageNumber][10],marky[MaxStageNumber][10];
int mkn,mkt[30];
point mk[30];
//item
int itnum;
int itemFullPower;
aitem item[100];
int double_atk,double_sp,double_def;
//Event
int EventNum;
int EventCdtCodeNum[100];
int EventFinish[100];
int EventCdtCode[100][10];
int EventCdtp[100][10];
int EventCdtx[100][10];
int EventCdty[100][10];
int EventCode[100];
aitem EventItem[100];
man EventPeople[100];
int	EventPeopleIndex[100];
char EventMessage[100][30];
int EventLifePp[100];
int EventLifeTo[100];
int EventBd[100];
int EventBdMdTo[100];
int EventPeopleOcPp[100];
int EventCdtr[100][10];
//graph
ACL_Image AtkStImage[10];
ACL_Image picture;
int bciPathNum,eciPathNum,imageIndex;
char bciPath[20][30],eciPath[20][30];
//result&evaluate
game_result result;
int cause_damage;
int kill;
