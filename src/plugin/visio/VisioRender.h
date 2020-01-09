/* $Id: VisioRender.h,v 1.6 2009/06/03 01:10:57 ellson Exp $ $Revision: 1.6 $ */
/* vim:set shiftwidth=4 ts=8: */

/**********************************************************
 *      This software is part of the graphviz package      *
 *                http://www.graphviz.org/                 *
 *                                                         *
 *            Copyright (c) 1994-2004 AT&T Corp.           *
 *                and is licensed under the                *
 *            Common Public License, Version 1.0           *
 *                      by AT&T Corp.                      *
 *                                                         *
 *        Information and Software Systems Research        *
 *              AT&T Research, Florham Park NJ             *
 **********************************************************/

#ifndef VISIORENDER_H
#define VISIORENDER_H

#include <map>
#include <vector>

#include "types.h"

#include "VisioGraphic.h"
#include "VisioText.h"

namespace Visio
{
	typedef std::map<Agnode_t*, unsigned int> NodeIds;
	typedef std::vector<const Graphic*> Graphics;
	typedef std::vector<const Text*> Texts;
	typedef std::vector<const Hyperlink*> Hyperlinks;

	/* object wrapper for render function callback */
	class Render
	{
	public:
		Render();
		~Render();
		
		/* render hierarchy */
		void BeginGraph(GVJ_t* job);
		void EndGraph(GVJ_t* job);
		void BeginPage(GVJ_t* job);
		void EndPage(GVJ_t* job);
		void BeginNode(GVJ_t* job);
		void EndNode(GVJ_t* job);
		void BeginEdge(GVJ_t* job);
		void EndEdge(GVJ_t* job);
		
		/* render graphic + text */
		void AddEllipse(GVJ_t* job, pointf* A, bool filled);
		void AddBezier(GVJ_t* job, pointf* A, int n, bool arrow_at_start, bool arrow_at_end, bool filled);
		void AddPolygon(GVJ_t* job, pointf* A, int n, bool filled);
		void AddPolyline(GVJ_t* job, pointf* A, int n);
		void AddText(GVJ_t *job, pointf p, textpara_t *para);
		void AddAnchor(GVJ_t *job, char *url, char *tooltip, char *target, char *id);
		
	private:
		/* graphics and texts maintenance */
		void ClearGraphicsAndTexts();
		void AddGraphic(GVJ_t* job, const Graphic* graphic);
		void AddText(GVJ_t* job, const Text* text);
		void AddHyperlink(GVJ_t* job, const Hyperlink* hyperlink);
		
		/* output the graphic as top level shape */
		void PrintOuterShape(GVJ_t* job, const Graphic* graphic);
		
		/* output the graphic as a subshape of a top level shape, given its id and bounds */
		void PrintInnerShape(GVJ_t* job, const Graphic* graphic, unsigned int outerId, boxf outerBounds);
		
		/* output the graphic as an edge connector, given the start and end node ids */
		bool PrintEdgeShape(GVJ_t* job, const Graphic* graphic, unsigned int beginId, unsigned int endId, int edgeType);
		
		/* output all the collected texts */
		void PrintTexts(GVJ_t* job);

		/* output all the collected hyperlinks */
		void PrintHyperlinks(GVJ_t* job);

		unsigned int _pageId;	/* sequential page id, starting from 1 */
		unsigned int _shapeId;	/* sequential shape id, starting from 1 */
		unsigned int _hyperlinkId;	/* sequential shape id, starting from 1 */
		
		bool _inComponent;		/* whether we currently inside a node/edge, or not */
		
		Graphics _graphics;		/* currently collected graphics within a component */
		Texts _texts;			/* currently collected texts within a component */
		Hyperlinks _hyperlinks;	/* currently collected hyperlinks within a component */
		
		NodeIds _nodeIds;		/* mapping nodes to assigned shape id */
	};
}
#endif