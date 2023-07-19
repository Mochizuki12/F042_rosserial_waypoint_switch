#ifndef _ROS_waypoint_manager_msgs_WaypointStamped_h
#define _ROS_waypoint_manager_msgs_WaypointStamped_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"
#include "waypoint_manager_msgs/Waypoint.h"

namespace waypoint_manager_msgs
{

  class WaypointStamped : public ros::Msg
  {
    public:
      typedef std_msgs::Header _header_type;
      _header_type header;
      typedef waypoint_manager_msgs::Waypoint _waypoint_type;
      _waypoint_type waypoint;

    WaypointStamped():
      header(),
      waypoint()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const override
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      offset += this->waypoint.serialize(outbuffer + offset);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer) override
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      offset += this->waypoint.deserialize(inbuffer + offset);
     return offset;
    }

    virtual const char * getType() override { return "waypoint_manager_msgs/WaypointStamped"; };
    virtual const char * getMD5() override { return "73ca0ed60527a7795f31a4e153735331"; };

  };

}
#endif
