#ifndef MUDUO_TIMEING_WHEEL_H_
#define MUDUO_TIMEING_WHEEL_H_

#include <boost/circular_buffer.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/unordered_set.hpp>
#include <boost/version.hpp>
#include <boost/weak_ptr.hpp>
#include <boost/function.hpp>
#include <utility>
#include <stdio.h>
typedef boost::function<void()> TimingWheelCallback;
//template <typename T>

class timingWheel
{
public:
  struct Entry;
  typedef boost::shared_ptr<Entry> EntryPtr;
  typedef boost::weak_ptr<Entry> WeakEntryPtr;
  typedef boost::unordered_set<EntryPtr> Bucket;
  typedef boost::circular_buffer<Bucket> BucketList;
  typedef typename BucketList::size_type size_type;
  typedef typename BucketList::iterator BucketList_iterator;
  struct Entry
  {
    explicit Entry(TimingWheelCallback &&cb, int second)
        : cb_(std::move(cb)), second_(second)
    {
    }
    //size_t getSecond() { return second_; }
    ~Entry()
    {
      cb_();
    }
    TimingWheelCallback cb_;
    size_t second_;
    BucketList_iterator it;
    friend class timingWheel;
  };
  timingWheel(size_t size)
      : list_(static_cast<size_type>(size), Bucket()), size_(size) {}
  ~timingWheel() {}
  WeakEntryPtr insert(TimingWheelCallback &&cb, int second)
  {
    //not thread safe
    assert(second < size_);
    EntryPtr p(new Entry(std::move(cb), second));
    WeakEntryPtr ret(p);
    p->it = list_.begin();
    list_[static_cast<size_type>(second)].insert(std::move(p));
    return ret;
  }
  void insert(const WeakEntryPtr &wp)
  {
    //assert(second < size_);
    //not thread safe
    EntryPtr p(wp.lock());
    if (p)
    {
      if (list_.begin() != p->it)
      {
        list_[static_cast<size_type>(p->second_)].insert(std::move(p));
      }
    }
  }
  // per-second timer
  void on_timer()
  {

    list_.push_back(Bucket());
  }
  BucketList list_;
  size_type size_;
};
#endif
