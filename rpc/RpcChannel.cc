#include "RpcChannel.h"
#include "stdio.h"
#include <rpc/RpcClosure.h>
#include <boost/make_shared.hpp>
#include <google/protobuf/descriptor.h>
//#include <google/protobuf/Message.h>
#include <google/protobuf/stubs/callback.h>
namespace protobufrpc {


RpcChannel::RpcChannel()
{
  
}
RpcChannel::RpcChannel(const TcpConnectionPtr &conn)
    : conn_(conn), codec_(boost::make_shared<ProtobufCodec>(boost::bind(
                       &RpcChannel::onRpcMessage, this, _1, _2, _3))) {}

void RpcChannel::onMessage(const TcpConnectionPtr &conn, Buffer *buf,
                           Timestamp receiveTime) {
  codec_->onMessage(conn, buf, receiveTime);
}

void RpcChannel::CallMethod(const ::google::protobuf::MethodDescriptor *method,
                            ::google::protobuf::RpcController *controller,
                            const ::google::protobuf::Message *request,
                            ::google::protobuf::Message *response,
                            ::google::protobuf::Closure *done) {
  printf("[RpcChannel::CallMethod]method:%s\nresponse:%s\nresponse:%s\n",
         method->DebugString().c_str(), request->DebugString().c_str(),
         response->DebugString().c_str());
}

void RpcChannel::onRpcMessage(const TcpConnectionPtr &conn,
                              const MessagePtr &messagePtr,
                              Timestamp receiveTime) {
  RpcMessagePtr pRpcMsg = ::muduo::down_pointer_cast<IMRpc::RpcMessage>(messagePtr);
  printf("%s\n", (*pRpcMsg).DebugString().c_str());
  if (pRpcMsg->type() == IMRpc::MessageType::RESPONSE)
    onResponse(pRpcMsg);
  else if (pRpcMsg->type() == IMRpc::MessageType::REQUEST)
    onRequest(pRpcMsg);
  else
    printf("onRpcMessage!!!\n");
}

void RpcChannel::onRequest(const RpcMessagePtr &messagePtr) {

  auto it = services_->find(messagePtr->service());
  if (it != services_->end()) {
    google::protobuf::Service *service = it->second;
    assert(service != NULL);
    const google::protobuf::ServiceDescriptor *desc = service->GetDescriptor();
    const google::protobuf::MethodDescriptor *method =
        desc->FindMethodByName(messagePtr->method());
    assert(method);
    if (method) {
      boost::scoped_ptr<google::protobuf::Message> request(
          service->GetRequestPrototype(method).New());
      if (request->ParseFromString(messagePtr->request())) {

        google::protobuf::Message *response =service->GetResponsePrototype(method).New();
        // response is deleted in doneCallback
        int64_t id = messagePtr->id();
        google::protobuf::Closure *closure = google::protobuf::internal::NewCallback(this, &RpcChannel::doneCallback,response, id);
        service->CallMethod(
            method, NULL, get_pointer(request), response,
            closure);
        //error = NO_ERROR;

      }
    }
  }
}

void RpcChannel::onResponse(const RpcMessagePtr &messagePtr) {
  int64_t id = messagePtr->id();
  // assert(message.has_response() || message.has_error());
  OutstandingCall out = {NULL, NULL};
  {
    MutexLockGuard lock(mutex_);
    auto it = outstandings_.find(id);
    if (it != outstandings_.end()) {
      out = it->second;
      outstandings_.erase(it);
    }
  }
  if (out.response) {
    boost::scoped_ptr<google::protobuf::Message> d(out.response);
    //MessagePtr response(out.response->New());
    out.response->ParseFromString(messagePtr->response());
    if (out.done) {
      out.done->Run();
    }
  }
}
void RpcChannel::doneCallback(::google::protobuf::Message *response, int64_t id)
{
  boost::scoped_ptr<google::protobuf::Message> d(response);
  IMRpc::RpcMessage message;
  message.set_type(IMRpc::MessageType::RESPONSE);
  message.set_id(id);
  message.set_response(response->SerializeAsString()); // FIXME: error check
  codec_->send(conn_, message);
}

}
