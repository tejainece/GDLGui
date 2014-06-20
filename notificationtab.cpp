#include "notificationtab.h"

NotificationTab::NotificationTab(QWidget *parent) :
    QTabWidget(parent)
{
}

void NotificationTab::notifyOn(int tabno)
{
    tabBar()->setTabTextColor(tabno, QColor(Qt::red));
}

void NotificationTab::notifyOff(int tabno)
{
    tabBar()->setTabTextColor(tabno, QColor(Qt::black));
}
