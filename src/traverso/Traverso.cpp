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

$Id: Traverso.cpp,v 1.13 2006/10/18 12:08:56 r_sijrier Exp $
*/

#include <signal.h>
#include "../config.h"

#include <QMessageBox>

#include "Traverso.h"
#include "Mixer.h"
#include "ProjectManager.h"
#include "Interface.h"
#include <Config.h>
#include <AudioDevice.h>
#include <ContextPointer.h>

// Always put me below _all_ includes, this is needed
// in case we run with memory leak detection enabled!
#include "Debugger.h"


Traverso::Traverso(int argc, char **argv )
	: QApplication ( argc, argv )
{
	QCoreApplication::setOrganizationName("Traverso");
	QCoreApplication::setApplicationName("Traverso");
	
	config().check_and_load_configuration();

	// Initialize random number generator
	srand ( time(NULL) );
	
	init_sse();
	
	prepare_audio_device();
	
	
	iface = new Interface();
	iface->show();
	
// 	pm().start();
	QMetaObject::invokeMethod(&pm(), "start", Qt::QueuedConnection);

	connect(this, SIGNAL(lastWindowClosed()), &pm(), SLOT(exit()));
}

Traverso::~Traverso()
{
	PENTERDES;
	delete iface;
}


void Traverso::shutdown( int signal )
{
	audiodevice().shutdown();
	
	bool save = false;
	
	// Just in case the mouse was grabbed...
	cpointer().release_mouse();
	
	switch(signal) {
		case SIGINT:
			printf("\nCatched the SIGINT signal!\nSaving your work....\n\nShutting down Traverso!\n\n");
			save = true;
			break;
		case SIGSEGV:
			printf("\nCatched the SIGSEGV signal!\n");
			switch (QMessageBox::critical( iface, "Crash",
						"The program made an invalid operation and crashed :-(\n"
						"should I try to save your work?",
						"Yes",
						"No",
						0, 1)) {
				case 0 :
					save = true;
					break;
				case 1 :
					break;
			}
	}

	/*	if (save) {
		Project* project = pm().get_project();
		if (project) {
			if (project->save() > 0)
				printf("Succesfully saved your work!\n");
			else
				printf("Couldn't save your work\n");
		}
	}*/
	
	printf("Stopped\n");

	exit(0);
}


void Traverso::init_sse( )
{
	bool generic_mix_functions = true;

#if defined (SSE_OPTIMIZATIONS)

	unsigned int use_sse = 0;

	asm volatile (
		"mov $1, %%eax\n"
		"pushl %%ebx\n"
		"cpuid\n"
		"popl %%ebx\n"
		"andl $33554432, %%edx\n"
		"movl %%edx, %0\n"
		: "=m" (use_sse)
		:
		: "%eax", "%ecx", "%edx", "memory");

	if (use_sse) {
		printf("Enabling SSE optimized routines\n");

		// SSE SET
		Mixer::compute_peak		= x86_sse_compute_peak;
		Mixer::apply_gain_to_buffer 	= x86_sse_apply_gain_to_buffer;
		Mixer::mix_buffers_with_gain 	= x86_sse_mix_buffers_with_gain;
		Mixer::mix_buffers_no_gain 	= x86_sse_mix_buffers_no_gain;

		generic_mix_functions = false;
	}
#endif


	if (generic_mix_functions) {
		Mixer::compute_peak 		= default_compute_peak;
		Mixer::apply_gain_to_buffer 	= default_apply_gain_to_buffer;
		Mixer::mix_buffers_with_gain 	= default_mix_buffers_with_gain;
		Mixer::mix_buffers_no_gain 	= default_mix_buffers_no_gain;

		printf("No Hardware specific optimizations in use\n");
	}

}

void Traverso::prepare_audio_device( )
{
	int rate = config().get_hardware_int_property("samplerate");
	int bufferSize = config().get_hardware_int_property("bufferSize");
	QString driverType = config().get_hardware_string_property("drivertype");

	if (bufferSize == 0) {
		qWarning("BufferSize read from Settings is 0 !!!");
		bufferSize = 1024;
	}
	if (rate == 0) {
		qWarning("Samplerate read from Settings is 0 !!!");
		rate = 44100;
	}
	if (driverType.isEmpty()) {
		qWarning("Driver type read from Settings is an empty String !!!");
		driverType = "ALSA";
	}

	audiodevice().set_parameters(rate, bufferSize, driverType);

}

void Traverso::saveState( QSessionManager &  manager)
{
	manager.setRestartHint(QSessionManager::RestartIfRunning);
	QStringList command;
	command << "traverso" << "-session" <<  QApplication::sessionId();
	manager.setRestartCommand(command);
}

void Traverso::commitData( QSessionManager &  )
{
	pm().save_project();
}

// eof
