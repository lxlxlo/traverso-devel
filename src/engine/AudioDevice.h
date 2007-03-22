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

$Id: AudioDevice.h,v 1.16 2007/03/22 15:59:23 r_sijrier Exp $
*/

#ifndef AUDIODEVICE_H
#define AUDIODEVICE_H

#include <QObject>
#include <QList>
#include <QHash>
#include <QStringList>
#include <QByteArray>
#include <QTimer>

#include "RingBufferNPT.h"
#include "defines.h"

class AudioDeviceThread;
class Driver;
class Client;
class AudioChannel;
class AudioBus;

class AudioDevice : public QObject
{
	Q_OBJECT

public:
	void set_parameters(int rate, 
			    		nframes_t bufferSize, 
					const QString& driverType, 
					bool capture=true, 
					bool playback=true,
			   		const QString& cardDevice="hw:0");

	void add_client(Client* client);
	void remove_client(Client* client);

	/**
	 * Get the Playback AudioBus instance with name \a name.
	 
	 * You can use this for example in your callback function to get a Playback Bus,
	 * and mix audiodata into the Buses' buffers. 
	 * \sa get_playback_buses_names(), AudioBus::get_buffer()
	 *
	 * @param name The name of the Playback Bus 
	 * @return An AudioBus if one exists with name \a name, 0 on failure
	 */
	AudioBus* get_playback_bus(QByteArray name) const
	{
		return playbackBuses.value(name);
	}
	
	/**
	 * Get the Capture AudioBus instance with name \a name.
	 
	 * You can use this for example in your callback function to get a Capture Bus,
	 * and read the audiodata from the Buses' buffers. 
	 * \sa AudioBus::get_buffer(),  get_capture_buses_names()
	 *
	 * @param name The name of the Capture Bus
	 * @return An AudioBus if one exists with name \a name, 0 on failure
	 */
	AudioBus* get_capture_bus(QByteArray name) const
	{
		return captureBuses.value(name);
	}

	QStringList get_capture_buses_names() const;
	QStringList get_playback_buses_names() const;

	QString get_device_name() const;
	QString get_device_longname() const;
	QString get_driver_type() const;

	QStringList get_available_drivers() const;

	uint get_sample_rate() const;
	uint get_bit_depth() const;

	/**
	 * 
	 * @return The period buffer size, as used by the Audio Driver.
	 */
	nframes_t get_buffer_size() const
	{
		return m_bufferSize;
	}


	void show_descriptors();

	int shutdown();
	
	uint capture_buses_count() const;
	uint playback_buses_count() const;


	trav_time_t get_cpu_time();


private:
	AudioDevice();
	~AudioDevice();
	AudioDevice(const AudioDevice&) : QObject()
	{}

	// allow this function to create one instance
	friend AudioDevice& audiodevice();

	friend class AlsaDriver;
	friend class PADriver;
	friend class Driver;
	friend class AudioDeviceThread;


	Driver* 				driver;
	AudioDeviceThread* 			audioThread;
	QList<Client *> 			clients;
	QHash<QByteArray, AudioChannel* >	playbackChannels;
	QHash<QByteArray, AudioChannel* >	captureChannels;
	QHash<QByteArray, AudioBus* >		playbackBuses;
	QHash<QByteArray, AudioBus* >		captureBuses;
	QStringList				availableDrivers;
#if defined (JACK_SUPPORT)
	QTimer					jackShutDownChecker;
	friend class JackDriver;
#endif

	RingBufferNPT<trav_time_t>*	m_cpuTime;
	volatile size_t		m_runAudioThread;
	trav_time_t		m_cycleStartTime;
	trav_time_t		m_lastCpuReadTime;
	uint 			m_bufferSize;
	uint 			m_rate;
	uint			m_bitdepth;
	QString			m_driverType;

	int run_one_cycle(nframes_t nframes, float delayed_usecs);
	int create_driver(QString driverType, bool capture, bool playback, const QString& cardDevice);

	void setup_buses();
	void post_process();
	void free_memory();

	// These are reserved for Driver Objects only!!
	AudioChannel* register_capture_channel(const QByteArray& busName, const QString& audioType, int flags, uint bufferSize, uint channel );
	AudioChannel* register_playback_channel(const QByteArray& busName, const QString& audioType, int flags, uint bufferSize, uint channel );
	
	int run_cycle(nframes_t nframes, float delayed_usecs);
	
	void set_buffer_size(uint size);
	void set_sample_rate(uint rate);
	void set_bit_depth(uint depth);
	void delay(float delay);

	void transport_cycle_start(trav_time_t time)
	{
		m_cycleStartTime = time;
	}

	void transport_cycle_end(trav_time_t time)
	{
		trav_time_t runcycleTime = time - m_cycleStartTime;
		m_cpuTime->write(&runcycleTime, 1);
	}

	Driver* get_driver() const
	{
		return driver;
	}

	void mili_sleep(int msec);
	void xrun();
	
	size_t run_audio_thread() const;

signals:
	/**
	 *      The stopped() signal is emited just before the AudioDeviceThread will be stopped.
	 *	Connect this signal to all Objects that have a pointer to an AudioBus (For example a VU meter),
	 *	since all he Buses will be deleted, and new ones created when the AudioDevice re-inits
	 *	the AudioDriver.
	 */
	void stopped();
	
	/**
	 *      The started() signal is emited ones the AudioThread and AudioDriver have been succesfully
	 *	setup.
	 */
	void started();
	
	/**
	 *      The driverParamsChanged() signal is emited just before the started() signal, you should 
	 *	connect all objects to this signal who need a pointer to one of the AudioBuses supplied by 
	 *	the AudioDevice!
	 */
	void driverParamsChanged();
	
	/**
	 *        Connect this signal to any Object who need to be informed about buffer under/overruns
	 */
	void bufferUnderRun();
	
	/**
	 *        This signal will be emited after succesfull Client removal from within the GUI Thread!
	 * @param  The Client \a client which as been removed from the AudioDevice
	 */
	void clientRemoved(Client*);

private slots:
	void private_add_client(Client* client);
	void private_remove_client(Client* client);
	void audiothread_finished();
#if defined (JACK_SUPPORT)
	void check_jack_shutdown();
#endif
};


// use this function to get the audiodevice object
AudioDevice& audiodevice();


inline size_t AudioDevice::run_audio_thread( ) const {return m_runAudioThread;}


#endif

//eof
