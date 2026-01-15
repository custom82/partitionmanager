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
#include <QScrollArea>
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

    constexpr int rows = 20;
    constexpr int columns = 20;
    constexpr int cellSize = 16;
    constexpr int totalCells = rows * columns;

    for (int index = 0; index < totalCells; ++index) {
        auto* cell = new QFrame(gridWidget);
        cell->setFixedSize(cellSize, cellSize);
        cell->setStyleSheet(QStringLiteral("background-color: #bdbdbd; border: 1px solid #4a4a4a;"));
        gridLayout->addWidget(cell, index / columns, index % columns);
        m_Cells.append(cell);
    }

    auto* scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);
    scrollArea->setFrameShape(QFrame::NoFrame);
    scrollArea->setWidget(gridWidget);
    mainLayout->addWidget(scrollArea);

    auto* buttonBox = new QDialogButtonBox(this);
    m_AnalyzeButton = buttonBox->addButton(xi18nc("@action:button", "Analyze"), QDialogButtonBox::ActionRole);
    m_RepairButton = buttonBox->addButton(xi18nc("@action:button", "Repair"), QDialogButtonBox::AcceptRole);
    m_RepairButton->setEnabled(false);
    connect(m_AnalyzeButton, &QPushButton::clicked, this, &BadSectorRepairDialog::analyzeSectors);
    connect(m_RepairButton, &QPushButton::clicked, this, &QDialog::accept);
    mainLayout->addWidget(buttonBox);

    setMinimumSize(QSize(480, 360));
}

void BadSectorRepairDialog::analyzeSectors()
{
    const int totalCells = m_Cells.size();
    for (int index = 0; index < totalCells; ++index) {
        const double ratio = totalCells > 1
            ? static_cast<double>(index) / static_cast<double>(totalCells - 1)
            : 0.0;
        QColor color;
        color.setRgbF(ratio, 1.0 - ratio, 0.0);
        m_Cells.at(index)->setStyleSheet(QStringLiteral("background-color: %1; border: 1px solid #4a4a4a;")
                                             .arg(color.name()));
    }

    if (m_AnalyzeButton) {
        m_AnalyzeButton->setEnabled(false);
    }
    if (m_RepairButton) {
        m_RepairButton->setEnabled(true);
    }
}
