#include "..\include_opaque\physical_topology_generator_20190221.h"


void PhysicalTopologyGenerator::initialize(void) 
{

}

bool PhysicalTopologyGenerator::runBlock(void) 
{
	if (!generate)
		return false;
	else
		generate = false;

	t_physical_topology outputPhysicalTopology;
	outputPhysicalTopology.physicalTopologyAdjacencyMatrix = physicalTopologyAdjacencyMatrix;
	t_optical_multiplexing_system outputOpticalMultiplexingSystem;
	
	t_integer index{ 0 };
	
	t_integer line{ 0 };
	t_integer nodes = physicalTopologyAdjacencyMatrix[0].size();

	double wavelength = initialWavelength;

	for (t_integer w = 0; w < numberOfOpticalChannelsPerOMS; w++) 
	{
		outputOpticalMultiplexingSystem.wavelengths.push_back(wavelength);
		if (w < numberOfOpticalChannelsPerOMS - 1)
			wavelength += wavelengthSpacing;

		//if (w == 0 || w == 1)
			//outputOpticalMultiplexingSystem.availableWavelengths.push_back(0);
		//else 
			outputOpticalMultiplexingSystem.availableWavelengths.push_back(1);
	}

	while (line < nodes) 
	{
		t_integer column{ 0 };
		while (column < nodes) 
		{
			if (physicalTopologyAdjacencyMatrix[line][column] == 1) 
			{
				outputOpticalMultiplexingSystem.OMSIndex = index;
				outputOpticalMultiplexingSystem.sourceNode = { line + 1 };
				outputOpticalMultiplexingSystem.destinationNode = { column + 1 };
				outputOpticalMultiplexingSystem.maximumNumberOfWavelengths = numberOfOpticalChannelsPerOMS;
				outputOpticalMultiplexingSystem.wavelengths;
				outputOpticalMultiplexingSystem.availableWavelengths;
				
				outputPhysicalTopology.OMS.push_back(outputOpticalMultiplexingSystem);

				physicalTopologyAdjacencyMatrix[line][column]--;
				index++;
			}
			column++;
		}
		line++;
	}
	
	outputSignals[0]->bufferPut((t_physical_topology)outputPhysicalTopology);	
		
	return true;
};


