// SPDX-License-Identifier: GPL-3.0-or-later
// SPDX-FileCopyrightText: 2017-2019 Alejandro Sirgo Rica & Contributors

#include "circletool.h"
#include <QPainter>

CircleTool::CircleTool(QObject* parent)
  : AbstractTwoPointTool(parent)
{
    m_supportsDiagonalAdj = true;
}

QIcon CircleTool::icon(const QColor& background, bool inEditor) const
{
    Q_UNUSED(inEditor)
    return QIcon(iconPath(background) + "circle-outline.svg");
}
QString CircleTool::name() const
{
    return tr("Circle");
}

ToolType CircleTool::type() const
{
    return ToolType::CIRCLE;
}

QString CircleTool::description() const
{
    return tr("Set the Circle as the paint tool");
}

CaptureTool* CircleTool::copy(QObject* parent)
{
    auto* tool = new CircleTool(parent);
    copyParams(this, tool);
    return tool;
}

void CircleTool::process(QPainter& painter, const QPixmap& pixmap)
{
    Q_UNUSED(pixmap)
    //painter.setPen(QPen(color(), thickness()));
    //painter.drawEllipse(QRect(points().first, points().second));

    // ++ Fill with Alpha ++
    QColor borderColor = QColor(color());
    borderColor.setAlpha(100);

    QColor fillColor = QColor(color());
    fillColor.setAlpha(20);

    QPainterPath path;
    path.addEllipse(QRect(points().first, points().second));
    QPen pen(borderColor, thickness());
    painter.setPen(pen);
    painter.fillPath(path, fillColor);
    painter.drawPath(path);
}

void CircleTool::pressed(const CaptureContext& context)
{
    Q_UNUSED(context)
}