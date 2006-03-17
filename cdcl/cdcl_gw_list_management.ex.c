//------------------------------------------------------
//
//	This package Manages the list of cluster-neighbors
//
//		For the Cdcl and dependant processes
//
//------------------------------------------------------


#include	<oms_dist_support.h>
#include 	<stdio.h>
#include 	<stdlib.h>
#include 	<malloc.h>
#include 	<opnet.h>
#include 	<string.h>
#include	<time.h>
#include	<math.h>

#include	"cdcl_gw_list_management.h"



//Verify that a cluster already exists in the list
Boolean cluster_present_in_gw_list(int address , List* gw_list){
	int			i;
	struct_gw*	entry;
	
	if (gw_list == NULL)
		op_sim_end("Error : ", "The gw_list is a null list in cluster_present.." , "please correct the pb" , "");
	for(i=0; i < op_prg_list_size(gw_list); i++ )
		{
			entry = (struct_gw*) op_prg_list_access (gw_list , i);
			if (entry->cluster == address)
				return(OPC_TRUE);
		}
	return(OPC_FALSE);
}

//Add a new gateway in gw_list (my own gw_list, or present in neighbourhood_table)
void add_in_gw_list(int address, List* gw_list){
	struct_gw*		entry;
	
	//Don't add doubles
	if (cluster_present_in_gw_list(address , gw_list))
		return;
		
	//Memory allocation (to have a valid entry outside this function)
	entry = (struct_gw*) op_prg_mem_alloc ( sizeof (struct_gw));
	
	//Info
	entry->cluster		= address;
	
	//Insert it
	op_prg_list_insert(gw_list , entry , OPC_LISTPOS_TAIL);	
}

//Empty a gw_list (because some changes occured, and we must empty it before filling it)
void empty_gw_list(List* gw_list){
	int	i;
	
	if (gw_list == NULL)
		op_sim_end("Error : ", "The gw_list is a null list in empty_gw_list()" , "please correct the pb" , "");

	//For each entry
	for (i = op_prg_list_size(gw_list) - 1 ; i >= 0 ; i--)
		op_prg_list_remove (gw_list , i);
}


//Print a line containing the list of the element in gw_list
void print_gw_list(List* gw_list){
	char		msg[300];
	int			i;
	struct_gw	*entry;

	if (gw_list == NULL)
		op_sim_end("Error : ", "The gw_list is a null list in print_gw_list" , "please correct the pb" , "");

	if (op_prg_list_size(gw_list) == 0)
		return;
	
	for (i=0; i < op_prg_list_size(gw_list) ; i++)
		{
			entry = (struct_gw*) op_prg_list_access(gw_list , i);
			sprintf(msg, "	%d	|",entry->cluster);
			cluster_message(msg);
		}
}
