//
// Copyright 2003-2006 Christopher Baus. http://baus.net/
// Read the LICENSE file for more information.

#include "i_connection_handler.hpp"

namespace serverlib{

void i_connection_handler::reset(int clientfd)
{
  client_event_.set(clientfd, this);
  socket_data_.fd(clientfd);
  socket_data_.state(socketlib::connection::CONNECTED);
}

} // namespace
