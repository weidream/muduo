#include "user_manager.h"
namespace msgserver {
#if 0
UserManager *UserManager::instance() {
  static UserManager T;
  return &T;
}
#endif
IMUserPtr UserManager::getUserByName(const std::string &name) {
  IMUserPtr pUser;
  IMUserWeakPtr &wkUser = usermap_[name];
  pUser = wkUser.lock();
  if (!pUser) {
    pUser.reset(new IMUser(name));
    wkUser = pUser;
  }
  return pUser;
}

} // msgserver
