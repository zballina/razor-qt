/* BEGIN_COMMON_COPYRIGHT_HEADER
 * (c)LGPL2+
 *
 * Razor - a lightweight, Qt based, desktop toolset
 * http://razor-qt.org
 *
 * Copyright: 2012 Razor team
 * Authors:
 *   Kuzma Shapran <kuzma.shapran@gmail.com>
 *
 * This program or library is free software; you can redistribute it
 * and/or modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.

 * You should have received a copy of the GNU Lesser General
 * Public License along with this library; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301 USA
 *
 * END_COMMON_COPYRIGHT_HEADER */

#ifndef RAZORPANELKBINDICATOR_H
#define RAZORPANELKBINDICATOR_H

#include "../panel/irazorpanelplugin.h"
#include "razorkbindicatorconfiguration.h"


class QLabel;

class RazorKbIndicator : public QObject, public IRazorPanelPlugin
{
    Q_OBJECT
public:
    RazorKbIndicator(const IRazorPanelPluginStartupInfo &startupInfo);
    ~RazorKbIndicator();

    virtual QWidget *widget();
    virtual QString themeId() const { return "KbIndicator"; }
    virtual IRazorPanelPlugin::Flags flags() const { return PreferRightAlignment | HaveConfigDialog; }
    virtual bool isSeparate() const { return false; }

    QDialog *configureDialog();
    virtual void realign();

signals:
    void indicatorsChanged(unsigned int, unsigned int);

protected slots:
    virtual void settingsChanged();

    void setIndicators(unsigned int, unsigned int);

protected:
    bool getLockStatus(int mBit);
    virtual void x11EventFilter(XEvent* event);

private:
    QLabel *mContent;

    int mBit;

    Display *mDisplay;
    int mXkbEventBase;
};


class RazorKbIndicatorLibrary: public QObject, public IRazorPanelPluginLibrary
{
    Q_OBJECT
    Q_INTERFACES(IRazorPanelPluginLibrary)
public:
    IRazorPanelPlugin *instance(const IRazorPanelPluginStartupInfo &startupInfo)
    {
        return new RazorKbIndicator(startupInfo);
    }
};
#endif // RAZORPANELKBINDICATOR_H
