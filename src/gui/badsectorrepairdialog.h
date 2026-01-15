/*
    SPDX-FileCopyrightText: 2025 OpenAI

    SPDX-License-Identifier: GPL-3.0-or-later
*/

#ifndef PARTITIONMANAGER_BADSECTORREPAIRDIALOG_H
#define PARTITIONMANAGER_BADSECTORREPAIRDIALOG_H

#include <QDialog>
#include <QVector>

class Device;
class QFrame;
class QPushButton;

class BadSectorRepairDialog : public QDialog
{
    Q_OBJECT

public:
    explicit BadSectorRepairDialog(QWidget* parent, Device& device);
    ~BadSectorRepairDialog() override = default;

private Q_SLOTS:
    void analyzeSectors();

private:
    Device& m_Device;
    QVector<QFrame*> m_Cells;
    QPushButton* m_AnalyzeButton = nullptr;
    QPushButton* m_RepairButton = nullptr;
};

#endif
