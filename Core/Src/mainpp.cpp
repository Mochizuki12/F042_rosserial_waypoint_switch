/*
 * main.cpp

 *
 *  Created on: 2018/01/17
 *      Author: yoneken
 */
#include <mainpp.h>
#include <ros.h>
#include <std_msgs/String.h>
#include <main.h>
#include <std_srvs/Trigger.h>

ros::NodeHandle nh;

ros::ServiceClient<std_srvs::Trigger::Request, std_srvs::Trigger::Response> next_waypoint_client("waypoint_manager/waypoint_server/next_waypoint");

/*//debug
std_msgs::String str_msg;
ros::Publisher chatter("chatter", &str_msg);
char hello[] = "Hello world!";
*/
bool button_push_continue = false;

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart){
  nh.getHardware()->flush();
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
  nh.getHardware()->reset_rbuf();
}

void setup(void)
{
  nh.initNode();
  nh.serviceClient(next_waypoint_client);

  /*//debug
  nh.advertise(chatter);
  */
}

void loop(void)
{
  std_srvs::Trigger::Request req;
  std_srvs::Trigger::Response res;

  if((HAL_GPIO_ReadPin(Button_GPIO_Port, GPIO_PIN_3) == GPIO_PIN_SET) && (button_push_continue == false)){
	  next_waypoint_client.call(req, res);
	  if(res.success){
	    nh.loginfo("call serial next SW");
	  }
	  button_push_continue = true;
  }
  else if(HAL_GPIO_ReadPin(Button_GPIO_Port, GPIO_PIN_3) == GPIO_PIN_RESET){
	  button_push_continue = false;
  }
  /*//debug
  str_msg.data = hello;
  chatter.publish(&str_msg);
  */
  nh.spinOnce();

  HAL_Delay(6);
}

