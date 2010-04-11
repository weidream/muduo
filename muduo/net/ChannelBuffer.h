// Copyright 2010, Shuo Chen.  All rights reserved.
// http://code.google.com/p/muduo/
//
// Use of this source code is governed by a BSD-style license
// that can be found in the License file.

// Author: Shuo Chen (chenshuo at chenshuo dot com)
//
// This is a public header file, it must only include public header files.

#ifndef MUDUO_NET_CHANNELBUFFER_H
#define MUDUO_NET_CHANNELBUFFER_H

#include <muduo/base/copyable.h>
#include <muduo/base/Types.h>

#include <vector>

#include <assert.h>
//#include <unistd.h>  // ssize_t

namespace muduo
{
namespace net
{

/// A buffer class modeled after org.jboss.netty.buffer.ChannelBuffer
///
/// @code
/// +-------------------+------------------+------------------+
/// | prependable bytes |  readable bytes  |  writable bytes  |
/// |                   |     (CONTENT)    |                  |
/// +-------------------+------------------+------------------+
/// |                   |                  |                  |
/// 0      <=      readerIndex   <=   writerIndex    <=     size
/// @endcode
class ChannelBuffer : public muduo::copyable
{
 public:
  static const size_t kCheapPrepend = 8;
  static const size_t kInitialSize = 1024;

  ChannelBuffer()
    : buffer_(kCheapPrepend + kInitialSize),
      readerIndex_(kCheapPrepend),
      writerIndex_(kCheapPrepend)
  {
    assert(readableBytes() == 0);
    assert(writableBytes() == kInitialSize);
    assert(prependableBytes() == kCheapPrepend);
  }

  // default copy-ctor, dtor and assignment are fine

  void swap(ChannelBuffer& rhs)
  {
    buffer_.swap(rhs.buffer_);
    std::swap(readerIndex_, rhs.readerIndex_);
    std::swap(writerIndex_, rhs.writerIndex_);
  }

  size_t readableBytes()
  { return writerIndex_ - readerIndex_; }

  size_t writableBytes()
  { return buffer_.size() - writerIndex_; }

  size_t prependableBytes()
  { return readerIndex_; }

  const char* peek() const
  { return begin() + readerIndex_; }

  // retrieve returns void, to prevent
  // string str(retrieve(readableBytes()), readableBytes());
  // the evaluation of two functions are unspecified
  void retrieve(size_t len)
  {
    assert(len <= readableBytes());
    readerIndex_ += len;
  }

  void retrieveAll()
  {
    readerIndex_ = kCheapPrepend;
    writerIndex_ = kCheapPrepend;
  }

  string retrieveAsString()
  {
    string str(peek(), readableBytes());
    readerIndex_ = kCheapPrepend;
    writerIndex_ = kCheapPrepend;
    return str;
  }

  void append(const char* /*restrict*/ data, size_t len)
  {
    if (writableBytes() < len)
    {
      makeSpace(len);
    }
    assert(len <= writableBytes());
    std::copy(data, data+len, begin()+writerIndex_);
    writerIndex_ += len;
  }

  void prepend(const char* /*restrict*/ data, size_t len)
  {
    assert(len <= prependableBytes());
    readerIndex_ -= len;
    std::copy(data, data+len, begin()+readerIndex_);
  }

  void shrink(size_t reserve)
  {
   std::vector<char> buf(kCheapPrepend+readableBytes()+reserve);
   std::copy(peek(), peek()+readableBytes(), buf.begin()+kCheapPrepend);
   buf.swap(buffer_);
  }

  /// Read data directly into buffer.
  ///
  /// It may implement with readv(2)
  /// @return result of read(2), @c errno is saved
  ssize_t readFd(int fd, int* savedErrno);

 private:
   char* begin()
   { return &*buffer_.begin(); }

   const char* begin() const
   { return &*buffer_.begin(); }

   void makeSpace(size_t more)
   {
     if (writableBytes() + prependableBytes() < more + kCheapPrepend)
     {
       buffer_.resize(writerIndex_+more);
     }
     else
     {
       // move readable data to the front, make space inside buffer
       size_t used = readableBytes();
       std::copy(begin()+readerIndex_,
                 begin()+writerIndex_,
                 begin()+kCheapPrepend);
       readerIndex_ = kCheapPrepend;
       writerIndex_ = readerIndex_ + used;
       assert(used = readableBytes());
     }
   }

 private:
   std::vector<char> buffer_;
   size_t readerIndex_;
   size_t writerIndex_;
};

}
}

#endif  // MUDUO_NET_CHANNELBUFFER_H