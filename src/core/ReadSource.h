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

$Id: ReadSource.h,v 1.19 2007/04/30 13:49:59 r_sijrier Exp $
*/

#ifndef READSOURCE_H
#define READSOURCE_H

#include "AudioSource.h"

class AudioClip;
class Peak;
class MonoReader;

class ReadSource : public AudioSource
{
	Q_OBJECT
public :
	ReadSource(const QDomNode node);
	ReadSource(const QString& dir, const QString& name);
	ReadSource(const QString& dir, const QString& name, int channelCount, int fileCount);
	~ReadSource();
	
	enum ReadSourceError {
		COULD_NOT_OPEN_FILE = -1,
  		INVALID_CHANNEL_COUNT = -2,
    		ZERO_CHANNELS = -3,
      		CHANNELCOUNT_FILECOUNT_MISMATCH = -4
	};
	
	ReadSource* deep_copy();

	int rb_read(int channel, audio_sample_t* dst, nframes_t start, nframes_t cnt);
	int file_read(int channel, audio_sample_t* dst, nframes_t start, nframes_t cnt) const;

	int init();
	int get_ref_count() const {return m_refcount;}
	int get_error() const {return m_error;}
	int reset_filename(const QString& filename);
	void set_active(bool active);
	void set_was_recording(bool wasRecording);
	
	void set_audio_clip(AudioClip* clip);
	Peak* get_peak(int channel);
	nframes_t get_nframes() const;
	
	QList<MonoReader*> get_private_sources() const {return m_sources;}

private:
	QList<MonoReader*> m_sources;
	int	m_refcount;
	int	m_error;
	
	
	int ref() { return m_refcount++;}
	int add_mono_reader(int channel, int channelNumber, const QString& fileName);
	
	friend class MonoReader;
	friend class ResourcesManager;
};

#endif
