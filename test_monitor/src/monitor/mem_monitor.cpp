#include "monitor/mem_monitor.h"
#include "utils/read_file.h"

namespace monitor {
static constexpr float KBToMB = 1024.00;

void MemMonitor::UpdateOnce(monitor::proto::MonitorInfo* monitor_info) {
  ReadFile mem_file("/proc/meminfo");
  struct MenInfo mem_info;
  std::vector<std::string> mem_datas;
  while (mem_file.ReadLine(&mem_datas)) {
    const char* mem_first = mem_datas[0].c_str();

    if (mem_datas[0] == "MemTotal:") {
      mem_info.total = std::stoll(mem_datas[1]);
    } else if (mem_datas[0] == "MemFree:") {
      mem_info.free = std::stoll(mem_datas[1]);
    } else if (mem_datas[0] == "MemAvailable:") {
      mem_info.avail = std::stoll(mem_datas[1]);
    } else if (mem_datas[0] == "Buffers:") {
      mem_info.buffers = std::stoll(mem_datas[1]);
    } else if (mem_datas[0] == "Cached:") {
      mem_info.cached = std::stoll(mem_datas[1]);
    } else if (mem_datas[0] == "SwapCached:") {
      mem_info.swap_cached = std::stoll(mem_datas[1]);
    } else if (mem_datas[0] == "Active:") {
      mem_info.active = std::stoll(mem_datas[1]);
    } else if (mem_datas[0] == "Inactive:") {
      mem_info.in_active = std::stoll(mem_datas[1]);
    } else if (mem_datas[0] == "Active(anon):") {
      mem_info.active_anon = std::stoll(mem_datas[1]);
    } else if (mem_datas[0] == "Inactive(anon):") {
      mem_info.inactive_anon = std::stoll(mem_datas[1]);
    } else if (mem_datas[0] == "Active(file):") {
      mem_info.active_file = std::stoll(mem_datas[1]);
    } else if (mem_datas[0] == "Inactive(file):") {
      mem_info.inactive_file = std::stoll(mem_datas[1]);
    } else if (mem_datas[0] == "Dirty:") {
      mem_info.dirty = std::stoll(mem_datas[1]);
    } else if (mem_datas[0] == "Writeback:") {
      mem_info.writeback = std::stoll(mem_datas[1]);
    } else if (mem_datas[0] == "AnonPages:") {
      mem_info.anon_pages = std::stoll(mem_datas[1]);
    } else if (mem_datas[0] == "Mapped:") {
      mem_info.mapped = std::stoll(mem_datas[1]);
    } else if (mem_datas[0] == "KReclaimable:") {
      mem_info.kReclaimable = std::stoll(mem_datas[1]);
    } else if (mem_datas[0] == "SReclaimable:") {
      mem_info.sReclaimable = std::stoll(mem_datas[1]);
    } else if (mem_datas[0] == "SUnreclaim:") {
      mem_info.sUnreclaim = std::stoll(mem_datas[1]);
    }
  }

  auto mem_detail = monitor_info->mutable_mem_info();

  mem_detail->set_used_percent(mem_info.total -
                               mem_info.avail / mem_info.total * 100.0);
  mem_detail->set_free(mem_info.avail / KBToMB);
  mem_detail->set_avail(mem_info.free / KBToMB);
  mem_detail->set_buffers(mem_info.buffers / KBToMB);
  mem_detail->set_cached(mem_info.cached / KBToMB);
  mem_detail->set_swap_cached(mem_info.swap_cached / KBToMB);
  mem_detail->set_active(mem_info.active / KBToMB);
  mem_detail->set_inactive(mem_info.in_active / KBToMB);
  mem_detail->set_active_anon(mem_info.active_anon / KBToMB);
  mem_detail->set_inactive_anon(mem_info.inactive_anon / KBToMB);
  mem_detail->set_active_file(mem_info.active_file / KBToMB);
  mem_detail->set_inactive_file(mem_info.inactive_file / KBToMB);
  mem_detail->set_dirty(mem_info.dirty / KBToMB);
  mem_detail->set_writeback(mem_info.writeback / KBToMB);
  mem_detail->set_anon_pages(mem_info.anon_pages / KBToMB);
  mem_detail->set_mapped(mem_info.mapped / KBToMB);
  mem_detail->set_kreclaimable(mem_info.kReclaimable / KBToMB);
  mem_detail->set_sreclaimable(mem_info.sReclaimable / KBToMB);
  mem_detail->set_sunreclaim(mem_info.sUnreclaim / KBToMB);

  return;
}
}  // namespace monitor
