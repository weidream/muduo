#include "user.h"

namespace msgserver {

IMUser::IMUser(const std::string &name)
    : user_name_(name), loginTime_(muduo::Timestamp::now()) {}

IMUser::~IMUser() {}

} // namespace msgserver
