#ifndef CMDUPlugin_H
#define CMDUPlugin_H

#include "pluginsiteminterface.h"
#include "cmduwidget.h"
#include <QTimer>
#include <QLabel>

class CMDUPlugin : public QObject, PluginsItemInterface
{
    Q_OBJECT
    Q_INTERFACES(PluginsItemInterface)
    Q_PLUGIN_METADATA(IID "com.deepin.dock.PluginsItemInterface" FILE "cmdu.json")

public:
    explicit CMDUPlugin(QObject *parent = 0);

    const QString pluginName() const override;
    const QString pluginDisplayName() const override;
    void init(PluginProxyInterface *proxyInter) override;

    void pluginStateSwitched() override;
    bool pluginIsAllowDisable() override { return true; }
    bool pluginIsDisable() override;

    int itemSortKey(const QString &itemKey) override;

    QWidget *itemWidget(const QString &itemKey) override;
    QWidget *itemTipsWidget(const QString &itemKey) override;

    const QString itemCommand(const QString &itemKey) override;
    const QString itemContextMenu(const QString &itemKey) override;

    void invokedMenuItem(const QString &itemKey, const QString &menuId, const bool checked) override;

private slots:
    void updateCMDU();

private:
    long int i, db, ub, tt0, idle0;
    int nl;
    QPointer<CMDUWidget> m_centralWidget;
    QPointer<QLabel> m_tipsLabel;
    QTimer *m_refershTimer;
    QString m_currentTimeString;
    QString KB(long k);
    QString BS(long b);
    QLabel *labelStartupDuration;
    void MBAbout();
    void MBChangeLog();
};

#endif // CMDUPlugin_H
