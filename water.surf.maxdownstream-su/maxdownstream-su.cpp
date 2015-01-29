/**
  \file maxdownstream-su.cpp
*/


/*
<sim2doc>

</sim2doc>
*/


#include <openfluid/ware/PluggableSimulator.hpp>


DECLARE_SIMULATOR_PLUGIN


// =====================================================================
// =====================================================================


BEGIN_SIMULATOR_SIGNATURE("water.surf.maxdownstream-su")

  DECLARE_NAME("");
  DECLARE_DESCRIPTION("");

  DECLARE_VERSION("15.01");
  DECLARE_STATUS(openfluid::ware::EXPERIMENTAL);

  DECLARE_DOMAIN("");
  DECLARE_PROCESS("");
  DECLARE_METHOD("");
  DECLARE_AUTHOR("","");

    
  
  
// Variables
  DECLARE_REQUIRED_VAR("water.surf.Q.downstream-su","SU","","m3")
  DECLARE_PRODUCED_VAR("water.surf.V.downstream-maxsu","SU","","m3")
  
  
  
// Scheduling
  DECLARE_SCHEDULING_UNDEFINED;

  

END_SIMULATOR_SIGNATURE


// =====================================================================
// =====================================================================


/**

*/
class maxdownstreamsu : public openfluid::ware::PluggableSimulator
{
  private:
	openfluid::core::IDDoubleMap m_MaxValue;
  
  public:

  
    maxdownstreamsu(): PluggableSimulator()
    {
  
  
    }
  
  
    // =====================================================================
    // =====================================================================
  
  
    ~maxdownstreamsu()
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
    	OPENFLUID_InitializeVariable(SU,"water.surf.V.downstream-maxsu",0.0);
    	ID=SU->getID();
    	m_MaxValue[ID]=0.0;

    	    	}
      
      return DefaultDeltaT();
    }


    // =====================================================================
    // =====================================================================
  
  
    openfluid::base::SchedulingRequest runStep()
    {
    	int ID;
    	openfluid::core::Unit* SU;
    	openfluid::core::DoubleValue LevelValue;


    	OPENFLUID_UNITS_ORDERED_LOOP("SU",SU)
    	{
    		OPENFLUID_GetVariable(SU,"water.surf.Q.downstream-su",LevelValue); // recquired var
    		ID=SU->getID();

    		if (LevelValue > m_MaxValue[ID])
    			m_MaxValue[ID]=LevelValue;

    		OPENFLUID_AppendVariable(SU,"water.surf.V.downstream-maxsu",m_MaxValue[ID]);

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


DEFINE_SIMULATOR_CLASS(maxdownstreamsu);

