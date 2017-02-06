/*
 *   Copyright (C) 2017 by Ivan Cukic <ivan.cukic(at)kde.org>
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

#ifndef PLASMAVAULT_BACKENDS_CRYFS_BACKEND_H
#define PLASMAVAULT_BACKENDS_CRYFS_BACKEND_H

#include <backend_p.h>

namespace PlasmaVault {

class CryFsBackend: public Backend {
public:
    CryFsBackend();
    ~CryFsBackend();

    static Backend::Ptr instance();

    bool isInitialized(const Device &device) const override;
    bool isOpened(const MountPoint &mountPoint) const override;

    FutureResult<> initialize(const QString &name,
                              const Device &device, const MountPoint &mountPoint,
                              const QString &password) override;

    FutureResult<> open(const Device &device,
                        const MountPoint &mountPoint,
                        const QString &password) override;

    FutureResult<> close(const Device &device,
                         const MountPoint &mountPoint) override;

    FutureResult<> destroy(const Device &device,
                           const MountPoint &mountPoint,
                           const QString &password) override;

    FutureResult<> validateBackend() override;

    QString name() const override { return "cryfs"; };
};

} // namespace PlasmaVault

#endif // PLASMAVAULT_BACKENDS_CRYFS_BACKEND_H

