// SPDX-License-Identifier: GPL-3.0-or-later
// SPDX-FileCopyrightText: 2017-2019 Alejandro Sirgo Rica & Contributors

#include "circletool.h"
#include <QPainter>

namespace {
#define PADDING_VALUE 2
}

CircleTool::CircleTool(QObject* parent)
  : AbstractTwoPointTool(parent)
{
    m_supportsDiagonalAdj = true;
}

QIcon CircleTool::icon(const QColor& background, bool inEditor) const
{
    Q_UNUSED(inEditor);
    return QIcon(iconPath(background) + "circle-outline.svg");
}
QString CircleTool::name() const
{
    return tr("Circle");
}

ToolType CircleTool::nameID() const
{
    return ToolType::CIRCLE;
}

QString CircleTool::description() const
{
    return tr("Set the Circle as the paint tool");
}

CaptureTool* CircleTool::copy(QObject* parent)
{
    return new CircleTool(parent);
}

void CircleTool::process(QPainter& painter,
                         const QPixmap& pixmap,
                         bool recordUndo)
{
    if (recordUndo) {
        updateBackup(pixmap);
    }
    // painter.setPen(QPen(m_color, m_thickness));
    // painter.drawEllipse(QRect(m_points.first, m_points.second));

    m_color.setAlpha(100);

    QColor fillColor = QColor(m_color);
    fillColor.setAlpha(20);

    QPainterPath path;
    path.addEllipse(QRect(m_points.first, m_points.second));
    QPen pen(m_color, m_thickness);
    painter.setPen(pen);
    painter.fillPath(path, fillColor);
    painter.drawPath(path);
}

void CircleTool::paintMousePreview(QPainter& painter,
                                   const CaptureContext& context)
{
    painter.setPen(QPen(context.color, PADDING_VALUE + context.thickness));
    painter.drawLine(context.mousePos, context.mousePos);
}

void CircleTool::drawStart(const CaptureContext& context)
{
    m_color = context.color;
    m_thickness = context.thickness + PADDING_VALUE;
    m_points.first = context.mousePos;
    m_points.second = context.mousePos;
}

void CircleTool::pressed(const CaptureContext& context)
{
    Q_UNUSED(context);
}
