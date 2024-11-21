#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <stdio.h>
#include <termios.h>

static float linear_vel = 0.1;
static float angular_vel = 0.1;
static int k_vel = 400;
int ctrl_robot = 1;

int GetCh()
{
  static struct termios oldt, newt;
  tcgetattr( STDIN_FILENO, &oldt);
  newt = oldt;
  newt.c_lflag &= ~(ICANON);
  tcsetattr( STDIN_FILENO, TCSANOW, &newt);
  int c = getchar();
  tcsetattr( STDIN_FILENO, TCSANOW, &oldt);
  return c;
}

int main(int argc, char** argv)
{
  ros::init(argc, argv, "keyboard_vel_cmd");

  printf("键盘控制机器人： \n");
  printf("w - 向前加速 \n");
  printf("s - 向后加速 \n");
  printf("a - 向左加速 \n");
  printf("d - 向右加速 \n");
  printf("q - 左旋加速 \n");
  printf("e - 右旋加速 \n");
  printf("空格 - 刹车 \n");
  printf("x - 退出 \n");
  printf("数字键切换机器人 \n");
  printf("当前操作机器人%d \n",ctrl_robot);
  printf("------------- \n");

  ros::NodeHandle n;
  ros::Publisher cmd1_vel_pub = n.advertise<geometry_msgs::Twist>("/cmd1_vel", 10);
  ros::Publisher cmd2_vel_pub = n.advertise<geometry_msgs::Twist>("/cmd2_vel", 10);
  ros::Publisher cmd3_vel_pub = n.advertise<geometry_msgs::Twist>("/cmd3_vel", 10);
  ros::Publisher cmd4_vel_pub = n.advertise<geometry_msgs::Twist>("/cmd4_vel", 10);

  geometry_msgs::Twist base_cmd;
  base_cmd.linear.x = 0;
  base_cmd.linear.y = 0;
  base_cmd.angular.z = 0;

  while(n.ok())
  {
    int cKey = GetCh();
    if(cKey=='w')
    {
      base_cmd.linear.x += linear_vel;
      if(base_cmd.linear.x > linear_vel*k_vel)
        base_cmd.linear.x = linear_vel*k_vel;
      printf(" - linear.x= %.2f linear.y= %.2f angular.z= %.2f \n",base_cmd.linear.x,base_cmd.linear.y,base_cmd.angular.z);
    } 
    else if(cKey=='s')
    {
      base_cmd.linear.x += -linear_vel;

      if(base_cmd.linear.x < -linear_vel*k_vel)
        base_cmd.linear.x = -linear_vel*k_vel;
      printf(" - linear.x= %.2f linear.y= %.2f angular.z= %.2f \n",base_cmd.linear.x,base_cmd.linear.y,base_cmd.angular.z);
    } 
    else if(cKey=='a')
    {
      base_cmd.linear.y += linear_vel;
      if(base_cmd.linear.y > linear_vel*k_vel)
        base_cmd.linear.y = linear_vel*k_vel;
      printf(" - linear.x= %.2f linear.y= %.2f angular.z= %.2f \n",base_cmd.linear.x,base_cmd.linear.y,base_cmd.angular.z);
    }
    else if(cKey=='d')
    {
      base_cmd.linear.y += -linear_vel;
      if(base_cmd.linear.y < -linear_vel*k_vel)
        base_cmd.linear.y = -linear_vel*k_vel;
      printf(" - linear.x= %.2f linear.y= %.2f angular.z= %.2f \n",base_cmd.linear.x,base_cmd.linear.y,base_cmd.angular.z);
    } 
    else if(cKey=='q')
    {
      base_cmd.angular.z += angular_vel;
      if(base_cmd.angular.z > angular_vel*k_vel)
        base_cmd.angular.z = angular_vel*k_vel;
      printf(" - linear.x= %.2f linear.y= %.2f angular.z= %.2f \n",base_cmd.linear.x,base_cmd.linear.y,base_cmd.angular.z);
    } 
    else if(cKey=='e')
    {
      base_cmd.angular.z += -angular_vel;
      if(base_cmd.angular.z < -angular_vel*k_vel)
        base_cmd.angular.z = -angular_vel*k_vel;
      printf(" - linear.x= %.2f linear.y= %.2f angular.z= %.2f \n",base_cmd.linear.x,base_cmd.linear.y,base_cmd.angular.z);
    } 
    else if(cKey==' ')
    {
      base_cmd.linear.x = 0;
      base_cmd.linear.y = 0;
      base_cmd.angular.z = 0;
      printf(" - linear.x= %.2f linear.y= %.2f angular.z= %.2f \n",base_cmd.linear.x,base_cmd.linear.y,base_cmd.angular.z);
    } 
    else if(cKey=='x')
    {
      base_cmd.linear.x = 0;
      base_cmd.linear.y = 0;
      base_cmd.angular.z = 0;
      cmd1_vel_pub.publish(base_cmd);
      cmd2_vel_pub.publish(base_cmd);
      cmd3_vel_pub.publish(base_cmd);
      cmd4_vel_pub.publish(base_cmd);
      printf(" - linear.x= %.2f linear.y= %.2f angular.z= %.2f \n",base_cmd.linear.x,base_cmd.linear.y,base_cmd.angular.z);
      printf("退出！ \n");
      return 0;
    } 
    else if(cKey=='1' || cKey=='2'
         || cKey=='3' || cKey=='4')
    {
      ctrl_robot=cKey-'0';
      printf("当前操作机器人%d \n",ctrl_robot);
    }
    else
    {
       printf(" - 未定义指令%d \n",cKey);
    }

  switch (ctrl_robot)
  {
  case 1:
    cmd1_vel_pub.publish(base_cmd);
    break;

  case 2:
    cmd2_vel_pub.publish(base_cmd);
    break;

  case 3:
    cmd3_vel_pub.publish(base_cmd);
    break;

  case 4:
    cmd4_vel_pub.publish(base_cmd);
    break;
  
  default:
    break;
  }
    
  }
  return 0;
}
