//type define
//flags
#define MaxStageNumber 30
enum{
	operate,
	dialog,
	pause,
	chooseChap,
	evaluate
} condition;
enum{
	beforeChap,
	endChap
}dialogFlag;
enum{
	R,
	E
} dismode;
typedef enum{
	flying,
	stop
} arrow_condition;
typedef enum{
	you,
	friends,
	enemy,
	two
} character;
//man
typedef struct {
	int x,y,r;//pos,size
	character ch;
	int sp,atk,atk_r,def,lda_r,lda_sp;//long distance attack range
	char name[20];
	int amn,am[30],amb[30],amx[30],amy[30],ame[30],amatko[30],cam,amatkn[30],amatk[30][10]; //current action mode
	int weapon,wpr[10],wpma[10],wpmr[10];//weapon rest number 
	int moving,atting,followed,damaged[300],damagedtoplayer;//whether move/attack
	int atkpn,attpat,attlt,atkp[14],atkpfn[14];//short attack pattern 
	int atkint,atkag[14],atkmr[14],atkma[14],atkdis[14];//attack interval
	int movetox,movetoy,atktox,atktoy;
	int musou,musou_begin,musou_last;
	int fl,rl,gl;//full,rest life,recover speed
	int occur_stage,occur,ltas,act_interval;//last time assigned
	int speedup,backing,preposx,preposy;
	int facepathi;
	char GraphPath[20];
	ACL_Image face;
} man;
//building
typedef struct {
	int u,d,l,r;
	int ul,dl,ll,rl;
	int ful,fdl,fll,frl;//door length=full life/5
	int R,G,B;
	int mode;
	char name[20];
} obstacle;
//weapon
typedef struct {
	int atk,sp,spc;
	int through_wall;
	int restd,fulld;
	int stx,sty,x,y;
	double angle;
	arrow_condition cdt;
	character ch;
	man* people;
} single_arrow;
typedef struct {
	int atk,sp;
	int through_wall;
	int restd,fulld;
	int stx,sty,x,y;
	double angle;
	arrow_condition cdt;
	character ch;
	man* people;
} single_shell;
typedef struct {
    int ic;
    int x,y;
    int wpr,ma,mr;
    int people;
}aitem;
//a set of colors of one 
typedef struct {
	ACL_Color pc,bc,tc,tbkc;// pen brush text textbk color
	int ts,pw;//text size & pen width
} mds;//man draw set
typedef struct{
	int x,y;
	int d,l;
}heap_element;
typedef struct{
	int x,y;
}point;
typedef enum{
	win,
	failed
}game_result;
