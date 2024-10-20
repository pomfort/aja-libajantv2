/* SPDX-License-Identifier: MIT */
/**
	@file		ancillarydatafactory.cpp
	@brief		Implementation of the AJAAncillaryDataFactory class.
	@copyright	(C) 2010-2022 AJA Video Systems, Inc.
**/

#include "ancillarydatafactory.h"
#include "ancillarydata.h"
#include "ancillarydata_timecode_atc.h"
#include "ancillarydata_timecode_vitc.h"
#include "ancillarydata_cea708.h"
#include "ancillarydata_cea608_vanc.h"
#include "ancillarydata_cea608_line21.h"
#include "ancillarydata_framestatusinfo524D.h"
#include "ancillarydata_framestatusinfo5251.h"
//#include "ancillarydata_smpte352.h"
//#include "ancillarydata_smpte2016-3.h"
//#include "ancillarydata_smpte2051.h"


AJAAncillaryData * AJAAncillaryDataFactory::Create (const AJAAncDataType inAncType, const AJAAncillaryData & inAncData)
{
	return Create (inAncType, &inAncData);
}


AJAAncillaryData * AJAAncillaryDataFactory::Create (const AJAAncDataType inAncType, const AJAAncillaryData *pAncData)
{
	AJAAncillaryData * pResult (NULL);
	switch (inAncType)
	{
		case AJAAncDataType_Unknown:				pResult = new AJAAncillaryData(pAncData);						break;	//	Use base type for 'Unknown'
		case AJAAncDataType_Timecode_ATC:			pResult = new AJAAncillaryData_Timecode_ATC(pAncData);			break;
		case AJAAncDataType_Timecode_VITC:			pResult = new AJAAncillaryData_Timecode_VITC(pAncData);			break;
		case AJAAncDataType_Cea708:					pResult = new AJAAncillaryData_Cea708(pAncData);				break;
		case AJAAncDataType_Cea608_Vanc:			pResult = new AJAAncillaryData_Cea608_Vanc(pAncData);			break;
		case AJAAncDataType_Cea608_Line21:			pResult = new AJAAncillaryData_Cea608_Line21(pAncData);			break;
		case AJAAncDataType_FrameStatusInfo524D:	pResult = new AJAAncillaryData_FrameStatusInfo524D(pAncData);	break;
		case AJAAncDataType_FrameStatusInfo5251:	pResult = new AJAAncillaryData_FrameStatusInfo5251(pAncData);	break;

 		case AJAAncDataType_Smpte2016_3:			break;	//	pResult = new AJAAncillaryData_Smpte2016_3(pAncData);	break;
 		case AJAAncDataType_Smpte352:				break;	//	pResult = new AJAAncillaryData_Smpte352(pAncData);		break;
 		case AJAAncDataType_Smpte2051:				break;	//	pResult = new AJAAncillaryData_Smpte2051(pAncData);		break;
 		case AJAAncDataType_HDR_SDR:				break;
 		case AJAAncDataType_HDR_HDR10:				break;
 		case AJAAncDataType_HDR_HLG:				break;
#if !defined(_DEBUG)
		default:	break;
#else
		case AJAAncDataType_Size:					break;
#endif
	}
	if (pResult)
		//	Populate the specialized AJAAncillaryData object's member variables from the packet data...
		pResult->ParsePayloadData();
	return pResult;
}



AJAAncDataType AJAAncillaryDataFactory::GuessAncillaryDataType (const AJAAncillaryData & inAncData)
{
	return GuessAncillaryDataType (&inAncData);
}

//---------------------------------
// Given a "raw" (unparsed) AJAAncillaryData object, see if we can identify it based on its contents (e.g. DID, SID, location, etc.)
// (Architectural note: while this isn't a "factory" method, per se, it's convenient to be here because the factory is the one thing
// that knows about ALL classes, and you're often calling this as a prelude to creating a new object of the appropriate type using
// the factory.)
//

AJAAncDataType AJAAncillaryDataFactory::GuessAncillaryDataType (const AJAAncillaryData * pAncData)
{
	AJAAncDataType result = AJAAncDataType_Unknown;

		// walk through each of the known derived AncillaryData derived classes
		// and ask them if they recognize this data

// 	if ( (result = AJAAncillaryData_Smpte2016_3::RecognizeThisAncillaryData(pAncData)) != AJAAncDataType_Unknown)
// 		return result;
// 
	if ( (result = AJAAncillaryData_Timecode_ATC::RecognizeThisAncillaryData(pAncData)) != AJAAncDataType_Unknown)
		return result;

	if ( (result = AJAAncillaryData_Timecode_VITC::RecognizeThisAncillaryData(pAncData)) != AJAAncDataType_Unknown)
		return result;

	if ( (result = AJAAncillaryData_Cea708::RecognizeThisAncillaryData(pAncData)) != AJAAncDataType_Unknown)
		return result;

	if ( (result = AJAAncillaryData_Cea608_Vanc::RecognizeThisAncillaryData(pAncData)) != AJAAncDataType_Unknown)
		return result;

	if ( (result = AJAAncillaryData_Cea608_Line21::RecognizeThisAncillaryData(pAncData)) != AJAAncDataType_Unknown)
		return result;

// 	if ( (result = AJAAncillaryData_Smpte352::RecognizeThisAncillaryData(pAncData)) != AJAAncDataType_Unknown)
// 		return result;

// 	if ( (result = AJAAncillaryData_Smpte2051::RecognizeThisAncillaryData(pAncData)) != AJAAncDataType_Unknown)
// 		return result;
// 
	if ( (result = AJAAncillaryData_FrameStatusInfo524D::RecognizeThisAncillaryData(pAncData)) != AJAAncDataType_Unknown)
		return result;

	if ( (result = AJAAncillaryData_FrameStatusInfo5251::RecognizeThisAncillaryData(pAncData)) != AJAAncDataType_Unknown)
		return result;

	return result;
}

