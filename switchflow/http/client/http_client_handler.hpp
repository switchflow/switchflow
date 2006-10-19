#ifndef HTTP_CLIENT_HANDLERS_H__
#define HTTP_CLIENT_HANDLERS_H__

#include <errno.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <openssl/sha.h>

#include <memory>
#include <list>
#include <string>

#include <boost/noncopyable.hpp>

#include <socketlib/status.hpp>
#include <socketlib/connection.hpp>
#include <util/read_write_buffer.hpp>
#include <http/url.hpp>
#include <http/header_parser.hpp>
#include <http/body_parser.hpp>
#include <http/header_pusher.hpp>
#include <http/header_handler.hpp>

#include <util/PessimisticMemoryManager.h>
#include <util/read_write_buffer.hpp>

#include <client/i_client.hpp>




class urlsucker;
class feed_writer;
class crawl_request;
class i_http_client;


// http_client_handler handles notifications client proxy connections.  It maintains
// the state of the client socket handles.  
//
class http_client_handler: public http::i_body_receiver,
                           public i_client
{
 public:
  http_client_handler();

  http_client_handler(std::auto_ptr<i_http_client> p_http_client,
                      http::header_cache& cache);

  //
  // copy construction
  //
  // Copy contruction is used by the memory management system.    
  http_client_handler(const http_client_handler& rhs);
  

  virtual ~http_client_handler();
  
  void shutdown();

  void dns_failed();
  
  socketlib::STATUS handle_stream(socketlib::connection& socket);
  

  http::STATUS set_body(read_write_buffer& body, bool bComplete);
  void set_body_encoding(http::BODY_ENCODING bodyEncoding);
  http::STATUS forward_chunk_size();
  http::STATUS forward_chunk_trailer();
  void set_chunk_size(unsigned int chunkSize);

  bool get_header_value(const char* header_name, std::string& header_value);
  
  void timeout();
  void connect_failed();

  void connect(socketlib::connection& conn);

private:
  
  
  http::header_pusher header_pusher_;
  

  enum MESSAGE_STATE
  {
    PUSH_HEADER,
    PUSH_BODY,
    PARSE_RESPONSE_HEADER,
    PARSE_BODY
  };

  read_write_buffer m_endlineBuf;
  MESSAGE_STATE m_messageState;
  http::header_handler header_handler_;
  http::HTTPHeaderParser m_headerParser;
  http::BodyParser m_bodyParser;

  std::auto_ptr<i_http_client> p_http_client_;
  
};

#endif