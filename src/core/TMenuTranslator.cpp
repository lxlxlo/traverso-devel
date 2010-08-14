/*
Copyright (C) 2010 Remon Sijrier

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

#include "TMenuTranslator.h"

TMenuTranslator* TMenuTranslator::m_instance = 0;

TMenuTranslator* TMenuTranslator::instance()
{
        if (m_instance == 0) {
                m_instance = new TMenuTranslator();
        }

        return m_instance;
}

void TMenuTranslator::add_meta_object(const QMetaObject* mo)
{
        m_objects.insertMulti(QString(mo->className()).remove("View"), mo);
}

TMenuTranslator::TMenuTranslator()
{
        add_entry("AudioClip",tr("Audio Clip"));
        add_entry("AudioTrack", tr("Audio Track"));
        add_entry("Curve",tr("Curve"));
        add_entry("CurveNode",tr("Curve Node"));
        add_entry("FadeCurve",tr("Fade Curve"));
        add_entry("FadeRange", tr("Fade Length"));
        add_entry("FadeBend", tr("Bend Factor"));
        add_entry("FadeStrength", tr("Strength Factor"));
        add_entry("Marker",tr("Marker"));
        add_entry("Sheet",tr("Sheet"));
        add_entry("TBusTrack",tr("Bus Track"));
        add_entry("TimeLine",tr("Time Line"));
        add_entry("TBusTrackPanel", tr("Bus Track"));
        add_entry("TrackPanelGain", tr("Gain"));
        add_entry("TrackPanelPan", tr("Panorama"));
        add_entry("TrackPanelLed", tr("Track Panel Button"));
        add_entry("TrackPanelBus", tr("Routing Indicator"));
        add_entry("AudioTrackPanel",tr("Audio Track"));
        add_entry("Plugin",tr("Plugin"));
        add_entry("PlayHead", tr("Play Head"));
        add_entry("WorkCursor", tr("Work Cursor"));
        add_entry("CorrelationMeter", tr("Correlation Meter"));
        add_entry("SpectralMeter", tr("Spectral Analyzer"));

        add_entry("ArmTracks", tr("Arm Tracks"));
        add_entry("Crop", tr("Remove and Magnetic Snap"));
        add_entry("Fade", tr("Fade"));
        add_entry("Gain", tr("Gain"));
        add_entry("MoveClip", tr("Move Clip"));
        add_entry("MoveCurveNod", tr("Move Node"));
        add_entry("MoveEdge", tr("Move Clip Edge"));
        add_entry("MoveMarker", tr("Move Marker"));
        add_entry("MoveTrack", tr("Move Track"));
        add_entry("PlayHeadMove", tr("Move Play Head"));
        add_entry("Shuttle", tr("Shuttle"));
        add_entry("TrackPan", tr("Track Pan"));
        add_entry("WorkCursorMove", tr("Move Work Cursor"));
        add_entry("Zoom", tr("Zoom"));

        add_entry("Track::solo", tr("Solo"));
        add_entry("Track::mute", tr("Mute"));
        add_entry("AudioClip::mute", tr("Mute"));
        add_entry("AudioClip::reset_fade_in", tr("In: Remove"));
        add_entry("AudioClip::reset_fade_out", tr("Out: Remove"));
        add_entry("AudioClip::reset_fade_both", tr("Both: Remove"));
        add_entry("AudioClip::normalize", tr("Normalize"));
        add_entry("AudioClip::lock", tr("Lock"));
        add_entry("AudioClip::clip_fade_in", tr("Fade In"));
        add_entry("AudioClip::clip_fade_out", tr("Fade Out"));
        add_entry("AudioClipManager::select_all_clips", tr("Select all"));
        add_entry("AudioClipManager::invert_clip_selection", tr("Invert"));
        add_entry("FadeCurve::toggle_bypass", tr("Toggle Bypass"));
        add_entry("FadeCurve::set_mode", tr("Cycle Shape"));
        add_entry("FadeCurve::reset", tr("Remove Fade"));
        add_entry("FadeCurve::toggle_raster", tr("Toggle Raster"));
        add_entry("ProcessingData::mute", tr("Mute"));
        add_entry("TSession::start_transport", tr("Play (Start/Stop)"));
        add_entry("Sheet::set_recordable_and_start_transport", tr("Record"));
        add_entry("Sheet::work_next_edge", tr("Workcursor: To next edge"));
        add_entry("Sheet::work_previous_edge", tr("Workcursor: To previous edge"));
        add_entry("Sheet::undo", tr("Undo"));
        add_entry("Sheet::redo", tr("Redo"));
        add_entry("Sheet::toggle_snap", tr("Snap: On/Off"));
        add_entry("Sheet::toggle_effects_mode", tr("Toggle Curve Mode: On/Off"));
        add_entry("Sheet::prev_skip_pos", tr("To previous snap position"));
        add_entry("Sheet::next_skip_pos", tr("To next snap position"));
        add_entry("TSession::toggle_solo", tr("Solo: On/Off"));
        add_entry("TSession::toggle_mute", tr("Mute: On/Off"));
        add_entry("TSession::toggle_arm", tr("Arm: On/Off"));
        add_entry("AudioClipView::fade_range", tr("Closest: Adjust Length"));
        add_entry("AudioClipView::clip_fade_in", tr("In: Adjust Length"));
        add_entry("AudioClipView::clip_fade_out", tr("Out: Adjust Length"));
        add_entry("AudioClipView::select_fade_in_shape", tr("In: Select Preset"));
        add_entry("AudioClipView::select_fade_out_shape", tr("Out: Select Preset"));
        add_entry("AudioClipView::reset_fade", tr("Closest: Delete"));
        add_entry("AudioClipView::set_audio_file", tr("Reset Audio File"));
        add_entry("AudioClipView::edit_properties", tr("Edit Properties"));
        add_entry("AudioTrackView::insert_silence", tr("Insert Silence"));
        add_entry("AudioTrackView::show_track_gain_curve", tr("Show Track Gain Curve"));
        add_entry("CurveView::add_node", tr("New node"));
        add_entry("CurveView::remove_node", tr("Remove node"));
        add_entry("CurveView::remove_all_nodes", tr("Remove all Nodes"));
        add_entry("CurveView::drag_node", tr("Move node"));
        add_entry("CurveView::drag_node_vertical_only", tr("Move node (vertical only)"));
        add_entry("FadeView::bend", tr("Adjust Bend"));
        add_entry("FadeView::strength", tr("Adjust Strength"));
        add_entry("FadeView::select_fade_shape", tr("Select Preset"));
        add_entry("PluginView::edit_properties", tr("Edit..."));
        add_entry("PluginView::remove_plugin", tr("Remove"));
        add_entry("SheetView::touch", tr("Set"));
        add_entry("SheetView::touch_play_cursor", tr("Set"));
        add_entry("SheetView::center", tr("Center View"));
        add_entry("SheetView::scroll_right", tr("Right"));
        add_entry("SheetView::scroll_left", tr("Left"));
        add_entry("SheetView::scroll_up", tr("Up"));
        add_entry("SheetView::scroll_down", tr("Down"));
        add_entry("SheetView::goto_begin", tr("To start"));
        add_entry("SheetView::goto_end", tr("To end"));
        add_entry("SheetView::play_to_begin", tr("To Start"));
        add_entry("SheetView::play_to_end", tr("To End"));
        add_entry("SheetView::play_cursor_move", tr("Move"));
        add_entry("SheetView::work_cursor_move", tr("Move"));
        add_entry("SheetView::add_marker", tr("Add Marker"));
        add_entry("SheetView::add_marker_at_playhead", tr("Add Marker at Playhead"));
        add_entry("SheetView::add_marker_at_work_cursor", tr("Add Marker at Work Cursor"));
        add_entry("SheetView::playhead_to_workcursor", tr("To workcursor"));
        add_entry("SheetView::workcursor_to_playhead", tr("To Playhead"));
        add_entry("SheetView::center_playhead", tr("Center"));
        add_entry("SheetView::add_track", tr("Add Track"));
        add_entry("SheetView::toggle_expand_all_tracks", tr("Expand/Collapse Tracks"));
        add_entry("SheetView::activate_previous_track", tr("To Previous Track"));
        add_entry("SheetView::activate_next_track", tr("To Next Track"));
        add_entry("SheetView::to_upper_context_level", tr("One Context Layer Up"));
        add_entry("SheetView::to_lower_context_level", tr("One Context Layer Down"));
        add_entry("SheetView::browse_to_previous_context_item", tr("To Previous Context Item"));
        add_entry("SheetView::browse_to_next_context_item", tr("To Next Context Item"));
        add_entry("SheetView::browse_to_context_item_above", tr("To Context Item Above"));
        add_entry("SheetView::browse_to_context_item_below", tr("To Context Item Below"));
        add_entry("SheetView::edit_properties", tr("Edit Properties"));
        add_entry("SheetView::browse_to_time_line", tr("To Timeline"));
        add_entry("TimeLineView::add_marker", tr("Add Marker"));
        add_entry("TimeLineView::add_marker_at_playhead", tr("Add Marker at Playhead"));
        add_entry("TimeLineView::add_marker_at_work_cursor", tr("Add Marker at Work Cursor"));
        add_entry("TimeLineView::remove_marker", tr("Remove Marker"));
        add_entry("TimeLineView::drag_marker", tr("Drag Marker"));
        add_entry("TimeLineView::clear_markers", tr("Clear all Markers"));
        add_entry("TimeLineView::playhead_to_marker", tr("Playhead to Marker"));
        add_entry("TimeLineView::TMainWindow::show_marker_dialog", tr("Edit Markers"));
        add_entry("TrackView::edit_properties", tr("Edit properties"));
        add_entry("TrackView::add_new_plugin", tr("Add new Plugin"));
        add_entry("TrackView::select_bus", tr("Select Bus"));
        add_entry("TrackPanelView::TrackView::edit_properties", tr("Edit properties"));
        add_entry("TrackPanelLed::toggle", tr("Toggle On/Off"));
        add_entry("TMainWindow::show_export_widget", tr("Show Export Dialog"));
        add_entry("TMainWindow::show_context_menu", tr("Show Context Menu"));
        add_entry("TMainWindow::show_export_widget", tr("Show Export Dialog"));
        add_entry("TMainWindow::show_context_menu", tr("Show Context Menu"));
        add_entry("TMainWindow::about_traverso", tr("About Traverso"));
        add_entry("TMainWindow::show_project_manager_dialog", tr("Show Project Management Dialog"));
        add_entry("TMainWindow::full_screen", tr("Full Screen"));
        add_entry("TMainWindow::export_keymap", tr("Export keymap"));
        add_entry("TMainWindow::start_transport", tr("Play"));
        add_entry("TMainWindow::set_recordable_and_start_transport", tr("Record"));
        add_entry("TMainWindow::sheet_audio_io_dialog", tr("Show Audio I/O dialog"));
        add_entry("TMainWindow::show_track_finder", tr("Activate Track Finder"));
        add_entry("TMainWindow::audio_io_dialog", tr("Show Audio I/O Dialog"));
        add_entry("TMainWindow::browse_to_first_track_in_active_sheet", tr("Browse to first Track in current View"));
        add_entry("TMainWindow::browse_to_last_track_in_active_sheet", tr("Browse to last Track in current View"));
        add_entry("CorrelationMeterView::set_mode", tr("Toggle display range"));
        add_entry("SpectralMeterView::edit_properties", tr("Settings..."));
        add_entry("SpectralMeterView::set_mode", tr("Toggle average curve"));
        add_entry("SpectralMeterView::reset", tr("Reset average curve"));
        add_entry("SpectralMeterView::export_average_curve", tr("Export average curve"));
        add_entry("SpectralMeterView::screen_capture", tr("Capture Screen"));
        add_entry("Plugin::toggle_bypass", tr("Bypass: On/Off"));
        add_entry("ProjectManager::save_project", tr("Save Project"));
        add_entry("ProjectManager::close_current_project", tr("Close Project"));
        add_entry("ProjectManager::exit", tr("Exit application"));
        add_entry("AudioTrack::toggle_arm", tr("Record: On/Off"));
        add_entry("AudioTrack::silence_others", tr("Silence other tracks"));
        add_entry("Crop::adjust_left", tr("Adjust Left"));
        add_entry("Crop::adjust_right", tr("Adjust Right"));
        add_entry("Gain::increase_gain", tr("Increase"));
        add_entry("Gain::decrease_gain", tr("Decrease"));
        add_entry("TrackPanelGain::gain_increment", tr("Increase"));
        add_entry("TrackPanelGain::gain_decrement", tr("Decrease"));
        add_entry("MarkerView::drag_marker", tr("Move Marker"));
        add_entry("MoveClip::next_snap_pos", tr("To next snap position"));
        add_entry("MoveClip::prev_snap_pos", tr("To previous snap position"));
        add_entry("MoveClip::start_zoom", tr("Jog Zoom"));
        add_entry("MoveClip::move_up", tr("Move Up"));
        add_entry("MoveClip::move_down", tr("Move Down"));
        add_entry("MoveClip::move_left", tr("Move Left"));
        add_entry("MoveClip::move_right", tr("Move Right"));
        add_entry("MoveClip::toggle_vertical_only", tr("Toggle Vertical Only"));
        add_entry("MoveCommand::move_faster", tr("Move Faster"));
        add_entry("MoveCommand::move_slower", tr("Move Slower"));
        add_entry("MoveCommand::toggle_snap_on_off", tr("Toggle Snap on/off"));
        add_entry("MoveCommand::move_left", tr("Move Left"));
        add_entry("MoveCommand::move_right", tr("Move Right"));
        add_entry("MoveCurveNode::move_up", tr("Move Up"));
        add_entry("MoveCurveNode::move_down", tr("Move Down"));
        add_entry("MoveCurveNode::move_left", tr("Move Left"));
        add_entry("MoveCurveNode::move_right", tr("Move Right"));
        add_entry("MoveMarker::move_left", tr("Move Left"));
        add_entry("MoveMarker::move_right", tr("Move right"));
        add_entry("MoveMarker::next_snap_pos", tr("To next snap position"));
        add_entry("MoveMarker::prev_snap_pos", tr("To previous snap position"));
        add_entry("MoveTrack::move_up", tr("Move Up"));
        add_entry("MoveTrack::move_down", tr("Move Down"));
        add_entry("MoveTrack::to_bottom", tr("To Bottom"));
        add_entry("MoveTrack::to_top", tr("To Top"));
        add_entry("MoveEdge::prev_snap_pos", tr("Previous Snap Pos"));
        add_entry("MoveEdge::next_snap_pos", tr("Next Snap Pos"));
        add_entry("PlayHeadMove::move_to_work_cursor", tr("To Play Cursor"));
        add_entry("PlayHeadMove::prev_snap_pos", tr("Previous Snap Pos"));
        add_entry("PlayHeadMove::next_snap_pos", tr("Next Snap Pos"));
        add_entry("Shuttle::move_up", tr("Move Up"));
        add_entry("Shuttle::move_down", tr("Move Down"));
        add_entry("Shuttle::move_left", tr("Move Left"));
        add_entry("Shuttle::move_right", tr("Move Right"));
        add_entry("TrackPanelPan::pan_left", tr("To Left"));
        add_entry("TrackPanelPan::pan_right", tr("To Right"));
        add_entry("WorkCursorMove::move_left", tr("Move Left"));
        add_entry("WorkCursorMove::move_right", tr("Move Right"));
        add_entry("WorkCursorMove::next_snap_pos", tr("To next snap position"));
        add_entry("WorkCursorMove::prev_snap_pos", tr("To previous snap position"));
        add_entry("WorkCursorMove::move_faster", tr("Move Faster"));
        add_entry("WorkCursorMove::move_slower", tr("Move Slower"));
        add_entry("WorkCursorMove::move_to_play_cursor", tr("To Play Cursor"));
        add_entry("WorkCursorMove::toggle_browse_markers", tr("Toggle Snap to Markers On/Off"));
        add_entry("Zoom::vzoom_in", tr("Zoom Vertical In"));
        add_entry("Zoom::vzoom_out", tr("Zoom Vertical Out"));
        add_entry("Zoom::hzoom_in", tr("Zoom Horizontal In"));
        add_entry("Zoom::hzoom_out", tr("Zoom Horizontal Out"));
        add_entry("Zoom::toggle_vertical_horizontal_jog_zoom", tr("Toggle Vertical / Horizontal"));
        add_entry("Zoom::toggle_expand_all_tracks", tr("Expand/Collapse Tracks"));
        add_entry("Zoom::track_vzoom_in", tr("Track Vertical Zoom In"));
        add_entry("Zoom::track_vzoom_out", tr("Track Vertical Zoom Out"));





}

void TMenuTranslator::add_entry(const QString &signature, const QString &translation)
{
        m_dict.insert(signature, translation);
}


QString TMenuTranslator::get_translation_for(const QString &entry)
{
        if (!m_dict.contains(entry)) {
                return QString("TMenuTranslator: %1 not found!").arg(entry);
        }
        return m_dict.value(entry);
}