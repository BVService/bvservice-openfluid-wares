/**
  \file statuppersu.cpp
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

  DECLARE_NAME("");
  DECLARE_DESCRIPTION("");

  DECLARE_VERSION("15.01");
  DECLARE_STATUS(openfluid::ware::EXPERIMENTAL);

  DECLARE_DOMAIN("");
  DECLARE_PROCESS("");
  DECLARE_METHOD("");
  DECLARE_AUTHOR("","");

    
  
// Attributes
  DECLARE_REQUIRED_ATTRIBUTE("area","SU","","m2")

  
// Variables
  DECLARE_PRODUCED_VAR("stat.upper.number","SU","","")
  DECLARE_PRODUCED_VAR("stat.upper.surface","SU","","m2") // surface des aires contributives (somme des surfaces en amont)

  
  
  
// Scheduling
  DECLARE_SCHEDULING_UNDEFINED;

  

END_SIMULATOR_SIGNATURE


// =====================================================================
// =====================================================================


/**

*/
class statuppersu : public openfluid::ware::PluggableSimulator
{
  private:
	openfluid::core::IDDoubleMap m_SumArea; // Computed data est accessible dans ttes les methodes grace a cette ligne (initialise et runstep)
	openfluid::core::IDDoubleMap m_NumEntities; // map pour les cle (identifiant des su) et nombre d'entite en amont de chaque su
  public:

  
    statuppersu(): PluggableSimulator()
    {
  
  
    }
  
  
    // =====================================================================
    // =====================================================================
  
  
    ~statuppersu()
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
// boucle sur toute les su et on les met a 0
        openfluid::core::Unit* SU;
        OPENFLUID_UNITS_ORDERED_LOOP("SU",SU )
        {
        	OPENFLUID_InitializeVariable(SU,"stat.upper.surface",0.0);
        	OPENFLUID_InitializeVariable(SU,"stat.upper.number",0.0);

        }

        // Comme la variable n'est pas liee aux pas de temps on ne va la calculer qu'une seule fois
        OPENFLUID_UNITS_ORDERED_LOOP("SU",SU)
        {

        	if (SU->getToUnits("SU") == NULL) // La fonction recursive par des feuilles pour aller plus bas donc on ne va lancer la fonction recursive que sur des feuilles (une unité qui n'a rien en amont)
        		computeRecursive("SU","area",SU,m_SumArea,m_NumEntities); // Est-ce que l'unité n'a rien en amont : si egale a nulle c'est une feuille donc je lance la fonction recursive
        } // La fonction recursive fonctionne sur des entites de classe su, l'area sera l'attribut sur lequel on fera la somme, (3) la feuille sur laquelle on commence, Computed data est la double map qu'on alimente avec les surfaces cumulees(4)



      return DefaultDeltaT();
    }


    // =====================================================================
    // =====================================================================
  
  
    openfluid::base::SchedulingRequest runStep()
    {
    	if (OPENFLUID_GetSimulationDuration()-OPENFLUID_GetCurrentTimeIndex() < OPENFLUID_GetDefaultDeltaT())  // ne produit la variable qu'au dernier pas de temps
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

      openfluid::core::UnitsPtrList_t* UpperUnits = U->getFromUnits(UnitsClass); // qd on est sur l'unite U (celle sur laquelle on tourne) on demande les unites en amont et on la met dans une liste d'unite qui sapelle uperunit
      openfluid::core::Unit* UU = NULL;


      // --- go to leafs recursivelyMapEntities
      if (UpperUnits != NULL) //si uperunit nest pas vide, donc si des unites en amont
      {
        OPENFLUID_UNITSLIST_LOOP(UpperUnits,UU) // je fait une boucle sur chaque unite au dessus
        {
          if (!(MapArea.find(UU->getID()) != MapArea.end())) // verifie que cette unite est bien dans la strucutre (securite pour eviter les boucle infinies)
          {
            computeRecursive(UnitsClass,AttrName,UU,MapArea,MapEntities); // recalcul les unite au dessus
          }
        }
      }
// si pas d'unite en amont on passe au calcul en dessous

      // --- processing of the current unit
      double UpperSum = 0.0;
      double Val;
      double UpperNum=0.0;

      // summ attributes of upper processed units (if exist)
      if (UpperUnits != NULL) // ne pas lancer la recursivite si nulle (gain de temps)
      {
        OPENFLUID_UNITSLIST_LOOP(UpperUnits,UU)
        {
          UpperSum = UpperSum + MapArea[UU->getID()];
          UpperNum= UpperNum+ MapEntities[UU->getID()]; // chercher le nombre d'entite en haut et les rajouter
         // NumEntities = NumEntities + 1;
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


DEFINE_SIMULATOR_CLASS(statuppersu);

