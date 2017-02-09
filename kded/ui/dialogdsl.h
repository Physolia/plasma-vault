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

#ifndef PLASMAVAULT_KDED_DIALOG_DSL_H
#define PLASMAVAULT_KDED_DIALOG_DSL_H

#include <QString>
#include <QHash>
#include <QWidget>
#include <QVariant>

#include <functional>

namespace DialogDsl {

// We want to have a normal ID for the QMap or QHash,
// but we also want it to have a translated name
class Key: public QByteArray {
public:
    Key(const QByteArray &id, const QString &translation = QString());

    QString translation() const;

private:
    QString m_translation;

};

namespace operators {
    // A nicer way to define a Key and its translation
    inline
    Key operator/ (const char *id, const QString &name) {
        return Key(id, name);
    }
}

// A dialog module can return a set of configured key-value pairs
class DialogModule: public QWidget {
    Q_OBJECT

    Q_PROPERTY(bool isValid READ isValid WRITE setIsValid NOTIFY isValidChanged)

public:
    DialogModule(bool isValid);

    virtual QHash<QString, QVariant> fields() const = 0;

    bool isValid() const;
    void setIsValid(bool valid);

Q_SIGNALS:
    void isValidChanged(bool valid);

private:
    bool m_isValid;
};

typedef std::function<DialogModule*()> ModuleFactory;

typedef QVector<ModuleFactory> step;
typedef QVector<step> steps;
typedef QMap<Key, steps> Logic;

// If we want to have a single page containing multiple modules
class CompoundDialogModule: public DialogModule {
public:
    CompoundDialogModule(const step &children);

    QHash<QString, QVariant> fields() const override;

private:
    QVector<DialogModule*> m_children;

};

} // namespace DialogDsl

#endif // PLASMAVAULT_KDED_DIALOG_DSL_H

