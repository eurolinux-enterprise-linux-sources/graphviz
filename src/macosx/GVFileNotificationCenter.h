/* $Id: GVFileNotificationCenter.h,v 1.3 2009/06/03 01:10:56 ellson Exp $ $Revision: 1.3 $ */
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

#import <Foundation/Foundation.h>

@interface GVFileNotificationCenter : NSObject
{
	CFFileDescriptorRef _queue;
	NSMutableSet *_records;
}

+ (void)initialize;
+ (id)defaultCenter;

- (id)init;

- (void)addObserver:(id)observer selector:(SEL)selector path:(NSString *)path;
- (void)removeObserver:(id)observer path:(NSString *)path;

@end
