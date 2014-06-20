#ifndef NOTIFICATIONTAB_H
#define NOTIFICATIONTAB_H

#include <QTabWidget>
#include <QtGui>
#include <QTabBar>

class NotificationTab : public QTabWidget
{
    Q_OBJECT
public:
    explicit NotificationTab(QWidget *parent = 0);

    void notifyOn(int tabno);

    void notifyOff(int tabno);
    
signals:
    
public slots:
    
};

#endif // NOTIFICATIONTAB_H
