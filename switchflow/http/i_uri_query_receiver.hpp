//
// Copyright 2003-2006 Christopher Baus. http://baus.net/
// Read the LICENSE file for more information.

#ifndef SF_URI_QUERY_RECEIVER_HPP
#define SF_URI_QUERY_RECEIVER_HPP

#include <boost/asio.hpp>

namespace switchflow{
namespace http{

class i_uri_query_receiver
{
 public:
  virtual STATUS key(boost::asio::const_buffer buffer, bool complete) = 0;
  virtual STATUS value(boost::asio::const_buffer buffer, bool complete) = 0;
};

} // namespace httplib
} // namespace switchflow
#endif
