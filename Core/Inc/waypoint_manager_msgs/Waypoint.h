#ifndef _ROS_waypoint_manager_msgs_Waypoint_h
#define _ROS_waypoint_manager_msgs_Waypoint_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "geometry_msgs/Pose.h"
#include "waypoint_manager_msgs/Property.h"

namespace waypoint_manager_msgs
{

  class Waypoint : public ros::Msg
  {
    public:
      typedef const char* _identity_type;
      _identity_type identity;
      typedef geometry_msgs::Pose _pose_type;
      _pose_type pose;
      uint32_t properties_length;
      typedef waypoint_manager_msgs::Property _properties_type;
      _properties_type st_properties;
      _properties_type * properties;

    Waypoint():
      identity(""),
      pose(),
      properties_length(0), st_properties(), properties(nullptr)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const override
    {
      int offset = 0;
      uint32_t length_identity = strlen(this->identity);
      varToArr(outbuffer + offset, length_identity);
      offset += 4;
      memcpy(outbuffer + offset, this->identity, length_identity);
      offset += length_identity;
      offset += this->pose.serialize(outbuffer + offset);
      *(outbuffer + offset + 0) = (this->properties_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->properties_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->properties_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->properties_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->properties_length);
      for( uint32_t i = 0; i < properties_length; i++){
      offset += this->properties[i].serialize(outbuffer + offset);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer) override
    {
      int offset = 0;
      uint32_t length_identity;
      arrToVar(length_identity, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_identity; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_identity-1]=0;
      this->identity = (char *)(inbuffer + offset-1);
      offset += length_identity;
      offset += this->pose.deserialize(inbuffer + offset);
      uint32_t properties_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      properties_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      properties_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      properties_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->properties_length);
      if(properties_lengthT > properties_length)
        this->properties = (waypoint_manager_msgs::Property*)realloc(this->properties, properties_lengthT * sizeof(waypoint_manager_msgs::Property));
      properties_length = properties_lengthT;
      for( uint32_t i = 0; i < properties_length; i++){
      offset += this->st_properties.deserialize(inbuffer + offset);
        memcpy( &(this->properties[i]), &(this->st_properties), sizeof(waypoint_manager_msgs::Property));
      }
     return offset;
    }

    virtual const char * getType() override { return "waypoint_manager_msgs/Waypoint"; };
    virtual const char * getMD5() override { return "93ac2b766c4b5929ef9030723517df3c"; };

  };

}
#endif
