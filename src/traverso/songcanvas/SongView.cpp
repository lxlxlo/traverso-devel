/*
Copyright (C) 2005-2006 Remon Sijrier 

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

$Id: SongView.cpp,v 1.1 2006/11/08 14:45:22 r_sijrier Exp $
*/


#include "SongView.h"
#include "TrackView.h"
#include "PlayCursor.h"
#include "ClipsViewPort.h"
#include "TimeLineViewPort.h"
#include "TrackPanelViewPort.h"
		
#include <Song.h>
#include <Peak.h>
#include <ContextPointer.h>
#include <Zoom.h>
		
#include <Debugger.h>

SongView::SongView(ClipsViewPort* viewPort, TrackPanelViewPort* tpvp, TimeLineViewPort* tlvp, Song* song)
	: ViewItem(0, song)
{
	m_song = song;
	m_clipsViewPort = viewPort;
	m_tpvp = tpvp;
	m_tlvp = tlvp;
	
	m_clipsViewPort->scene()->addItem(this);
	
	scale_factor_changed();
	
	connect(m_song, SIGNAL(trackAdded(Track*)), this, SLOT(add_new_trackview(Track*)));
	connect(m_song, SIGNAL(trackRemoved(Track*)), this, SLOT(remove_trackview(Track*)));
	
	m_playCursor = new PlayCursor(m_song);
	m_clipsViewPort->scene()->addItem(m_playCursor);
	
	foreach(Track* track, m_song->get_tracks()) {
		add_new_trackview(track);
	}
	
	calculate_scene_rect();
	
	connect(m_song, SIGNAL(hzoomChanged()), this, SLOT(scale_factor_changed()));
}

SongView::~SongView()
{
}
		
void SongView::scale_factor_changed( )
{
	scalefactor = Peak::zoomStep[m_song->get_hzoom()];
	
	QList<QGraphicsItem*> list = scene()->items(m_clipsViewPort->sceneRect());
	
	for (int i=0; i<list.size(); ++i) {
		ViewItem* item = (ViewItem*)list.at(i);
		item->prepare_geometry_change();
		item->calculate_bounding_rect();
	}
}

TrackView* SongView::get_trackview_under( QPointF point )
{
	TrackView* view = 0;
	QList<QGraphicsItem*> views = m_clipsViewPort->items(m_clipsViewPort->mapFromScene(point));
	
	for (int i=0; i<views.size(); ++i) {
		view = qgraphicsitem_cast<TrackView*>(views.at(i));
		if (view) {
			return view;
		}
	}
	return  0;
	
}


void SongView::add_new_trackview(Track* track)
{
	TrackView* view = new TrackView(this, track);
	
	int sortIndex = track->get_sort_index();
	
	if (sortIndex < 0) {
		sortIndex = m_trackViews.size();
		track->set_sort_index(sortIndex);
	}
	
	view->move_to(0, sortIndex * (track->get_height() + 6) + 6);
	m_trackViews.append(view);
}

void SongView::remove_trackview(Track* track)
{
	foreach(TrackView* view, m_trackViews) {
		if (view->get_track() == track) {
			scene()->removeItem(view);
			delete view;
			return;
		}
	}
}

void SongView::calculate_scene_rect()
{
	int totalheight = 0;
	foreach(Track* track, m_song->get_tracks()) {
		totalheight += track->get_height() + 6;
	}
	totalheight += 200;
	int width = m_song->get_last_frame() / scalefactor + 500;
	
	m_clipsViewPort->setSceneRect(0, 0, width, totalheight);
	m_tlvp->setSceneRect(0, -2, width, -23);
	m_clipsViewPort->centerOn(m_song->get_first_visible_frame() / scalefactor, 0);
}


Command* SongView::zoom()
{
	return new Zoom(this);
}

Command* SongView::hzoom_out()
{
	PENTER;
	m_song->set_hzoom(m_song->get_hzoom() + 1);
	center();
	return (Command*) 0;
}


Command* SongView::hzoom_in()
{
	PENTER;
	m_song->set_hzoom(m_song->get_hzoom() - 1);
	center();
	return (Command*) 0;
}


Command* SongView::vzoom_out()
{
	PENTER;
	return (Command*) 0;
}


Command* SongView::vzoom_in()
{
	PENTER;
	return (Command*) 0;
}

Command* SongView::center()
{
	PENTER2;
	
	return (Command*) 0;
}


Command* SongView::scroll_right()
{
	PENTER3;
	return (Command*) 0;
}


Command* SongView::scroll_left()
{
	PENTER3;
	return (Command*) 0;
}


Command* SongView::shuttle()
{
// 	return new Shuttle(this, m_vp);
}

void SongView::update_shuttle()
{
}


Command* SongView::goto_begin()
{
	printf("SongView::goto_begin\n");
	m_song->set_work_at(0);
	m_song->set_first_visible_frame(0);
	return (Command*) 0;
}


Command* SongView::goto_end()
{
	m_song->set_work_at(m_song->get_last_frame());
	center();
	return (Command*) 0;
}


 
void SongView::update_zoom( int xFactor, int vZoomDirection )
{
	m_song->set_hzoom(xFactor);
}

TrackPanelViewPort* SongView::get_trackpanel_view_port( ) const
{
	return m_tpvp;
}


//eof
