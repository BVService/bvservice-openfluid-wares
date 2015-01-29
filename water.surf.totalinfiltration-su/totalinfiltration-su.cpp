/**
  \file totalinfiltration-su.cpp
*/


/*
<sim2doc>

</sim2doc>
*/


#include <openfluid/ware/PluggableSimulator.hpp>


DECLARE_SIMULATOR_PLUGIN


// =====================================================================
// =====================================================================


BEGIN_SIMULATOR_SIGNATURE("water.surf.totalinfiltration-su")

  DECLARE_NAME("");
  DECLARE_DESCRIPTION("");

  DECLARE_VERSION("15.01");
  DECLARE_STATUS(openfluid::ware::EXPERIMENTAL);

  DECLARE_DOMAIN("");
  DECLARE_PROCESS("");
  DECLARE_METHOD("");
  DECLARE_AUTHOR("JV","");

    
  
  
// Variables
  DECLARE_REQUIRED_VAR("water.surf.H.infiltration","SU","","m")
  DECLARE_PRODUCED_VAR("water.surf.H.totalinfiltrationsu","SU","","m")

  
  
  
// Scheduling
  DECLARE_SCHEDULING_UNDEFINED;

  

END_SIMULATOR_SIGNATURE


// =====================================================================
// =====================================================================


/**

*/
class totalinfiltrationsu : public openfluid::ware::PluggableSimulator
{
  private:
	openfluid::core::IDDoubleMap m_LastValue;
  
  public:

  
    totalinfiltrationsu(): PluggableSimulator()
    {
  
  
    }
  
  
    // =====================================================================
    // =====================================================================
  
  
    ~totalinfiltrationsu()
    {
  
  
    }
  
  
    // =====================================================================
    // =====================================================================
  
  
    void initParams(const openfluid::ware::WareParams_t& /*Params*/)
    {


    }


    // =====================================================================
    // =====================================================================
  
  
    void prepareData()
    {
  
  
    }
  
  
    // =====================================================================
    // =====================================================================
  
  
    void checkConsistency()
    {
  
  
    }
  
  
    // =====================================================================
    // =====================================================================
  
  
    openfluid::base::SchedulingRequest initializeRun()
    {  
    	int ID;
    	openfluid::core::Unit* SU;
    	OPENFLUID_UNITS_ORDERED_LOOP("SU",SU )
    	    	{
    	OPENFLUID_InitializeVariable(SU,"water.surf.H.totalinfiltrationsu",0.0);

    	ID=SU->getID();
    	m_LastValue[ID]=0.0;

    	    	}
      
      return DefaultDeltaT();
    }


    // =====================================================================
    // =====================================================================
  
  
    openfluid::base::SchedulingRequest runStep()
    {
    	int ID;
    	openfluid::core::Unit* SU;
    	openfluid::core::DoubleValue CurrentValue;


    	OPENFLUID_UNITS_ORDERED_LOOP("SU",SU)
    	{
    		OPENFLUID_GetVariable(SU,"water.surf.H.infiltration",CurrentValue);
    		ID=SU->getID();

    		CurrentValue = CurrentValue + m_LastValue[ID];
    		m_LastValue[ID]= CurrentValue;
    		OPENFLUID_AppendVariable(SU,"water.surf.H.totalinfiltrationsu",CurrentValue);

    	}

      return DefaultDeltaT();
    }


    // =====================================================================
    // =====================================================================
  
  
    void finalizeRun()
    {
  
  
    }

};


// =====================================================================
// =====================================================================


DEFINE_SIMULATOR_CLASS(totalinfiltrationsu);

