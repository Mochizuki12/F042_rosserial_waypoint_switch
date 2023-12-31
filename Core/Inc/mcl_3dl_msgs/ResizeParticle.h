#ifndef _ROS_SERVICE_ResizeParticle_h
#define _ROS_SERVICE_ResizeParticle_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace mcl_3dl_msgs
{

static const char RESIZEPARTICLE[] = "mcl_3dl_msgs/ResizeParticle";

  class ResizeParticleRequest : public ros::Msg
  {
    public:
      typedef int32_t _size_type;
      _size_type size;

    ResizeParticleRequest():
      size(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const override
    {
      int offset = 0;
      union {
        int32_t real;
        uint32_t base;
      } u_size;
      u_size.real = this->size;
      *(outbuffer + offset + 0) = (u_size.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_size.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_size.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_size.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->size);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer) override
    {
      int offset = 0;
      union {
        int32_t real;
        uint32_t base;
      } u_size;
      u_size.base = 0;
      u_size.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_size.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_size.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_size.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->size = u_size.real;
      offset += sizeof(this->size);
     return offset;
    }

    virtual const char * getType() override { return RESIZEPARTICLE; };
    virtual const char * getMD5() override { return "97da5de9999c5ce84f539773c8d0b2a3"; };

  };

  class ResizeParticleResponse : public ros::Msg
  {
    public:

    ResizeParticleResponse()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const override
    {
      int offset = 0;
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer) override
    {
      int offset = 0;
     return offset;
    }

    virtual const char * getType() override { return RESIZEPARTICLE; };
    virtual const char * getMD5() override { return "d41d8cd98f00b204e9800998ecf8427e"; };

  };

  class ResizeParticle {
    public:
    typedef ResizeParticleRequest Request;
    typedef ResizeParticleResponse Response;
  };

}
#endif
