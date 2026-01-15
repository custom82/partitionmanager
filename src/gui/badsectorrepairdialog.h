/*
    SPDX-FileCopyrightText: 2025 OpenAI

    SPDX-License-Identifier: GPL-3.0-or-later
*/

#ifndef PARTITIONMANAGER_BADSECTORREPAIRDIALOG_H
#define PARTITIONMANAGER_BADSECTORREPAIRDIALOG_H

#include <QDialog>

class Device;

class BadSectorRepairDialog : public QDialog
{
    Q_OBJECT

public:
    explicit BadSectorRepairDialog(QWidget* parent, Device& device);
    ~BadSectorRepairDialog() override = default;

private:
    Device& m_Device;
};

#endif
