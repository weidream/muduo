#ifndef _MUDUO_RPC_RPCCLOSURE_H_
#define _MUDUO_RPC_RPCCLOSU
#include <google/protobuf/stubs/callback.h>
//#include <boost/bind.hpp>
#include <boost/function.hpp>
namespace protobufrpc{
#if 0
typedef boost::function<void()>  ClosureFunc;

class OnceClosure : public google::protobuf::Closure {
public:
 OnceClosure(const ClosureFunc &f) : f_(f) {
 }
 void Run() {
   f_();
   delete this;
 }
private:
 boost::function0<void> f_;
};

inline google::protobuf::Closure *NewClosure(const ClosureFunc &f) 
{
  return new OnceClosure(f);
}
#endif
}//namespace protobufrpc
#endif