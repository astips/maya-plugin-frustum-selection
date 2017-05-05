/*

Author  :   astips

Github  :   https://github.com/astips

*/


#ifndef __FRUSTUMSELECTION_H__
#define __FRUSTUMSELECTION_H__

#include <math.h>
#include <maya/MFnPlugin.h>
#include <maya/MArgList.h>
#include <maya/MGlobal.h>
#include <maya/MPxCommand.h>
#include <maya/MString.h>
#include <maya/MStringArray.h>
#include <maya/MMatrix.h>
#include <maya/MSyntax.h>
#include <maya/MTypes.h>
#include <maya/MArgParser.h>
#include <maya/MArgDatabase.h>
#include <maya/MDagPath.h> 
#include <maya/MDagPathArray.h> 
#include <maya/MSelectionList.h>
#include <maya/MItSelectionList.h>
#include <maya/MDrawTraversal.h> 
#include <maya/MObject.h>
#include <maya/MFnDagNode.h>
#include <maya/MTime.h> 
#include <maya/MAnimControl.h>

#define kViewportWidth		"-vw"
#define kViewportWidthLong	"-viewportWidth"
#define kViewportHeight		"-vh"
#define kViewportHeightLong	"-viewportHeight"
#define kStartFrame			"-sf"
#define kStartFrameLong		"-startFrame"
#define kEndFrame			"-ef"
#define kEndFrameLong		"-endFrame"
#define kUseTimeSlider		"-uts"
#define kUseTimeSliderLong	"-useTimeSlider"
#define kInvert				"-i"
#define kInvertLong			"-invert"
#define kOrthoLeft			"-ol"
#define kOrthoLeftLong		"-orthoLeft"
#define kOrthoRight			"-or"
#define kOrthoRightLong		"-orthoRight"
#define kOrthoBottom		"-ob"
#define kOrthoBottomLong	"-orthoBottom"
#define kOrthoTop			"-ot"
#define kOrthoTopLong		"-orthoTop"
#define	kOrthoNear			"-on"
#define kOrthoNearLong		"-orthoNear"
#define kOrthoFar			"-of"
#define kOrthoFarLong		"-orthoFar"
#define kOrthoZ				"-oz"
#define kOrthoZLong			"-orthoZ"


class frustumSelection : public MPxCommand
{
public:
						frustumSelection() {};
	virtual				~frustumSelection() {};

	static void*		creator();
	static	MSyntax		createSyntax();
	MStatus				parseArgs( const MArgList& args );

	void				traverseObjects( MSelectionList& list, MDagPathArray& cam );
	void				traverseAll( MSelectionList& list );

    MStatus				doIt( const MArgList& );
    bool				isUndoable() const;

private:
	unsigned int		width;
	unsigned int		height;
	double				startFrame;
	double				endFrame;
	bool				isFrameSet;
	bool				useSlider;
	bool				invert;
	double				orthoL;
	double				orthoR;
	double				orthoB;
	double				orthoT;
	double				orthoN;
	double				orthoF;
	double				orthoZ;
};

#endif 
