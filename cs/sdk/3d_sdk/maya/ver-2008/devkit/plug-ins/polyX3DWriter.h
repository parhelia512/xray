//-
// ==========================================================================
// Copyright (C) 1995 - 2006 Autodesk, Inc. and/or its licensors.  All 
// rights reserved.
//
// The coded instructions, statements, computer programs, and/or related 
// material (collectively the "Data") in these files contain unpublished 
// information proprietary to Autodesk, Inc. ("Autodesk") and/or its 
// licensors, which is protected by U.S. and Canadian federal copyright 
// law and by international treaties.
//
// The Data is provided for use exclusively by You. You have the right 
// to use, modify, and incorporate this Data into other products for 
// purposes authorized by the Autodesk software license agreement, 
// without fee.
//
// The copyright notices in the Software and this entire statement, 
// including the above license grant, this restriction and the 
// following disclaimer, must be included in all copies of the 
// Software, in whole or in part, and all derivative works of 
// the Software, unless such copies or derivative works are solely 
// in the form of machine-executable object code generated by a 
// source language processor.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND. 
// AUTODESK DOES NOT MAKE AND HEREBY DISCLAIMS ANY EXPRESS OR IMPLIED 
// WARRANTIES INCLUDING, BUT NOT LIMITED TO, THE WARRANTIES OF 
// NON-INFRINGEMENT, MERCHANTABILITY OR FITNESS FOR A PARTICULAR 
// PURPOSE, OR ARISING FROM A COURSE OF DEALING, USAGE, OR 
// TRADE PRACTICE. IN NO EVENT WILL AUTODESK AND/OR ITS LICENSORS 
// BE LIABLE FOR ANY LOST REVENUES, DATA, OR PROFITS, OR SPECIAL, 
// DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES, EVEN IF AUTODESK 
// AND/OR ITS LICENSORS HAS BEEN ADVISED OF THE POSSIBILITY 
// OR PROBABILITY OF SUCH DAMAGES.
//
// ==========================================================================
//+

#ifndef __POLYX3DWRITER_H
#define __POLYX3DWRITER_H

// polyX3DWriter.h

//
// *****************************************************************************
//
// CLASS:    polyX3DWriter
//
// *****************************************************************************
//
// CLASS DESCRIPTION (polyX3DWriter)
// 
// polyX3DWriter is a class derived from polyWriter.  It currently outputs, in
// X3D compliant format, the following polygonal mesh data:
// - faces and their vertex components
// - vertex coordinates
// - colors per vertex
// - normals per vertex
// - current uv set and coordinates
// - component sets
// - file textures (for the current uv set)
//
// *****************************************************************************

#include "polyWriter.h"

class polyX3DWriter:public polyWriter {

	public:
						polyX3DWriter (const MDagPath& dagPath, MStatus& status);
		virtual			~polyX3DWriter ();
				MStatus extractGeometry ();
				MStatus writeToFile (ostream& os);

	private:
		//Methods
		//
				MStatus	outputSingleSet (ostream& os, 
										 MString setName, 
										 MIntArray faces, 
										 MString textureName);
				MStatus outputX3DShapeTag (ostream& os,
										   const MString shapeName,
										   const MIntArray& faces,
										   const MString textureName,
										   const unsigned int tabCount);
				MStatus outputX3DAppearanceTag (ostream& os, 
												const MString textureName, 
												const unsigned int tabCount);
				MStatus outputX3DIndexedFaceSetTag (ostream& os, 
													const MIntArray& faces, 
													const MString textureName, 
													unsigned int tabCount);
				MStatus outputX3DCoordinateTag (ostream& os, const unsigned int tabCount);
				MStatus outputX3DTextureCoordinateTag (ostream& os, const unsigned int tabCount);
				MStatus outputX3DNormalTag (ostream& os, const unsigned int tabCount);
				MStatus outputX3DColorTag (ostream& os, const unsigned int tabCount);

		//Data Members
		//for keeping track of already outputted X3D tags
		//
		short int			fTagFlags;

		//for formatting purposes - this changes depending on whether or not
		//a group node is being outputted
		//
		short int			fInitialTabCount;

		//for storing UV information
		//
		MFloatArray			fUArray;
		MFloatArray			fVArray;
};

#endif /*__POLYX3DWRITER_H*/