#include <iostream>
#include <vector>
#include <string>
#include <boost/algorithm/string.hpp>
using namespace boost;
using namespace std;

    typedef vector< string > split_vector_type;
    
int main()
{
    
    split_vector_type v; // #2: Search for tokens
	string str("PhysFaceToFaceStartDate, BillRecurringAncillary, AddOutpatientTherapyCodeModifiers, COBReported, COBUseFullDetailFromPrior, COBEnforcePaperBalancing, ApplyNonSpecific, \
		PlaceOfServiceValidation, ShowHigherPriority, NonCoveredCharges, UseClaimAdjReasonCode, ReasonCodeID, ClaimAdjReasonCategory, NonCoveredValueCodes, ABNIssuedDate, ShowLowerPriority, \
		TFA14thVisitCloseToThreshold, TFA20thVisitCloseToThreshold, AllowNoChargeCOBClaim, TFADisciplineIndependentDate, TFACoveredUntimelyDate, PECOSEnrolledDate, FunctionalGCodeStartDate, FunctionalGCodeValidation, \
		ShowPrimaryPayerUnitsOnClaim, SplitByDay, StateID, PhysicianEnrollmentValidation, PhysicianEnrollmentDate, ICD10StartDate, ShowHippsCodeStartDate, ClaimTotalOnLastPage, HospiceReporting8358StartDate, \
		Paper1500Version, SequentialBilling, NonTreatmentTime, Respite5DayStartDate,ValueCode44Flag, EncounterPhysicianEffDate, UnitsOnBillNotPositive, DischDayByDeathOnBill, LateFilingEffectiveDate, HospicePaymentAdjEffDate, ServiceIntensityAddOnLOCID, \
		LocationCodeReasonCodeID, LocationCodeGroupCode, TFACY2015Date, SplitEmployeeDCMedicaid, SplitByMonth, AIN9016StartDate");
	
    split( v, str, is_any_of(", "), token_compress_on );
	
    cout<<v.size();
    
	for (vector<string>::iterator it = v.begin(); it != v.end(); it++)
	{
		//cout << (*it);
	}
    cout<<endl<<"sid";
    
    
	return 0;
}