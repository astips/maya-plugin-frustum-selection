/*

Author  :   astips

Github  :   https://github.com/astips

*/


#include "frustumSelection.h"


void* FrustumSelection::creator()
{
	return new FrustumSelection();
}


bool FrustumSelection::isUndoable() const
{
    return true;
}


MSyntax FrustumSelection::createSyntax()
{
    MSyntax syntax;
	syntax.addFlag( kViewportWidth, kViewportWidthLong, MSyntax::kDouble );
	syntax.addFlag( kViewportHeight, kViewportHeightLong, MSyntax::kDouble );
	syntax.addFlag( kStartFrame, kStartFrameLong, MSyntax::kDouble );
	syntax.addFlag( kEndFrame, kEndFrameLong, MSyntax::kDouble );
	syntax.addFlag( kUseTimeSlider, kUseTimeSliderLong, MSyntax::kBoolean );
	syntax.addFlag( kInvert, kInvertLong, MSyntax::kBoolean );
	syntax.addFlag( kOrthoLeft, kOrthoLeftLong, MSyntax::kDouble );
	syntax.addFlag( kOrthoRight, kOrthoRightLong, MSyntax::kDouble );
	syntax.addFlag( kOrthoBottom, kOrthoBottomLong, MSyntax::kDouble );
	syntax.addFlag( kOrthoTop, kOrthoTopLong, MSyntax::kDouble );
	syntax.addFlag( kOrthoNear, kOrthoNearLong, MSyntax::kDouble );
	syntax.addFlag( kOrthoFar, kOrthoFarLong, MSyntax::kDouble );
	syntax.addFlag( kOrthoZ, kOrthoZLong, MSyntax::kDouble );
    syntax.enableQuery( false );
    syntax.enableEdit( false );
    return syntax;
}


MStatus FrustumSelection::parseArgs( const MArgList& args )
{
	MStatus         status;
	MArgDatabase	argData(syntax(), args);

	if( argData.isFlagSet( kViewportWidth ) )
	{
		double tmp;
		status = argData.getFlagArgument( kViewportWidth, 0, tmp );
		if( !status )
		{
			status.perror( "viewportWidth flag parsing failed" );
			return status;
		}
		width = (unsigned int)tmp;
	}
	else 
	{
		width = 2048;
	}

	if( argData.isFlagSet( kViewportHeight ) )
	{
		double tmp;
		status = argData.getFlagArgument( kViewportHeight, 0, tmp );
		if( !status )
		{
			status.perror( "viewportHeight flag parsing failed" );
			return status;
		}
		height = (unsigned int)tmp;
	}
	else 
	{
		height = 871;
	}

	if( argData.isFlagSet( kStartFrame ) )
	{
		double tmp;
		status = argData.getFlagArgument( kStartFrame, 0, tmp );
		if( !status )
		{
			status.perror( "startFrame flag parsing failed" );
			return status;
		}
		startFrame = tmp;
		isFrameSet = true;
	}
	else
	{
		isFrameSet = false;
	}

	if( argData.isFlagSet( kEndFrame ) )
	{
		double tmp;
		status = argData.getFlagArgument( kEndFrame, 0, tmp );
		if( !status )
		{
			status.perror( "endFrame flag parsing failed" );
			return status;
		}
		endFrame = tmp;
		isFrameSet = true;
	}
	else 
	{
		isFrameSet = false;
	}

	if( argData.isFlagSet( kUseTimeSlider ) )
	{
		bool tmp;
		status = argData.getFlagArgument( kUseTimeSlider, 0, tmp );
		if( !status )
		{
			status.perror( "useTimeSlider flag parsing failed" );
			return status;
		}
		useSlider = tmp;
	}
	else 
	{
		useSlider = false;
	}
	if( useSlider ) 
	{
		isFrameSet = false;
	}
	if( isFrameSet )
	{
		if( startFrame >= endFrame ) 
		{
			isFrameSet = false;
		}
	}

	if( argData.isFlagSet( kInvert ) )
	{
		bool tmp;
		status = argData.getFlagArgument( kInvert, 0, tmp );
		if( !status )
		{
			status.perror( "invert flag parsing failed" );
			return status;
		}
		invert = tmp;
	}
	else
	{
		invert = false;
	}

	if( argData.isFlagSet( kOrthoLeft ) )
	{
		double tmp;
		status = argData.getFlagArgument( kOrthoLeft, 0, tmp );
		if( !status )
		{
			status.perror( "orthoLeft flag parsing failed" );
			return status;
		}
		orthoL = tmp;
	}
	else 
	{
		orthoL = -99999999;
	}

	if( argData.isFlagSet( kOrthoRight ) )
	{
		double tmp;
		status = argData.getFlagArgument( kOrthoRight, 0, tmp );
		if( !status )
		{
			status.perror( "orthoRight flag parsing failed" );
			return status;
		}
		orthoR = tmp;
	}
	else 
	{
		orthoR = 99999999;
	}

	if( argData.isFlagSet( kOrthoBottom ) )
	{
		double tmp;
		status = argData.getFlagArgument( kOrthoBottom, 0, tmp );
		if( !status )
		{
			status.perror( "orthoBottom flag parsing failed" );
			return status;
		}
		orthoB = tmp;
	}
	else 
	{
		orthoB = -99999999;
	}

	if( argData.isFlagSet( kOrthoTop ) )
	{
		double tmp;
		status = argData.getFlagArgument( kOrthoTop, 0, tmp );
		if( !status )
		{
			status.perror( "orthoTop flag parsing failed" );
			return status;
		}
		orthoT = tmp;
	}
	else 
	{
		orthoT = 99999999;
	}

	if( argData.isFlagSet( kOrthoNear ) )
	{
		double tmp;
		status = argData.getFlagArgument( kOrthoNear, 0, tmp );
		if( !status )
		{
			status.perror( "orthoNear flag parsing failed" );
			return status;
		}
		orthoN = tmp;
	}
	else 
	{
		orthoN = -99999999;
	}

	if( argData.isFlagSet( kOrthoFar ) )
	{
		double tmp;
		status = argData.getFlagArgument( kOrthoFar, 0, tmp );
		if( !status )
		{
			status.perror( "orthoFar flag parsing failed" );
			return status;
		}
		orthoF = tmp;
	}
	else 
	{
		orthoF = 99999999;
	}

	if(argData.isFlagSet( kOrthoZ ))
	{
		double tmp;
		status = argData.getFlagArgument( kOrthoZ, 0, tmp );
		if(!status)
		{
			status.perror( "orthoZ flag parsing failed" );
			return status;
		}
		orthoZ = tmp;
	}
	else 
	{
		orthoZ = 0;
	}

	return MS::kSuccess;
}

void FrustumSelection::traverseObjects( MSelectionList& list, MDagPathArray& cam )
{
	unsigned int cam_i;
	unsigned int cam_num = cam.length();
	for( cam_i=0; cam_i<cam_num; cam_i++ )
	{
		MDrawTraversal *trav = new MDrawTraversal;
		trav->enableFiltering( false );
		if( !trav )
		{
			MGlobal::displayWarning( "frustumSelection : failed to create a traversal class !\n" );
			continue;
		}
		trav->setFrustum( cam[cam_i], width, height );

		if( !trav->frustumValid() )
		{
			MGlobal::displayWarning( "frustumSelection : Frustum is invalid !\n" );
			continue;
		}

		trav->traverse();
		
		unsigned int numItems = trav->numberOfItems();
		unsigned int i;
		for ( i=0; i<numItems; i++ )
		{
			MDagPath path;
			trav->itemPath( i, path );
			if( path.isValid() && (path.hasFn(MFn::kMesh) || path.hasFn(MFn::kNurbsSurface) || path.hasFn(MFn::kSubdiv) || path.hasFn(MFn::kPluginShape)) )
			{
				list.add( path.transform() );
			}
		}
		if( trav )
		{
			delete trav;
		}
	}
}

void FrustumSelection::traverseAll( MSelectionList& list )
{
	MDrawTraversal *trav = new MDrawTraversal;
	trav->enableFiltering( false );
	if( !trav )
	{
		MGlobal::displayWarning( "frustumSelection : failed to create a traversal class !\n" );
		return;
	}

	MMatrix worldXform;
	worldXform.setToIdentity();
	worldXform.matrix[3][2] = orthoZ;
	trav->setOrthoFrustum( orthoL, orthoR, orthoB, orthoT, orthoN, orthoF, worldXform);

	if( !trav->frustumValid() )
	{
		MGlobal::displayWarning( "frustumSelection : Ortho Frustum is invalid !\n" );
		return;
	}

	trav->traverse();
	
	unsigned int numItems = trav->numberOfItems();
	unsigned int i;
	for ( i=0; i<numItems; i++ )
	{
		MDagPath path;
		trav->itemPath(i, path);
		if( path.isValid() && (path.hasFn(MFn::kMesh) || path.hasFn(MFn::kNurbsSurface) || path.hasFn(MFn::kSubdiv) || path.hasFn(MFn::kPluginShape)) )
		{
			list.add( path.transform() );
		}
	}
	if( trav ) 
	{
		delete trav;
	}
}

MStatus FrustumSelection::doIt( const MArgList& args )
{
	MStatus status = parseArgs( args );
	if( MS::kSuccess != status ) 
	{
		return status;
	}
	MSelectionList activeList;
	MGlobal::getActiveSelectionList( activeList );
	MItSelectionList iter( activeList, MFn::kCamera );

	MDagPathArray cameras;
	for ( ; !iter.isDone(); iter.next() )
    {
        MDagPath camera;
        iter.getDagPath( camera );
		cameras.append( camera );
	}

	if( cameras.length()<=0 )
	{
		MGlobal::displayWarning( "frustumSelection : select camera(s) please !\n" );
		return MS::kFailure;
	}

	MSelectionList collection;
	
	MTime current_time = MAnimControl::currentTime();

	if( useSlider )
	{
		double startT = MAnimControl::minTime().value();
		double endT = MAnimControl::maxTime().value();
		double t;
		for( t=startT; t<=endT; t++ )
		{
			MAnimControl::setCurrentTime( MTime(t) );
			traverseObjects( collection, cameras );
		}
		MAnimControl::setCurrentTime( current_time );
	}
	else if( isFrameSet )
	{
		double t;
		for( t=startFrame; t<=endFrame; t++ )
		{
			MAnimControl::setCurrentTime( MTime(t) );
			traverseObjects( collection, cameras );
		}
		MAnimControl::setCurrentTime( current_time );
	}
	else 
	{
		traverseObjects( collection, cameras );
	}
	MSelectionList	allGeometry;

	if( invert )
	{
		traverseAll( allGeometry );
		allGeometry.merge( collection, MSelectionList::kRemoveFromList );
	}
	else 
	{
		allGeometry = collection;
	}
	MStringArray foundObj;

	unsigned int sel_i;
	unsigned int sel_num = allGeometry.length();
	for( sel_i=0; sel_i<sel_num; sel_i++ )
	{
		MObject item;
		allGeometry.getDependNode( sel_i, item );
		MFnDagNode dagFn( item );
		foundObj.append( dagFn.partialPathName() );
	}
	
	clearResult();
	setResult( foundObj );

	return MS::kSuccess;
}

MStatus initializePlugin(MObject obj)
{ 
    MStatus   status;
    MFnPlugin plugin( obj, "astips", "1.0", "Any" );

    status = plugin.registerCommand( CMD_NAME,
									 FrustumSelection::creator,
									 FrustumSelection::createSyntax );
    if ( !status ) 
    {
        status.perror( "registering frustumSelection command failed." );
        return status;
    }

    return status;
}


MStatus uninitializePlugin( MObject obj )
{
    MStatus   status;
    MFnPlugin plugin( obj );

    status = plugin.deregisterCommand( CMD_NAME );
    if ( !status )
    {
        status.perror( "deregistering frustumSelection command failed." );
        return status;
    }
    return status;
}
