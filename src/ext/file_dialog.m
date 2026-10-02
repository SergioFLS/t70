// Copyright (c) 2017 Vadim Grigoruk @nesbox // grigoruk@gmail.com
// SPDX-License-Identifier: MIT

#include "file_dialog.h"

#include <AppKit/AppKit.h>

bool file_dialog_load_path(char* buffer)
{
	NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
	NSWindow *keyWindow = [[NSApplication sharedApplication] keyWindow];    
	NSOpenPanel *dialog = [NSOpenPanel openPanel];
	[dialog setAllowsMultipleSelection:NO];

	bool success = false;
	if ( [dialog runModal] == NSModalResponseOK )
	{
		NSURL *url = [dialog URL];
		const char *utf8Path = [[url path] UTF8String];

		strcpy( buffer, utf8Path);

		success = true;
	}

	[pool release];
	[keyWindow makeKeyAndOrderFront:nil];

	return success;
}

bool file_dialog_save_path(const char* name, char* buffer)
{
	NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
	NSWindow *keyWindow = [[NSApplication sharedApplication] keyWindow]; 
	NSSavePanel *dialog = [NSSavePanel savePanel];
	[dialog setExtensionHidden:NO];

	NSString *nameString = [NSString stringWithUTF8String: name];
	[dialog setNameFieldStringValue:nameString];

	bool success = false;
	if ( [dialog runModal] == NSModalResponseOK )
	{
		NSURL *url = [dialog URL];
		const char *utf8Path = [[url path] UTF8String];

		strcpy( buffer, utf8Path);

		success = true;
	}

	[pool release];
	[keyWindow makeKeyAndOrderFront:nil];

	return success;
}
