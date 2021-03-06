// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: rpc.proto

#ifndef PROTOBUF_rpc_2eproto__INCLUDED
#define PROTOBUF_rpc_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 3000000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 3000000 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/metadata.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/generated_enum_reflection.h>
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)

namespace IMRpc {

// Internal implementation detail -- do not call these.
void protobuf_AddDesc_rpc_2eproto();
void protobuf_AssignDesc_rpc_2eproto();
void protobuf_ShutdownFile_rpc_2eproto();

class RpcMessage;

enum MessageType {
  REQUEST = 0,
  RESPONSE = 1,
  ERROR = 2,
  MessageType_INT_MIN_SENTINEL_DO_NOT_USE_ = ::google::protobuf::kint32min,
  MessageType_INT_MAX_SENTINEL_DO_NOT_USE_ = ::google::protobuf::kint32max
};
bool MessageType_IsValid(int value);
const MessageType MessageType_MIN = REQUEST;
const MessageType MessageType_MAX = ERROR;
const int MessageType_ARRAYSIZE = MessageType_MAX + 1;

const ::google::protobuf::EnumDescriptor* MessageType_descriptor();
inline const ::std::string& MessageType_Name(MessageType value) {
  return ::google::protobuf::internal::NameOfEnum(
    MessageType_descriptor(), value);
}
inline bool MessageType_Parse(
    const ::std::string& name, MessageType* value) {
  return ::google::protobuf::internal::ParseNamedEnum<MessageType>(
    MessageType_descriptor(), name, value);
}
enum ErrorCode {
  NO_ERROR = 0,
  WRONG_PROTO = 1,
  NO_SERVICE = 2,
  NO_METHOD = 3,
  INVALID_REQUEST = 4,
  INVALID_RESPONSE = 5,
  TIMEOUT = 6,
  ErrorCode_INT_MIN_SENTINEL_DO_NOT_USE_ = ::google::protobuf::kint32min,
  ErrorCode_INT_MAX_SENTINEL_DO_NOT_USE_ = ::google::protobuf::kint32max
};
bool ErrorCode_IsValid(int value);
const ErrorCode ErrorCode_MIN = NO_ERROR;
const ErrorCode ErrorCode_MAX = TIMEOUT;
const int ErrorCode_ARRAYSIZE = ErrorCode_MAX + 1;

const ::google::protobuf::EnumDescriptor* ErrorCode_descriptor();
inline const ::std::string& ErrorCode_Name(ErrorCode value) {
  return ::google::protobuf::internal::NameOfEnum(
    ErrorCode_descriptor(), value);
}
inline bool ErrorCode_Parse(
    const ::std::string& name, ErrorCode* value) {
  return ::google::protobuf::internal::ParseNamedEnum<ErrorCode>(
    ErrorCode_descriptor(), name, value);
}
// ===================================================================

class RpcMessage : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:IMRpc.RpcMessage) */ {
 public:
  RpcMessage();
  virtual ~RpcMessage();

  RpcMessage(const RpcMessage& from);

  inline RpcMessage& operator=(const RpcMessage& from) {
    CopyFrom(from);
    return *this;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const RpcMessage& default_instance();

  void Swap(RpcMessage* other);

  // implements Message ----------------------------------------------

  inline RpcMessage* New() const { return New(NULL); }

  RpcMessage* New(::google::protobuf::Arena* arena) const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const RpcMessage& from);
  void MergeFrom(const RpcMessage& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const {
    return InternalSerializeWithCachedSizesToArray(false, output);
  }
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  void InternalSwap(RpcMessage* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return _internal_metadata_.arena();
  }
  inline void* MaybeArenaPtr() const {
    return _internal_metadata_.raw_arena_ptr();
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // optional .IMRpc.MessageType type = 1;
  void clear_type();
  static const int kTypeFieldNumber = 1;
  ::IMRpc::MessageType type() const;
  void set_type(::IMRpc::MessageType value);

  // optional fixed64 id = 2;
  void clear_id();
  static const int kIdFieldNumber = 2;
  ::google::protobuf::uint64 id() const;
  void set_id(::google::protobuf::uint64 value);

  // optional string service = 3;
  void clear_service();
  static const int kServiceFieldNumber = 3;
  const ::std::string& service() const;
  void set_service(const ::std::string& value);
  void set_service(const char* value);
  void set_service(const char* value, size_t size);
  ::std::string* mutable_service();
  ::std::string* release_service();
  void set_allocated_service(::std::string* service);

  // optional string method = 4;
  void clear_method();
  static const int kMethodFieldNumber = 4;
  const ::std::string& method() const;
  void set_method(const ::std::string& value);
  void set_method(const char* value);
  void set_method(const char* value, size_t size);
  ::std::string* mutable_method();
  ::std::string* release_method();
  void set_allocated_method(::std::string* method);

  // optional bytes request = 5;
  void clear_request();
  static const int kRequestFieldNumber = 5;
  const ::std::string& request() const;
  void set_request(const ::std::string& value);
  void set_request(const char* value);
  void set_request(const void* value, size_t size);
  ::std::string* mutable_request();
  ::std::string* release_request();
  void set_allocated_request(::std::string* request);

  // optional bytes response = 6;
  void clear_response();
  static const int kResponseFieldNumber = 6;
  const ::std::string& response() const;
  void set_response(const ::std::string& value);
  void set_response(const char* value);
  void set_response(const void* value, size_t size);
  ::std::string* mutable_response();
  ::std::string* release_response();
  void set_allocated_response(::std::string* response);

  // optional .IMRpc.ErrorCode error = 7;
  void clear_error();
  static const int kErrorFieldNumber = 7;
  ::IMRpc::ErrorCode error() const;
  void set_error(::IMRpc::ErrorCode value);

  // @@protoc_insertion_point(class_scope:IMRpc.RpcMessage)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  bool _is_default_instance_;
  ::google::protobuf::uint64 id_;
  ::google::protobuf::internal::ArenaStringPtr service_;
  ::google::protobuf::internal::ArenaStringPtr method_;
  int type_;
  int error_;
  ::google::protobuf::internal::ArenaStringPtr request_;
  ::google::protobuf::internal::ArenaStringPtr response_;
  mutable int _cached_size_;
  friend void  protobuf_AddDesc_rpc_2eproto();
  friend void protobuf_AssignDesc_rpc_2eproto();
  friend void protobuf_ShutdownFile_rpc_2eproto();

  void InitAsDefaultInstance();
  static RpcMessage* default_instance_;
};
// ===================================================================


// ===================================================================

#if !PROTOBUF_INLINE_NOT_IN_HEADERS
// RpcMessage

// optional .IMRpc.MessageType type = 1;
inline void RpcMessage::clear_type() {
  type_ = 0;
}
inline ::IMRpc::MessageType RpcMessage::type() const {
  // @@protoc_insertion_point(field_get:IMRpc.RpcMessage.type)
  return static_cast< ::IMRpc::MessageType >(type_);
}
inline void RpcMessage::set_type(::IMRpc::MessageType value) {
  
  type_ = value;
  // @@protoc_insertion_point(field_set:IMRpc.RpcMessage.type)
}

// optional fixed64 id = 2;
inline void RpcMessage::clear_id() {
  id_ = GOOGLE_ULONGLONG(0);
}
inline ::google::protobuf::uint64 RpcMessage::id() const {
  // @@protoc_insertion_point(field_get:IMRpc.RpcMessage.id)
  return id_;
}
inline void RpcMessage::set_id(::google::protobuf::uint64 value) {
  
  id_ = value;
  // @@protoc_insertion_point(field_set:IMRpc.RpcMessage.id)
}

// optional string service = 3;
inline void RpcMessage::clear_service() {
  service_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& RpcMessage::service() const {
  // @@protoc_insertion_point(field_get:IMRpc.RpcMessage.service)
  return service_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void RpcMessage::set_service(const ::std::string& value) {
  
  service_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:IMRpc.RpcMessage.service)
}
inline void RpcMessage::set_service(const char* value) {
  
  service_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:IMRpc.RpcMessage.service)
}
inline void RpcMessage::set_service(const char* value, size_t size) {
  
  service_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:IMRpc.RpcMessage.service)
}
inline ::std::string* RpcMessage::mutable_service() {
  
  // @@protoc_insertion_point(field_mutable:IMRpc.RpcMessage.service)
  return service_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* RpcMessage::release_service() {
  // @@protoc_insertion_point(field_release:IMRpc.RpcMessage.service)
  
  return service_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void RpcMessage::set_allocated_service(::std::string* service) {
  if (service != NULL) {
    
  } else {
    
  }
  service_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), service);
  // @@protoc_insertion_point(field_set_allocated:IMRpc.RpcMessage.service)
}

// optional string method = 4;
inline void RpcMessage::clear_method() {
  method_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& RpcMessage::method() const {
  // @@protoc_insertion_point(field_get:IMRpc.RpcMessage.method)
  return method_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void RpcMessage::set_method(const ::std::string& value) {
  
  method_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:IMRpc.RpcMessage.method)
}
inline void RpcMessage::set_method(const char* value) {
  
  method_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:IMRpc.RpcMessage.method)
}
inline void RpcMessage::set_method(const char* value, size_t size) {
  
  method_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:IMRpc.RpcMessage.method)
}
inline ::std::string* RpcMessage::mutable_method() {
  
  // @@protoc_insertion_point(field_mutable:IMRpc.RpcMessage.method)
  return method_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* RpcMessage::release_method() {
  // @@protoc_insertion_point(field_release:IMRpc.RpcMessage.method)
  
  return method_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void RpcMessage::set_allocated_method(::std::string* method) {
  if (method != NULL) {
    
  } else {
    
  }
  method_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), method);
  // @@protoc_insertion_point(field_set_allocated:IMRpc.RpcMessage.method)
}

// optional bytes request = 5;
inline void RpcMessage::clear_request() {
  request_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& RpcMessage::request() const {
  // @@protoc_insertion_point(field_get:IMRpc.RpcMessage.request)
  return request_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void RpcMessage::set_request(const ::std::string& value) {
  
  request_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:IMRpc.RpcMessage.request)
}
inline void RpcMessage::set_request(const char* value) {
  
  request_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:IMRpc.RpcMessage.request)
}
inline void RpcMessage::set_request(const void* value, size_t size) {
  
  request_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:IMRpc.RpcMessage.request)
}
inline ::std::string* RpcMessage::mutable_request() {
  
  // @@protoc_insertion_point(field_mutable:IMRpc.RpcMessage.request)
  return request_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* RpcMessage::release_request() {
  // @@protoc_insertion_point(field_release:IMRpc.RpcMessage.request)
  
  return request_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void RpcMessage::set_allocated_request(::std::string* request) {
  if (request != NULL) {
    
  } else {
    
  }
  request_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), request);
  // @@protoc_insertion_point(field_set_allocated:IMRpc.RpcMessage.request)
}

// optional bytes response = 6;
inline void RpcMessage::clear_response() {
  response_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& RpcMessage::response() const {
  // @@protoc_insertion_point(field_get:IMRpc.RpcMessage.response)
  return response_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void RpcMessage::set_response(const ::std::string& value) {
  
  response_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:IMRpc.RpcMessage.response)
}
inline void RpcMessage::set_response(const char* value) {
  
  response_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:IMRpc.RpcMessage.response)
}
inline void RpcMessage::set_response(const void* value, size_t size) {
  
  response_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:IMRpc.RpcMessage.response)
}
inline ::std::string* RpcMessage::mutable_response() {
  
  // @@protoc_insertion_point(field_mutable:IMRpc.RpcMessage.response)
  return response_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* RpcMessage::release_response() {
  // @@protoc_insertion_point(field_release:IMRpc.RpcMessage.response)
  
  return response_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void RpcMessage::set_allocated_response(::std::string* response) {
  if (response != NULL) {
    
  } else {
    
  }
  response_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), response);
  // @@protoc_insertion_point(field_set_allocated:IMRpc.RpcMessage.response)
}

// optional .IMRpc.ErrorCode error = 7;
inline void RpcMessage::clear_error() {
  error_ = 0;
}
inline ::IMRpc::ErrorCode RpcMessage::error() const {
  // @@protoc_insertion_point(field_get:IMRpc.RpcMessage.error)
  return static_cast< ::IMRpc::ErrorCode >(error_);
}
inline void RpcMessage::set_error(::IMRpc::ErrorCode value) {
  
  error_ = value;
  // @@protoc_insertion_point(field_set:IMRpc.RpcMessage.error)
}

#endif  // !PROTOBUF_INLINE_NOT_IN_HEADERS

// @@protoc_insertion_point(namespace_scope)

}  // namespace IMRpc

#ifndef SWIG
namespace google {
namespace protobuf {

template <> struct is_proto_enum< ::IMRpc::MessageType> : ::google::protobuf::internal::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::IMRpc::MessageType>() {
  return ::IMRpc::MessageType_descriptor();
}
template <> struct is_proto_enum< ::IMRpc::ErrorCode> : ::google::protobuf::internal::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::IMRpc::ErrorCode>() {
  return ::IMRpc::ErrorCode_descriptor();
}

}  // namespace protobuf
}  // namespace google
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_rpc_2eproto__INCLUDED
