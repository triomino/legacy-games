上下键改变炮弹大小和速度,上是大和慢
左右键改变出射方向
空格键发炮
f键暂停
r键重来
在parameter.txt里可以改变参数(格式要正确,每行行末不能有空格):
width:1000 
height:500
plane_patten_number:2(飞机图形的数目,如果是2,接下来两行就要写对应路径)
graph\001.jpg
graph\002.jpg
lower bound of plane speed:3(飞机初始速度下界)
plane speed range:7(飞机初始速度范围,随时间增加会不断加速)
total plane:950(飞机总数)
shell speed:7(炮弹速度,游戏中可调)
shell radius:10(炮弹半径,游戏中可调)
shell number upper bound at every moment:100(任意一个时刻屏幕内最大炮弹数)
flexible of your cannon:0.3(按一下左/右键大炮改变的角度）
draw_interval:10（每10毫秒输出画面，相当于每秒100帧）
plane_move_interval:10（移动飞机的时间间隔）
plane_occur_interval:1000（飞机从左边出现的时间间隔，会加速）
game_start_interval:1000（游戏开始后一段没有飞机的准备时间,不能超过5秒）
shell_move_interval:10（炮弹移动的时间间隔）
soldier falling speed:1
soldier walking speed:1
life at beginning:5
