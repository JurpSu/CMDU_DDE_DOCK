#include "cmduwidget.h"
#include "dde-dock/constants.h"
#include <QApplication>
#include <QPainter>
#include <QDebug>
#include <QSvgRenderer>
#include <QMouseEvent>

#define PLUGIN_STATE_KEY    "enable"

CMDUWidget::CMDUWidget(QWidget *parent)
    : QWidget(parent),
    m_settings("deepin", "dde-dock-cmdu")
{
    text = "↑0.00B/s\n↓0.00B/s";
    mp = 0;
    cp = 0;
}

bool CMDUWidget::enabled()
{
    return m_settings.value(PLUGIN_STATE_KEY, true).toBool();
}

void CMDUWidget::setEnabled(const bool b)
{
    m_settings.setValue(PLUGIN_STATE_KEY, b);
}

QSize CMDUWidget::sizeHint() const
{
    QFontMetrics FM(qApp->font());
    return FM.boundingRect("↑000.00KB/s  ").size() + QSize(0,FM.boundingRect("↓000.00KB/s  ").height());
}

void CMDUWidget::resizeEvent(QResizeEvent *e)
{
    QWidget::resizeEvent(e);
}

void CMDUWidget::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    if(mp >= 90){
        painter.fillRect(rect(), QBrush(Qt::red));
    }
    painter.setPen(Qt::white);
    painter.drawText(rect(), Qt::AlignLeft | Qt::AlignVCenter, text);
    painter.fillRect(0, height()*(100-mp)/100, 2, height()*mp/100, Qt::green);
    painter.fillRect(width()-2, height()*(100-cp)/100, 2, height()*cp/100, Qt::green);
}

void CMDUWidget::mousePressEvent(QMouseEvent *e)
{
    if (e->button() != Qt::RightButton)
        return QWidget::mousePressEvent(e);

    const QPoint p(e->pos() - rect().center());
    if (p.manhattanLength() < std::min(width(), height()) * 0.8 * 0.5)
    {
        emit requestContextMenu();
        return;
    }

    QWidget::mousePressEvent(e);
}
