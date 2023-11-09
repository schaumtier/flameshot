// SPDX-License-Identifier: GPL-3.0-or-later
// SPDX-FileCopyrightText: 2017-2019 Alejandro Sirgo Rica & Contributors

#include "applaunchertool.h"
#include "applauncherwidget.h"

#include "src/utils/filenamehandler.h"
#include <QMessageBox>
#include <QDir>
#include <QProcess>

AppLauncher::AppLauncher(QObject* parent)
  : AbstractActionTool(parent)
{}

bool AppLauncher::closeOnButtonPressed() const
{
    return true;
}

QIcon AppLauncher::icon(const QColor& background, bool inEditor) const
{
    Q_UNUSED(inEditor)
    return QIcon(iconPath(background) + "open_with.svg");
}
QString AppLauncher::name() const
{
    return tr("App Launcher");
}

CaptureTool::Type AppLauncher::type() const
{
    return CaptureTool::TYPE_OPEN_APP;
}

QString AppLauncher::description() const
{
    return tr("Open with eog");
}

QWidget* AppLauncher::widget()
{
    return new AppLauncherWidget(capture);
}

CaptureTool* AppLauncher::copy(QObject* parent)
{
    return new AppLauncher(parent);
}

void AppLauncher::pressed(CaptureContext& context)
{
    capture = context.selectedScreenshotArea();
    emit requestAction(REQ_CAPTURE_DONE_OK);
    // emit requestAction(REQ_ADD_EXTERNAL_WIDGETS);

    // close immediately after open "eog" - not sure if this is 100% correct...
    emit requestAction(REQ_CLOSE_GUI);

    QString m_tempFile;
    if (!QFileInfo(m_tempFile).isReadable()) {
        m_tempFile =
          FileNameHandler().properScreenshotPath(QDir::tempPath(), "png");
        //   FileNameHandler().properScreenshotPath(QDir::homePath() + "/Data/Eimer/.tmp", "png");
        capture.save(m_tempFile);
    }
    
    QProcess::startDetached("eog", { m_tempFile });
}
