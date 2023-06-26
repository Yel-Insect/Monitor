#include "monitor_widget.h"

namespace monitor {

MonitorWidget::MonitorWidget(QWidget *parent) {}

QWidget *MonitorWidget::InitMonitorWidget() {
  QWidget *widget = new QWidget();
  QLabel *monitor_label = new QLabel(this);
  monitor_label->setText(tr("Monitor softirq:"));
  monitor_label->setFont(QFont("Microsoft YaHei", 10, 40));

  monitor_view_ = new QTableView;
  monitor_model_ = new MonitorBaseModel;
  QSortFilterProxyModel *sort_proxy = new QSortFilterProxyModel(this);
  sort_proxy->setSourceModel(monitor_model_);
  monitor_view_->setModel(sort_proxy);
  monitor_view_->setSortingEnabled(true);
  monitor_view_->show();

  QLabel *cpu_load_label = new QLabel(this);
  cpu_load_label->setText(tr("Monitor CpuLoad:"));
  cpu_load_label->setFont(QFont("Microsoft YaHei", 10, 40));

  cpu_load_monitor_view_ = new QTableView;
  cpu_load_model_ = new CpuLoadModel;
  // QSortFilterProxyModel *sort_proxy = new QSortFilterProxyModel(this);
  // sort_proxy->setSourceModel(monitor_model_);
  cpu_load_monitor_view_->setModel(cpu_load_model_);
  // monitor_view_->setSortingEnabled(true);
  cpu_load_monitor_view_->show();

  QLabel *cpu_stat_label = new QLabel(this);
  cpu_load_label->setText(tr("Monitor CpuStat:"));
  cpu_load_label->setFont(QFont("Microsoft YaHei", 10, 40));

  cpu_stat_monitor_view_ = new QTableView;
  cpu_stat_model_ = new CpuStatModel;
  // QSortFilterProxyModel *cpu_stat_sort_proxy = new
  // QSortFilterProxyModel(this);
  // cpu_stat_sort_proxy->setSourceModel(cpu_stat_model_);
  cpu_stat_monitor_view_->setModel(cpu_stat_model_);
  // cpu_stat_monitor_view_->setSortingEnabled(true);
  cpu_stat_monitor_view_->show();

  QGridLayout *layout = new QGridLayout();
  layout->addWidget(monitor_label, 1, 0);
  layout->addWidget(monitor_view_, 2, 0, 1, 2);

  layout->addWidget(cpu_load_label, 3, 0);
  layout->addWidget(cpu_load_monitor_view_, 4, 0, 1, 1);

  layout->addWidget(cpu_stat_label, 5, 0);
  layout->addWidget(cpu_stat_monitor_view_, 6, 0, 1, 2);

  widget->setLayout(layout);
  widget->show();
  return widget;
}

void MonitorWidget::UpdateData(
    const monitor::proto::MonitorInfo &monitor_info) {
  monitor_model_->UpdateMonitorInfo(monitor_info);
  cpu_load_model_->UpdateMonitorInfo(monitor_info);
  cpu_stat_model_->UpdateMonitorInfo(monitor_info);
}
}  // namespace monitor
