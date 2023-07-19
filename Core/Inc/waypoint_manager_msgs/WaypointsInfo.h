#ifndef _ROS_waypoint_manager_msgs_WaypointsInfo_h
#define _ROS_waypoint_manager_msgs_WaypointsInfo_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"
#include "geometry_msgs/Pose.h"

namespace waypoint_manager_msgs
{

  class WaypointsInfo : public ros::Msg
  {
    public:
      typedef std_msgs::Header _header_type;
      _header_type header;
      typedef geometry_msgs::Pose _pose_type;
      _pose_type pose;

    WaypointsInfo():
      header(),
      pose()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const override
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      offset += this->pose.serialize(outbuffer + offset);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer) override
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      offset += this->pose.deserialize(inbuffer + offset);
     return offset;
    }

    virtual const char * getType() override { return "waypoint_manager_msgs/WaypointsInfo"; };
    virtual const char * getMD5() override { return "d3812c3cbc69362b77dc0b19b345f8f5"; };

  };

}
#endif
