/*
 *   Copyright (C) 2017 Ivan Čukić <ivan.cukic(at)kde.org>
 *
 *   This library is free software; you can redistribute it and/or
 *   modify it under the terms of the GNU Lesser General Public
 *   License as published by the Free Software Foundation; either
 *   version 2.1 of the License, or (at your option) version 3, or any
 *   later version accepted by the membership of KDE e.V. (or its
 *   successor approved by the membership of KDE e.V.), which shall
 *   act as a proxy defined in Section 6 of version 3 of the license.
 *
 *   This library is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *   Lesser General Public License for more details.
 *
 *   You should have received a copy of the GNU Lesser General Public
 *   License along with this library.
 *   If not, see <http://www.gnu.org/licenses/>.
 */

#include "activitieslinkingwidget.h"

#include "ui_activitieslinkingwidget.h"

#include <QItemDelegate>

#include <KActivities/ActivitiesModel>

class ActivitiesLinkingWidget::Private {
public:
    Ui::ActivitiesLinkingWidget ui;
};


namespace {
    class CheckboxDelegate: public QItemDelegate { //_
    public:
        CheckboxDelegate(QObject *parent)
            : QItemDelegate(parent)
        {
        }

        void paint(QPainter *painter, const QStyleOptionViewItem &option,
                   const QModelIndex &index) const override
        {
            auto wholeRect = option.rect;

            // Drawing the checkbox
            auto checkRect = wholeRect;
            checkRect.setWidth(checkRect.height());
            drawCheck(painter, option, checkRect,
                    option.state & QStyle::State_Selected ?
                        Qt::Checked : Qt::Unchecked);

            // Drawing the text
            auto textRect = wholeRect;
            textRect.setLeft(textRect.left() + 8 + textRect.height());
            drawDisplay(painter, option, textRect,
                        index.data(Qt::DisplayRole).toString());
        }

        QSize sizeHint(const QStyleOptionViewItem &option,
                       const QModelIndex &index) const override
        {
            return QSize(100, 22);
        }
    }; //^
}



ActivitiesLinkingWidget::ActivitiesLinkingWidget()
    : DialogDsl::DialogModule(true)
    , d(new Private())
{
    d->ui.setupUi(this);

    d->ui.listActivities->setModel(new KActivities::ActivitiesModel(this));
    d->ui.listActivities->setItemDelegate(new CheckboxDelegate(this));
}



ActivitiesLinkingWidget::~ActivitiesLinkingWidget()
{
}



QHash<QString, QVariant> ActivitiesLinkingWidget::fields() const
{
    return {};
}



