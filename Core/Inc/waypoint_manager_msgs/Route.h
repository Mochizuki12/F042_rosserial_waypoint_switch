#ifndef _ROS_waypoint_manager_msgs_Route_h
#define _ROS_waypoint_manager_msgs_Route_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"

namespace waypoint_manager_msgs
{

  class Route : public ros::Msg
  {
    public:
      typedef std_msgs::Header _header_type;
      _header_type header;
      uint32_t identities_length;
      typedef char* _identities_type;
      _identities_type st_identities;
      _identities_type * identities;

    Route():
      header(),
      identities_length(0), st_identities(), identities(nullptr)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const override
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      *(outbuffer + offset + 0) = (this->identities_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->identities_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->identities_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->identities_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->identities_length);
      for( uint32_t i = 0; i < identities_length; i++){
      uint32_t length_identitiesi = strlen(this->identities[i]);
      varToArr(outbuffer + offset, length_identitiesi);
      offset += 4;
      memcpy(outbuffer + offset, this->identities[i], length_identitiesi);
      offset += length_identitiesi;
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer) override
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      uint32_t identities_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      identities_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      identities_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      identities_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->identities_length);
      if(identities_lengthT > identities_length)
        this->identities = (char**)realloc(this->identities, identities_lengthT * sizeof(char*));
      identities_length = identities_lengthT;
      for( uint32_t i = 0; i < identities_length; i++){
      uint32_t length_st_identities;
      arrToVar(length_st_identities, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_st_identities; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_st_identities-1]=0;
      this->st_identities = (char *)(inbuffer + offset-1);
      offset += length_st_identities;
        memcpy( &(this->identities[i]), &(this->st_identities), sizeof(char*));
      }
     return offset;
    }

    virtual const char * getType() override { return "waypoint_manager_msgs/Route"; };
    virtual const char * getMD5() override { return "ae973d1ed4497eea7a8984d7f7387c2e"; };

  };

}
#endif
