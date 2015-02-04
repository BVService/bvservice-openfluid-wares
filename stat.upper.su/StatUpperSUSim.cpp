/**
  \file StatUpperSUSim.cpp
 */


/*
<sim2doc>

</sim2doc>
 */


#include <openfluid/ware/PluggableSimulator.hpp>


DECLARE_SIMULATOR_PLUGIN


// =====================================================================
// =====================================================================


BEGIN_SIMULATOR_SIGNATURE("stat.upper.su")

DECLARE_NAME("stat.upper.su");
DECLARE_DESCRIPTION("Compute geometric indicators on SU");

DECLARE_VERSION("15.01");
DECLARE_STATUS(openfluid::ware::EXPERIMENTAL);

DECLARE_DOMAIN("geometric");
DECLARE_PROCESS("");
DECLARE_METHOD("");
DECLARE_AUTHOR("Jonathan Vanhouteghem","v.jonath@live.fr");
DECLARE_AUTHOR("Michael Rabotin","rabotin@supagro.inra.fr");


// Attributes
DECLARE_REQUIRED_ATTRIBUTE("area","SU","Area of the SU","m2")


// Variables
DECLARE_PRODUCED_VAR("stat.upper.number","SU","Number of upstream SU","")
DECLARE_PRODUCED_VAR("stat.upper.surface","SU","Total length of upstream SU","m2")



// Scheduling
DECLARE_SCHEDULING_UNDEFINED;



END_SIMULATOR_SIGNATURE


// =====================================================================
// =====================================================================


/**

 */
class StatUpperSUSimulator : public openfluid::ware::PluggableSimulator
{
  private:
    // Map container to store values
    openfluid::core::IDDoubleMap m_SumArea;
    openfluid::core::IDDoubleMap m_NumEntities;

  public:


    StatUpperSUSimulator(): PluggableSimulator()
  {


  }


    // =====================================================================
    // =====================================================================


    ~StatUpperSUSimulator()
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
      // Initialize variables for each SU
      openfluid::core::Unit* SU;
      OPENFLUID_UNITS_ORDERED_LOOP("SU",SU )
      {
        OPENFLUID_InitializeVariable(SU,"stat.upper.surface",0.0);
        OPENFLUID_InitializeVariable(SU,"stat.upper.number",0.0);

      }

      // Variables are computed here
      OPENFLUID_UNITS_ORDERED_LOOP("SU",SU)
      {

        if (SU->getToUnits("SU") == NULL) // Call the recursive method only for SU leafs
          computeRecursive("SU","area",SU,m_SumArea,m_NumEntities);
      }



      return DefaultDeltaT();
    }


    // =====================================================================
    // =====================================================================


    openfluid::base::SchedulingRequest runStep()
    {
      // test if it is the last step
      if (OPENFLUID_GetSimulationDuration()-OPENFLUID_GetCurrentTimeIndex() < OPENFLUID_GetDefaultDeltaT())
      {
        openfluid::core::Unit* SU;
        int ID;
        OPENFLUID_UNITS_ORDERED_LOOP("SU",SU)
        {
          ID=SU->getID();
          OPENFLUID_AppendVariable(SU,"stat.upper.surface",m_SumArea[ID]);
          OPENFLUID_AppendVariable(SU,"stat.upper.number",m_NumEntities[ID]);
        }
      }
      return DefaultDeltaT();
    }


    // =====================================================================
    // =====================================================================


    void finalizeRun()
    {


    }

    // =====================================================================
    // =====================================================================


    void computeRecursive(const openfluid::core::UnitClass_t& UnitsClass,
                          const openfluid::core::AttributeName_t& AttrName,
                          openfluid::core::Unit* U,
                          openfluid::core::IDDoubleMap& MapArea,
                          openfluid::core::IDDoubleMap& MapEntities)
    {
      // postfixed depth-first search to process leafs first and go back to root

      openfluid::core::UnitsPtrList_t* UpperUnits = U->getFromUnits(UnitsClass);
      openfluid::core::Unit* UU = NULL;


      // --- go to leafs recursively
      if (UpperUnits != NULL) //if UpperUnits not empty, upstream Units are present
      {
        OPENFLUID_UNITSLIST_LOOP(UpperUnits,UU) // loop for each upstream unit
        {
          if (!(MapArea.find(UU->getID()) != MapArea.end()))
            computeRecursive(UnitsClass,AttrName,UU,MapArea,MapEntities); // recursive method for upstream unit

        }
      }


      // --- processing of the current unit
      double UpperSum = 0.0;
      double Val;
      double UpperNum=0.0;

      // summ attributes of upper processed units (if exist)
      if (UpperUnits != NULL)
      {
        OPENFLUID_UNITSLIST_LOOP(UpperUnits,UU)
        {
          UpperSum = UpperSum + MapArea[UU->getID()];
          UpperNum= UpperNum+ MapEntities[UU->getID()];
        }
      }

      // add current unit attribute
      OPENFLUID_GetAttribute(U,AttrName,Val);
      UpperSum = UpperSum + Val;
      MapArea[U->getID()] = UpperSum;
      UpperNum = UpperNum + 1;
      MapEntities[U->getID()] = UpperNum;

    }


};


// =====================================================================
// =====================================================================


DEFINE_SIMULATOR_CLASS(StatUpperSUSimulator);

