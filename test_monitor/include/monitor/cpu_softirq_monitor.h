#pragma once

#include <map>
#include <string>

#include <boost/chrono.hpp>

 #include "monitor/monitor_inter.h"
#include "monitor_info.grpc.pb.h"
#include "monitor_info.pb.h"

namespace monitor {
class CpuSoftIrqMonitor : public MonitorInter {
  struct SoftIrq {
    std::string cpu_name;
    int64_t hi;
    int64_t timer;
    int64_t net_tx;
    int64_t net_rx;
    int64_t block;
    int64_t irq_poll;
    int64_t tasklet;
    int64_t sched;
    int64_t hrtimer;
    int64_t rcu;
    boost::chrono::steady_clock::time_point timepoint;
  };

 public:
  CpuSoftIrqMonitor() {}
  void RunOnce(monitor::proto::MonitorInfo* monitor_info);
  void Stop()override {}

 private:
  std::map<std::string, struct SoftIrq> cpu_softirqs_;
};

}  // namespace monitor
