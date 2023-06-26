#pragma once

#include <QStandardItemModel>
#include <QtWidgets>
#include <thread>

#include "cpu_load_model.h"
#include "cpu_stat_model.h"
#include "monitor_model.h"

#include "monitor_info.grpc.pb.h"
#include "monitor_info.pb.h"

namespace monitor {
class MonitorWidget : public QWidget {
  Q_OBJECT
 public:
  explicit MonitorWidget(QWidget* parent = nullptr);
  ~MonitorWidget() {
    // stop_ = true;
    // if (thread_->joinable()) {
    //   thread_->join();
    // }
  }

  QWidget* InitMonitorWidget();
  void UpdateData(const monitor::proto::MonitorInfo& monitor_info);

 private:
  QTableView* monitor_view_ = nullptr;
  QTableView* cpu_load_monitor_view_ = nullptr;
  QTableView* cpu_stat_monitor_view_ = nullptr;

  MonitorBaseModel* monitor_model_ = nullptr;
  CpuLoadModel* cpu_load_model_ = nullptr;
  CpuStatModel* cpu_stat_model_ = nullptr;
  // std::unique_ptr<std::thread> thread_;
  // bool stop = false;
};
}  // namespace monitor
