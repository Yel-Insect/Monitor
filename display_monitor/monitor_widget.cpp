#include "monitor_widget.h"

namespace monitor {

MonitorWidget::MonitorWidget(QWidget *parent) {}
QWidget *MonitorWidget::ShowAllMonitorWidget() {
  QWidget *widget = new QWidget();
  stack_menu_ = new QStackedLayout();
  stack_menu_->addWidget(InitCpuMonitorWidget());
  stack_menu_->addWidget(InitSoftIrqMonitorWidget());

  QGridLayout *layout = new QGridLayout(this);
  layout->addWidget(InitButtonMenu(), 1, 0);
  layout->addLayout(stack_menu_, 2, 0);
  widget->setLayout(layout);
  return widget;
}

QWidget *MonitorWidget::InitButtonMenu() {
  QPushButton *cpu_button = new QPushButton("cpu", this);
  QPushButton *soft_irq_button = new QPushButton("soft_irq", this);
  QFont *font = new QFont("Microsoft YaHei", 15, 60);
  cpu_button->setFont(*font);
  soft_irq_button->setFont(*font);

  QHBoxLayout *layout = new QHBoxLayout();
  layout->addWidget(cpu_button);
  layout->addWidget(soft_irq_button);

  QWidget *widget = new QWidget();
  widget->setLayout(layout);

  connect(cpu_button, SIGNAL(clicked()), this, SLOT(ClickCpuButton()));
  connect(soft_irq_button, SIGNAL(clicked()), this, SLOT(ClickSoftIrqButton()));

  return widget;
}

QWidget *MonitorWidget::InitCpuMonitorWidget() {
  QWidget *widget = new QWidget();

  QLabel *cpu_load_label = new QLabel(this);
  cpu_load_label->setText(tr("Monitor CpuLoad:"));
  cpu_load_label->setFont(QFont("Microsoft YaHei", 10, 40));

  cpu_load_monitor_view_ = new QTableView;
  cpu_load_model_ = new CpuLoadModel;
  cpu_load_monitor_view_->setModel(cpu_load_model_);
  cpu_load_monitor_view_->show();

  QLabel *cpu_stat_label = new QLabel(this);
  cpu_load_label->setText(tr("Monitor CpuStat:"));
  cpu_load_label->setFont(QFont("Microsoft YaHei", 10, 40));

  cpu_stat_monitor_view_ = new QTableView;
  cpu_stat_model_ = new CpuStatModel;
  cpu_stat_monitor_view_->setModel(cpu_stat_model_);
  cpu_stat_monitor_view_->show();

  QGridLayout *layout = new QGridLayout();

  layout->addWidget(cpu_load_label, 1, 0);
  layout->addWidget(cpu_load_monitor_view_, 2, 0, 1, 1);

  layout->addWidget(cpu_stat_label, 3, 0);
  layout->addWidget(cpu_stat_monitor_view_, 4, 0, 1, 2);

  widget->setLayout(layout);
  return widget;
}

QWidget *MonitorWidget::InitSoftIrqMonitorWidget() {
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

  QGridLayout *layout = new QGridLayout();
  layout->addWidget(monitor_label, 1, 0);
  layout->addWidget(monitor_view_, 2, 0, 1, 2);

  widget->setLayout(layout);
  return widget;
}

void MonitorWidget::UpdateData(
    const monitor::proto::MonitorInfo &monitor_info) {
  monitor_model_->UpdateMonitorInfo(monitor_info);
  cpu_load_model_->UpdateMonitorInfo(monitor_info);
  cpu_stat_model_->UpdateMonitorInfo(monitor_info);
}

void MonitorWidget::ClickCpuButton() { stack_menu_->setCurrentIndex(0); }
void MonitorWidget::ClickSoftIrqButton() { stack_menu_->setCurrentIndex(1); }
}  // namespace monitor