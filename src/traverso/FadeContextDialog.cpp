/*
Copyright (C) 2006 Remon Sijrier 

This file is part of Traverso

Traverso is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA.

$Id: FadeContextDialog.cpp,v 1.1 2006/08/03 14:33:02 r_sijrier Exp $
*/

#include "FadeContextDialog.h"
#include "FadeContextDialogView.h"
#include "ViewPort.h"

#include <QtCore>

static const QString BG_COLOR		= "#a4aa94";
static const QString VERSION		= "0.0.3";

FadeContextDialog::FadeContextDialog(FadeCurve* fadeCurve)
	: ContextDialog()
{
	m_fadeCDV = new FadeContextDialogView(m_vp, fadeCurve);
	
	qDebug() << "JmbFade version" << VERSION;
	setWindowTitle("JmbFade " + VERSION);

	// set the background color
	setAutoFillBackground(false);
	setAttribute(Qt::WA_PaintOnScreen);

	resize(400, 200);
}

FadeContextDialog::~FadeContextDialog()
{
}

//eof


