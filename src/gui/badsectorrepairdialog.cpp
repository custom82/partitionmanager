/*
    SPDX-FileCopyrightText: 2025 OpenAI

    SPDX-License-Identifier: GPL-3.0-or-later
*/

#include "gui/badsectorrepairdialog.h"

#include <core/device.h>

#include <QDialogButtonBox>
#include <QColor>
#include <QFrame>
#include <QGridLayout>
#include <QPushButton>
#include <QVBoxLayout>

#include <KLocalizedString>

BadSectorRepairDialog::BadSectorRepairDialog(QWidget* parent, Device& device)
    : QDialog(parent)
    , m_Device(device)
{
    setWindowTitle(xi18nc("@title:window", "Repair Bad Sector: <filename>%1</filename>", m_Device.deviceNode()));

    auto* mainLayout = new QVBoxLayout(this);
    auto* gridWidget = new QWidget(this);
    auto* gridLayout = new QGridLayout(gridWidget);
    gridLayout->setSpacing(2);
    gridLayout->setContentsMargins(0, 0, 0, 0);

    constexpr int rows = 10;
    constexpr int columns = 10;
    constexpr int totalCells = rows * columns;

    for (int index = 0; index < totalCells; ++index) {
        const double ratio = totalCells > 1
            ? static_cast<double>(index) / static_cast<double>(totalCells - 1)
            : 0.0;
        QColor color;
        color.setRgbF(ratio, 1.0 - ratio, 0.0);

        auto* cell = new QFrame(gridWidget);
        cell->setFixedSize(12, 12);
        cell->setStyleSheet(QStringLiteral("background-color: %1; border: 1px solid #4a4a4a;")
                                .arg(color.name()));
        gridLayout->addWidget(cell, index / columns, index % columns);
    }

    mainLayout->addWidget(gridWidget, 0, Qt::AlignCenter);

    auto* buttonBox = new QDialogButtonBox(this);
    buttonBox->addButton(xi18nc("@action:button", "Analyze"), QDialogButtonBox::ActionRole);
    auto* repairButton = buttonBox->addButton(xi18nc("@action:button", "Repair"), QDialogButtonBox::AcceptRole);
    connect(repairButton, &QPushButton::clicked, this, &QDialog::accept);
    mainLayout->addWidget(buttonBox);

    setMinimumSize(sizeHint());
}
