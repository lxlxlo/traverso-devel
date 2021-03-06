/*
Copyright (C) 2005-2007 Remon Sijrier

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

*/

#include "PluginView.h"

#include <QPainter>

#include "AudioTrackView.h"
#include "PluginChainView.h"
#include "TMainWindow.h"

#include <Themer.h>
#include <Plugin.h>
#include <PluginChain.h>
#include <Track.h>
#include <Utils.h>

#include <PluginPropertiesDialog.h>

// Always put me below _all_ includes, this is needed
// in case we run with memory leak detection enabled!
#include "Debugger.h"

PluginView::PluginView(PluginChainView* parent, PluginChain* chain, Plugin* plugin, int index)
	: ViewItem(parent, plugin)
	, m_pluginchain(chain)
	, m_plugin(plugin)
	, m_index(index)
{
	PENTERCONS;
	
	m_propertiesDialog = 0;

        setZValue(parent->zValue() + 2);
	
	m_name = plugin->get_name();
	
	QFontMetrics fm(themer()->get_font("Plugin:fontscale:name"));
	m_textwidth = fm.width(m_name);
	
	calculate_bounding_rect();
	
	connect(m_plugin, SIGNAL(bypassChanged()), this, SLOT(repaint()));
        connect(m_plugin, SIGNAL(activeContextChanged()), this, SLOT(repaint()));
}

PluginView::~PluginView( )
{
	PENTERDES2;
	if (m_propertiesDialog) {
		delete m_propertiesDialog;
	}
}

void PluginView::paint(QPainter* painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	Q_UNUSED(option);
	Q_UNUSED(widget);
	
	QColor color;
	if (m_plugin->is_bypassed()) {
		color = themer()->get_color("Plugin:background:bypassed");
	} else {
		color = themer()->get_color("Plugin:background");
	}

	int height, width;
        if (has_active_context()) {
		height = (int)m_boundingRect.height() + 1;
		width = (int)m_boundingRect.width() + 1;
		color = color.light(120);
	} else {
		height = (int)m_boundingRect.height();
		width = (int)m_boundingRect.width();
	}
	
	QBrush brush(color);
	QRect rect(0, 0, width, height); 
	painter->fillRect(rect, brush);
	painter->setPen(themer()->get_color("Plugin:text"));
	painter->setFont(themer()->get_font("Plugin:fontscale:name"));
	painter->drawText(rect, Qt::AlignCenter, m_name);
}


TCommand * PluginView::edit_properties( )
{
	if (! m_propertiesDialog) {
		m_propertiesDialog = new PluginPropertiesDialog(TMainWindow::instance(), m_plugin);
		m_propertiesDialog->setWindowTitle(m_name);
	} 
	m_propertiesDialog->show();
	return (TCommand*) 0;
}

TCommand* PluginView::remove_plugin()
{
	return m_pluginchain->remove_plugin(m_plugin);
}

Plugin * PluginView::get_plugin( )
{
	return m_plugin;
}

void PluginView::set_index(int index)
{
	m_index = index;
}

void PluginView::repaint( )
{
	update();
}

void PluginView::calculate_bounding_rect()
{
	int height = 25;
	int parentheight = (int)m_parentViewItem->boundingRect().height();
	if (parentheight < 30) {
		height = parentheight - 4;
	}
	int y = parentheight - height;
	m_boundingRect = QRectF(0, 0, m_textwidth + 8, height);
	setPos(x(), y);
}

