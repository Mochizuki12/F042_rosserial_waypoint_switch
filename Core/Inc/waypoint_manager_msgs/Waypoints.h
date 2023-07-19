#ifndef _ROS_waypoint_manager_msgs_Waypoints_h
#define _ROS_waypoint_manager_msgs_Waypoints_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "waypoint_manager_msgs/WaypointsInfo.h"
#include "waypoint_manager_msgs/Waypoint.h"

namespace waypoint_manager_msgs
{

  class Waypoints : public ros::Msg
  {
    public:
      typedef waypoint_manager_msgs::WaypointsInfo _info_type;
      _info_type info;
      uint32_t waypoints_length;
      typedef waypoint_manager_msgs::Waypoint _waypoints_type;
      _waypoints_type st_waypoints;
      _waypoints_type * waypoints;

    Waypoints():
      info(),
      waypoints_length(0), st_waypoints(), waypoints(nullptr)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const override
    {
      int offset = 0;
      offset += this->info.serialize(outbuffer + offset);
      *(outbuffer + offset + 0) = (this->waypoints_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->waypoints_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->waypoints_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->waypoints_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->waypoints_length);
      for( uint32_t i = 0; i < waypoints_length; i++){
      offset += this->waypoints[i].serialize(outbuffer + offset);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer) override
    {
      int offset = 0;
      offset += this->info.deserialize(inbuffer + offset);
      uint32_t waypoints_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      waypoints_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      waypoints_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      waypoints_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->waypoints_length);
      if(waypoints_lengthT > waypoints_length)
        this->waypoints = (waypoint_manager_msgs::Waypoint*)realloc(this->waypoints, waypoints_lengthT * sizeof(waypoint_manager_msgs::Waypoint));
      waypoints_length = waypoints_lengthT;
      for( uint32_t i = 0; i < waypoints_length; i++){
      offset += this->st_waypoints.deserialize(inbuffer + offset);
        memcpy( &(this->waypoints[i]), &(this->st_waypoints), sizeof(waypoint_manager_msgs::Waypoint));
      }
     return offset;
    }

    virtual const char * getType() override { return "waypoint_manager_msgs/Waypoints"; };
    virtual const char * getMD5() override { return "2b66034a100075d3ed374cef442c23fc"; };

  };

}
#endif
