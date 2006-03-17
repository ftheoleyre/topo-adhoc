/* Process model C form file: process_wlan_mac_interface.pr.c */
/* Portions of this file copyright 1992-2002 by OPNET Technologies, Inc. */



/* This variable carries the header into the object file */
static const char process_wlan_mac_interface_pr_c [] = "MIL_3_Tfile_Hdr_ 81A 30A op_runsim 7 43C50900 43C50900 1 ares-theo-1 ftheoley 0 0 none none 0 0 none 0 0 0 0 0 0                                                                                                                                                                                                                                                                                                                                                                                                               ";
#include <string.h>



/* OPNET system definitions */
#include <opnet.h>

#if defined (__cplusplus)
extern "C" {
#endif
FSM_EXT_DECS
#if defined (__cplusplus)
} /* end of 'extern "C"' */
#endif


/* Header Block */

/***** Include Files. *****/

/* Address assignment definitions.	*/
#include "oms_auto_addr_support.h"

/* Topology analysis-related definitions. */
#include "oms_tan.h"

/* Process registry-related definitions. */
#include "oms_pr.h"

/***** Transition Macros ******/
#define MAC_LAYER_PKT_ARVL	(intrpt_type == OPC_INTRPT_STRM && intrpt_strm == instrm_from_mac)
#define APPL_LAYER_PKT_ARVL	(intrpt_type == OPC_INTRPT_STRM && intrpt_strm != instrm_from_mac)
#define MAC_BROADCAST		-1

/***** Functional declaration ******/
static void			wlan_mac_higher_layer_intf_sv_init ();
static void			wlan_mac_higher_layer_register_as_arp ();


/* End of Header Block */


#if !defined (VOSD_NO_FIN)
#undef	BIN
#undef	BOUT
#define	BIN		FIN_LOCAL_FIELD(last_line_passed) = __LINE__ - _block_origin;
#define	BOUT	BIN
#define	BINIT	FIN_LOCAL_FIELD(last_line_passed) = 0; _block_origin = __LINE__;
#else
#define	BINIT
#endif /* #if !defined (VOSD_NO_FIN) */



/* State variable definitions */
typedef struct
	{
	/* Internal state tracking for FSM */
	FSM_SYS_STATE
	/* State Variables */
	Objid	                  		my_objid;
	Objid	                  		my_node_objid;
	int	                    		instrm_from_mac;
	int	                    		outstrm_to_mac;
	OmsT_Aa_Address_Handle	 		oms_aa_handle;
	int	                    		mac_address;
	Ici*	                   		wlan_mac_req_iciptr;
	} process_wlan_mac_interface_state;

#define pr_state_ptr            		((process_wlan_mac_interface_state*) SimI_Mod_State_Ptr)
#define my_objid                		pr_state_ptr->my_objid
#define my_node_objid           		pr_state_ptr->my_node_objid
#define instrm_from_mac         		pr_state_ptr->instrm_from_mac
#define outstrm_to_mac          		pr_state_ptr->outstrm_to_mac
#define oms_aa_handle           		pr_state_ptr->oms_aa_handle
#define mac_address             		pr_state_ptr->mac_address
#define wlan_mac_req_iciptr     		pr_state_ptr->wlan_mac_req_iciptr

/* This macro definition will define a local variable called	*/
/* "op_sv_ptr" in each function containing a FIN statement.	*/
/* This variable points to the state variable data structure,	*/
/* and can be used from a C debugger to display their values.	*/
#undef FIN_PREAMBLE
#define FIN_PREAMBLE	process_wlan_mac_interface_state *op_sv_ptr = pr_state_ptr;


/* Function Block */

enum { _block_origin = __LINE__ };
static void
wlan_mac_higher_layer_intf_sv_init ()
	{
	int			type_of_service;

	/** Initializes all state variables used in this	**/
	/** process model.									**/
	FIN (wlan_mac_higher_layer_intf_sv_init ());

	/* Object identifier for the surrounding module and node.	*/
	my_objid = op_id_self ();
	my_node_objid = op_topo_parent (my_objid);

	/* Stream indices to and from the WLAN MAC process.	*/
	/* these will be set in the "exit execs" of "init".	*/
	outstrm_to_mac  = OPC_INT_UNDEF;
	instrm_from_mac = OPC_INT_UNDEF;

	/* Determine the destination to which packet should	*/
	/* be sent,and the prioritization to be provided to	*/
	/* the transmitted packet.							*/
	op_ima_obj_attr_get (my_objid, "Type of Service", 	  &type_of_service);

	/* Some interface control information is needed to	*/
	/* indicate to the MAC of the destination to which	*/
	/* a given packet needs to be sent. Create it.		*/
	wlan_mac_req_iciptr = op_ici_create ("wlan_mac_request");
	op_ici_attr_set (wlan_mac_req_iciptr, "type_of_service", type_of_service);
	op_ici_attr_set (wlan_mac_req_iciptr, "protocol_type",   0x800);

	FOUT;
	}

static void
wlan_mac_higher_layer_register_as_arp ()
	{
	char				proc_model_name [128];
	OmsT_Pr_Handle		own_process_record_handle;
	Prohandle			own_prohandle;

	/** Register this process in the model-wide process registry.	**/
	FIN (wlan_mac_higher_layer_register_as_arp ());

	/* Obtain the process model name and process handle.	*/
	op_ima_obj_attr_get (my_objid, "process model", proc_model_name);
	own_prohandle = op_pro_self ();

	/* Register this process in the model-wide process registry	*/
	own_process_record_handle = (OmsT_Pr_Handle) oms_pr_process_register (
			my_node_objid, my_objid, own_prohandle, proc_model_name);

	/* Register this protocol attribute and the element address	*/
	/* of this process into the model-wide registry.			*/
	oms_pr_attr_set (own_process_record_handle,
		"protocol",		OMSC_PR_STRING,		"arp",
		OPC_NIL);

	FOUT;
	}


/* End of Function Block */

/* Undefine optional tracing in FIN/FOUT/FRET */
/* The FSM has its own tracing code and the other */
/* functions should not have any tracing.		  */
#undef FIN_TRACING
#define FIN_TRACING

#undef FOUTRET_TRACING
#define FOUTRET_TRACING

#if defined (__cplusplus)
extern "C" {
#endif
	void process_wlan_mac_interface (void);
	Compcode process_wlan_mac_interface_init (void **);
	void process_wlan_mac_interface_diag (void);
	void process_wlan_mac_interface_terminate (void);
	void process_wlan_mac_interface_svar (void *, const char *, char **);
#if defined (__cplusplus)
} /* end of 'extern "C"' */
#endif




/* Process model interrupt handling procedure */


void
process_wlan_mac_interface (void)
	{
	int _block_origin = 0;
	FIN (process_wlan_mac_interface ());
	if (1)
		{
		List*				proc_record_handle_list_ptr;
		int					record_handle_list_size;
		OmsT_Pr_Handle		process_record_handle;
		Objid				mac_module_objid;
		Boolean				dest_addr_okay = OPC_FALSE;
		double				ne_address = OPC_DBL_UNDEF;
		int					curr_dest_addr = OMSC_AA_AUTO_ASSIGN;
		Packet*				pkptr;
		int					intrpt_type = OPC_INT_UNDEF;
		int					intrpt_strm = OPC_INT_UNDEF;
		int					i;
		OmsT_Aa_Address_Info * ith_address_info_ptr;
		
		
		Ici*	ici_dest_ptr;


		FSM_ENTER (process_wlan_mac_interface)

		FSM_BLOCK_SWITCH
			{
			/*---------------------------------------------------------*/
			/** state (init) enter executives **/
			FSM_STATE_ENTER_UNFORCED_NOLABEL (0, "init", "process_wlan_mac_interface () [init enter execs]")
				{
				/* Initialize the state variables used by this model.	*/
				wlan_mac_higher_layer_intf_sv_init ();
				
				/* Register this process as "arp" so that lower layer	*/
				/* MAC process can connect to it.						*/
				wlan_mac_higher_layer_register_as_arp ();
				
				/* Schedule a self interrupt to wait for lower layer	*/
				/* wlan MAC process to initialize and register itself in	*/
				/* the model-wide process registry.						*/
				op_intrpt_schedule_self (op_sim_time (), 0);
				
				}


			/** blocking after enter executives of unforced state. **/
			FSM_EXIT (1,process_wlan_mac_interface)


			/** state (init) exit executives **/
			FSM_STATE_EXIT_UNFORCED (0, "init", "process_wlan_mac_interface () [init exit execs]")
				{
				/* Schedule a self interrupt to wait for lower layer	*/
				/* wlan MAC process to initialize and register itself in*/
				/* the model-wide process registry.						*/
				op_intrpt_schedule_self (op_sim_time (), 0);
				
				}


			/** state (init) transition processing **/
			FSM_TRANSIT_FORCE (5, state5_enter_exec, ;, "default", "", "init", "init2")
				/*---------------------------------------------------------*/



			/** state (idle) enter executives **/
			FSM_STATE_ENTER_UNFORCED (1, state1_enter_exec, "idle", "process_wlan_mac_interface () [idle enter execs]")
				{
				
				}


			/** blocking after enter executives of unforced state. **/
			FSM_EXIT (3,process_wlan_mac_interface)


			/** state (idle) exit executives **/
			FSM_STATE_EXIT_UNFORCED (1, "idle", "process_wlan_mac_interface () [idle exit execs]")
				{
				/* The only interrupt expected in this state is a	*/
				/* stream interrupt. It can be either from the MAC	*/
				/* layer for a packet destined for this node or		*/
				/* from the application layer for a packet destined	*/
				/* for some other node.								*/
				intrpt_type = op_intrpt_type ();
				intrpt_strm = op_intrpt_strm ();
				pkptr = op_pk_get (intrpt_strm);
				
				}


			/** state (idle) transition processing **/
			FSM_INIT_COND (APPL_LAYER_PKT_ARVL)
			FSM_TEST_COND (MAC_LAYER_PKT_ARVL)
			FSM_TEST_LOGIC ("idle")

			FSM_TRANSIT_SWITCH
				{
				FSM_CASE_TRANSIT (0, 2, state2_enter_exec, ;, "APPL_LAYER_PKT_ARVL", "", "idle", "appl layer arrival")
				FSM_CASE_TRANSIT (1, 3, state3_enter_exec, ;, "MAC_LAYER_PKT_ARVL", "", "idle", "mac layer arrival")
				}
				/*---------------------------------------------------------*/



			/** state (appl layer arrival) enter executives **/
			FSM_STATE_ENTER_FORCED (2, state2_enter_exec, "appl layer arrival", "process_wlan_mac_interface () [appl layer arrival enter execs]")
				{
				/* A packet has arrived from the application layer.	*/
				/* If the destination address specified is "Random"	*/
				/* then generate a destination and forward the appl	*/
				/* packet to the MAC layer with that information.	*/
				/*if (destination_address == OMSC_AA_AUTO_ASSIGN)
					{
					// Initialize current destination address to the Auto 
					// Assign value										  
					curr_dest_addr = destination_address;
				
					// Call function to generate a random destination	
					// from the pool of available addresses.			
					oms_aa_dest_addr_get (oms_aa_handle, &curr_dest_addr);
				
					// Keep on generating the random addresses until source 
					// address is not same as current address.				
					while (curr_dest_addr == mac_address)
						{
						// Initialize current destination address to the Auto 
						// Assign value										  
						curr_dest_addr = destination_address;
				
						// Call function to generate a random destination	
						// from the pool of available addresses.			
						oms_aa_dest_addr_get (oms_aa_handle, &curr_dest_addr);
						}
					
					}
				else
					{
					// The packet needs to be sent to an explicit	
					// destination as specified in the "Destination	
					// Address" attribute.							
					curr_dest_addr = destination_address;
					}
				*/
				
				int pk_type;
				
				//Gathers the Ici sent along the packet
				ici_dest_ptr = op_intrpt_ici();
				op_ici_attr_get(ici_dest_ptr,"dest_addr",&curr_dest_addr);
				
				//debug
				op_pk_nfd_get(pkptr , "OPTION_TYPE", &pk_type);
				/*if (pk_type == 11)
					{
						op_pk_print(pkptr);
						printf("----------------->%d\n", curr_dest_addr);
					}
				*/
				
				//Debug Purpose if No 
				if (ici_dest_ptr == NULL)
					op_pk_print(pkptr);
				
				/* Set this information in the interface control	*/
				/* information to be sent to the MAC layer.			*/
				op_ici_attr_set (wlan_mac_req_iciptr, "dest_addr", curr_dest_addr);
				
				/* Install the control informationand send it to	*/
				/* the MAC layer.									*/
				op_ici_install (wlan_mac_req_iciptr);
				op_pk_send (pkptr, outstrm_to_mac);
				
				}


			/** state (appl layer arrival) exit executives **/
			FSM_STATE_EXIT_FORCED (2, "appl layer arrival", "process_wlan_mac_interface () [appl layer arrival exit execs]")
				{
				}


			/** state (appl layer arrival) transition processing **/
			FSM_TRANSIT_FORCE (1, state1_enter_exec, ;, "default", "", "appl layer arrival", "idle")
				/*---------------------------------------------------------*/



			/** state (mac layer arrival) enter executives **/
			FSM_STATE_ENTER_FORCED (3, state3_enter_exec, "mac layer arrival", "process_wlan_mac_interface () [mac layer arrival enter execs]")
				{
				/* A packet arrived from the MAC layer. Since the MAC	*/
				/* layer would have forwarded this only if it were		*/
				/* destined for this node, forward this packet to the	*/
				/* sink module.											*/
				
				//op_pk_send (op_pk_copy(pkptr) , 0);
				op_pk_send (pkptr , 0);
				
				}


			/** state (mac layer arrival) exit executives **/
			FSM_STATE_EXIT_FORCED (3, "mac layer arrival", "process_wlan_mac_interface () [mac layer arrival exit execs]")
				{
				}


			/** state (mac layer arrival) transition processing **/
			FSM_TRANSIT_FORCE (1, state1_enter_exec, ;, "default", "", "mac layer arrival", "idle")
				/*---------------------------------------------------------*/



			/** state (wait) enter executives **/
			FSM_STATE_ENTER_UNFORCED (4, state4_enter_exec, "wait", "process_wlan_mac_interface () [wait enter execs]")
				{
				
				}


			/** blocking after enter executives of unforced state. **/
			FSM_EXIT (9,process_wlan_mac_interface)


			/** state (wait) exit executives **/
			FSM_STATE_EXIT_UNFORCED (4, "wait", "process_wlan_mac_interface () [wait exit execs]")
				{
				/* Obtain the MAC layer information for the local MAC	*/
				/* process from the model-wide registry.				*/
				proc_record_handle_list_ptr = op_prg_list_create ();
				oms_pr_process_discover (my_objid, proc_record_handle_list_ptr,
					"node objid",	OMSC_PR_OBJID,		my_node_objid,
					"protocol", 	OMSC_PR_STRING,		"mac",
					OPC_NIL);
				 
				/* If the MAC process regostered itself, then there	*/
				/* must be a valid match							*/
				record_handle_list_size = op_prg_list_size (proc_record_handle_list_ptr);
					
				if (record_handle_list_size !=  1)
					{
					/* An error should be created if there are more	*/
					/* than one WLAN-MAC process in the local node,	*/
					/* or if no match is found.						*/
					op_sim_end ("Error: either zero or several WLAN MAC processes found in the interface", "", "", "");
					}
				else
					{
					/*	Obtain a handle on the process record.	*/
					process_record_handle = (OmsT_Pr_Handle) op_prg_list_access (proc_record_handle_list_ptr, 0);
				 
					/* Obtain the module objid for the WLAN MAC module. 		*/
					oms_pr_attr_get (process_record_handle, "module objid", OMSC_PR_OBJID, &mac_module_objid);
				 
					/* Obtain the stream numbers connected to and from the	*/
					/* WLAN MAC layer process.								*/
					oms_tan_neighbor_streams_find (my_objid, mac_module_objid, &instrm_from_mac, &outstrm_to_mac);
				 
					/* Obtain the address handle maintained by the MAC process.	*/
					oms_pr_attr_get (process_record_handle, "address",             OMSC_PR_NUMBER,  &ne_address);
					oms_pr_attr_get (process_record_handle, "auto address handle", OMSC_PR_ADDRESS, &oms_aa_handle);
				 
					/* Set the variable to indicate the MAC address of the	*/
					/* associated MAC layer process.						*/
					mac_address = (int) ne_address;
					}
				
				
				
				//// NO DEST_ADDRESS VALIDATION : the destination address is specified in the packet, not arbitrarly !!!!!!
				
				
				
				
				/* Check if the specified destination address (via the "Destination	*/
				/* Address" attribute) is valid or not.								*/
				
				/* 
				//Check for broadcast address.										
				if (destination_address == MAC_BROADCAST)
					{
					// Do Nothing	
					}
				else if (destination_address != OMSC_AA_AUTO_ASSIGN)
					{
				*/
					
				/*	// An explicit destination address has been specified. Check if	
					// it is a valid address.										
					if (destination_address == (int) mac_address)
						{
						// Write a log stating that source node can not be a destination. 
						printf ("\n\nInvalid destination address specification. Changing\n");
						printf ("the specification from its own MAC address (%d) to \"Random\"\n\n", destination_address);
				
						// The destination address is set same as the lower layer MAC	
						// address of this node. Ignore the original specification and 
						// and set it to random.										
						destination_address = OMSC_AA_AUTO_ASSIGN;
						}
					else
						{
						// Checks if this is a valid address from the pool of addresses	
						// available.													
				
						dest_addr_okay = oms_aa_dest_addr_check (oms_aa_handle, destination_address);
						if (dest_addr_okay != OPC_TRUE)
							{
				
						// Write a log stating that source node can not be a destination. 
							printf ("\n\nInvalid destination address specification. Changing\n");
							printf ("the specification from %d, to \"Random\"\n\n", destination_address);
				
							// The specified destination address is invalid. Set it to	
							// random.													
							destination_address = OMSC_AA_AUTO_ASSIGN;
							}
						}
					}
				*/
				}


			/** state (wait) transition processing **/
			FSM_TRANSIT_FORCE (1, state1_enter_exec, ;, "default", "", "wait", "idle")
				/*---------------------------------------------------------*/



			/** state (init2) enter executives **/
			FSM_STATE_ENTER_UNFORCED (5, state5_enter_exec, "init2", "process_wlan_mac_interface () [init2 enter execs]")
				{
				}


			/** blocking after enter executives of unforced state. **/
			FSM_EXIT (11,process_wlan_mac_interface)


			/** state (init2) exit executives **/
			FSM_STATE_EXIT_UNFORCED (5, "init2", "process_wlan_mac_interface () [init2 exit execs]")
				{
				/* Schedule a self interrupt to wait for lower layer	*/
				/* Wlan MAC process to finalize the MAC address			*/
				/* registration and resolution.							*/
				op_intrpt_schedule_self (op_sim_time (), 0);
				}


			/** state (init2) transition processing **/
			FSM_TRANSIT_FORCE (4, state4_enter_exec, ;, "default", "", "init2", "wait")
				/*---------------------------------------------------------*/



			}


		FSM_EXIT (0,process_wlan_mac_interface)
		}
	}

#if defined (__cplusplus)
	extern "C" { 
#endif
	extern VosT_Fun_Status Vos_Catmem_Register (const char * , int , VosT_Void_Null_Proc, VosT_Address *);
	extern VosT_Address Vos_Catmem_Alloc (VosT_Address, size_t);
	extern VosT_Fun_Status Vos_Catmem_Dealloc (VosT_Address);
#if defined (__cplusplus)
	}
#endif


Compcode
process_wlan_mac_interface_init (void ** gen_state_pptr)
	{
	int _block_origin = 0;
	static VosT_Address	obtype = OPC_NIL;

	FIN (process_wlan_mac_interface_init (gen_state_pptr))

	if (obtype == OPC_NIL)
		{
		/* Initialize memory management */
		if (Vos_Catmem_Register ("proc state vars (process_wlan_mac_interface)",
			sizeof (process_wlan_mac_interface_state), Vos_Vnop, &obtype) == VOSC_FAILURE)
			{
			FRET (OPC_COMPCODE_FAILURE)
			}
		}

	*gen_state_pptr = Vos_Catmem_Alloc (obtype, 1);
	if (*gen_state_pptr == OPC_NIL)
		{
		FRET (OPC_COMPCODE_FAILURE)
		}
	else
		{
		/* Initialize FSM handling */
		((process_wlan_mac_interface_state *)(*gen_state_pptr))->current_block = 0;

		FRET (OPC_COMPCODE_SUCCESS)
		}
	}



void
process_wlan_mac_interface_diag (void)
	{
	/* No Diagnostic Block */
	}




void
process_wlan_mac_interface_terminate (void)
	{
	int _block_origin = __LINE__;

	FIN (process_wlan_mac_interface_terminate (void))

	Vos_Catmem_Dealloc (pr_state_ptr);

	FOUT;
	}


/* Undefine shortcuts to state variables to avoid */
/* syntax error in direct access to fields of */
/* local variable prs_ptr in process_wlan_mac_interface_svar function. */
#undef my_objid
#undef my_node_objid
#undef instrm_from_mac
#undef outstrm_to_mac
#undef oms_aa_handle
#undef mac_address
#undef wlan_mac_req_iciptr



void
process_wlan_mac_interface_svar (void * gen_ptr, const char * var_name, char ** var_p_ptr)
	{
	process_wlan_mac_interface_state		*prs_ptr;

	FIN (process_wlan_mac_interface_svar (gen_ptr, var_name, var_p_ptr))

	if (var_name == OPC_NIL)
		{
		*var_p_ptr = (char *)OPC_NIL;
		FOUT;
		}
	prs_ptr = (process_wlan_mac_interface_state *)gen_ptr;

	if (strcmp ("my_objid" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->my_objid);
		FOUT;
		}
	if (strcmp ("my_node_objid" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->my_node_objid);
		FOUT;
		}
	if (strcmp ("instrm_from_mac" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->instrm_from_mac);
		FOUT;
		}
	if (strcmp ("outstrm_to_mac" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->outstrm_to_mac);
		FOUT;
		}
	if (strcmp ("oms_aa_handle" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->oms_aa_handle);
		FOUT;
		}
	if (strcmp ("mac_address" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->mac_address);
		FOUT;
		}
	if (strcmp ("wlan_mac_req_iciptr" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->wlan_mac_req_iciptr);
		FOUT;
		}
	*var_p_ptr = (char *)OPC_NIL;

	FOUT;
	}

