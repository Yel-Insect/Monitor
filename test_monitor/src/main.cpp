#pragma once
#include <memory>
#include <thread>
#include <vector>

#include "client/rpc_client.h"
#include "monitor/cpu_load_monitor.h"
#include "monitor/cpu_softirq_monitor.h"
#include "monitor/cpu_stat_monitor.h"
#include "monitor/mem_monitor.h"
#include "monitor/net_monitor.h"

#include "monitor/monitor_inter.h"
#include "monitor_info.grpc.pb.h"
#include "monitor_info.pb.h"

int main() {
  std::vector<monitor::MonitorInter*> runners_;
  runners_.push_back(new monitor::CpuSoftIrqMonitor());
  runners_.push_back(new monitor::CpuLoadMonitor());
  runners_.push_back(new monitor::CpuStatMonitor());
  runners_.push_back(new monitor::MemMonitor());
  runners_.push_back(new monitor::NetMonitor());

  monitor::RpcClient rpc_client_;

  while (true) {
    monitor::proto::MonitorInfo monitor_info;
    for (auto& runner : runners_) {
      runner->UpdateOnce(&monitor_info);
    }

    rpc_client_.SetMonitorInfo(monitor_info);
    std::this_thread::sleep_for(std::chrono::seconds(3));
  }

  return 0;
}
