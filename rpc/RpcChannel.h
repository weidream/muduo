// Copyright 2010, Shuo Chen.  All rights reserved.
// http://code.google.com/p/muduo/
//
// Use of this source code is governed by a BSD-style license
// that can be found in the License file.

// Author: Shuo Chen (chenshuo at chenshuo dot com)
//
// This is a public header file, it must only include public header files.

#ifndef _IMMUDUO_RPC_RPCCHANNEL_H
#define _IMMUDUO_RPC_RPCCHANNEL_H

#include <IMRpc.pb.h>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <codec/codec.h>
#include <google/protobuf/service.h>
#include <map>
#include <muduo/base/Atomic.h>
#include <muduo/base/Mutex.h>
#include <muduo/net/TcpServer.h>
// Service and RpcChannel classes are incorporated from
// google/protobuf/service.h

namespace google {
namespace protobuf {
// Defined in other files.
class Descriptor;        // descriptor.h
class ServiceDescriptor; // descriptor.h
class MethodDescriptor;  // descriptor.h
class Message;           // message.h
class Closure;
class RpcController;
class Service;
class ProtobufCodec;
// class RpcMessage;
} // namespace protobuf
} // namespace google

// class IMRpc::RpcMessage;

using namespace muduo;
using namespace muduo::net;

// typedef boost::shared_ptr<::google::protobuf::RpcMessage> RpcMessagePtr;
namespace protobufrpc {

// Abstract interface for an RPC channel.  An RpcChannel represents a
// communication line to a Service which can be used to call that Service's
// methods.  The Service may be running on another machine.  Normally, you
// should not call an RpcChannel directly, but instead construct a stub Service
// wrapping it.  Example:
// FIXME: update here
//   RpcChannel* channel = new MyRpcChannel("remotehost.example.com:1234");
//   MyService* service = new MyService::Stub(channel);
//   service->MyMethod(request, &response, callback);
typedef boost::shared_ptr<IMRpc::RpcMessage> RpcMessagePtr;

class RpcChannel : public ::google::protobuf::RpcChannel {
public:
  RpcChannel();

  explicit RpcChannel(const TcpConnectionPtr &conn);

  virtual ~RpcChannel(){}

  void setConnection(const TcpConnectionPtr &conn) { conn_ = conn; }

  void setServices(
      const std::map<std::string, ::google::protobuf::Service *> *services) {
    services_ = services;
  }

  // Call the given method of the remote service.  The signature of this
  // procedure looks the same as Service::CallMethod(), but the requirements
  // are less strict in one important way:  the request and response objects
  // need not be of any specific class as long as their descriptors are
  // method->input_type() and method->output_type().
  void CallMethod(const ::google::protobuf::MethodDescriptor *method,
                  ::google::protobuf::RpcController *controller,
                  const ::google::protobuf::Message *request,
                  ::google::protobuf::Message *response,
                  ::google::protobuf::Closure *done);

  void onMessage(const TcpConnectionPtr &conn, Buffer *buf,
                 Timestamp receiveTime);
  void onRpcMessage(const TcpConnectionPtr &conn,
                    const MessagePtr &messagePtr, Timestamp receiveTime);

private:
  void onRequest(const RpcMessagePtr &messagePtr);
  void onResponse(const RpcMessagePtr &messagePtr);
  void doneCallback(::google::protobuf::Message *response, int64_t id);
  struct OutstandingCall {
    ::google::protobuf::Message *response;
    ::google::protobuf::Closure *done;
  };

  muduo::net::TcpConnectionPtr conn_;
  ProtobufCodecPtr codec_;
  AtomicInt64 id_;
  muduo::MutexLock mutex_;
  std::map<int64_t, OutstandingCall> outstandings_;
  const std::map<std::string, ::google::protobuf::Service *> *services_;
};

typedef boost::shared_ptr<RpcChannel> RpcChannelPtr;
}

#endif // MUDUO_NET_PROTORPC_RPCCHANNEL_H
