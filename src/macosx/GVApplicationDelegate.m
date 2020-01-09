/* $Id: GVApplicationDelegate.m,v 1.4 2009/06/03 01:10:56 ellson Exp $ $Revision: 1.4 $ */
/* vim:set shiftwidth=4 ts=8: */

/**********************************************************
*      This software is part of the graphviz package      *
*                http://www.graphviz.org/                 *
*                                                         *
*            Copyright (c) 1994-2008 AT&T Corp.           *
*                and is licensed under the                *
*            Common Public License, Version 1.0           *
*                      by AT&T Corp.                      *
*                                                         *
*        Information and Software Systems Research        *
*              AT&T Research, Florham Park NJ             *
**********************************************************/

#import "GVApplicationDelegate.h"
#import "GVAttributeInspectorController.h"

@implementation GVApplicationDelegate

- (IBAction)showAttributeInspector:(id)sender
{
	if (!_attributeInspectorController)
		_attributeInspectorController = [[GVAttributeInspectorController alloc] init];
	[_attributeInspectorController showWindow:sender];
}

- (BOOL)applicationOpenUntitledFile:(NSApplication*)theApplication
{
	if (!_applicationStarted)
		[[NSDocumentController sharedDocumentController] openDocument:self];
	return YES;
}

- (void)applicationDidFinishLaunching:(NSNotification*)aNotification
{
	_applicationStarted = YES;
}

@end
