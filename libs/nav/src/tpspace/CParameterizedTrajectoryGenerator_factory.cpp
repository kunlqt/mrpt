/* +---------------------------------------------------------------------------+
   |                     Mobile Robot Programming Toolkit (MRPT)               |
   |                          http://www.mrpt.org/                             |
   |                                                                           |
   | Copyright (c) 2005-2016, Individual contributors, see AUTHORS file        |
   | See: http://www.mrpt.org/Authors - All rights reserved.                   |
   | Released under BSD License. See details in http://www.mrpt.org/License    |
   +---------------------------------------------------------------------------+ */

#include "nav-precomp.h" // Precomp header

#include <mrpt/nav/tpspace/CParameterizedTrajectoryGenerator.h>
#include <mrpt/system/string_utils.h>

using namespace mrpt::nav;

/*---------------------------------------------------------------
					Class factory
  ---------------------------------------------------------------*/
CParameterizedTrajectoryGenerator * CParameterizedTrajectoryGenerator::CreatePTG(const std::string &ptgClassName_, mrpt::utils::TParameters<double> &params)
{
	MRPT_START

	mrpt::utils::registerAllPendingClasses();

	// Special names for backwards compatibility with MRPT < 1.5.0
	std::string ptgClassName = mrpt::system::trim(ptgClassName_);
	if (ptgClassName.size()==1) {
		switch (ptgClassName[0])
		{
		case '1': ptgClassName="CPTG_DiffDrive_C"; break; 
		case '2': ptgClassName="CPTG_DiffDrive_alpha"; break; 
		case '3': ptgClassName="CPTG_DiffDrive_CCS"; break; 
		case '4': ptgClassName="CPTG_DiffDrive_CC"; break; 
		case '5': ptgClassName="CPTG_DiffDrive_CS"; break; 
		};
	}

	// Factory:
	const mrpt::utils::TRuntimeClassId *classId = mrpt::utils::findRegisteredClass( ptgClassName );
	if (!classId) {
		THROW_EXCEPTION_CUSTOM_MSG1("[CreatePTG] No PTG named `%s` is registered!",ptgClassName.c_str());
	}
	
	CParameterizedTrajectoryGenerator *ptg = dynamic_cast<CParameterizedTrajectoryGenerator*>( classId->createObject() );
	if (!ptg) {
		THROW_EXCEPTION_CUSTOM_MSG1("[CreatePTG] Object of type `%s` seems not to be a PTG!",ptgClassName.c_str());
	}

	ptg->setParams(params);
	return ptg;
	MRPT_END
}