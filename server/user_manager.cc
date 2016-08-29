#include "user_manager.h"
namespace msgserver {
UserManager *UserManager::instance() {
  static UserManager T;
  return &T;
}

IMUserPtr getUserByName(const sting &name) {
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
