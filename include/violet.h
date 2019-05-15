#ifndef VIOLET_H
#define VIOLET_H
/*
 * This file should be included for all extension. 
 */
#include "config.h"

// edge related
#include "edge/lineedge.h"
#include "edge/arrowheadedge.h"
#include "edge/labeledlineedge.h"
#include "edge/noteedge.h"
#include "edge/linestyle.h"
#include "edge/bentstyle.h"

// node related
#include "node/notenode.h"
#include "node/pointnode.h"
//#include "node/imagenode.h"

// graph related
#include "graph/vpoint.h"
#include "graph/vrect.h"
#include "graph/vcolor.h"
#include "graph/vstroke.h"
#include "graph/vline.h"
#include "graph/vpath.h"
#include "graph/vrelativepath.h"
#include "graph/vshape.h"
#include "graph/vrectangle.h"
#include "graph/vdiamond.h"
#include "graph/vimage.h"
#include "graph/vicon.h"
#include "graph/vimageicon.h"
#include "graph/vcontext.h"


// content and layout related
#include "content/vcontentborder.h"
#include "content/vcontentbackground.h"
#include "content/vcontentempty.h"
#include "content/vcontenttext.h"
#include "content/vcontentpadding.h"
#include "content/vcontentinrectangle.h"
#include "content/vcontentindiamond.h"
// layout related 
#include "content/horizontallayout.h"
#include "content/verticallayout.h"
#include "content/separator.h"
#include "content/lineseparator.h"

// text related
#include "text/vlinetext.h"
#include "text/singlelinetext.h"
#include "text/multilinetext.h"

// util
#include "util/uuidgen.h"
#include "util/stringutil.h"

#endif
