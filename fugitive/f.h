//function declare
void set_value(void);
void color_set(void);	
void set_timer(void);
void set_action(void);

void KeyboardListener(int key,int event); 
void MouseListener(int x,int y,int button,int event);
void TimerListener(int TimerID);

void get_man_info(man *p,FILE* fp,character chrct);
void new_s(int x,int y,character ch);
//prepare and clean
void beginChapter(int bc);
void endChapter(int ec,game_result result);
int completionCal(void);
void newStage(int ns);
void newAtkStage(int st);
void map_cut(void);
int findmx(int x);
int findmy(int y);
int order_insert(int x,int a[],int n);//return length
void neardoor_set(void);
//actions
void actions(void);
void act(man*p);
int finishAtkPtMode(man *p,int i);
int UnfinishedAtkPtMode(man *p);
int finishAllAtkPtMode(man*p);
void arrow_move(void);
void arrow_attack(man*p,int atk,man*q,int qss);
void shell_attack(man*p,int atk,man*q,int qss);
void shell_move(void);
//attack
void attackto(man*p,int x,int y);
void d_cal(man*p);
void weapon_consider(man*p);
man* danger(int x,int y,character ch); //one enemy that can touch (x,y) if none return null
int canTouch(man*p,man*t);
int ShellMoveAble(character ch,int x,int y,int tox,int toy);
//damage
int back(man *p,man *q,int dis);
void pkillq(man*p,man *q,int qss);
void touch(man *p,man *q,int qss);
void getDamage(man*p,int x);
void bdDamage(obstacle *p,int door,int dmg);
//move
void move(man*p);
int firstStepTonearestAktGt(man *p);
int firstStepToArd(int x,int y,man *p);
void go_random(man *p,int tox,int toy,int radius); //if go return 1
int algo(character ch,int x,int y,int tox,int toy);
int onwall(int x,int y,obstacle *p);
int inbd(int x,int y,obstacle* p);
int onbd(int x,int y,obstacle* p);
int outbd(int x,int y,obstacle*p);
int safeinbd(man*p);
void new_arrow(man *q);
void new_shell(man *q);
//draw
void draw(void);
void draw_man(man*p,mds *c);
void draw_set_man(mds*c);
void draw_block(void);
void draw_palace(void);
void draw_obstacle(void);
void draw_friend(void);
void draw_enemy(void);
void draw_condition_block(void);
void draw_life_bar(int x,int y,int rest_life,int full_life,char *s);
void draw_life(void);
void draw_arrow(void);
void draw_small_soldier(void);
void draw_shell(void);
void draw_item(void);
void _putImageTransparent(ACL_Image *p,int x,int y,int wid,int hei,ACL_Color color);
//tools
int dis2(int x,int y,int tox,int toy);
int incircle(int x,int y,int cx,int cy,int r);
char *val_to_string(int points);
double vector_angle(int x,int y);
void _line(int x,int y,int tox,int toy);
void _ellipse(int x,int y,int x2,int y2);
void _rectangle(int x,int y,int tox,int toy);
int lineCrossCircle(int x,int y,int tox,int toy,int cx,int cy,int r);
int st_order3(int a,int b,int c);//strictly in order 
int order3(int a,int b,int c);
void getBlock(int x,int y,int point[]);
int firstStep(int x,int y,man *p);
int oppo_ch(character a,character b);
int samesidemanbuilding(man*p,obstacle*x);
int maninsamesidebd(man*p);
int reduce(int x);
int out_of_screen(int x,int y);

int atkdis(man*p);
int maxatkdis2(man*p);
int atk(man*p); 
int spd(man*p);
int def(man*p);
point* nearestAtkPt(man *p);
point* nearestAtkDr(man *p);
int canGoAround(man*p,int x,int y);

void next_weapon(man *p);
int int_abs(int x);
man* findEnemy(man*p);//return null if no alive 
int out_of_map(int x,int y);
int nocrossing(character ch,int x,int y,int tox,int toy);
int nocrossingtoArdPt(character ch,int x,int y,int tox,int toy);
int nocrossingArtoPt(character ch,int x,int y,int tox,int toy);
void swap(int *a,int *b);
//the Core of moving
int minHamDis(character ch,int x,int y,int tox,int toy,int *dis);//return -1 if not connected
void add_to_heap(int x,int y,int d,int l);
void swap_heap_element(heap_element *a,heap_element *b);
void delete_root(void);
int heSmall(int i,int j);
//message and words
void newMessage(char *q);
//mark 
void newMark(int x,int y);
//item
void newRandomItem(int code,int x,int y,man*q,int z);
void newItem(int itemcode,int flap,int x,int y,man*p);
void item_eat(int x);
//
void EventSearch(void);
void EventBegin(int i);
//save
void putManInfo(man *p,FILE*fp);
