# robot
GDUT RC 9th robo_sim test  
把文件拉取到~/catkin_ws/src即可  
然后运行 `roslaunch robo_test.launch`  
机器人仿真环境，只做了四台机器人，并没有完全搭建完。  
对应的控制及传感器话题已经写好，但是只验证了速度控制和imu话题。  
场地大小按照规则标准搭建，机器人半径为46cm。  
A队底座为红色，B队为蓝绿色。A队机器人编号为1和2，B队为3和4.  
编号为奇数的机器人顶上的杆子是有颜色的，偶数则都是灰色。  
如何查看话题？  
去对应的机器人model文件里面搜索topic即可查到  
一般来说除了速度控制话题是cmdx_vel,x换成机器人编号，其他都是直接在话题后面加编号。  
参考教程：  
[机器人操作系统 ROS 快速入门教程] (https://www.bilibili.com/video/BV1BP4y1o7pw/?share_source=copy_web&vd_source=2d9681237ef7d9ae6e0c4a3d85c9f569)  
机器人模型就是直接从视频里面嫖的，话题也是从里面改的。  
只做策略验证的话机器人长什么样不重要（主要是手搓机器人太麻烦😭）  

#### provided by 唐子卿 颜钦煜
