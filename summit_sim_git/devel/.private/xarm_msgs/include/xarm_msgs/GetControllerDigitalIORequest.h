// Generated by gencpp from file xarm_msgs/GetControllerDigitalIORequest.msg
// DO NOT EDIT!


#ifndef XARM_MSGS_MESSAGE_GETCONTROLLERDIGITALIOREQUEST_H
#define XARM_MSGS_MESSAGE_GETCONTROLLERDIGITALIOREQUEST_H


#include <string>
#include <vector>
#include <memory>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>


namespace xarm_msgs
{
template <class ContainerAllocator>
struct GetControllerDigitalIORequest_
{
  typedef GetControllerDigitalIORequest_<ContainerAllocator> Type;

  GetControllerDigitalIORequest_()
    : io_num(0)  {
    }
  GetControllerDigitalIORequest_(const ContainerAllocator& _alloc)
    : io_num(0)  {
  (void)_alloc;
    }



   typedef int16_t _io_num_type;
  _io_num_type io_num;





  typedef boost::shared_ptr< ::xarm_msgs::GetControllerDigitalIORequest_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::xarm_msgs::GetControllerDigitalIORequest_<ContainerAllocator> const> ConstPtr;

}; // struct GetControllerDigitalIORequest_

typedef ::xarm_msgs::GetControllerDigitalIORequest_<std::allocator<void> > GetControllerDigitalIORequest;

typedef boost::shared_ptr< ::xarm_msgs::GetControllerDigitalIORequest > GetControllerDigitalIORequestPtr;
typedef boost::shared_ptr< ::xarm_msgs::GetControllerDigitalIORequest const> GetControllerDigitalIORequestConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::xarm_msgs::GetControllerDigitalIORequest_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::xarm_msgs::GetControllerDigitalIORequest_<ContainerAllocator> >::stream(s, "", v);
return s;
}


template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator==(const ::xarm_msgs::GetControllerDigitalIORequest_<ContainerAllocator1> & lhs, const ::xarm_msgs::GetControllerDigitalIORequest_<ContainerAllocator2> & rhs)
{
  return lhs.io_num == rhs.io_num;
}

template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator!=(const ::xarm_msgs::GetControllerDigitalIORequest_<ContainerAllocator1> & lhs, const ::xarm_msgs::GetControllerDigitalIORequest_<ContainerAllocator2> & rhs)
{
  return !(lhs == rhs);
}


} // namespace xarm_msgs

namespace ros
{
namespace message_traits
{





template <class ContainerAllocator>
struct IsMessage< ::xarm_msgs::GetControllerDigitalIORequest_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::xarm_msgs::GetControllerDigitalIORequest_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::xarm_msgs::GetControllerDigitalIORequest_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::xarm_msgs::GetControllerDigitalIORequest_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::xarm_msgs::GetControllerDigitalIORequest_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::xarm_msgs::GetControllerDigitalIORequest_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::xarm_msgs::GetControllerDigitalIORequest_<ContainerAllocator> >
{
  static const char* value()
  {
    return "3d30b3ebd5a1d172f02950e37a7469f3";
  }

  static const char* value(const ::xarm_msgs::GetControllerDigitalIORequest_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x3d30b3ebd5a1d172ULL;
  static const uint64_t static_value2 = 0xf02950e37a7469f3ULL;
};

template<class ContainerAllocator>
struct DataType< ::xarm_msgs::GetControllerDigitalIORequest_<ContainerAllocator> >
{
  static const char* value()
  {
    return "xarm_msgs/GetControllerDigitalIORequest";
  }

  static const char* value(const ::xarm_msgs::GetControllerDigitalIORequest_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::xarm_msgs::GetControllerDigitalIORequest_<ContainerAllocator> >
{
  static const char* value()
  {
    return "# Getting the controller DIGITAL input port status, io_num: from 1 to 8\n"
"\n"
"int16 io_num\n"
"\n"
;
  }

  static const char* value(const ::xarm_msgs::GetControllerDigitalIORequest_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::xarm_msgs::GetControllerDigitalIORequest_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.io_num);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct GetControllerDigitalIORequest_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::xarm_msgs::GetControllerDigitalIORequest_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::xarm_msgs::GetControllerDigitalIORequest_<ContainerAllocator>& v)
  {
    s << indent << "io_num: ";
    Printer<int16_t>::stream(s, indent + "  ", v.io_num);
  }
};

} // namespace message_operations
} // namespace ros

#endif // XARM_MSGS_MESSAGE_GETCONTROLLERDIGITALIOREQUEST_H
